/* 
 * File:   Main.c
 * Author: Philipp
 *
 * Created on December 29, 2015, 11:35 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

#define IIC_CLK_DRIVE_LOW() (TRISAbits.TRISA4 = 0)
#define IIC_CLK_DRIVE_HIGH() (TRISAbits.TRISA4 = 1)
#define IIC_CLK_TRISTATE() (TRISAbits.TRISA4 = 1)
#define IIC_CLK_READ (PORTAbits.RA4)
#define IIC_CLK_INIT (LATAbits.LATA4)

#define IIC_DAT_DRIVE_LOW() (TRISAbits.TRISA5 = 0)
#define IIC_DAT_DRIVE_HIGH() (TRISAbits.TRISA5 = 1)
#define IIC_DAT_TRISTATE() (TRISAbits.TRISA5 = 1)
#define IIC_DAT_READ (PORTAbits.RA5)
#define IIC_DAT_INIT (LATAbits.LATA5)

#define MUX_RESET (catcher)
#define MUX_ADVANCE (catcher)
#define GATE (catcher)

#define IIC_ADR_INT 0x30

/*
// NORMAL
#define IIC_CLK_DRIVE_LOW() (TRISAbits.TRISA1 = 0)
#define IIC_CLK_DRIVE_HIGH() (TRISAbits.TRISA1 = 1)
#define IIC_CLK_TRISTATE() (TRISAbits.TRISA1 = 1)
#define IIC_CLK_READ (PORTAbits.RA1)
#define IIC_CLK_INIT (LATAbits.LATA1)

#define IIC_DAT_DRIVE_LOW() (TRISAbits.TRISA2 = 0)
#define IIC_DAT_DRIVE_HIGH() (TRISAbits.TRISA2 = 1)
#define IIC_DAT_TRISTATE() (TRISAbits.TRISA2 = 1)
#define IIC_DAT_READ (PORTAbits.RA2)
#define IIC_DAT_INIT (LATAbits.LATA2)

#define MUX_RESET (LATAbits.LATA5)
#define MUX_ADVANCE (LATAbits.LATA4)
#define GATE (LATAbits.LATA0)

#define IIC_ADR_INT 0x30

 * */

typedef enum {
    IIC_READ = 1,
    IIC_WRITE = 0
} IIC_OPERATION;

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
void IIC();


//Servo Values (0 - 2^12)
int Serv1;
int Serv2;
int Serv3;
int Serv4;
int Serv5;
int Serv6;

int catcher;

#define timeoutmax 5000

/*
 *  
 */
int i;

int main(int argc, char** argv) {

    for (int xz = 0; xz < 10000; xz++) {
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

    IIC_CLK_TRISTATE();
    IIC_CLK_INIT = 0;
    IIC_DAT_TRISTATE();
    IIC_DAT_INIT = 0;

}

void init_IO() {
    ANSELA = 0b0;
    TRISA = 0;
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
    MUX_ADVANCE = 1;
    for (int i = 0; i < 50; i++) {
        asm("nop");
    }
    MUX_ADVANCE = 0;

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
    GATE = 1;


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
    GATE = 0;

    
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
    MUX_RESET = 1;
    for (int i = 0; i < 50; i++) {
        asm("nop");
    }
    MUX_RESET = 0;
}

int rc[6];
int error;
int count;
char deadcycle;

void timeout() {
    //check if the bus is low, if so, deadcycle
    if (IIC_DAT_READ == 0 || IIC_CLK_READ == 0) {
        deadcycle = 1;
    } else {
        deadcycle = 0;
    }

    //Advance mux to ready position
    MUX_ADVANCE = 1;
    for (int i = 0; i < 50; i++) {
        asm("nop");
     }
    MUX_ADVANCE = 0;

    //Start timer
    PIR1bits.TMR2IF = 0;
    TMR2 = TM_OUT_PRELOAD;

    int running = 1;
    count = 0;
    error = 0;


    while (running) {
        if (PIR1bits.TMR2IF) {
            count++;
            if (count == 10) {
                running = 0;
            }
        }

        if (!deadcycle) {
            //Check for START
            if (IIC_DAT_READ == 0 || IIC_CLK_READ == 1) {
                //This might be a start... start checking for clock low.
                IIC();
            }
        }

    }

    //reset mux
    reset_mux();

    //Reset Timeout Timer
    PIR1bits.TMR2IF = 0;
}

#define timeout 100
char address_shiftin;
int timer;
char data;

void IIC() {
    

    //Check for Clock Low to complete start
    timer = 0;
    while (1) {
        timer++;
        if (IIC_CLK_READ == 0)
            break;
        if (timer > timeout) {
            error = 1;
            return;
        }
    }

    //We are in the Address byte
    //Clock in 8 bytes
    address_shiftin = 0;
           
       
    //LATAbits.LATA2 = 1;
    for (int ad_bit_num = 0; ad_bit_num < 8; ad_bit_num++) {

        timer = 0;
        while (1) {
            timer++;
            if (IIC_CLK_READ == 1) {
                break;
            }
            if (timer > timeout) {
                error = 1;
                return;
            }
        }
        //LATAbits.LATA2 = 0;
        //Received High
        //Shift in bit:
        address_shiftin = (address_shiftin<<1)| IIC_DAT_READ;
        //Wait for LOW 
        timer = 0;
        while (1) {
            timer++;
            if (IIC_CLK_READ == 0)
                break;
            if (timer > timeout) {
                error = 1;
                return;
            }
        }
    }
    //Check if address is valid and is write (Interface is write only)
    
    if ( address_shiftin == ((IIC_ADR_INT & 0b11111110) | IIC_WRITE)) {
       
        //Acknowledge
        IIC_DAT_DRIVE_LOW();
        //wait for high edge
        timer = 0;
        while (1) {
            timer++;
            if (IIC_CLK_READ == 1)
                break;
            if (timer > timeout) {
                error = 1;
                return;
            }
        }
        int sum = timer;

        //wait for low edge
        timer = 0;
        while (1) {
            //START HERE
            timer++;
            if (IIC_CLK_READ == 0)
                break;
            if (timer > timeout) {
                error = 1;
                return;
            }
            //STOP HERE
        }
        sum = sum + timer;
        //return to tristate
        for(int finish_ack = 0; finish_ack < sum; finish_ack = finish_ack + 3){
            asm("NOP");
        }
        IIC_DAT_TRISTATE();

        //Clock in 6 bytes of data
        for (int bitnum = 0; bitnum < 6; bitnum++) {
            data = 0;
            for (int i = 0; i < 8; i++) {
                timer = 0;
                while (1) {
                    timer++;
                    if (IIC_CLK_READ == 1) {
                        break;
                    }
                    if (timer > timeout) {
                        error = 1;
                        return;
                    }
                }
                //Received High
                //Shift in bit:
                data = (data < 1) | IIC_DAT_READ;
                //Wait for LOW 
                timer = 0;
                while (1) {
                    timer++;
                    if (IIC_CLK_READ == 0)
                        break;
                    if (timer > timeout) {
                        error = 1;
                        return;
                    }
                }
            }

            //Acknowledge
            IIC_DAT_DRIVE_LOW();
            //wait for high edge
            timer = 0;
            while (1) {
                timer++;
                if (IIC_CLK_READ == 1)
                    break;
                if (timer > timeout) {
                    error = 1;
                    return;
                }
            }

            //wait for low edge
            timer = 0;
            while (1) {
                timer++;
                if (IIC_CLK_READ == 0)
                    break;
                if (timer > timeout) {
                    error = 1;
                    return;
                }
            }
            IIC_DAT_TRISTATE();
            rc[bitnum] = data;
            
        }

        //Wait for stop
        //Wait for high edge on clock
        timer = 0;
        while (1) {
            timer++;
            if (IIC_CLK_READ == 1)
                break;
            if (timer > timeout) {
                error = 1;
                return;
            }
        }

        //wait for high edge on data
        timer = 0;
        while (1) {
            timer++;
            if (IIC_DAT_READ == 1)
                break;
            if (timer > timeout) {
                error = 1;
                return;
            }
            
        }
    } else {
        //Not ours... exit I2C sequences
        error = 1;
        return;
    }
}