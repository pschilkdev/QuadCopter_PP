#include "NRF.h"
volatile char wreg_test1;
volatile char wreg_test2;
volatile char probe;
volatile char rndtester;

char defCONFIG;
char defEN_AA;
char defEN_RXADDR;
char defSETUP_AW;
char defSETUP_RETR;
char defRF_CH;
char defRF_SETUP;
char defRX_PW_P0;

BOOL powerOn = TRUE;
char currentSTATUS;


void NRF_init() {
    //Compile Startup Settings into Default Register Values
    defCONFIG = (MASK_RX_DR << 6)|(MASK_TX_DS<< 5)|(MASK_MAX_RT<< 4)|(EN_CRC<< 3)|(CRCO<< 2);
    defEN_AA = (ENAA_P5 << 5)|(ENAA_P4 << 4)|(ENAA_P3 << 3)|(ENAA_P2 << 2)|(ENAA_P1 << 1)|(ENAA_P0);
    defEN_RXADDR = (ERX_P5 << 5)|(ERX_P4 << 4)|(ERX_P3 << 3)|(ERX_P2 << 2)|(ERX_P1 << 1)|(ERX_P0);
    defSETUP_AW = 0b00000011 & AW;
    defSETUP_RETR = (ARD<<4)|(ARC);
    defRF_CH = 0b01111111 & RF_CH;
    defRF_SETUP = (CONT_WAVE << 7)|(RF_DR << 3)|(PLL_LOCK << 4)|( RF_PWR << 1);
    defRX_PW_P0 = 0b00111111 & RX_PW_P0;
   
    
    
    int x;
    for (x = 0; x < 100; x++) {
       asm("nop");
    }
    
    //Active SPI module with correct edge, mode, phase etc
    SPI_init();

    ncs = 1;
    nce = 0;
    
    char n=0;


    //Write to config registers 
    //Settings + Power On + RX
    NRF_wreg(NRF_RG__CONFIG, defCONFIG | 0b11);
    for (int i = 0; i < 10; i++) {
        asm("nop");
    }
    
   
    
    rndtester = NRF_rreg(NRF_RG__CONFIG);
    asm("NOP");
    //Set Auto Acknowledge
    NRF_wreg(NRF_RG__EN_AA, defEN_AA);
    //Set Data Pipes Enabled
    NRF_wreg(NRF_RG__EN_RXADDR, defEN_RXADDR);
    //Setup Adress Width
    NRF_wreg(NRF_RG__SETUP_AW, defSETUP_AW);
    //Disable retransmit
    NRF_wreg(NRF_RG__SETUP_RETR, defSETUP_RETR);
    //Set RF Channel
    NRF_wreg(NRF_RG__RF_CH, defRF_CH);
    //Config RF:
    NRF_wreg(NRF_RG__RF_SETUP, defRF_SETUP);
    //32bye P1 width
    NRF_wreg(NRF_RG__RX_PW_P0, defRX_PW_P0);
    //Enable NO ACK transmit command
    NRF_wreg(NRF_RG__FEATURE, 0b00000001);

    //Set RX Address
    ncs = 0;
    SPI_trans(NRF_CMD__W_REGISTER | NRF_RG__RX_ADDR_P0);
    SPI_trans(ADDRESS0);
    SPI_trans(ADDRESS1);
    SPI_trans(ADDRESS2);
    ncs = 1;

    //Set TX Address
    ncs = 0;
    SPI_trans(NRF_CMD__W_REGISTER | NRF_RG__TX_ADDR);
    SPI_trans(ADDRESS0);
    SPI_trans(ADDRESS1);
    SPI_trans(ADDRESS2);
    ncs = 1;

    //Flush
    NRF_cmd(NRF_CMD__FLUSH_RX);
    NRF_cmd(NRF_CMD__FLUSH_TX);
    NRF_wreg(NRF_RG__STATUS, 0x70);
    
    //Check if Status register contains written value
    asm("NOP");
    asm("NOP");
    asm("NOP");
    
    ncs = 0;
    probe = SPI_trans(0b11111111);
    SPI_trans(0x00);
    ncs = 1;   
 
    while(probe == 0){
        asm("nop");
    }
    
}

void NRF_wreg(char Reg, char val) {
   ncs = 0;
    wreg_test1 = SPI_trans(NRF_CMD__W_REGISTER |(Reg & 0b00011111));
    wreg_test2 = SPI_trans(val);
   ncs = 1;
}

int NRF_cmd(char cmd) {
    ncs = 0;
    int val = SPI_trans(cmd);
    ncs = 1;
    return val;
}

int NRF_rreg(char Reg) {
    ncs = 0;
    SPI_trans(NRF_CMD__R_REGISTER | (Reg & 0b00011111));
    int val = SPI_trans(0b00);
    ncs = 1;
    return val;
}

void NRF_grabClearStatus(){
    currentSTATUS = NRF_rreg(NRF_RG__STATUS);
    NRF_wreg(NRF_RG__STATUS,0x70);
}

BOOL NRF_checkRX() {
return (currentSTATUS && 0b01000000);
}

BOOL NRF_checkMAX(){
    return (currentSTATUS && 0b00010000);
}

BOOL NRF_checkTX(){
    return (currentSTATUS && 0b00100000);
}

void NRF_setRX(){
    NRF_wreg(NRF_RG__CONFIG, defCONFIG | (0b10) | powerOn);
}

void NRF_setTX(){
    NRF_wreg(NRF_RG__CONFIG, defCONFIG | (0b00) | powerOn); 
}

int NRF_RXBuffer_Length() {
    return NRF_rreg(NRF_RG__RX_PW_P0);
}

int NRF_RXBuffer(char* buf) {
    int length = NRF_RXBuffer_Length();
}

BOOL NRF_TX_done(){
    return !(NRF_rreg(NRF_RG__STATUS) & 0b00100000);
    
}
