 
/* Define to prevent recursive inclusion */
#ifndef __FLASH_H
#define __FLASH_H

#include "main.h"

#define FMC_ADDR          (0x7800)
#define FMC_PAGE_SIZE     (1024) 
 
void FLASH_Write(uint32_t *data, uint32_t size);
void FLASH_Read(uint32_t *data, uint32_t size);

#endif /*__FLASH_H */
