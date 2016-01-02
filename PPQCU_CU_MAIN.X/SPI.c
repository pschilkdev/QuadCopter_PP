#include "SPI.h"
#include "config.h"
{
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

int SPI_trans(SPI_CHANNEL channel, int data){
    if(channel ==SPI1){
        SPI1BUF = data;
        while(SPI1STATbits.SPIBUSY){asm("nop");}
        return SPI1BUF;
    } else if (channel == SPI2){
        SPI2BUF = data;
        while(SPI2STATbits.SPIBUSY){asm("nop");}
        return SPI3BUF;
    } else if (channel == SPI3){
        SPI3BUF = data;
        while(SPI3STATbits.SPIBUSY){asm("nop");}
        return SPI3BUF; 
    } else {
        //?
        while(1){asm("nop");}
    }
}