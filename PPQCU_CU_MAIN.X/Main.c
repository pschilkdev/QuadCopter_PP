/* 
 * File:   Main.c
 * Author: Philipp
 *
 * Created on December 28, 2015, 10:47 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p32xxxx.h>
#include <xc.h>
#include "config.h"
#include "NRF.h"


//Inital Configs:
void init_INT();
void init_IO();


//Handshakes:
void shake_BATSENSE();
void shake_INTERFACE();
void shake_LIGHTS();
void shake_NRF();

int main(int argc, char** argv) {

    
    for(int i = 0; i<10000000; i++){}
    init_IO();
    
    //TESTING SPI
    shake_NRF();
    
    
}

int tester;

void init_IO() {
    
    //Disable JTAG as it conflicts with some of the pins
    //DEVCFG0bits.JTAGEN = 0;
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
    TRISBbits.TRISB9 = 1; //MISO
    SDI3Rbits.SDI3R = 0b0101;
    TRISBbits.TRISB10 = 0; //MOSI
    RPB10Rbits.RPB10R = 0b1110;
    TRISBbits.TRISB13 = 0; //CE
    TRISBbits.TRISB14 = 0; //SCK
    TRISBbits.TRISB15 = 0; //CSN
    
    //BMI
    TRISGbits.TRISG7 = 1;//MISO
    SDI2Rbits.SDI2R = 0b0001;
    TRISGbits.TRISG8 = 0;//MOSI
    RPG8Rbits.RPG8R = 0b0110;
    TRISGbits.TRISG6 = 0;//SCK
    TRISBbits.TRISB5 = 0;//CSB
}


void shake_NRF() {
    NRF_init(SPI3);
}

