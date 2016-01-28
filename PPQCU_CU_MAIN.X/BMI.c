#include "BMI.h"
SPI_CHANNEL spic;

void BMI_init(SPI_CHANNEL spi) {
    spic = spi;

    SPI_init(spic,
            SPI_INITF_MASTER |
            SPI_INITF_MODE_8 |
            SPI_INITF_CKE_ACTIVE_TO_IDLE
            , 9600);

    bcsb_H;
    __asm__("nop");
    __asm__("nop");
}

char BMI_trans(char operation, char address, char value) {
    bcsb_L;
    SPI_trans(spic, (operation << 7) | address);
    volatile char val = SPI_trans(spic, value);
    bcsb_H;
    return val;
}

void BMI_write_multiple(char address, char value[], char num) {
    bcsb_L;
    int i;
    SPI_trans(spic, (BMI_WRITE << 7) | (address & 0b1111111));
    for (i = 1; i <= num; i++) {
        SPI_trans(spic, value[i]);
    }
    bcsb_H;
}

char * BMI_read_multiple(char address, char value[], char num) {
    int result[num - 1];
    bcsb_L;
    int i;
    SPI_trans(spic, (BMI_READ << 7) | (address & 0b1111111));
    for (i = 1; i <= num; i++) {
        result[i - 1] = SPI_trans(spic, value[i]);
    }
    bcsb_H;
    return result;
}

char BMI_read(char address) {
    return BMI_trans(BMI_READ & 0b1, address & 0b1111111, 0x0);
}

void BMI_write(char address, char val) {
    return BMI_trans(BMI_WRITE & 0b1, address & 0b1111111, val);
}

