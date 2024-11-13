
///* Includes */
#include "i2c.h"


//uint8_t dataBufPt = 0;
//uint8_t txDataBuf[DATA_BUF_SIZE] = {0};
//uint8_t rxDataBuf[DATA_BUF_SIZE] = {0};

///* Direction. RX or TX  */
//I2C_DIRECTION_T i2cDirection = I2C_DIRECTION_TX;


///*!
// * @brief       I2C Init
// *
// * @param       None
// *
// * @retval      None
// */
void I2C_Init(void)
{
    I2C_Config_T i2cConfig;

    /* ACK when current byte being received  */
    i2cConfig.ack = I2C_ACK_CURRENT;
    /* Set Address  */
    i2cConfig.addr = SLAVE_ADDR;
    /* 7-bit address */
    i2cConfig.addrMode = I2C_ADDR_7_BIT;
    /* duty cycle = 2 */
    i2cConfig.dutyCycle = I2C_DUTYCYCLE_2;
    /* Input clock frequency is 48MHZ */
    i2cConfig.inputClkFreqMhz = 48;
    /* Disable interrupt */
    i2cConfig.interrupt = I2C_INT_NONE;
    /* Output clock frequency is 100KHZ */
    i2cConfig.outputClkFreqHz = 100000;
    I2C_Config(&i2cConfig);

    /* Enable I2C */
    I2C_Enable();
}

//uint8_t I2C_ReadRegister(uint8_t deviceAddr, uint8_t regAddr, uint8_t *dataBuf, uint16_t bufSize)
//{
//    // Write register address to select the register
//    I2C_ConfigAcknowledge(I2C_ACK_CURRENT);
//    while(I2C_ReadStatusFlag(I2C_FLAG_BUSBUSY) == SET);
//    I2C_EnableGenerateStart();
//    while(I2C_ReadStatusFlag(I2C_FLAG_START) == RESET);
//    I2C_TxAddress7Bit(deviceAddr, I2C_DIRECTION_TX); // Send device address in write mode
//    while(I2C_ReadStatusFlag(I2C_FLAG_ADDR) == RESET);
//    (void)I2C->STS3;
//    I2C_RxData(regAddr); // Send register address

//    // Read data from the selected register
//    while(I2C_ReadStatusFlag(I2C_FLAG_BUSBUSY) == SET);
//    I2C_EnableGenerateStart();
//    while(I2C_ReadStatusFlag(I2C_FLAG_START) == RESET);
//    I2C_TxAddress7Bit(deviceAddr, I2C_DIRECTION_RX); // Send device address in read mode
//    while(I2C_ReadStatusFlag(I2C_FLAG_ADDR) == RESET);
//    (void)I2C->STS3;

//    uint16_t bytesRead = 0;
//    while(bytesRead < bufSize)
//    {
//        if((I2C_ReadStatusFlag(I2C_FLAG_RXBNE) == SET) && (I2C_ReadStatusFlag(I2C_FLAG_RWMF) == RESET))
//        {
//            if(bytesRead == (bufSize - 1)) // Last byte
//            {
//                I2C_ConfigAcknowledge(I2C_ACK_NONE);
//                I2C_EnableGenerateStop();
//            }
//            dataBuf[bytesRead++] = I2C_RxData();
//        }
//    }

//    return bytesRead; // Return number of bytes read
//}

//uint8_t I2C_WriteRegister(uint8_t deviceAddr, uint8_t regAddr, const uint8_t *dataBuf, uint16_t bufSize)
//{
//    uint16_t bytesWritten = 0;

//    /* Wait for the bus to be idle */
//    while (I2C_ReadStatusFlag(I2C_FLAG_BUSBUSY) == SET);

//    /* Generate a start condition */
//    I2C_EnableGenerateStart();

//    /* Wait for the start condition to be generated */
//    while (I2C_ReadStatusFlag(I2C_FLAG_START) == RESET);

//    /* Send the device address in write mode */
//    I2C_TxAddress7Bit(deviceAddr, I2C_DIRECTION_TX);

//    /* Wait for the address to be acknowledged */
//    while (I2C_ReadStatusFlag(I2C_FLAG_ADDR) == RESET);
//    (void)I2C->STS3;

//    /* Send the register address */
//    I2C_TxData(regAddr);

//    /* Wait for the register address to be acknowledged */
//    while (I2C_ReadStatusFlag(I2C_FLAG_RWMF | I2C_FLAG_TXBE) != SET);

//    /* Send the data buffer */
//    while (bytesWritten < bufSize)
//    {
//        /* Wait for the transmit buffer to be empty and the write mode to be active */
//        while (I2C_ReadStatusFlag(I2C_FLAG_RWMF | I2C_FLAG_TXBE) != SET);

//        /* Send the next byte of data */
//        I2C_TxData(dataBuf[bytesWritten++]);

//        /* If this is the last byte, generate a stop condition */
//        if (bytesWritten == bufSize)
//        {
//            I2C_EnableGenerateStop();
//        }
//    }

//    return bytesWritten; // Return the number of bytes written
//}