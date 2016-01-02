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
void handshake();
int checkBattery();

/*
 * 
 */

int status;

int main(int argc, char** argv) {
    
    init_OSC();
    init_ADC();
    init_I2C();
    init_INT();
    
    handshake();
    
    while(1){
        status = checkBattery();
        
        if(status == 0){
            //Batter Ok
        } if (status == 1){
            //Warn Stage 1
        } if (status == 2){
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

void init_ADC(){
    
}

void init_I2C(){
    
}

void init_INT(){
    
}

void handshake(){
    
}

int checkBattery(){
    
}