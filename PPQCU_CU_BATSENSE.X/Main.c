/* 
 * File:   Main.c
 * Author: Philipp
 *
 * Created on December 29, 2015, 11:35 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

void init_OSC();
void init_ADC();
void init_I2C();
void init_INT();
void init_IO();

void handshake();
int checkBattery();
int readADC();

/*
 * 
 */

int status;
int thresh1;
int thresh2;

int main(int argc, char** argv) {

    init_OSC();
    init_ADC();
    init_I2C();
    init_INT();

    handshake();

    while (1) {
        status = checkBattery();

        if (status == 0) {
            //Battery Ok
        }
        if (status == 1) {
            //Warn Stage 1
        }
        if (status == 2) {
            //Warn Stage 2
        }

    }

    return (EXIT_SUCCESS);
}

void init_OSC() {

    //Clock Frequency 8mhz
    OSCCONbits.IRCF = 0b1110;
    //Multiply clock by 4 to yield 32
    OSCCONbits.SPLLEN = 0b1;
    //Clock determined by oscillator config fuses
    OSCCONbits.SCS = 0b00;

}

void init_ADC() {
    ADCON0bits.CHS = 0b00011;
    ADCON0bits.ADON = 0b1;
    ADCON1bits.ADFM = 0b1;
    ADCON1bits.ADCS = 0b110;
    ADCON1bits.ADPREF = 0b00;
}

void init_I2C() {

}

void init_INT() {

}

void handshake() {
    thresh1 = 500;
    thresh2 = 400;
}

int checkBattery() {
    int v1 = readADC();
    for (int i = 0; i < 15; i++) {
        asm("nop");
    }
    int v2 = readADC();
    for (int i = 0; i < 15; i++) {
        asm("nop");
    }
    int v3 = readADC();
    for (int i = 0; i < 15; i++) {
        asm("nop");
    }
    int val = (v1+v2+v3)/4;

    if (val <= thresh1) {
        return 1;
    } else if (val <= thresh2){
        return 2;
    } else {
        return 0;
    }
}

int readADC() {
    for (int i = 0; i < 15; i++) {
        asm("nop");
    }
    ADCON0bits.ADGO = 0b1;
    while (ADCON0bits.ADGO) {
        asm("nop");
    }
    return ((ADRESH << 8) | ADRESL);
}