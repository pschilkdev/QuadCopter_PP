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
#include "NRF.h"
#include "IIC.h"
#include "IO.h"

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
    init_INT();
    init_IO();
    init_IIC();
    init_INTERFACE();
    init_LIGHTS();
    init_BATSENSE();
    init_NRF();
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
    IO_wMISO_TRI = 1; //MISO
    SDI3Rbits.SDI3R = IO_wMISO_REG;
    IO_wMOSI_TRI = 0; //MOSI
    IO_wMOSI_REG = 0b1110;
    IO_wCE_TRI = 0; //CE
    IO_wSCK_TRI = 0; //SCK
    IO_wCSN_TRI = 0; //CSN
    
    //Debug parallel Port
    IO_DEBUG_TRI = 0;
    
    //BMI
    IO_aMISO_TRI = 1;//MISO
    SDI2Rbits.SDI2R = IO_aMISO_REG;
    IO_aMOSI_TRI = 0;//MOSI
    IO_aMOSI_REG = 0b0110;
    IO_aSCK_TRI = 0;//SCK
    IO_aCSB_TRI = 0;//CSB
    
    //BattWarn
    IO_battWarn1_TRI = 1;
    IO_battWarn2_TRI = 1;
    
    //Battery Leds
    IO_battLed1_TRI = 0;
    IO_battLed2_TRI = 0; //NOTE: ERROR IN HEADER FILE SEE IO.h
    
    //SCLEAR
    IO_SCLEAR_TRI = 0;
    
    //BUTTON INPUT & CHANNEL SELECT BITS 
    IO_B1_TRI = 1;
    IO_B2_TRI = 1;
    IO_B3_TRI = 1;
    
    IO_C1_TRI = 1;
    IO_C2_TRI = 1;
    IO_C3_TRI = 1;
    IO_C4_TRI = 1;
}

void init_INT(){
     
}

void init_IIC(){
    
}

void init_INTERFACE(){
    
}

void init_LIGHTS(){
    
}

void init_BATSENSE(){
    
}

void init_NRF() {
    NRF_init(SPI3);
}

