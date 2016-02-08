/* 
 * File:   IIC.h
 * Author: Philipp
 *
 * Created on February 4, 2016, 1:27 PM
 */

#ifndef IIC_H
#define	IIC_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum {
        SPI1 = 1,
        SPI2 = 2
    } IIC_CHANNEL;
    
    
    void IIC_init(IIC_CHANNEL, int, int);
    
#define IIC_RG__STOP_IN_IDLE
#define IIC_RG__CONTINUE_IN_IDLE
    
#define IIC_RG__STRICT_ADR
#define IIC_RG__NOT_STRICT_ADR
    
#define IIC_RG__10BIT_ADR
#define IIC_RG__7BIT_ADR
    
#define IIC_RG__ENABLE_SLEW_CONTROL
#define IIC_RG__DISABLE_SLEW_CONTROL
    
#define IIC_RG__USE_SMBUS_LEVELS 
    


    


#ifdef	__cplusplus
}
#endif

#endif	/* IIC_H */

