/* 
 * File:   IO.h
 * Author: Philipp
 *
 * Created on February 21, 2016, 1:55 PM
 */

#ifndef IO_H
#define	IO_H

#ifdef	__cplusplus
extern "C" {
#endif

    //NRF SPI Bus
#define IO_wMISO_TRI TRISBbits.TRISB9
#define IO_wMISO_REG 0b0101
#define IO_wMOSI_TRI TRISBbits.TRISB1
#define IO_wMOSI_REG RPB10Rbits.RPB10R
#define IO_wCE_TRI TRISBbits.TRISB13
#define IO_wCE LATBbits.LATB13
#define IO_wSCK_TRI TRISBbits.TRISB14
#define IO_wCSN_TRI TRISBbits.TRISB15
#define IO_wCSN LATBbits.LATB15

    //BMI SPI Bus
#define IO_aMISO_TRI TRISGbits.TRISG7
#define IO_aMISO_REG 0b0001
#define IO_aMOSI_TRI TRISGbits.TRISG8
#define IO_aMOSI_REG RPG8Rbits.RPG8R
#define IO_aSCK_TRI TRISGbits.TRISG6
#define IO_aCSB_TRI TRISBbits.TRISB5
#define IO_aCSB LATBbits.LATB5
  
    //BatWarn
#define IO_battWarn1_TRI TRISBbits.TRISB11
#define IO_battWarn1 PORTBbits.RB11
#define IO_battWarn2_TRI TRISFbits.TRISF3
#define IO_battWarn2 PORTFbits.RF3

#define IO_battLed1_TRI TRISFbits.TRISF2
#define IO_battLed1 LATFbits.LATF2
#define IO_battLed2_TRI TRISFbits.TRISF6
#define IO_battLed2 LATFbits.LATF6
    
#define IO_SCLEAR_TRI TRISFbits.TRISF0
#define IO_SCLEAR LATFbits.LATF0
 
#define IO_DEBUG_TRI TRISE
#define IO_DEBUG_R PORTE
#define IO_DEBUG_RB PORTEbits
#define IO_DEBUG_W LATESET

#define IO_B1_TRI TRISDbits.TRISD1
#define IO_B1 PORTDbits.RD1
#define IO_B2_TRI TRISDbits.TRISD2
#define IO_B2 PORTDbits.RD2
#define IO_B3_TRI TRISDbits.TRISD3
#define IO_B3 PORTDbits.RD3
    
#define IO_C1_TRI TRISDbits.TRISD4
#define IO_C1 PORTDbits.RD4
#define IO_C2_TRI TRISDbits.TRISD5
#define IO_C2 PORTDbits.RD5
#define IO_C3_TRI TRISDbits.TRISD6
#define IO_C3 PORTDbits.RD6
#define IO_C4_TRI TRISDbits.TRISD7
#define IO_C4 PORTDbits.RD7
    /*          
        //BUTTON INPUT & CHANNEL SELECT BITS 
        TRISD = 0b11111110;  
     */


#ifdef	__cplusplus
}
#endif

#endif	/* IO_H */

