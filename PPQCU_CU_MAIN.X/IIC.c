#include <proc/p32mx120f064h.h>

#include "IIC.h"

void IIC_init(IIC_CHANNEL channel, int flags, int baud) {

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
BOOL IIC_STATUS(IIC_CHANNEL channel, IIC_STATUS stat){
   if(channel = IIC2){
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



