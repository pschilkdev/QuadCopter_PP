/* 
 * File:   Main.c
 * Author: Philipp
 *
 * Created on January 2, 2016, 3:40 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

void init_ADC();
void init_OSC();
void init_IO();
double map(double value, float x_min, float x_max, float y_min, float y_max);
void calibrate_joystick();
int sample(char);
int read_ADC(char channel);

#define button PORTCbits.RC1
#define led LATAbits.LA5
#define deadzone 15
#define timeout 5000

#define ac_j1 0b00000
#define ac_j2 0b00001
#define ac_j3 0b00010
#define ac_j4 0b00011

int sample1;
int sample2;
int sample3;
int sample4;

char v1;
char v2;
char v3;
char v4;
int j1_min;
int j1_max;

int j2_min;
int j2_max;
int j2_center;

int j3_min;
int j3_max;
int j3_center;

int j4_min;
int j4_max;
int j4_center;

int main(int argc, char** argv) {
    init_IO();
    init_OSC();
    init_ADC();

    calibrate_joystick();

    while (1) {
        //Read ADC
        //lx
        sample1 = read_ADC(ac_j1);

        //ly
        sample2 = read_ADC(ac_j2);

        //rx
        sample3 = read_ADC(ac_j3);

        //ry 
        sample4 = read_ADC(ac_j4);

        //add center deadzone to 2 3 and 4, map to 8 bit
        if (sample2 <= (j2_center + deadzone) && sample2 >= (j2_center - deadzone)) {
            v2 = 127;
        } else {
            if (sample2 > (j2_max - 10))
                sample2 = (j2_max - 10);
            if (sample2 < j2_min)
                sample2 = j2_min;

            if (sample2 > j2_center) {
                v2 = (char) map(sample2, j2_center, j2_max - 10, 128, 255);
            } else {
                v2 = (char) map(sample2, j2_min, j2_center, 0, 128);
            }
        }

        if (sample3 <= (j3_center + deadzone) && sample3 >= (j3_center - deadzone)) {
            v3 = 128;
        } else {
            if (sample3 > (j3_max - 10))
                sample3 = (j3_max - 10);
            if (sample3 < j3_min)
                sample3 = j3_min;
            if (sample3 > j3_center) {
                v3 = (char) map(sample3, j3_center, j3_max - 10, 128, 255);
            } else {
                v3 = (char) map(sample3, j3_min, j3_center, 0, 128);
            }
        }

        if (sample4 <= (j4_center + deadzone) && sample4 >= (j4_center - deadzone)) {
            v4 = 128;
        } else {
            if (sample4 > (j4_max - 10))
                sample4 = (j4_max - 10);
            if (sample4 < j4_min)
                sample4 = j4_min;
            if (sample4 > j4_center) {
                v4 = (char) map(sample4, j4_center, j4_max - 10, 128, 255);
            } else {
                v4 = (char) map(sample4, j4_min, j4_center, 0, 128);
            }
        }

        //add bottom deadzone to 1, map to 8 bit
        if (sample1 >= (j1_max - deadzone))
            v1 = 255;
        else
            v1 = (char) map(sample1, j1_min, j1_max - deadzone, 0, 255);
        asm("NOP");

        //invert left joystick:
        v1 = 255 - v1;
        v2 = 255 - v2;

        //Send
        char out[5];
        out[0] = 0;
        out[1] = v1;
        out[2] = v2;
        out[3] = v3;
        out[4] = v4;
    }
}

void init_ADC() {
    ADCON1bits.PVCFG = 0b00;
    ADCON1bits.NVCFG = 0b00;
    ADCON2bits.ADFM = 0b1;
    ADCON2bits.ACQT = 0b100;
    ADCON2bits.ADCS = 0b101;
    ADCON0bits.ADON = 1;
}

void init_OSC() {
    OSCCONbits.IRCF = 0b111;
    OSCTUNEbits.PLLEN = 0;
}

void init_IO() {
    //Joystick In:
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELAbits.ANSA0 = 1;
    TRISAbits.TRISA0 = 1;
    ANSELAbits.ANSA1 = 1;
    TRISAbits.TRISA1 = 1;
    ANSELAbits.ANSA2 = 1;
    TRISAbits.TRISA2 = 1;
    ANSELAbits.ANSA3 = 1;
    TRISAbits.TRISA3 = 1;

    //Button in:
    TRISCbits.RC1 = 1;

    //LED Out
    TRISAbits.RA5 = 0;

    //NRF:
    //SCK
    TRISCbits.RC3 = 0;
    //MISO
    TRISCbits.RC4 = 1;
    //MOSI
    TRISCbits.RC5 = 0;
    //CE
    TRISCbits.RC0 = 0;
    //CSN
    TRISCbits.RC7 = 0;
    //IRQ
    TRISCbits.RC6 = 1;
}

void calibrate_joystick() {
    asm("nop");
    led = 1;
    for (int a = 0; a < 10; a++)
        for (int b = 0; b < 20000; b++) {
        }
    led = 0;
    j2_center = read_ADC(ac_j2);
    j3_center = read_ADC(ac_j3);
    j4_center = read_ADC(ac_j4);

    //samples
    j1_min = sample(ac_j1);
    j2_min = sample(ac_j2);
    j1_max = sample(ac_j1);
    j2_max = sample(ac_j2);

    j3_max = sample(ac_j3);
    j4_max = sample(ac_j4);
    j3_min = sample(ac_j3);
    j4_min = sample(ac_j4);

    led = 0;
    for (int a = 0; a < 10; a++)
        for (int b = 0; b < 20000; b++) {
        }
    led = 1;
    for (int a = 0; a < 10; a++)
        for (int b = 0; b < 20000; b++) {
        }
    led = 0;
    for (int a = 0; a < 10; a++)
        for (int b = 0; b < 20000; b++) {
        }
    led = 1;
    for (int a = 0; a < 10; a++)
        for (int b = 0; b < 20000; b++) {
        }
    led = 0;
}

double map(double value, float x_min, float x_max, float y_min, float y_max) {
    return (y_min + (((y_max - y_min) / (x_max - x_min)) * (value - x_min)));
}

int sample(char channel) {
    led = 0;
    //wait for press
    while (button) {
    }
    //wait for release
    while (!button) {
    }
    //read
    int result = read_ADC(channel);
    //timeout    
    led = 1;
    for (int a = 0; a < 20; a++)
        for (int b = 0; b < 20000; b++) {
        }
    led = 0;
    return result;
}

int read_ADC(char channel) {
    ADCON0bits.CHS = channel;
    ADCON0bits.GO_nDONE = 1;
    while (ADCON0bits.GO_nDONE) {
        ;
    }
    return ((ADRESH & 0b11) << 8) | ADRESL;
}
