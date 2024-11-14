  
/* Includes */
#include "main.h"
 
#define  DEBUG
 
#define DATA_BUF_SIZE       (16)
#define DEBUG_USART         USART2

uint8_t rxDataBuf[DATA_BUF_SIZE] = {'h','e','l','l','o',',','w','o','r','l','d','!'};

struct sys_status sys;

/* System tick */
uint32_t sysTick = 0;
uint8_t lisid;
uint8_t Key_name=0;
uint8_t response=0;
void ClockOutputInit(void);
void FMC_OPT(void);
int aaa=0;

uint16_t pwm_L=30,pwm_R=30;

/* USART Init */
void USART_Init(void);

 
  
int main(void)
{
	
   //	   MotorControlSystem mcs;
   //    motor_control_init(&mcs, 1.0, 0.1, 0.05, 0.5, 0.05, 0.02, 0.8, 0.02, 0.01);
	 	     
	    APM_DelayInit(APM_DELAY_MS);
		APM_Delay(2000);
 
        init_beep(&sm);

		// 假设系统遇到了内存错误和网络错误
		sys.err = set_error_flag(sys.err, E1_SHOCK);
 
		// 检查内存错误是否置位
		if (is_error_flag_set(sys.err, E1_SHOCK)) {
			printf("Memory error is set.\n");
		} else {
			printf("Memory error is not set.\n");
		}

       FMC_OPT();    
   
     //USART_Init();
 

	  //RCM_SwitchClockStruct_T switchClockStruct;

    /* Setup SysTick Timer for 1 msec interrupts */
    //  SysTick_Config(RCM_GetMasterClockFreq() / 1000);

//      APM_MINI_LEDInit(LED1); //PD1
//      APM_MINI_LEDInit(LED2); //PD4
//	    APM_MINI_LEDInit(LED3); //PD5
//      APM_MINI_LEDInit(LED4); //PD6
	
    //  APM_MINI_LEDOn(LED2);
    //  APM_MINI_LEDOn(LED3);
   //   APM_MINI_LEDToggle(LED2);


//      APM_MINI_PBInit(BUTTON_KEY1, BUTTON_MODE_EINT);  //PD2
//      APM_MINI_PBInit(BUTTON_KEY2, BUTTON_MODE_EINT);  //PD3
//      APM_MINI_PBInit(BUTTON_KEY3, BUTTON_MODE_EINT);  //PC3
//      APM_MINI_PBInit(BUTTON_KEY4, BUTTON_MODE_EINT);  //PC4
 
  	//  lis3dhinit();
	  //  LIS3DH_GetWHO_AM_I(&lisid);
    //  I2C_Init();
   
     TM1650_init();
     TM1650_cfg_display( TM1650_BRIGHT5 );
     TM1650_clear();
     
 //   ClockOutputInit();
  //  moto_stop();
		 
 
    while(1)
    {
// 				for(int i=0; i<100; i++)
// 				{
// 					 moto(i,i) ;
// 					 APM_Delay(200);
//                   beep_loop(&sm);
// 				}
				 
	          printf("123456\r\n");

	 		  APM_Delay(1000);

				Key_name=TM1650_Get_KEY()%100/10;
				if(Key_name <= 6 && Key_name >= 1)
				{
						TM1650_print(TM1650_DIG3,TUBE_TABLE_0[Key_name]);
					  if(Key_name == 1)
						{
							  moto(true, false, true, false, pwm_L, pwm_R);
						}
						
						if(Key_name == 2)
						{
						 	  moto(false, true, false, true, pwm_L, pwm_R);
						}
						  
						if(Key_name == 3)
						{
							 pwm_L += 10; 
						   pwm_R += 10; 
						}
						
						if(Key_name == 4)
						{
							 pwm_L -= 10; 
						   pwm_R -= 10; 
						}
						
						 if(Key_name == 5)
						{
							 pwm_L = 0; 
						   pwm_R = 0; 
						}
						
					  if(Key_name == 6)
						{
							 pwm_L = 100; 
						   pwm_R = 100; 
						}
						
						if(pwm_L > 100)
						{
						    pwm_L = 100;
						}
										
						if(pwm_R > 100)
						{
						    pwm_R = 100;
						}		
						
						if(pwm_L < 0)
						{
						    pwm_L = 0;
						}	
						
						if(pwm_R < 0)
						{
						    pwm_R = 0;
						}	
									 
						TM1650_print(TM1650_DIG1,TUBE_TABLE_0[pwm_L/10]);
						TM1650_print(TM1650_DIG2,TUBE_TABLE_0[pwm_L%10]);
 		    }
				else
				{
						 moto(false, false, false, false, 0, 0);
				}
				 
			  if(sysTick >= 500)
				{		  
							sysTick = 0; 				 
				}
				
		}
}



//			if(APM_MINI_ReadPBState(BUTTON_KEY1) == BIT_RESET)
//			 { 
//				 APM_MINI_LEDOn(LED2);
//			 }
//			  if(APM_MINI_ReadPBState(BUTTON_KEY2) == BIT_RESET)
//			 {
//					APM_MINI_LEDOn(LED2);
//			 }
//			else if(APM_MINI_ReadPBState(BUTTON_KEY3) == BIT_RESET)
//			 {
//					 APM_MINI_LEDOn(LED2);
//			 }
//			else if(APM_MINI_ReadPBState(BUTTON_KEY4) == BIT_RESET)
//			 {
//					APM_MINI_LEDOn(LED2);
//			 }
//			 else
//			 {
//			 		  APM_MINI_LEDOff(LED2);
//			 }



void FMC_OPT(void)
{
    FMC_AFRConfig_T AFRConfig;

    AFRConfig.AFR0 = FMC_OB_AFR_DISABLE;
    AFRConfig.AFR1 = FMC_OB_AFR_DISABLE;
    AFRConfig.AFR3 = FMC_OB_AFR_DISABLE;
    AFRConfig.AFR4 = FMC_OB_AFR_DISABLE;
    AFRConfig.AFR5 = FMC_OB_AFR_ENABLE;
    AFRConfig.AFR7 = FMC_OB_AFR_DISABLE;

//    if((OB->AFR != 0x01FE))
    {
        FMC_Unlock();
        FMC_EraseOptionByte();
        FMC_ConfigOptionByteAFR(&AFRConfig);
        FMC_Lock();
//        while(OB->AFR!= 0x01FE);
 //       NVIC_SystemReset();
    }
}

/*!
 * @brief       Clock output init
 *
 * @param       None
 *
 * @retval      None
 */
void ClockOutputInit(void)
{
    GPIO_Config_T gpioConfig;

    /* GPIO configuration  */
    gpioConfig.mode = GPIO_MODE_OUT_PP;
    gpioConfig.pin = GPIO_PIN_4;
    gpioConfig.speed = GPIO_SPEED_10MHz;
    GPIO_Config(GPIOC, &gpioConfig);

    /* master clock freq = 48MHZ / 2 = 24MHZ  */
    RCM_ConfigHIRCDiv(RCM_HIRC_DIV_2);

    /* master clock as clock output  */
    RCM_ConfigClockOutput(RCM_COCCLK_MASTER);
    RCM_EnableClockOutput();
}

/**@} end of group SysTick_Functions */
/**@} end of group SysTick */
/**@} end of group Examples */





#if defined (__CC_ARM) || defined (__ICCARM__) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))

/*!
* @brief       Redirect C Library function printf to serial port.
*              After Redirection, you can use printf function.
*
* @param       ch:  The characters that need to be send.
*
* @param       *f:  pointer to a FILE that can recording all information
*              needed to control a stream
*
* @retval      The characters that need to be send.
*/
int fputc(int ch, FILE* f)
{
    /* send a byte of data to the serial port */
    USART_TxData8(DEBUG_USART, (uint8_t)ch);

    /* wait for the data to be send */
    while (USART_ReadStatusFlag(DEBUG_USART, USART_FLAG_TXBE) == RESET);

    return (ch);
}

#elif defined (__GNUC__)

/*!
* @brief       Redirect C Library function printf to serial port.
*              After Redirection, you can use printf function.
*
* @param       ch:  The characters that need to be send.
*
* @retval      The characters that need to be send.
*/
int __io_putchar(int ch)
{
    /* send a byte of data to the serial port */
    USART_TxData8(DEBUG_USART, ch);

    /* wait for the data to be send  */
    while (USART_ReadStatusFlag(DEBUG_USART, USART_FLAG_TXBE) == RESET);

    return ch;
}

/*!
* @brief       Redirect C Library function printf to serial port.
*              After Redirection, you can use printf function.
*
* @param       file:  Meaningless in this function.
*
* @param       *ptr:  Buffer pointer for data to be sent.
*
* @param       len:  Length of data to be sent.
*
* @retval      The characters that need to be send.
*/
int _write(int file, char *ptr, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        __io_putchar(*ptr++);
    }

    return len;
}

#else
  #warning Not supported compiler type
#endif
