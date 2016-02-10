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
        IIC1 = 1,
        IIC2 = 2
    } IIC_CHANNEL;
    
    
    void IIC_init(IIC_CHANNEL, int, int);
    
#define IIC_RG__STOP_IN_IDLE 0x00002000
#define IIC_RG__CONTINUE_IN_IDLE 0x00000000
    
#define IIC_RG__STRICT_ADR 0x00000800
#define IIC_RG__NOT_STRICT_ADR 0x00000000
    
#define IIC_RG__10BIT_ADR 0x00000400
#define IIC_RG__7BIT_ADR  0x00000000
    
#define IIC_RG__ENABLE_SLEW_CONTROL 0x00000000
#define IIC_RG__DISABLE_SLEW_CONTROL 0x00000200
    
#define IIC_RG__USE_SMBUS_LEVELS 0x00000100
    
#define IIC_RG__ENABLE_GEN_CALL  0x00000080
#define IIC_RG__DISABLE_GEN_CALL 0x00000000

#define IIC_RG__ENABLE_CLOCK_STRETCHING  0x00000040 
#define IIC_RG__DISABLE_CLOCK_STRETCHING 0x00000000

#ifdef	__cplusplus
}
#endif

#endif	/* IIC_H */

