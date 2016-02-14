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
void receive();


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

    for(int xz = 0; xz < 10000; xz++){
        asm("NOP");
    }
    
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

    //Timer0(Equivelant)
    OPTION_REGbits.TMR0CS = 0b0;
    OPTION_REGbits.PSA = 0b0;
    OPTION_REGbits.PS = 0b101;

    //Timer1(value)
    T1CONbits.TMR1CS = 0b00;
    T1CONbits.T1CKPS = 0b00;
    T1CONbits.T1OSCEN = 0b0;
    T1CONbits.TMR1ON = 0b0;

    //Timer2(timeout)
    T2CONbits.T2OUTPS = 0b0110;
    T2CONbits.T2CKPS = 0b11;
    T2CONbits.TMR2ON = 1;
}

void init_I2C() {
    SSP1CON1bits.SSPEN = 0;
    SSP1CON1bits.SSPM = 0b0110;
    SSP1STATbits.SMP = 0;
    SSP1ADD = 0x30;
    SSP1CON2bits.SEN = 0;
    PIR1bits.SSP1IF = 0;
    SSP1CON1bits.SSPEN = 1;
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

int currentVal;
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
    while (!PIR1bits.TMR1IF) {
        asm("nop");
    }

    //Close Gate
    LATAbits.LATA0 = 0b0;

    //Reset T1

    T1CONbits.TMR1ON = 0;
    PIR1bits.TMR1IF = 0;

    //Wait till equivelant is over
    while (!INTCONbits.TMR0IF) {
        asm("nop");
    }
    INTCONbits.TMR0IF = 0;

}

void reset_mux() {
    LATAbits.LATA5 = 1;
    for (int i = 0; i < 10; i++) {
        asm("nop");
    }
    LATAbits.LATA5 = 0;
}

int rc1, rc2, rc3, rc4, rc5, rc6;
int error;
int count;
void timeout() {
    //Advance mux to ready position
    LATAbits.LATA4 = 1;
    for (int i = 0; i < 10; i++) {
        asm("nop");
    }
    LATAbits.LATA4 = 0;

    //Start timer
    PIR1bits.TMR2IF = 0;
    TMR2 = TM_OUT_PRELOAD;
    
    int running = 1;
    count = 0;
    //Wait till over
    
    while (running) {
        if(PIR1bits.TMR2IF){
            count++;
            if(count == 10){
                running = 0;
            }
        } 
        if (PIR1bits.SSP1IF) {
            error = 0;
            //RECEIVE
            PIR1bits.SSP1IF = 0;
            //clear Buffer Full Flag
            int temp = SSP1BUF;
            receive();     
            //Reconstruct Data
            if (!error) {
                Serv1 = (0b111111111111) & ((rc1 << 4) | ((rc2 & 0b11110000) >> 4));
                Serv2 = (0b111111111111) & (((rc2 & 0b1111) << 8) | rc3);
                Serv3 = (0b111111111111) & ((rc4 << 4) | ((rc5 & 0b11110000) >> 4));
                Serv2 = (0b111111111111) & (((rc5 & 0b1111) << 8) | rc6);
            }
            PIR1bits.SSP1IF = 0;
        } 
    }
    
    //reset mux
    reset_mux();
    
    //Reset Timeout Timer
    PIR1bits.TMR2IF = 0;
}

void wait(int time){
    int n = 0;
    while(!PIR1bits.SSP1IF){
        n++;
        if(n > time){
            error = 1;
            return;
        }
    }
}

void receive(){
    wait(1000);
    if(error)
        return;
    rc1 = SSP1BUF;
    
    wait(1000);
    if(error)
        return;
    rc2 = SSP1BUF;
    
    wait(1000);
    if(error)
        return;
    rc3 = SSP1BUF;
    
    wait(1000);
    if(error)
        return;
    rc4 = SSP1BUF;
    
    wait(1000);
    if(error)
        return;
    rc5 = SSP1BUF;
    
    wait(1000);
    if(error)
        return;
    rc6 = SSP1BUF;
}

