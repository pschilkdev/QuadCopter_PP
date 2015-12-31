#include "SPI.h"

void SPI_init(SPI_CHANNEL channel, SPI_INITF flag, int baud) {
    //Calc Prescalar for Baud
    int prsclr;
    prsclr = F_PER / baud / 2 - 1;
    if (prsclr < 1 || prsclr > 512) {
        while (1) {
            //Prescalar too large/small
            asm("nop");
        }
    } else {
        //Available Prescalar. Continue:
        if (channel == SPI1) {
            asm("nop"); //Just to be sure
            SPI1CONbits.ON = 0; //Disable SPI
            asm("nop"); //Nop as SFR should not be accesed 1 cycle after ON clear
            SPI1BUF = 0; //Clear Buffer
            SPI1BRG = prsclr;
            SPI1CON = flag; //Setup options determined by flags
            asm("nop"); //Just to be sure
            SPI1CONbits. ON = 1;
            asm("nop"); //Just to be sure
        } else if (channel == SPI2) {
            asm("nop"); //Just to be sure
            SPI2CONbits.ON = 0; //Disable SPI
            asm("nop"); //Nop as SFR should not be accesed 1 cycle after ON clear
            SPI2BUF = 0; //Clear Buffer
            SPI2BRG = prsclr;
            SPI2CON = flag; //Setup options determined by flags
            asm("nop"); //Just to be sure
            SPI2CONbits. ON = 1;
            asm("nop"); //Just to be sure
        } else if (channel == SPI3) {
            asm("nop"); //Just to be sure
            SPI3CONbits.ON = 0; //Disable SPI
            asm("nop"); //Nop as SFR should not be accesed 1 cycle after ON clear
            SPI3BUF = 0; //Clear Buffer
            SPI3BRG = prsclr;
            SPI3CON = flag; //Setup options determined by flags
            asm("nop"); //Just to be sure
            SPI3CONbits. ON = 1;
            asm("nop"); //Just to be sure
        }
    }
}