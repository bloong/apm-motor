 
/* Define to prevent recursive inclusion */
#ifndef __I2C_H
#define __I2C_H

#include "main.h"

/* Master address  */
#define MASTER_ADDR         (0XA0)
/* Slave address  */
#define SLAVE_ADDR          (0XB0)

#define DATA_BUF_SIZE       (32)



void I2C_Init(void);
void DataBufInit(void);

uint8_t I2C_ReadRegister(uint8_t deviceAddr, uint8_t regAddr, uint8_t *dataBuf, uint16_t bufSize);
uint8_t I2C_WriteRegister(uint8_t deviceAddr, uint8_t regAddr, const uint8_t *dataBuf, uint16_t bufSize);

#endif /*__I2C_H */
