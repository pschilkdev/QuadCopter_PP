#include "IIC.h"

void IIC_init(IIC_CHANNEL channel, int flags, int baud) {

}

void IIC_do_clkstretch(IIC_CHANNEL channel) {
    if (channel == IIC2) {
        I2C2CONbits.STREN = 1;
    } else {
        I2C1CONbits.STREN = 1;
    }
}
BOOL IIC_c_clkstretch(IIC_CHANNEL channel) {
    if (channel == IIC2) {
        return !I2C2CONbits.STREN;
    } else {
        //Default to Channel 1
        return !I2C1CONbits.STREN;
    }
}
void IIC_w_clkstretch(IIC_CHANNEL channel) {
        while(IIC_c_clkstretch(channel)){}
}
void IIC_dow_clkstretch(IIC_CHANNEL channel) {
    IIC_do_clkstretch(channel);
    IIC_w_clkstretch(channel);
}

void IIC_do_receive(IIC_CHANNEL channel) {
    if (channel == IIC2) {
        I2C2CONbits.RCEN = 1;
    } else {
        //Default to Channel 1
        I2C1CONbits.RCEN = 1;
    }
}
BOOL IIC_c_receive(IIC_CHANNEL channel) {
    if (channel == IIC2) {
        return !I2C2CONbits.RCEN;
    } else {
        //Default to Channel 
        return !I2C1CONbits.RCEN;
    }
}
void IIC_w_receive(IIC_CHANNEL channel) {
        while(IIC_c_receive(channel)){}
}
void IIC_dow_receive(IIC_CHANNEL channel) {
  IIC_do_receive(channel);
  IIC_w_receive(channel);
}

void IIC_do_stop(IIC_CHANNEL channel) {
    if (channel == IIC2) {
       I2C2CONbits.PEN = 1;
    } else {
        //Default to Channel 1
        I2C1CONbits.PEN = 1;   
    }
}
BOOL IIC_c_stop(IIC_CHANNEL channel) {
    if (channel == IIC2) {
        return !I2C2CONbits.PEN;
    } else {
        //Default to Channel 1
        return !I2C1CONbits.PEN;
    }
}
void IIC_w_stop(IIC_CHANNEL channel) {
        while(IIC_c_stop(channel)){}
}
void IIC_dow_stop(IIC_CHANNEL channel) {
    IIC_do_stop(channel);
    IIC_w_stop(channel);
}

void IIC_do_start(IIC_CHANNEL channel) {
    if (channel == IIC2) {
        I2C2CONbits.SEN = 1;
    } else {
        //Default to Channel 1
        I2C1CONbits.SEN = 1;
    }
}
BOOL IIC_c_start(IIC_CHANNEL channel) {
    if (channel == IIC2) {
        return !I2C2CONbits.SEN;
    } else {
        //Default to Channel 1
        return !I2C1CONbits.SEN;
    }
}
void IIC_w_start(IIC_CHANNEL channel) {
        while(IIC_c_start(channel)){}
}
void IIC_dow_start(IIC_CHANNEL channel) {
    IIC_do_start();
    IIC_w_start();
}

void IIC_do_restart(IIC_CHANNEL channel) {
    if (channel == IIC2) {
        I2C2CONbits.RSEN = 1;
    } else {
        //Default to Channel 1
        I2C1CONbits.RSEN = 1;
    }
}
BOOL IIC_c_restart(IIC_CHANNEL channel) {
    if (channel == IIC2) {
        return !I2C2CONbits.RSEN;
    } else {
        //Default to Channel 1
        return !I2C1CONbits.RSEN;
    }
}
void IIC_w_restart(IIC_CHANNEL channel) {
        while(IIC_c_restart(channel)){}
}
void IIC_dow_restart(IIC_CHANNEL channel) {
    IIC_do_restart(channel);
    IIC_w_restart(channel);
}


void IIC_send(IIC_CHANNEL channel, int address, char data) {

}



