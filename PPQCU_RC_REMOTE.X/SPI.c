
#include <pic18f26k22.h>

void SPI_init(){
    SSP1CON1bits.SSPEN = 1;
    SSP1CON1bits.SSPM = 0b0010;
    SSP1STAT = 0;
    SSP1STATbits.CKE = 1;
    SSP1CON1bits.CKP = 0;
   
}

char SPI_trans(char dat){
     
        PIR1bits.SSP1IF = 0;
        if (SSP1STATbits.BF) {
            int temp = SSP1BUF;
        }
        SSP1BUF = dat;
        int x = 0;
        while ((!PIR1bits.SSP1IF ) | (!SSP1STATbits.BF)) {
            x++;
        }
        char result = SSP1BUF;
        PIR1bits.SSP1IF = 0;
        return result;
}