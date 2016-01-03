#include "NRF.h"

BOOL NRF_init(char channel) {
    int x;
    for (x = 0; x < 100; x++) {
        __asm__("nop");
    }
    //Active SPI module with corrct edge, mode, phase etc
    SPI_init(SPI3,
            SPI_INITF_CKE_ACTIVE_TO_IDLE |
            SPI_INITF_MASTER |
            SPI_INITF_CKP_IDLE_IS_LO |
            SPI_INITF_SMP_END |
            SPI_INITF_MODE_8
            , 9600);

    ncsn = 1;
    nce = 0;

    //Write to config registers 
    //RX Mode, Powered On, 1 Byte Checksum, Cheksum enabled
    NRF_wreg(NRF_RG__CONFIG, 0b0001011);
    for (int i = 0; i < 10; i++) {
        __asm__("nop");
    }
    //Disable AutoAknowledge
    NRF_wreg(NRF_RG__EN_AA, 0b00000000);
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
    SPI_trans(SPI3, NRF_CMD__R_REGISTER | NRF_RG__RX_ADDR_P0);
    SPI_trans(SPI3, ADDRESS0);
    SPI_trans(SPI3, ADDRESS1);
    SPI_trans(SPI3, ADDRESS2);
    ncsn = 1;

    //Set TX Address
    ncsn = 0;
    SPI_trans(SPI3, NRF_CMD__R_REGISTER | NRF_RG__TX_ADDR);
    SPI_trans(SPI3, ADDRESS0);
    SPI_trans(SPI3, ADDRESS1);
    SPI_trans(SPI3, ADDRESS2);
    ncsn = 1;

    //Flush
    NRF_wreg(NRF_RG__STATUS, 0x70);
    NRF_cmd(NRF_CMD__FLUSH_RX);
    NRF_cmd(NRF_CMD__FLUSH_TX);
    
    ncsn = 0;
    SPI_trans(SPI3, NRF_CMD__R_REGISTER | NRF_RG__CONFIG);
    char val = SPI_trans(SPI3,0x00);
    ncsn = 1;     
    if ((val & 0x08) != 0){
        __asm__("nop");
    } else {
        __asm__("nop");
    }
}

void NRF_wreg(char Reg, char val) {
    ncsn = 0;
    SPI_trans(SPI3, NRF_CMD__R_REGISTER | Reg);
    SPI_trans(SPI3, val);
    ncsn = 1;
}

int NRF_cmd(char cmd) {
    ncsn = 0;
    SPI_trans(SPI3, cmd);
    ncsn = 1;
}

int NRF_rreg(char Reg) {

}

BOOL NRF_check() {

}

int NRF_RXBuffer_Length() {

}

void NRF_RXBuffer(char* buf) {

}

void NRF_TXBuffer(char l, char* buf) {

}