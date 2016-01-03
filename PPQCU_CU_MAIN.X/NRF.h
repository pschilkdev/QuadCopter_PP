/* 
 * File:   NRF.h
 * Author: Philipp
 *
 * Created on January 2, 2016, 6:30 PM
 */

#ifndef NRF_H
#define	NRF_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "SPI.h"
#include "config.h"

// ====== Commands ========
    
#define NRF_CMD__R_REGISTER 0b00000000
#define NRF_CMD__W_REGISTER 0b00100000
#define NRF_CMD__R_RX_PAYLOAD 0b01100000
#define NRF_CMD__W_TX_PAYLOAD 0b10100000
#define NRF_CMD__FLUSH_TX 0b11100001
#define NRF_CMD__FLUSH_RX 0b11100010
#define NRF_CMD__REUSE_TX_PL 0b11100011
#define NRF_CMD__ACTIVATE 0b01010000
#define NRF_CMD__R_RX_PL_WID 0b01100000
#define NRF_CMD__W_ACK_PAYLOAD 0b10101000
#define NRF_CMD__W_TX_PAYLOAD_NO_ACK 0b10110000
#define NRF_CMD__NOP 0b11111111
    
// ====== Registers =======
    
#define NRF_RG__CONFIG 0x00
#define NRF_RG__EN_AA 0x01
#define NRF_RG__EN_RXADDR 0x02
#define NRF_RG__SETUP_AW 0x03
#define NRF_RG__SETUP_RETR 0x04
#define NRF_RG__RF_CH 0x05
#define NRF_RG__RF_SETUP 0x06
#define NRF_RG__STATUS 0x07
#define NRF_RG__OBSERVE_TX 0x08
#define NRF_RG__CD 0x09
#define NRF_RG__RX_ADDR_P0 0x0A
#define NRF_RG__RX_ADDR_P1 0x0B
#define NRF_RG__RX_ADDR_P2 0x0C
#define NRF_RG__RX_ADDR_P3 0x0D
#define NRF_RG__RX_ADDR_P4 0x0E
#define NRF_RG__RX_ADDR_P5 0x0F
#define NRF_RG__TX_ADDR 0x10
#define NRF_RG__RX_PW_P0 0x11
#define NRF_RG__RX_PW_P1 0x12
#define NRF_RG__RX_PW_P2 0x13
#define NRF_RG__RX_PW_P3 0x14
#define NRF_RG__RX_PW_P4 0x15
#define NRF_RG__RX_PW_P5 0x16
#define NRF_RG__FIFO_STATUS 0x17
#define NRF_RG__DYNPD 0x1C
#define NRF_RG__FEATURE 0x1D
    
    void NRF_init();
    int NRF_cmd(int cmd);
    void NRF_wreg(char Reg,char val);
    int  NRF_rreg(char Reg);
    BOOL NRF_check();
    int NRF_RXBuffer_Length();
    void NRF_RXBuffer(char*);
    void NRF_TXBuffer(char, char*);

#define nce LATBbits.LATB13
#define ncsn LATBbits.LATB15
    
#define ADDRESS0 0b00101011
#define ADDRESS1 0b00101011
#define ADDRESS2 0b00101011
    
#ifdef	__cplusplus
}
#endif

#endif	/* NRF_H */
