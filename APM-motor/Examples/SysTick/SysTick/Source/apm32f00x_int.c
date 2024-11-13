/*!
 * @file        apm32f00x_int.c
 *
 * @brief       Main Interrupt Service Routines
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

/* Includes */
#include "apm32f00x_int.h"

/** @addtogroup Examples
  @{
*/

/** @addtogroup SysTick
  @{
*/

uint8_t PWMStep = 0;


/** @defgroup SysTick_INT_Functions INT_Functions
  @{
*/

/*!
 * @brief       This function handles NMI exception
 *
 * @param       None
 *
 * @retval      None
 */
void NMI_Handler(void)
{
}

/*!
 * @brief       This function handles Hard Fault exception
 *
 * @param       None
 *
 * @retval      None
 */
void HardFault_Handler(void)
{

}

/*!
 * @brief       This function handles SVCall exception
 *
 * @param       None
 *
 * @retval      None
 */
void SVC_Handler(void)
{
}

/*!
 * @brief       This function handles PendSV_Handler exception
 *
 * @param       None
 *
 * @retval      None
 */
void PendSV_Handler(void)
{
}

/*!
 * @brief       This function handles SysTick exception
 *
 * @param       None
 *
 * @retval      None
 */
void SysTick_Handler(void)
{
    sysTick++;
	  APM_DelayIsr();
}

/*!
 * @brief       This function handles EINTD exception
 *
 * @param       None
 *
 * @retval      None
 */
void EINTD_IRQHandler(void)
{
    Key_Isr();
}

/*!
 * @brief       This function handles USART1 receiver exception
 *
 * @param       None
 *
 * @retval      None
 */
void USART2_RX_IRQHandler(void)
{
    USART2_RxIsr();
}

/*!
 * @brief       This function handles USART1 transmitter exception
 *
 * @param       None
 *
 * @retval      None
 */
void USART2_TX_IRQHandler(void)
{
    USART2_TxIsr();
}


/**@} end of group SysTick_INT_Functions */
/**@} end of group SysTick */
/**@} end of group Examples */
