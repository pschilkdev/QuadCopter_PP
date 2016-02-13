#include "IIC.h"

void IIC_init(IIC_CHANNEL channel, int flags, int baud) {
    //Calc Baud Rate Register
    int baudreg = (F_PER/(2*baud)) - 2;
    
    //CHECK FOR VALIDITY OF BAUD RATE VALUE
    if(baudreg < 2 || baudreg >  4095)
    {
        while(1){
            //Invalid Baud Reg Value
        }
    }
    if(channel == IIC2){
        //Turn IIC off
        I2C2CONbits.ON = 0;
        //Write flags with bitmask
        I2C2CONSET = (0b00000000000000000010111110100000) & flags;
        //Write Baud Rate
        I2C2BRG = baudreg;
        //nop just to be sure
        __asm__("nop");
        I2C2CONbits.ON = 1;
    } else {
        //default to channel 1
       //Turn IIC off
        I2C1CONbits.ON = 0;
        //Write flags with bitmask
        I2C1CONSET = (0b00000000000000000010111110100000) & flags;
        //Write Baud Rate
        I2C1BRG = baudreg;
        //nop just to be sure
        __asm__("nop");
        I2C1CONbits.ON = 1;
    }
}

void IIC_clkstretch(IIC_CHANNEL channel) {
    if (channel == IIC2) {
        I2C2CONbits.STREN = 1;
    } else {
        //Default to channel 1  
        I2C1CONbits.STREN = 1;
    }
}
void IIC_receive(IIC_CHANNEL channel) {
    if (channel == IIC2) {
        I2C2CONbits.RCEN = 1;
    } else {
        //Default to Channel 1
        I2C1CONbits.RCEN = 1;
    }
}
void IIC_stop(IIC_CHANNEL channel) {
    if (channel == IIC2) {
       I2C2CONbits.PEN = 1;
    } else {
        //Default to Channel 1
        I2C1CONbits.PEN = 1;   
    }
}
void IIC_start(IIC_CHANNEL channel) {
    if (channel == IIC2) {
        I2C2CONbits.SEN = 1;
    } else {
        //Default to Channel 1
        I2C1CONbits.SEN = 1;
    }
}
void IIC_restart(IIC_CHANNEL channel) {
    if (channel == IIC2) {
        I2C2CONbits.RSEN = 1;
    } else {
        //Default to Channel 1
        I2C1CONbits.RSEN = 1;
    }
}
void IIC_ack(IIC_CHANNEL channel){
    if(channel == IIC2){
        I2C2CONbits.ACKEN = 1;
    } else {
        I2C1CONbits.ACKEN = 1;
    }
}
BOOL IIC_status(IIC_CHANNEL channel, IIC_STATUS stat){
   if(channel == IIC2){
       if((stat & 0x80000000)){
           return ((I2C2CON) & (0x7FFFFFFF & stat));
       } else {
           return ((I2C2STAT) & (0x7FFFFFFF & stat));
       }
   } else{
       if((stat & 0x80000000)){
           return ((I2C1CON) & (0x7FFFFFFF & stat));
       } else {
           return ((I2C1STAT) & (0x7FFFFFFF & stat));
       }
   }
}
void IIC_address(IIC_CHANNEL channel, char address, IIC_OPERATION op){
    char value = ((address & 0b1111111) << 1) | op;
    IIC_put(channel, value);
}
void IIC_put(IIC_CHANNEL channel,char data) {
    if(channel == IIC2){
        I2C2TRN = data;
    } else {
        //default to channel 1
        I2C1TRN = data;                                     
    }
}
char IIC_get(IIC_CHANNEL channel){
    if(channel == IIC2){
        return I2C2RCV;
    } else {
        return I2C1RCV;
    }
}



