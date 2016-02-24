/*    
 *      Modifications by pschilkdev
 *      https://github.com/pschilkdev
 *
 *      2013 Elia Ritterbusch
 *      http://eliaselectronics.com
 *
 *      This work is licensed under the Creative Commons Attribution 3.0 Unported License.
 *      To view a copy of this license, visit http://creativecommons.org/licenses/by/3.0/
 */
#include <xc.h>
#include "spi.h"

void spi_init(void){
    SSP1CON1bits.CKP = 0; // Idle state for clock is a low level
    SSP1STATbits.CKE = 1; // Transmit occurs on transition from active to Idle clock state
    SSP1STATbits.SMP = 1; // Input data sampled at end of data output time (took me 5 friggin' hours)
    SSP1CON1bits.SSPM = 0; // SPI Master mode, SCK = FOSC/4
    SSP1CON1bits.SSPEN = 1; // enable MSSP1
}

void spi_transmit_sync(unsigned char * data, unsigned int length){
    unsigned char tmp;
    while(length != 0){
        tmp = spi_fast_shift(*data);
        length--;
	    data++;
    }
}

void spi_transfer_sync(unsigned char * dataout, unsigned char * datain, unsigned int length){
    while(length != 0){
        *datain = spi_fast_shift(*dataout);
        length--;
	    dataout++;
        datain++;
    }
}

unsigned char spi_fast_shift(unsigned char data){
    SSP1BUF = data;
    while( !PIR1bits.SSP1IF ); // wait for buffer full
    PIR1bits.SSP1IF = 0; // clear SSP1IF
    return SSP1BUF;
}