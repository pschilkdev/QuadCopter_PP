/* 
 * File:   Main.c
 * Author: Philipp
 *
 * Created on December 29, 2015, 11:35 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

//INIT
void init_OSC();
void init_INT();
void init_I2C();

//OPERATION
void handshake();
void read_data();
void output(int value);
void reset_mux();
void timeout();

//Servo Values
int Serv1 = 0;
int Serv2 = 0;
int Serv3 = 0;
int Serv4 = 0;
int Serv5 = 0;
int Serv6 = 0;


/*
 *  
 */
int main(int argc, char** argv) {

    init_OSC();
    init_INT();
    init_I2C();
    
    handshake();
    
    while(1){
        read_data();
        output(Serv1);
        output(Serv2);
        output(Serv3);
        output(Serv4);
        output(Serv5);
        output(Serv6);
        reset_mux();
        timeout();
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

void init_INT() {
    //Reset all Flags and disable all interrupts
    INTCONbits.TMR0IF = 0b0;
    INTCONbits.INTF = 0b0;
    INTCONbits.IOCIF = 0b0;
    PIE1 = 0b0;
    PIE2 = 0b0;
    PIR1 = 0b0;
    PIR1 = 0b0;
    
    //General Initialization
    INTCONbits.GIE = 0b1;
    INTCONbits.PEIE = 0b1;
    
    //Timer0
    
    //Timer1
    
}

void init_I2C(){
    //TODO
}

void output(int value){
    //TODO
}

void reset_mux(){
    //TODO
}

void timeout(){
    //TODO
}