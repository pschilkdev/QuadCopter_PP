#include "Quadcopter.h"
#include "IIC.h"
#include "IO.h"

#define timeout 10000

int battWarnLevel = 0;

void motor_updated(int mfl, int mfr, int mbl, int mbr) {

    IIC_start(IIC1);
    while (IIC_status(IIC1, IIC_STAT_START)) {
        ;
    }

    //Send Address, Prepare ms1, wait
    IIC_address(IIC1, IIC_ADR_INT, IIC_WRITE);
    char msg = ((0b111111110000 & mfl) >> 4);
    if(IIC_wait_TX(IIC1)){
       IIC_stop(IIC1);
       while(IIC_status(IIC1,IIC_STAT_STOP)){;}
    }

    //Send ms1, Prepare ms2, wait
    IIC_put(IIC1, msg);
    msg = ((0b1111 & mfl) << 4) | ((0b1111000000000 & mfr) >> 8);
    if(IIC_wait_TX(IIC1)){
       IIC_stop(IIC1);
       while(IIC_status(IIC1,IIC_STAT_STOP)){;}
    }

    //Send ms2, Prepare ms3, wait
    IIC_put(IIC1, msg);
    msg = ((0b11111111 & mfr));
    if(IIC_wait_TX(IIC1)){
       IIC_stop(IIC1);
       while(IIC_status(IIC1,IIC_STAT_STOP)){;}
    }

    //Send ms3, Prepare ms4, wait
    IIC_put(IIC1, msg);
    msg = ((0b111111110000 & mbl) >> 4);
    if(IIC_wait_TX(IIC1)){
       IIC_stop(IIC1);
       while(IIC_status(IIC1,IIC_STAT_STOP)){;}
    }

    //Send ms4, Prepare ms5, wait
    IIC_put(IIC1, msg);
    msg = ((0b1111 & mbl) << 4) | ((0b111100000000 & mbr) >> 8);
    if(IIC_wait_TX(IIC1)){
       IIC_stop(IIC1);
       while(IIC_status(IIC1,IIC_STAT_STOP)){;}
    }

    //Send ms5, Prepare ms6, wait
    IIC_put(IIC1, msg);
    msg = (IIC1, ((0b11111111 & mbr)));
    if(IIC_wait_TX(IIC1)){
       IIC_stop(IIC1);
       while(IIC_status(IIC1,IIC_STAT_STOP)){;}
    }

    //Send ms6, wait
    IIC_put(IIC1, msg);
    if(IIC_wait_TX(IIC1)){
       IIC_stop(IIC1);
       while(IIC_status(IIC1,IIC_STAT_STOP)){;}
    }

    //Stop
    IIC_stop(IIC1);
    while (IIC_status(IIC1, IIC_STAT_STOP)) {
        ;
    }
}

void light_update(QC_LIGHTS lights) {
    IIC_start(IIC1);
    while (IIC_status(IIC1, IIC_STAT_START)) {
        ;
    }
    IIC_address(IIC1, IIC_ADR_RGB, IIC_WRITE);
    if(IIC_wait_TX(IIC1)){
       IIC_stop(IIC1);
       while(IIC_status(IIC1,IIC_STAT_STOP)){;}
    }
    IIC_put(IIC1, 0b11111111 & lights);   
    if(IIC_wait_TX(IIC1)){
       IIC_stop(IIC1);
       while(IIC_status(IIC1,IIC_STAT_STOP)){;}
    }
    IIC_stop(IIC1);
    while (IIC_status(IIC1, IIC_STAT_STOP)) {
        ;
    }
}

char read_battery() {

}

BOOL battWarn() {
    if (battWarnLevel == 0) {
        if (IO_battWarn1) {
            //Entering Level 1
            battWarnLevel = 1;
            light_update(LIGHTS_FLYING_BAT);
            return FALSE;
        }
    } else if (battWarnLevel == 1) {
        if (IO_battWarn2) {
            //Entering Level 2
            battWarnLevel = 2;
            light_update(LIGHTS_RECOVER);
            return TRUE;
        }
    } else {
        return 0;
    }
}

void chips_reset() {
    IO_SCLEAR = 0;
}

void chips_run() {
    IO_SCLEAR = 1;
}