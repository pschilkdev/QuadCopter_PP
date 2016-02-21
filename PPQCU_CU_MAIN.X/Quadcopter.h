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

#include "config.h"
    
#define IIC_ADR_BAT 0x50
#define IIC_ADR_RGB 0x40
#define IIC_ADR_INT 0x30

    typedef enum {
        STARTUP = 1,
        STANDBY = 2,
        FLYING = 3,
        FLYING_BAT = 4,
        RECOVER = 5
    } QC_LIGHTS;

#ifdef	__cplusplus
}
#endif

#endif	/* QUADCOPTER_H */

