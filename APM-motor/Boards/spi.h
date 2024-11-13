/*************** (C) COPYRIGHT  ??iCreate???????? ********************
 * ???  :spi_flash.c
 * ??    :SPI?????????  
 * ????:iCreate STM8???
 * ???  :V2.1.0
 * ??    :ling_guansheng  QQ:779814207
 * ??    :
 *???? :2012-11-20
  iCreate STM8???????
    |--------------------|
    |  SPI_CS---PE6      |
    |  SPI_MISO-PC7      |
    |  SPI_MOSI-PC6      |
    |  SPI_CLK--PC5      |
    |--------------------|
*******************************************************************************/
#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H


/* ??????? */

/* ???????? */
#include "main.h"


/* ?????? */
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* ???? */
#define SPI_CS                   GPIOA
#define SPI_Pin_CS               GPIO_PIN_3
#define W25X16_PAGE_SIZE         256
#define W25X16_SECTOR_SIZE	 4096
#define W25X16_SECTOR_COUNT	 512
#define W25X16_BLOCK_SIZE	 65536
#define W25X16_PAGES_PER_SECTOR	W25X16_SECTOR_SIZE/W25X16_PAGE_SIZE
#define WRITE      0x02  /* Write to Memory instruction */
#define WRSR       0x01  /* Write Status Register instruction */
#define WREN       0x06  /* Write enable instruction */

#define READ       0x03  /* Read from Memory instruction */
#define RDSR       0x05  /* Read Status Register instruction  */
#define RDID       0x9F  /* Read identification */
#define SE         0x20  /*Sector Erase instruction*/
#define BE         0xD8  /* Block Erase instruction */
#define CE         0xC7  /* Bulk Erase instruction */

#define WIP_Flag   0x01  /* Write In Progress (WIP) flag */

#define Dummy_Byte 0xFF

#define  FLASH_WriteAddress     18*W25X16_BLOCK_SIZE
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress

/* ??SPI????,??CS???? */
#define SPI_FLASH_CS_LOW()       APM_MINI_LEDOn(LED2);
/* ??SPI????,??CS???? */
#define SPI_FLASH_CS_HIGH()      APM_MINI_LEDOff(LED2);



  
	
	
/* ?????? */


/*******************************************************************************
 * ??: SPI_FLASH_Init
 * ??: SPI?????
 * ??: ?
 * ??: ?
 * ??: ? 
 ******************************************************************************/
void SPI_Init(void);

uint8_t SPI_FLASH_SendByte(uint8_t byte);
void SPI_FLASH_WriteEnable(void);
void SPI_FLASH_WaitForWriteEnd(void);
void SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
uint16_t SPI_FLASH_ReadID(void);
void SPI_FLASH_StartReadSequence(uint32_t ReadAddr);
uint8_t SPI_FLASH_ReadByte(void);
uint16_t SPI_FLASH_SendHalfWord(uint16_t HalfWord);
void SPI_FLASH_SectorErase(uint32_t SectorAddr);
void SPI_FLASH_BlockErase(uint32_t BlockAddr);
void SPI_FLASH_ChipErase(void);
void W25X16_SPI_FLASH_WriteOneByte(uint8_t* pBuffer,uint32_t nSector ,uint8_t nBytes);

#endif

/******************* (C) COPYRIGHT ??iCreate???????? *****END OF FILE****/

