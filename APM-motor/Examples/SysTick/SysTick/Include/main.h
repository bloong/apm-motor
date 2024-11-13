/*!
 * @file        main.h
 *
 * @brief       Header for main.c module
 *
 * @version     V1.0.2
 *
 * @date        2023-03-31
 *
 * @attention
 *
 *  Copyright (C) 2023 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __MAIN_H
#define __MAIN_H

/* Includes */
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
#include <stdio.h>





/** @addtogroup Examples
  @{
*/

/** @addtogroup SysTick
  @{
*/

/** @defgroup SysTick_Variables Variables
  @{
*/

extern uint32_t sysTick;

/**@} end of group SysTick_Variables */
/**@} end of group SysTick */
/**@} end of group Examples */

#endif /*__MAIN_H */
