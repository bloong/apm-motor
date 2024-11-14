
/* Define to prevent recursive inclusion */
#ifndef __MAIN_H
#define __MAIN_H

/* Includes */
#include <stdio.h>
#include <stdint.h>

#include "apm32f00x.h"
#include "Board.h"
#include "apm32f00x_gpio.h"
#include "apm32f00x_misc.h"
#include "apm32f00x_rcm.h"
#include "apm32f00x_adc.h"
#include "apm32f00x_i2c.h"
#include "apm32f00x_spi.h"
#include "apm32f00x_tmr1.h"
#include "apm32f00x_tmr2.h"
#include "apm32f00x_fmc.h"
#include "apm32f00x_usart.h"
#include "pwm.h"
#include "moto.h"
#include "spi.h"
#include "i2c.h"
#include "key.h"
#include "eint.h"
#include "flash.h"
#include "lis3dhtr.h"
#include "tm1650.h"
#include "tm1650_config.h"
 #include "err.h"

extern uint32_t sysTick;


struct sys_status
{
  


    uint32_t err;
};
 





#endif /*__MAIN_H */
