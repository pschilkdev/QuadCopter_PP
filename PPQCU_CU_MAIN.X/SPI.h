/* 
 * File:   SPI.h
 * Author: Philipp
 *
 * Simple Library for SPI communications. Written for the PIC32MX120F064H.
 * Adapted from the Legacy SPI Peripheral Library by Micochip.
 * 
 * Created on December 29, 2015, 12:03 PM
 */

#ifndef SPI_H
#define	SPI_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "config.h"

    /*
     *      ========= Structures and Enums =========
     */

    typedef enum {
        SPI_INITF_FRM_EN = 0x80000000,
        SPI_INITF_FRMSYNC_EN = 0x40000000,
        SPI_INITF_FRMPOL_ACTH = 0x20000000,
        SPI_INITF_FRMPOL_ACTL = 0x0,
        SPI_INITF_SPIFE_CO = 0x20000,
        SPI_INITF_SPIFE_PRE = 0x0,
        SPI_INITF_FRZ = 0x4000,
        SPI_INITF_SIDL = 0x2000,
        SPI_INITF_DISSDO = 0x1000,
        SPI_INITF_MODE_8 = 0x0,
        SPI_INITF_MODE_16 = 0x400,
        SPI_INITF_MODE_32 = 0x800,
        SPI_INITF_SMP_END = 0x200,
        SPI_INITF_SMP_MID = 0x0,
        SPI_INITF_CKE_ACTIVE_TO_IDLE = 0x100,
        SPI_INITF_CKE_IDLE_TO_ACTIVE = 0x0,
        SPI_INITF_SSEN = 0x80,
        SPI_INITF_CKP_IDLE_IS_LO = 0x40,
        SPI_INITF_CKP_ACTI_IS_HI = 0x40,
        SPI_INITF_CKP_IDLE_IS_HI = 0x0,
        SPI_INITF_CKP_ACTI_IS_LO = 0x0,
        SPI_INITF_MSTEN =  0x20,
        SPI_INITF_MASTER = 0x20,
        SPI_INITF_SLAVE = 0x0
    } SPI_INITF;

    typedef enum {
        SPI1 = 1,
        SPI2 = 2,
        SPI3 = 3
    } SPI_CHANNEL;

    /*
     *       ======= Functions =======
     */
    void SPI_init(SPI_CHANNEL, SPI_INITF, int baud);
    int  SPI_trans(SPI_CHANNEL, int data);

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

