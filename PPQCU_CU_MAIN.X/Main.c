/* 
 * File:   Main.c
 * Author: Philipp
 *
 * Created on December 28, 2015, 10:47 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p32xxxx.h>
#include "config.h"
#include "Quadcopter.h"
#include "NRF.h"
#include <Math.h>
#include "BMI.h"

//Inital Configs:
void init_INT();
void init_IO();
void init_IIC();
void init_BATSENSE();
void init_INTERFACE();
void init_LIGHTS();
void init_NRF();
int map(unsigned char in);

int tilt_target_X;
int tilt_target_Y;

unsigned char vs1;
unsigned char vs2;
unsigned char vs3;
unsigned char vs4;

char key = 0b11011010;

int main(int argc, char** argv) {

    init_IO();


    chips_reset();
    for (int xz = 0; xz < 10000; xz++) {
        __asm__("NOP");
    }
    chips_run();

    SPI_init(SPI3,
            SPI_INITF_SLAVE |
            SPI_INITF_MODE_8 |
            SPI_INITF_CKE_ACTIVE_TO_IDLE
            , 100000);

    char msg;
    //Run Loop:
    while (1) {
        //Receive
        //Wait in case there is a transmittion atm
        while (SPI3STATbits.SPIBUSY) {
        }

        vs1 = 0;
        vs2 = 0;
        vs3 = 0;
        vs4 = 0;
        //get module ready
        int temp = SPI3BUF;

        SPI3STATbits.SPIROV = 0;
        while (1) {
            //receive messages until the beginning bit is received, then receive 4 more
            if (SPI3STATbits.SPIRBF) {
                __asm__("NOP");
                __asm__("NOP");
                __asm__("NOP");
                msg = SPI3BUF;
                __asm__("NOP");
                __asm__("NOP");
                __asm__("NOP");
                if (msg == key) {
                    //process next 4
                    while (!SPI3STATbits.SPIRBF) {
                    }
                    vs1 = SPI3BUF & 0b11111111;
                    if (vs1 == key)
                        break;
                    while (!SPI3STATbits.SPIRBF) {
                    }
                    vs2 = SPI3BUF & 0b11111111;
                    while (!SPI3STATbits.SPIRBF) {
                    }
                    vs3 = SPI3BUF & 0b11111111;
                    while (!SPI3STATbits.SPIRBF) {
                    }
                    vs4 = SPI3BUF & 0b11111111;

                    break;
                }
            }

        }
        //Update
        motor_update(map(vs1), map(vs1), map(vs1), map(vs1));

    }

}

int tester;

void init_IO() {

    //Disable JTAG as it conflicts with some of the pins
    CFGCONbits.JTAGEN = 0;

    //Get Rid of Analog
    ANSELA = 0x0000;
    ANSELB = 0x0000;
    ANSELC = 0x0000;
    ANSELD = 0x0000;
    ANSELE = 0x0000;
    ANSELF = 0x0000;
    ANSELG = 0x0000;

    //NRF

    TRISBbits.TRISB10 = 1; //MOSI
    SDI3Rbits.SDI3R = 0b0110;
    TRISBbits.TRISB13 = 0; //CE
    TRISBbits.TRISB14 = 0; //SCK
    TRISBbits.TRISB15 = 0; //CSN
    TRISBbits.TRISB12 = 1; //IRQ

    //Debug parallel Port
    TRISE = 0;

    //BMI
    TRISGbits.TRISG7 = 1; //MISO
    SDI2Rbits.SDI2R = 0b0001;
    TRISGbits.TRISG8 = 0; //MOSI
    RPG8Rbits.RPG8R = 0b0110;
    TRISGbits.TRISG6 = 0; //SCK
    TRISBbits.TRISB5 = 0; //CSB

    //BatWarn
    TRISBbits.TRISB11 = 1;

    //ServIntRd
    TRISBbits.TRISB8 = 1;

    //battled
    //TRISF2 = 0 battled out1
    //TRISF3 = 1 battled in
    //TRISF6 = 0 battled out2
    TRISFSET = 0b0001000;

    //SCLEAR
    TRISFbits.TRISF0 = 0;

    //BUTTON INPUT & CHANNEL SELECT BITS 
    TRISD = 0b11111110;

    //Servos:
    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    TRISGbits.TRISG2 = 0;
    TRISGbits.TRISG3 = 0;

}

void init_NRF() {
    NRF_init(SPI3);
}

void init_INT() {
    T1CONbits.ON = 0;
    __asm__("NOP");
    T1CONbits.SIDL = 0;
    T1CONbits.TWDIS = 1;
    T1CONbits.TCKPS = 0b00;
}

int map(unsigned char in) {
    return in * 94;
}
//void init_BMI(){
//    BMI_init(SPI2);
//}
