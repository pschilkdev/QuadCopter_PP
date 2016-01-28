/* 
 * File:   BMI.h
 * Author: Philipp
 *
 * Created on January 28, 2016, 9:41 AM
 */

#ifndef BMI_H
#define	BMI_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "SPI.h"
#include "config.h"
#include <xc.h>

    typedef enum{
        BMI_READ = 1,
        BMI_WRITE = 0
    }BMI_OPERATION;
    
    #define bcsb_H (LATBbits.LATB5 = 1)
    #define bcsb_L (LATBbits.LATB5 = 0)
    


#ifdef	__cplusplus
}
#endif

#endif	/* BMI_H */

