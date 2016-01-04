/* 
 * File:   Main.c
 * Author: Philipp
 *
 * Created on December 29, 2015, 11:35 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <xc.h>

void init_OSC();
void init_I2C();
void init_INT();
void init_IO();
void write();
void shiftout(int);
void bitout(char);
void end();

int led0 = 0;
int led1 = 0;
int led2 = 0;
int led3 = 0;
int led4 = 0;
int led5 = 0;

/*
 * 
 */
int main(int argc, char** argv) {

    init_OSC();
    init_I2C();
    init_INT();

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

void init_I2C() {

}

void init_INT(){
    
}

void init_IO() {

}



/*
 * X = Don't Care
 * 1 = Set
 * 2 = Cleared
 * V = VALUE
 * 
 * Message Format Select LED:
 * VVVXXXX0
 * 
 * Message Format Push:
 * XXXXXXX1
 * 
 * Message Value:
 * VVVVVVV0
 * 
 * 
 * 
 * First Message sent has to be Select LED 
 * Followed by 3 Values
 * 
 * Followed by either a new LED or A Push
 * 
 * Push is followed by new LED
 * 
 */
int message_num = 0;
int editing_led = 0;

void interrupt inter() {
    if (/*I2C*/0) {
        //Clear I2C Flag
        char message = /*I2C Value*/0;
        if ((message & 0b01) == 1) {
            write();
        }
        if (message_num == 0) {
            editing_led = ((0/*I2C Values*/ & 0xE0) >> 5);
            message_num = 1;
        } else {
            //Add Data to values
            if (editing_led == 0) {
                led0 = ((led0 << 8 ) | (message & 0xFE));
            } else if (editing_led == 1) {
                led1 = ((led1 << 8) | (message & 0xFE));
            } else if (editing_led == 2) {
                led2 = ((led2 << 8) | (message & 0xFE));
            } else if (editing_led == 3) {
                led3 = ((led3 << 8) | (message & 0xFE));
            } else if (editing_led == 4) {
                led4 = ((led4 << 8) | (message & 0xFE));
            } else if (editing_led == 5) {
                led5 = ((led5 << 8) | (message & 0xFE));
            }
            if (message_num == 3) {
                message_num = 0;
            } else {
                message_num++;
            }
        }
    }
}

void write(){
    shiftout(led0);
    shiftout(led1);
    shiftout(led2);
    shiftout(led3);
    shiftout(led4);
    shiftout(led5); 
    end();
}

void shiftout(int val){
    for(int i = 0; i <32; i++){
        bitout(((val & 0x0000001) >> i));
    }
}

void bitout(char b){
    if(b){
        
    } else {
        
    }
}

void end(){
    
}
