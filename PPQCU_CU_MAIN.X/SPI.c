#include "SPI.h"
#include "config.h"
#include <xc.h>

void SPI_init(SPI_CHANNEL channel, SPI_INITF flag, int baud) {
    //Calc Prescalar for Baud
    int prsclr;
    prsclr = F_PER / baud / 2 - 1;
    if (prsclr < 1 || prsclr > 512) {
        while (1) {
            //Prescalar too large/small
            __asm__("nop");
        }
    } else {
        //Available Prescalar. Continue:
        if (channel == SPI1) {
            __asm__("nop"); //Just to be sure
            SPI1CONbits.ON = 0; //Disable SPI
            __asm__("nop"); //Nop as SFR should not be accesed 1 cycle after ON clear
            SPI1BUF = 0; //Clear Buffer
            SPI1BRG = prsclr;
            SPI1CON = flag; //Setup options determined by flags
            SPI1CONbits.ENHBUF = 1;
            __asm__("nop"); //Just to be sure
            SPI1CONbits. ON = 1;
            __asm__("nop"); //Just to be sure
        } else if (channel == SPI2) {
            __asm__("nop"); //Just to be sure
            SPI2CONbits.ON = 0; //Disable SPI
            __asm__("nop"); //Nop as SFR should not be accesed 1 cycle after ON clear
            SPI2BUF = 0; //Clear Buffer
            SPI2BRG = prsclr;
            SPI2CON = flag; //Setup options determined by flags
            SPI2CONbits.ENHBUF = 1;
            __asm__("nop"); //Just to be sure
            SPI2CONbits. ON = 1;
            __asm__("nop"); //Just to be sure
        } else if (channel == SPI3) {
            __asm__("nop"); //Just to be sure
            SPI3CONbits.ON = 0; //Disable SPI
            __asm__("nop"); //Nop as SFR should not be accesed 1 cycle after ON clear
            SPI3BUF = 0; //Clear Buffer
            SPI3BRG = prsclr;
            SPI3CON = flag; //Setup options determined by flags
            SPI3CONbits.ENHBUF = 1;
            __asm__("nop"); //Just to be sure
            SPI3CONbits. ON = 1;
            __asm__("nop"); //Just to be sure
        }
    }
}

volatile int tester;

int SPI_trans(SPI_CHANNEL channel, int data) {
    if (channel == SPI1) {
        if (SPI1STATbits.SPIRBF) {
            int temp = (char) SPI1BUF;
        }
        SPI1BUF = data;
        while (SPI1STATbits.SPIBUSY) {
            __asm__("nop");
        }
        return SPI1BUF;
    } else if (channel == SPI2) {
        if (SPI2STATbits.SPIRBF) {
            int temp = (char) SPI2BUF;
        }
        
        SPI2BUF = data;
        while (SPI2STATbits.SPIBUSY) {
            __asm__("nop");
        }
        __asm__("nop");
        tester = SPI2BUF;
        return tester;
    } else if (channel == SPI3) {
      
        if (SPI3STATbits.SPIRBF) {
            int temp = (char) SPI3BUF;
        }
        SPI3BUF = data;
        while ( SPI3STATbits.SPIBUSY) {
            __asm__("nop");
        }
        __asm__("nop");
        tester = SPI3BUF;
        return tester;
        
    } else {
        
        
        //?
        while (1) {
            __asm__("nop");
        }
    }
}