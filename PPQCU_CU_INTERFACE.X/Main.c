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
void init_IO();

//OPERATION
void handshake();
void output(int value);
void reset_mux();
void timeout();

//Servo Values (0 - 2^12)
int Serv1;
int Serv2;
int Serv3;
int Serv4;
int Serv5;
int Serv6;

/*
 *  
 */
int i;

int main(int argc, char** argv) {
    
    Serv1 = 0;
    Serv2 = 0;
    Serv3 = 0;
    Serv4 = 0;
    Serv5 = 0;
    Serv6 = 0;
    
    
    init_IO();
    init_OSC();
    init_INT();
    init_I2C();

    handshake();
    while (1) {
        output(Serv1);
        output(Serv2);
        output(Serv3);
        output(Serv4);
        output(Serv5);
        output(Serv6); 
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

    //Timer0
    OPTION_REGbits.TMR0CS = 0b0;
    OPTION_REGbits.PSA = 0b0;
    OPTION_REGbits.PS = 0b101;
    
    //Timer1
    T1CONbits.TMR1CS = 0b00;
    T1CONbits.T1CKPS = 0b00;
    T1CONbits.T1OSCEN = 0b0;
    T1CONbits.TMR1ON = 0b0;
}

void init_I2C() {
    //TODO
}

void init_IO() {
    ANSELA = 0b0;
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
}

void handshake() {
    //TODO
}



int  currentVal;
char currentValH;
char currentValL;

void output(int value) {
    //turn into 13 bit value
    value = value << 1;
    
    //Config Timers
    //TM1: Val Timer
    PIR1bits.TMR1IF = 0;
    T1CONbits.TMR1ON = 0;
    currentVal = (((TM_VAL_PRELOAD_H << 8) | TM_VAL_PRELOAD_L) + (8185 - value));
    currentValH = (currentVal & 0xFF00) >> 8;
    currentValL = currentVal & 0x00FF;

    //Advance MUX
    LATAbits.LATA4 = 1;
    for (int i = 0; i < 10; i++) {
        asm("nop");
    }
    LATAbits.LATA4 = 0;

    //===Time Sensitive===
    //Start Equivelant wait (2.1 ms)
    INTCONbits.TMR0IF = 0;
    TMR0 = TM_EQV_PRELOAD;
    
   
    //1ms default wait
    INTCONbits.TMR0IF = 0;
    TMR1H = TM_VAL_PRELOAD_H;
    TMR1L = TM_VAL_PRELOAD_L;
    T1CONbits.TMR1ON = 0b1;
    
    //Open Gate
    LATAbits.LATA0 = 1;

    
    //wait for finish
    while (!PIR1bits.TMR1IF) {
    }
    T1CONbits.TMR1ON = 0;
    PIR1bits.TMR1IF = 0;
     

    //Start valued
    TMR1H = currentValH;
    TMR1L = currentValL;
    T1CONbits.TMR1ON = 1;

    //wait for finish
    while (!PIR1bits.TMR1IF) {asm("nop");}

    //Close Gate
    LATAbits.LATA0 = 0b0;

    //Reset T1

    T1CONbits.TMR1ON = 0;
    PIR1bits.TMR1IF = 0;

    //Wait till equivelant is over
    while (!INTCONbits.TMR0IF) {asm("nop");}
    INTCONbits.TMR0IF = 0;
    
}

void reset_mux() {
    LATAbits.LATA5 = 1;
    for (int i = 0; i < 10; i++) {
        asm("nop");
    }
    LATAbits.LATA5 = 0;
}

void timeout() {
    //Enable I2C com 
    
    //Advance mux to ready position
    LATAbits.LATA4 = 1;
    for (int i = 0; i < 10; i++) {
        asm("nop");
    }
    LATAbits.LATA4 = 0;
    
    //Wait till over
    
    //reset mux
    
    //disable I2C com
}
