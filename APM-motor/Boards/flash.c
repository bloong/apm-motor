
/* Includes */
#include "flash.h"
  
/**
 * @brief 写入数据到指定地址的闪存
 * @param data 指向要写入的数据缓冲区
 * @param size 要写入的数据大小（以字节为单位）
 */
void FLASH_Write(uint32_t *data, uint32_t size)
{
    uint32_t addr = FMC_ADDR;
    uint32_t wordsToWrite = size / 4;  // 计算要写入的32位字的数量

    // 解锁闪存控制器
    FMC_Unlock();

    // 擦除页面
     /* Erase page  */
    FMC_ErasePage(FMC_ADDR);

    // 编程
    for (uint32_t i = 0; i < wordsToWrite; i++)
    {
        FMC_ProgramWord(addr, data[i]);
        addr += 4;
    }

    /* Lock flash controler  */
    FMC_Lock();
}
 

 /**
 * @brief 读取指定地址的闪存数据
 * @param data 指向存储读取数据的缓冲区
 * @param size 要读取的数据大小（以字节为单位）
 */
void FLASH_Read(uint32_t *data, uint32_t size)
{
    uint32_t *p = (uint32_t *)FMC_ADDR;
    uint32_t wordsToRead = size / 4;  // 计算要读取的32位字的数量

    // 读取数据
    for (uint32_t i = 0; i < wordsToRead; i++)
    {
        data[i] = p[i];
    }
}