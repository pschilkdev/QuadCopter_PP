s/* 
 * File:   Main.c
 * Author: Philipp
 *
 * Created on December 28, 2015, 10:47 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p32xxxx.h>
#include "config.h"
#include "NRF.h"
#include <Math.h>

//Inital Configs:
void init_INT();
void init_IO();
void init_IIC();
void init_BATSENSE();
void init_INTERFACE();
void init_LIGHTS();
void init_NRF();

int main(int argc, char** argv) {

    
    for(int i = 0; i<10000000; i++){}
    //INIT
    init_IO();
    init_INT();
    
   
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
    
    //Debug parallel Port
    TRISE = 0;
    
    //BMI
    TRISGbits.TRISG7 = 1;//MISO
    SDI2Rbits.SDI2R = 0b0001;
    TRISGbits.TRISG8 = 0;//MOSI
    RPG8Rbits.RPG8R = 0b0110;
    TRISGbits.TRISG6 = 0;//SCK
    TRISBbits.TRISB5 = 0;//CSB
    
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
}

void init_INT(){
    
    //IoC for BattWarn
    
    
    //IoC for ServIntRD
    
    
}

void init_NRF() {
    NRF_init(SPI3);
}

