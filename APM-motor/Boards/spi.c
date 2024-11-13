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
/* ??????? */

/* ???????? */
#include "main.h"
 

/* ?????? */

/* ???? */

/* ?????? */

/*******************************************************************************
 * ??: SPI_FLASH_Init
 * ??: SPI?????
 * ??: ?
 * ??: ?
 * ??: ? 
 ******************************************************************************/
void SPI_Init(void)
{ 
    SPI_Config_T spiConfig;

    /* Baudrate divider is 32  */
    spiConfig.baudrateDiv = SPI_BAUDRATE_DIV_32;
    /* 2 line full duplex  */
    spiConfig.direction = SPI_DIRECTION_2LINES_FULLDUPLEX;
    /* LSB first  */
    spiConfig.firstBit = SPI_FIRST_BIT_LSB;
    /* No interrupt  */
    spiConfig.interrupt = SPI_INT_NONE;
    /* Slave mode  */
    spiConfig.mode = SPI_MODE_SLAVE;
    /* Polarity is high  */
    spiConfig.polarity = SPI_CLKPOL_HIGH;
    /* Software select slave enable  */
    spiConfig.slaveSelect = SPI_SSC_ENABLE;
    /* Phase is 2 edge  */
    spiConfig.phase = SPI_CLKPHA_2EDGE;
    /* SPI config  */
    SPI_Config(&spiConfig);

    SPI_Enable();
}

/*******************************************************************************
* Function Name  : SPI_FLASH_SendByte
* Description    : Sends a byte through the SPI interface and return the byte
*                  received from the SPI bus.
* Input          : byte : byte to send.
* Output         : None
* Return         : The value of the received byte.
*******************************************************************************/
uint8_t SPI_FLASH_SendByte(uint8_t byte)
{
  /* Loop while DR register in not emplty */
  //  while(SPI_ReadStatusFlag(SPI_FLAG_TXBE) == RESET);
        /* Write data in SPI transmit data register */
    SPI_TxData(byte);

  /* Wait to receive a byte */
 //  while(SPI_ReadStatusFlag(SPI_FLAG_RXBNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_RxData(); 
 }

/*******************************************************************************
* Function Name  : SPI_FLASH_WriteEnable
* Description    : Enables the write access to the FLASH.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_WriteEnable(void)
{
  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "Write Enable" instruction */
  SPI_FLASH_SendByte(WREN);

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();
}


/*******************************************************************************
* Function Name  : SPI_FLASH_WaitForWriteEnd
* Description    : Polls the status of the Write In Progress (WIP) flag in the
*                  FLASH's status  register  and  loop  until write  opertaion
*                  has completed.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_WaitForWriteEnd(void)
{
  uint8_t FLASH_Status = 0;

  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "Read Status Register" instruction */
  SPI_FLASH_SendByte(RDSR);

  /* Loop as long as the memory is busy with a write cycle */
  do
  {
    /* Send a dummy byte to generate the clock needed by the FLASH
    and put the value of the status register in FLASH_Status variable */
    FLASH_Status = SPI_FLASH_SendByte(Dummy_Byte);

  }
  while ((FLASH_Status & WIP_Flag) == SET); /* Write in progress */

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();
}
void W25X16_SPI_FLASH_WriteOneByte(uint8_t* pBuffer,uint32_t nSector ,uint8_t nBytes)
{
  uint8_t i=0;
  /* Enable the write access to the FLASH */
  SPI_FLASH_WriteEnable();
  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "Write to Memory " instruction */
  SPI_FLASH_SendByte(WRITE);

  /****************************************************************/
  /* Send WriteAddr high nibble address byte to write to */
  SPI_FLASH_SendByte((nSector & 0xFF0000) >> 16);
  /* Send WriteAddr medium nibble address byte to write to */
  SPI_FLASH_SendByte((nSector & 0xFF00) >> 8);
  /* Send WriteAddr low nibble address byte to write to */
  SPI_FLASH_SendByte(nSector & 0xFF);
 /*****************************************************************/
  for(i=0;i<nBytes;i++)
    SPI_FLASH_SendByte(pBuffer[i]);
  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();

  /* Wait the end of Flash writing */
  SPI_FLASH_WaitForWriteEnd();
}

/*******************************************************************************
* Function Name  : SPI_FLASH_PageWrite
* Description    : Writes more than one byte to the FLASH with a single WRITE
*                  cycle(Page WRITE sequence). The number of byte can't exceed
*                  the FLASH page size.
* Input          : - pBuffer : pointer to the buffer  containing the data to be
*                    written to the FLASH.
*                  - WriteAddr : FLASH's internal address to write to.
*                  - NumByteToWrite : number of bytes to write to the FLASH,
*                    must be equal or less than "W25X16_PAGE_SIZE" value.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
  /* Enable the write access to the FLASH */
  SPI_FLASH_WriteEnable();

  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();
  /* Send "Write to Memory " instruction */
  SPI_FLASH_SendByte(WRITE);

  /****************************************************************/
  /* Send WriteAddr high nibble address byte to write to */
  SPI_FLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
  /* Send WriteAddr medium nibble address byte to write to */
  SPI_FLASH_SendByte((WriteAddr & 0xFF00) >> 8);
  /* Send WriteAddr low nibble address byte to write to */
  SPI_FLASH_SendByte(WriteAddr & 0xFF);
 /*****************************************************************/

  /* while there is data to be written on the FLASH */
  while (NumByteToWrite--)
  {
    /* Send the current byte */
    SPI_FLASH_SendByte(*pBuffer);
    /* Point on the next byte to be written */
    pBuffer++;
  }

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();

  /* Wait the end of Flash writing */
  SPI_FLASH_WaitForWriteEnd();
}

/*******************************************************************************
* Function Name  : SPI_FLASH_BufferWrite
* Description    : Writes block of data to the FLASH. In this function, the
*                  number of WRITE cycles are reduced, using Page WRITE sequence.
* Input          : - pBuffer : pointer to the buffer  containing the data to be
*                    written to the FLASH.
*                  - WriteAddr : FLASH's internal address to write to.
*                  - NumByteToWrite : number of bytes to write to the FLASH.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
  uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

  Addr = WriteAddr % W25X16_PAGE_SIZE;
  count = W25X16_PAGE_SIZE - Addr;
  NumOfPage =  NumByteToWrite / W25X16_PAGE_SIZE;
  NumOfSingle = NumByteToWrite % W25X16_PAGE_SIZE;

  if (Addr == 0) /* WriteAddr is W25X16_PAGE_SIZE aligned  */
  {
    if (NumOfPage == 0) /* NumByteToWrite < W25X16_PAGE_SIZE */
    {
      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
    }
    else /* NumByteToWrite > W25X16_PAGE_SIZE */
    {
      while (NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, W25X16_PAGE_SIZE);
        WriteAddr +=  W25X16_PAGE_SIZE;
        pBuffer += W25X16_PAGE_SIZE;
      }

      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
    }
  }
  else /* WriteAddr is not W25X16_PAGE_SIZE aligned  */
  {
    if (NumOfPage == 0) /* NumByteToWrite < W25X16_PAGE_SIZE */
    {
      if (NumOfSingle > count)
      { /* (NumByteToWrite + WriteAddr) > W25X16_PAGE_SIZE */
        temp = NumOfSingle - count;

        SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
        WriteAddr +=  count;
        pBuffer += count;

        SPI_FLASH_PageWrite(pBuffer, WriteAddr, temp);
      }
      else
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else /* NumByteToWrite > W25X16_PAGE_SIZE */
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / W25X16_PAGE_SIZE;
      NumOfSingle = NumByteToWrite % W25X16_PAGE_SIZE;

      SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
      WriteAddr +=  count;
      pBuffer += count;

      while (NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, W25X16_PAGE_SIZE);
        WriteAddr +=  W25X16_PAGE_SIZE;
        pBuffer += W25X16_PAGE_SIZE;
      }

      if (NumOfSingle != 0)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
}

/*******************************************************************************
* Function Name  : SPI_FLASH_BufferRead
* Description    : Reads a block of data from the FLASH.
* Input          : - pBuffer : pointer to the buffer that receives the data read
*                    from the FLASH.
*                  - ReadAddr : FLASH's internal address to read from.
*                  - NumByteToRead : number of bytes to read from the FLASH.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "Read from Memory " instruction */
  SPI_FLASH_SendByte(READ);

  /* Send ReadAddr high nibble address byte to read from */
  SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
  /* Send ReadAddr medium nibble address byte to read from */
  SPI_FLASH_SendByte((ReadAddr& 0xFF00) >> 8);
  /* Send ReadAddr low nibble address byte to read from */
  SPI_FLASH_SendByte(ReadAddr & 0xFF);

  while (NumByteToRead--) /* while there is data to be read */
  {
    /* Read a byte from the FLASH */
    *pBuffer = SPI_FLASH_SendByte(Dummy_Byte);
    /* Point to the next location where the byte read will be saved */
    pBuffer++;
  }

  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();
}


/*******************************************************************************
* Function Name  : SPI_FLASH_ReadID
* Description    : Reads FLASH identification.
* Input          : None
* Output         : None
* Return         : FLASH identification
*******************************************************************************/
uint16_t SPI_FLASH_ReadID(void)
{
  uint16_t Device_ID = 0;
  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "RDID " instruction */
  SPI_FLASH_SendByte(0x90);
  
  SPI_FLASH_SendByte(0X00);
  SPI_FLASH_SendByte(0X00);
  SPI_FLASH_SendByte(0X00);
  /* Read a byte from the FLASH */
  Device_ID = (SPI_FLASH_SendByte(Dummy_Byte)<<8);
  Device_ID|=SPI_FLASH_SendByte(Dummy_Byte);
  SPI_FLASH_CS_HIGH();
  return Device_ID;
}

/*******************************************************************************
* Function Name  : SPI_FLASH_StartReadSequence
* Description    : Initiates a read data byte (READ) sequence from the Flash.
*                  This is done by driving the /CS line low to select the device,
*                  then the READ instruction is transmitted followed by 3 bytes
*                  address. This function exit and keep the /CS line low, so the
*                  Flash still being selected. With this technique the whole
*                  content of the Flash is read with a single READ instruction.
* Input          : - ReadAddr : FLASH's internal address to read from.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_StartReadSequence(uint32_t ReadAddr)
{
  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();

  /* Send "Read from Memory " instruction */
  SPI_FLASH_SendByte(READ);

  /* Send the 24-bit address of the address to read from -----------------------*/
  /* Send ReadAddr high nibble address byte */
  SPI_FLASH_SendByte((ReadAddr & 0xFF0000) >> 16);
  /* Send ReadAddr medium nibble address byte */
  SPI_FLASH_SendByte((ReadAddr& 0xFF00) >> 8);
  /* Send ReadAddr low nibble address byte */
  SPI_FLASH_SendByte(ReadAddr & 0xFF);
}

/*******************************************************************************
* Function Name  : SPI_FLASH_ReadByte
* Description    : Reads a byte from the SPI Flash.
*                  This function must be used only if the Start_Read_Sequence
*                  function has been previously called.
* Input          : None
* Output         : None
* Return         : Byte Read from the SPI Flash.
*******************************************************************************/
uint8_t SPI_FLASH_ReadByte(void)
{
  return (SPI_FLASH_SendByte(Dummy_Byte));
}

 
/*******************************************************************************
* Function Name  : SPI_FLASH_SectorErase
* Description    : Erases the specified FLASH sector.
* Input          : SectorAddr: address of the sector to erase.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_SectorErase(uint32_t SectorAddr)
{
  SectorAddr*=W25X16_SECTOR_SIZE;
  /* Send write enable instruction */
  SPI_FLASH_WriteEnable();
  /* Sector Erase */
  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();
  /* Send Sector Erase instruction */
  SPI_FLASH_SendByte(SE);
  /* Send SectorAddr high nibble address byte */
  SPI_FLASH_SendByte((SectorAddr & 0xFF0000) >> 16);
  /* Send SectorAddr medium nibble address byte */
  SPI_FLASH_SendByte((SectorAddr & 0xFF00) >> 8);
  /* Send SectorAddr low nibble address byte */
  SPI_FLASH_SendByte(SectorAddr & 0xFF);
  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();

  /* Wait the end of Flash writing */
  SPI_FLASH_WaitForWriteEnd();
}

/*******************************************************************************
* Function Name  : SPI_FLASH_BlockErase
* Description    : Erases the specified FLASH block.
* Input          : SectorAddr: address of the block to erase.
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_BlockErase(uint32_t BlockAddr)
{
  BlockAddr*=W25X16_BLOCK_SIZE;
  /* Send write enable instruction */
  SPI_FLASH_WriteEnable();
  /* Sector Erase */
  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();
  /* Send Block Erase instruction */
  SPI_FLASH_SendByte(BE);
  /* Send BlockAddr high nibble address byte */
  SPI_FLASH_SendByte((BlockAddr & 0xFF0000) >> 16);
  /* Send BlockAddr medium nibble address byte */
  SPI_FLASH_SendByte((BlockAddr & 0xFF00) >> 8);
  /* Send BlockAddr low nibble address byte */
  SPI_FLASH_SendByte(BlockAddr & 0xFF);
  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();

  /* Wait the end of Flash writing */
  SPI_FLASH_WaitForWriteEnd();
}
/*******************************************************************************
* Function Name  : SPI_FLASH_ChipErase
* Description    : Erases the entire FLASH.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_FLASH_ChipErase(void)
{
  /* Send write enable instruction */
  SPI_FLASH_WriteEnable();

  /* Select the FLASH: Chip Select low */
  SPI_FLASH_CS_LOW();
  /* Send Chip Erase instruction  */
  SPI_FLASH_SendByte(CE);
  /* Deselect the FLASH: Chip Select high */
  SPI_FLASH_CS_HIGH();

  /* Wait the end of Flash writing */
  SPI_FLASH_WaitForWriteEnd();
}



/*************** (C) COPYRIGHT ??iCreate???????? *****END OF FILE****/