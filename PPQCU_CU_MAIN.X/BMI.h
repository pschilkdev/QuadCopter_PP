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

    typedef enum {
        BMI_READ = 1,
        BMI_WRITE = 0
    } BMI_OPERATION;

#define bcsb_H (LATBbits.LATB5 = 1)
#define bcsb_L (LATBbits.LATB5 = 0)

    //Registers
#define BMI_REG__CMD 0x7E
#define BMI_REG__STEP_CONF_1 0x7B
#define BMI_REG__STEP_CONF_o 0x7A
#define BMI_REG__STEP_CNT_1 0x79
#define BMI_REG__STEP_CNT_0 0x78
#define BMI_REG__OFFSET_6 0x77
#define BMI_REG__OFFSET_5 0x76
#define BMI_REG__OFFSET_4 0x75
#define BMI_REG__OFFSET_3 0x74
#define BMI_REG__OFFSET_2 0x73
#define BMI_REG__OFFSET_1 0x72
#define BMI_REG__OFFSET_0 0x71
#define BMI_REG__NV_CONF 0x70 
#define BMI_REG__SELF_TEST 0x6D 
#define BMI_REG__PMU_TRIGGER 0x6C 
#define BMI_REG__IF_CONF 0x6B 
#define BMI_REG__CONF 0x6A 
#define BMI_REG__FOC_CONF 0x69 
#define BMI_REG__INT_FLAT_1 0x68 
#define BMI_REG__INT_FLAT_0 0x67 
#define BMI_REG__INT_ORIENT_1 0x66
#define BMI_REG__INT_ORIENT_0 0x65 
#define BMI_REG__INT_TAP_1 0x64 
#define BMI_REG__INT_TAP_0 0x63 
#define BMI_REG__INT_MOTION_3 0x62 
#define BMI_REG__INT_MOTION_2 0x61 
#define BMI_REG__INT_MOTION_2 0x60 
#define BMI_REG__INT_MOTION_0 0x5F 
#define BMI_REG__INT_LOWHIGH_4 0x5E 
#define BMI_REG__INT_LOWHIGH_3 0x5D 
#define BMI_REG__INT_LOWHIGH_2 0x5C 
#define BMI_REG__INT_LOWHIGH_1 0x5B 
#define BMI_REG__INT_LOWHIGH_0 0x5A 
#define BMI_REG__INT_DATA_1 0x59 
#define BMI_REG__INT_DATA_0 0x58 
#define BMI_REG__INT_MAP_2 0x57 
#define BMI_REG__INT_MAP_1 0x56 
#define BMI_REG__INT_MAP_0 0x55 
#define BMI_REG__INT_LATCH 0x54 
#define BMI_REG__IN_OUT_CTRL 0x53 
#define BMI_REG__INT_EN_2 0x52 
#define BMI_REG__INT_EN_1 0x51 
#define BMI_REG__INT_EN_0 0x50 
#define BMI_REG__MAG_IF_4 0x4F 
#define BMI_REG__MAG_IF_3 0x4E 
#define BMI_REG__MAG_IF_2 0x4D 
#define BMI_REG__MAG_IF_1 0x4C 
#define BMI_REG__MAG_IF_0 0x4B 
#define BMI_REG__FIFO_CONFIG_1 0x47 
#define BMI_REG__FIFO_CONFIG_0 0x46 
#define BMI_REG__FIFO_DOWNS 0x45 
#define BMI_REG__MAG_CONF 0x44 
#define BMI_REG__GYR_RANGE 0x43 
#define BMI_REG__GYR_CONF 0x42 
#define BMI_REG__ACC_RANGE 0x41 
#define BMI_REG__ACC_CONF 0x40 
#define BMI_REG__FIFO_DATA 0x24 
#define BMI_REG__FIFO_LENGTH_1 0x23 
#define BMI_REG__FIFO_LENGTH_0 0x22 
#define BMI_REG__TEMPERATURE_1 0x21 
#define BMI_REG__TEMPERATURE_0 0x20 
#define BMI_REG__INT_STATUS_3 0x1F 
#define BMI_REG__INT_STATUS_2 0x1E 
#define BMI_REG__INT_STATUS_1 0x1D 
#define BMI_REG__INT_STATUS_0 0x1C 
#define BMI_REG__STATUS 0x1B 
#define BMI_REG__SENSORTIME_2 0x1A 
#define BMI_REG__SENSORTIME_1 0x19 
#define BMI_REG__SENSORTIME_0 0x18 
#define BMI_REG__DATA_19 0x17 
#define BMI_REG__DATA_18 0x16 
#define BMI_REG__DATA_17 0x15 
#define BMI_REG__DATA_16 0x14 
#define BMI_REG__DATA_15 0x13 
#define BMI_REG__DATA_14 0x12 
#define BMI_REG__DATA_13 0x11 
#define BMI_REG__DATA_12 0x10 
#define BMI_REG__DATA_11 0x0F 
#define BMI_REG__DATA_10 0x0E 
#define BMI_REG__DATA_9 0x0D 
#define BMI_REG__DATA_8 0x0C 
#define BMI_REG__DATA_7 0x0B 
#define BMI_REG__DATA_6 0x0A 
#define BMI_REG__DATA_5 0x09 
#define BMI_REG__DATA_4 0x08 
#define BMI_REG__DATA_3 0x07 
#define BMI_REG__DATA_2 0x06 
#define BMI_REG__DATA_1 0x05 
#define BMI_REG__DATA_0 0x04 
#define BMI_REG__PMU_STATUS 0x03 
#define BMI_REG__ERR_REG 0x02 
#define BMI_REG__CHIP_ID 0x00 

#ifdef	__cplusplus
}
#endif

#endif	/* BMI_H */

