/* 
 * File:   Quadcopter.h
 * Author: Philipp
 *
 * Created on February 8, 2016, 2:34 PM
 */

#ifndef QUADCOPTER_H
#define	QUADCOPTER_H

#ifdef	__cplusplus
extern "C" {
#endif

#define IIC_ADR_BAT 0x50
#define IIC_ADR_RGB 0x40
#define IIC_ADR_INT 0x30 >> 1

    typedef enum{
    TEST = 1,   
    }QC_LIGHTS;
    
    
    
    #include "Quadcopter.h"
#include "IIC.h"

BOOL motor_update(int mfl, int mfr, int mbl, int mbr);

char read_battery();
void chips_reset();
void chips_run();

#ifdef	__cplusplus
}
#endif

#endif	/* QUADCOPTER_H */

