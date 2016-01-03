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
    for(int i = 0; i < 1000; i++){__asm__("nop");} 
    __asm__("nop");
    shake_NRF(); //SHOULD BE LAST -> TIMEOUT
    return (EXIT_SUCCESS);
}

void init_IO(){
    //NRF SPI:
    ANSELB = 0x0000;
    TRISBbits.TRISB9 = 1; //MISO
    SDI3Rbits.SDI3R = 0b0101;
    TRISBbits.TRISB10 = 0;//MOSI
    RPB10Rbits.RPB10R = 0b1110;
    TRISBbits.TRISB13 = 0;//CE
    TRISBbits.TRISB14 = 0;//SCK
    TRISBbits.TRISB15 = 0;//CSN
}

void shake_NRF(){
    NRF_init(100);
}

