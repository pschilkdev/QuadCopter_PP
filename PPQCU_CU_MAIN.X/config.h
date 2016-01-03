/* 
 * File:   config.h
 * Author: Philipp
 *
 * Created on December 28, 2015, 11:16 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <p32xxxx.h>
#include <xc.h>
    
typedef unsigned char BOOL;
#define TRUE    1
#define FALSE   0
    
    // ======== GLOBAL OPTIONS ==========

    //System clock frequency
#define F_OSC 48000000
    //Peripheral Clock Divider
#define F_PER_DIV 8
    //Peripheral Clock frequency
#define F_PER F_OSC/F_PER_DIV


#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

