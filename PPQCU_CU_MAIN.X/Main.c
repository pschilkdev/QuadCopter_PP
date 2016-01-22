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

    init_IO();
    
    //TESTING SPI
    SPI_init(SPI3,
            SPI_INITF_MASTER |
            SPI_INITF_MODE_8
            , 9600);
    
    int n = 0;
    while(1){
        SPI_trans(SPI3, n);
        n++;
        for(int i = 0; i < 100000; i++){__asm__("nop");}
    }
}

void init_IO() {
    
    //Disable JTAG as it conflicts with some of the pins
    //DEVCFG0bits.JTAGEN = 0;
    CFGCONbits.JTAGEN = 0;
    
    //NRF SPI:
    ANSELA = 0x0000;

    TRISBbits.TRISB9 = 1; //MISO
    SDI3Rbits.SDI3R = 0b0101;
    TRISBbits.TRISB10 = 0; //MOSI
    RPB10Rbits.RPB10R = 0b1110;    
    TRISBbits.TRISB13 = 0; //CE
    
    TRISBbits.TRISB14 = 0; //SCK
    
    TRISBbits.TRISB15 = 0; //CSN
}

void shake_NRF() {
    NRF_init(100);
}

