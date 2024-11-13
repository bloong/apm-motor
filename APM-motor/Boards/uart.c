 
/* Includes */
#include "uart.h"

uint8_t txDataPt = 0;
uint8_t txDataBufUSART2[DATA_BUF_SIZE] = {0};
uint8_t rxDataPt = 0;
uint8_t rxDataBufUSART2[DATA_BUF_SIZE] = {0};


/*!
 * @brief       USART Init
 *
 * @param       None
 *
 * @retval      None
 */
void USART_Init(void)
{
    USART_Config_T usartConfig;

    /*  BaudRate is 9600 */
    usartConfig.baudRate = 9600;
    /*  Receiver interrupt */
    usartConfig.interrupt = USART_INT_RX;
    /*  Enable receiver */
    usartConfig.mode = USART_MODE_RX;
    /*  Parity disable */
    usartConfig.parity = USART_PARITY_NONE;
    /*  One stop bit */
    usartConfig.stopBits = USART_STOP_BIT_1;
    /*  Word length is 8bit */
    usartConfig.wordLength = USART_WORD_LEN_8B;
  
    /*  Transmitter interrupt */
    usartConfig.interrupt = USART_INT_TX;
    /*  Enable transmitter */
    usartConfig.mode = USART_MODE_TX;
    /*  USART2 configuration */
    USART_Config(USART2, &usartConfig);


    /*  Enable USART2 */
    USART_Enable(USART2);

    /*  Enable USART2 transmitter IRQ request */
    NVIC_EnableIRQRequest(USART2_TX_IRQn, 0x01);
}


/*!
 * @brief       USART2 transmitter interrupt service routine
 *
 * @param       None
 *
 * @retval      None
 */
void USART2_TxIsr(void)
{
    if(USART_ReadIntFlag(USART2, USART_INT_FLAG_TX) == SET)
    {
        if(txDataPt < DATA_BUF_SIZE)
        {
            USART_TxData8(USART2, txDataBufUSART2[txDataPt++]);
        }
        else
        {
            /* Disable USART2 transmitter interrupt */
            USART_DisableInterrupt(USART2, USART_INT_TX);
        }
    }
}

/*!
 * @brief       USART1 receiver interrupt service routine
 *
 * @param       None
 *
 * @retval      None
 */
void USART2_RxIsr(void)
{
    if(USART_ReadIntFlag(USART2, USART_INT_FLAG_RX) == SET)
    {
        if(rxDataPt < DATA_BUF_SIZE)
        {
            rxDataBufUSART2[rxDataPt++] = USART_RxData8(USART2);
        }
        else
        {
            /* Disable USART1 receiver interrupt */
            USART_DisableInterrupt(USART2, USART_INT_RX);
        }
    }
}
 
 