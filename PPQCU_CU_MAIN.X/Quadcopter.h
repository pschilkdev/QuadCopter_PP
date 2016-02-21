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
        LIGHTS_STARTUP = 1,
        LIGHTS_STANDBY = 2,
        LIGHTS_FLYING = 3,
        LIGHTS_FLYING_BAT = 4,
        LIGHTS_RECOVER = 5
    } QC_LIGHTS;

#ifdef	__cplusplus
}
#endif

#endif	/* QUADCOPTER_H */

