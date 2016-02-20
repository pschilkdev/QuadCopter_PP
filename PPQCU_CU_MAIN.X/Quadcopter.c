#include "Quadcopter.h"
#include "IIC.h"

#define VAL_PRELOAD 41536

#define s1 (LATEbits.LATE0)
#define s2 (LATEbits.LATE1)
#define s3 (LATGbits.LATG2)
#define s4 (LATGbits.LATG3)

void output(int);

//motor values 0-23999
BOOL motor_update(int mfl, int mfr, int mbl, int mbr) {
    mfl = 23999-mfl;
    mfr = 23999-mfr;
    mbl = 23999-mbl;
    mbr = 23999-mbr;
    s1 = 1;
    output(mfl);
    s1 = 0;
    
    s2 = 1;
    output(mfr);
    s2 = 0;
    
    s3 = 1;
    output(mbl);
    s3 = 0;
    
    s4 = 1;
    output(mbr);
    s4 = 0;
}

void output(int time){
    //Default timeout
    IFS0bits.T1IF = 0;
    TMR1 = VAL_PRELOAD;
    T1CONbits.ON = 1;
    while(!IFS0bits.T1IF){;}
    //valued timeout
   IFS0bits.T1IF = 0;
    TMR1 = VAL_PRELOAD+time;
    T1CONbits.ON = 1;
    while(!IFS0bits.T1IF){;}
}
   
void chips_reset() {
    LATFbits.LATF0 = 0;
}

void chips_run() {
    LATFbits.LATF0 = 1;
}

