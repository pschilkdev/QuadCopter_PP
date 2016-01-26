#include "NRF.h"
volatile char wreg_test1;
volatile char wreg_test2;
volatile char probe;
volatile char rndtester;

char defCONFIG;
char defEN_AA;

BOOL powerOn = TRUE;
char currentSTATUS;

BOOL NRF_init(char channel) {
    //Compile Startup Settings into Default Register Values
    defCONFIG = (MASK_RX_DR << 6)|(MASK_TX_DS<< 5)|(MASK_MAX_RT<< 4)|(EN_CRC<< 3)|(CRCO<< 2);
    defEN_AA = (ENAA_P5 << 5)|(ENAA_P4 << 4)|(ENAA_P3 << 3)|(ENAA_P2 << 2)|(ENAA_P1 << 1)|(ENAA_P0);
    
    
    
    int x;
    for (x = 0; x < 100; x++) {
        __asm__("nop");
    }
    
    //Active SPI module with corrct edge, mode, phase etc
    SPI_init(SPI3,
            SPI_INITF_MASTER |
            SPI_INITF_MODE_8 |
            SPI_INITF_CKE_ACTIVE_TO_IDLE /*|
            SPI_INITF_SMP_END*/
            , 9600);

    ncsn = 1;
    nce = 1;
    
    char n=0;


    //Write to config registers 
    //Settings + Power On + RX
    NRF_wreg(NRF_RG__CONFIG, defCONFIG | 0b11);
    for (int i = 0; i < 10; i++) {
        __asm__("nop");
    }
    
    rndtester = NRF_rreg(NRF_RG__CONFIG);
    __asm__("NOP");
    //Disable AutoAknowledge
    NRF_wreg(NRF_RG__EN_AA, defEN_AA);
    //Enable only Data Pipe1
    NRF_wreg(NRF_RG__EN_RXADDR, 0x01);
    //3 byte adress
    NRF_wreg(NRF_RG__SETUP_AW, 0x01);
    //Disable retransmit
   NRF_wreg(NRF_RG__SETUP_RETR, 0x00);
    //Set RF Channel
    NRF_wreg(NRF_RG__RF_CH, channel);
    //Config RF:
    NRF_wreg(NRF_RG__RF_SETUP, 0x26);
    //32bye P1 width
    NRF_wreg(NRF_RG__RX_PW_P0, 32);

    //Set RX Address
    ncsn = 0;
    SPI_trans(SPI3, NRF_CMD__W_REGISTER | NRF_RG__RX_ADDR_P0);
    SPI_trans(SPI3, ADDRESS0);
   SPI_trans(SPI3, ADDRESS1);
    SPI_trans(SPI3, ADDRESS2);
    ncsn = 1;

    //Set TX Address
    ncsn = 0;
     SPI_trans(SPI3, NRF_CMD__W_REGISTER | NRF_RG__TX_ADDR);
    SPI_trans(SPI3, ADDRESS0);
     SPI_trans(SPI3, ADDRESS1);
      SPI_trans(SPI3, ADDRESS2);
    ncsn = 1;

    //Flush
     NRF_wreg(NRF_RG__STATUS, 0x70);
     NRF_cmd(NRF_CMD__FLUSH_RX);
     NRF_cmd(NRF_CMD__FLUSH_TX);
    
    ncsn = 0;
    SPI_trans(SPI3, 0b11111111);
    probe = SPI_trans(SPI3, 0x00);
    ncsn = 1;     
    

    if (probe != 0){
        __asm__("nop");
    } else {
        __asm__("nop");
    }
}

void NRF_wreg(char Reg, char val) {
    ncsn = 0;
    wreg_test1 = SPI_trans(SPI3, NRF_CMD__W_REGISTER |(Reg & 0b00011111));
    wreg_test2 = SPI_trans(SPI3, val);
    ncsn = 1;
}

int NRF_cmd(char cmd) {
    ncsn = 0;
    int val = SPI_trans(SPI3, cmd);
    ncsn = 1;
    return val;
}

int NRF_rreg(char Reg) {
    ncsn = 0;
    SPI_trans(SPI3, NRF_CMD__R_REGISTER | (Reg & 0b00011111));
    int val = SPI_trans(SPI3, 0b00);
    ncsn = 1;
    return val;
}

void NRF_grabClearStatus(){
    currentSTATUS = NRF_rreg(NRF_RG__STATUS);
    NRF_wreg(NRF_RG__STATUS,0b00000000);
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

}

void NRF_RXBuffer(char* buf) {

}

void NRF_TXBuffer(char l, char* buf,BOOL ack) {

}