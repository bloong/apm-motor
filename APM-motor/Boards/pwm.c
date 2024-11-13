 
/* Includes */
#include "pwm.h"
 
/*!
 * @brief       TMR1 Init
 *
 * @param       None
 *
 * @retval      None
 */
//void TMR1_Init(void)
//{
//    TMR1_OCConfig_T ocConfigStruct;
//    TMR1_TimeBaseConfig_T timeBaseConfig;
//    
//	  GPIO_Config_T gpioConfig;

//    gpioConfig.mode = GPIO_MODE_OUT_PP;
//    gpioConfig.speed = GPIO_SPEED_10MHz;
//    gpioConfig.intEn = GPIO_EINT_DISABLE;
//    gpioConfig.pin = GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;

//    GPIO_Config(GPIOD, &gpioConfig);
//	
//    /* Up-counter */
//    timeBaseConfig.cntMode = TMR1_CNT_MODE_UP;
//    /* Set counter = 250 */
//    timeBaseConfig.count = 250; //2kHz    500 1Khz   
//    /* Set divider = 47.So TMR1 clock freq ~= 24/(47 + 1) = 500KHZ */
//    timeBaseConfig.divider = 47;
//    /* Repetition counter = 0x0 */
//    timeBaseConfig.repetitionCount = 0;
//    TMR1_ConfigTimerBase(TMR1A, &timeBaseConfig);

//    /* Select channen1 1 */
//    ocConfigStruct.channel = TMR1_CHANNEL_1;
//    /* Set compare value = 0x7D */
//    ocConfigStruct.count = 0x32;
//    /* PWM1 mode */
//    ocConfigStruct.mode = TMR1_OC_MODE_PWM1;
//    /* Idle State is reset */
//    ocConfigStruct.OCxIdleState = TMR1_OC_IDLE_RESET;
//    /* Idle State is reset */
//    ocConfigStruct.OCxNIdleState = TMR1_OC_IDLE_RESET;
//    /* Enable CH1N ouput */
//    ocConfigStruct.OCxNOutputState = TMR1_OC_OUTPUT_ENABLE;
//    /* Enable CH1 ouput */
//    ocConfigStruct.OCxOutputState = TMR1_OC_OUTPUT_ENABLE;
//    /* CH1N polarity is high */
//    ocConfigStruct.OCxNPolarity = TMR1_OC_POLARITY_HIGH;
//    /* CH1 polarity is high */
//    ocConfigStruct.OCxPolarity = TMR1_OC_POLARITY_HIGH;
//    TMR1_ConfigOutputCompare(TMR1A, &ocConfigStruct);
//  
//	  /* Select channen1 1 */
//    ocConfigStruct.channel = TMR1_CHANNEL_2;
//    /* Set compare value = 0x7D */
//    ocConfigStruct.count = 1;
//    /* PWM1 mode */
//    ocConfigStruct.mode = TMR1_OC_MODE_PWM1;
//    /* Idle State is reset */
//    ocConfigStruct.OCxIdleState = TMR1_OC_IDLE_RESET;
//    /* Idle State is reset */
//    ocConfigStruct.OCxNIdleState = TMR1_OC_IDLE_RESET;
//    /* Enable CH1N ouput */
//    ocConfigStruct.OCxNOutputState = TMR1_OC_OUTPUT_ENABLE;
//    /* Enable CH1 ouput */
//    ocConfigStruct.OCxOutputState = TMR1_OC_OUTPUT_ENABLE;
//    /* CH1N polarity is high */
//    ocConfigStruct.OCxNPolarity = TMR1_OC_POLARITY_HIGH;
//    /* CH1 polarity is high */
//    ocConfigStruct.OCxPolarity = TMR1_OC_POLARITY_HIGH;
//    TMR1_ConfigOutputCompare(TMR1A, &ocConfigStruct);
//		
//    /* Set dead time */
//    TMR1_SetDeadTime(TMR1A, 100);
//    /* Disable output when CHx output closed */
//    TMR1_SelectOffStateInRunMode(TMR1A, TMR1_OSRM_DISABLE);
//    /* Disable output when CHxN output closed */
//    TMR1_SelectOffStateInIdleMode(TMR1A, TMR1_OSIM_DISABLE);

//    /* Enable PWM output */
//    TMR1_EnableOutputPWM(TMR1A);

//    /* Enable TMR1  */
//    TMR1_Enable(TMR1A);
//}



void pwm_init(bool ch1_P, bool ch1_N, bool ch2_P,  bool ch2_N, uint32_t frequency, uint32_t dutyCycle_1, uint32_t dutyCycle_2)
{
    TMR1_OCConfig_T ocConfigStruct;
    TMR1_TimeBaseConfig_T timeBaseConfig;
    GPIO_Config_T gpioConfig;

    // ����GPIO
    gpioConfig.mode = GPIO_MODE_OUT_PP;
    gpioConfig.speed = GPIO_SPEED_10MHz;
    gpioConfig.intEn = GPIO_EINT_DISABLE;
    gpioConfig.pin = GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
    GPIO_Config(GPIOD, &gpioConfig);

    // ��ʱ����������
    uint32_t systemClock = 24000000; // ʱ��Ƶ��24MHz
    uint32_t prescaler = (systemClock / (frequency * 1000)) - 1; 
    uint16_t period = 1000; // ����

 
    if (prescaler > 65535) {
        prescaler = 65535;
    }

    // ��ʱ������
    timeBaseConfig.cntMode = TMR1_CNT_MODE_UP;
    timeBaseConfig.count = period;
    timeBaseConfig.divider = prescaler;
    timeBaseConfig.repetitionCount = 0;
    TMR1_ConfigTimerBase(TMR1A, &timeBaseConfig);

    // ����ͨ��
    
        ocConfigStruct.channel =  TMR1_CHANNEL_1;
        ocConfigStruct.count = (period * dutyCycle_1) / 100; // ռ�ձ�ת��Ϊ����ֵ
        ocConfigStruct.mode = TMR1_OC_MODE_PWM1;
        ocConfigStruct.OCxIdleState = TMR1_OC_IDLE_RESET;
        ocConfigStruct.OCxNIdleState = TMR1_OC_IDLE_RESET;
        ocConfigStruct.OCxNOutputState = ch1_N ? TMR1_OC_OUTPUT_ENABLE : TMR1_OC_OUTPUT_DISABLE;
        ocConfigStruct.OCxOutputState = ch1_P ? TMR1_OC_OUTPUT_ENABLE : TMR1_OC_OUTPUT_DISABLE;
        ocConfigStruct.OCxNPolarity = TMR1_OC_POLARITY_HIGH;
        ocConfigStruct.OCxPolarity = TMR1_OC_POLARITY_HIGH;
        TMR1_ConfigOutputCompare(TMR1A, &ocConfigStruct);
    
		    ocConfigStruct.channel =  TMR1_CHANNEL_2;
        ocConfigStruct.count = (period * dutyCycle_2) / 100; // ռ�ձ�ת��Ϊ����ֵ
        ocConfigStruct.mode = TMR1_OC_MODE_PWM1;
        ocConfigStruct.OCxIdleState = TMR1_OC_IDLE_RESET;
        ocConfigStruct.OCxNIdleState = TMR1_OC_IDLE_RESET;
        ocConfigStruct.OCxNOutputState = ch2_N ? TMR1_OC_OUTPUT_ENABLE : TMR1_OC_OUTPUT_DISABLE;
        ocConfigStruct.OCxOutputState = ch2_P ? TMR1_OC_OUTPUT_ENABLE : TMR1_OC_OUTPUT_DISABLE;
        ocConfigStruct.OCxNPolarity = TMR1_OC_POLARITY_HIGH;
        ocConfigStruct.OCxPolarity = TMR1_OC_POLARITY_HIGH;
        TMR1_ConfigOutputCompare(TMR1A, &ocConfigStruct);
				

    // ����
    TMR1_SetDeadTime(TMR1A, 100);

    // ��������ر�״̬
    TMR1_SelectOffStateInRunMode(TMR1A, TMR1_OSRM_DISABLE);
    TMR1_SelectOffStateInIdleMode(TMR1A, TMR1_OSIM_DISABLE);

    // ʹ��PWM���
    TMR1_EnableOutputPWM(TMR1A);

    // ʹ�ܶ�ʱ��
    TMR1_Enable(TMR1A);
}


