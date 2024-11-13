 
/* Includes */
#include "eint.h"
 
 
/*!
 * @brief       Key interrupt server routine
 *
 * @param       None
 *
 * @retval      None
 */
 
int a,b,c,d;
 
void Key_Isr(void)
{
	 if(APM_MINI_ReadPBState(BUTTON_KEY1) == BIT_RESET)
	 { 
		  a++;
	 }
	 if(APM_MINI_ReadPBState(BUTTON_KEY2) == BIT_RESET)
	 {
		 	b++;
	 }
	 if(APM_MINI_ReadPBState(BUTTON_KEY3) == BIT_RESET)
	 {
			c++; 
	 }
	 if(APM_MINI_ReadPBState(BUTTON_KEY4) == BIT_RESET)
	 {
		 	d++; 
	 }
	 EINT_ClearIntFlag(EINT_PORT_C);
   EINT_ClearIntFlag(EINT_PORT_D);
}


/*!
 * @brief       Configure OSCIN and OSCOUT as normal GPIO
 *
 * @param       None
 *
 * @retval      None
 */
void GPIOA_Init(void)
{
    GPIO_Config_T gpioConfig;

    gpioConfig.mode = GPIO_MODE_OUT_OD;
    gpioConfig.speed = GPIO_SPEED_10MHz;
    gpioConfig.intEn = GPIO_EINT_DISABLE;
    gpioConfig.pin = GPIO_PIN_1 | GPIO_PIN_2;
    GPIO_Config(GPIOA, &gpioConfig);
}
