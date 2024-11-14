 
/* Includes */
#include "pwm.h"
 
void pwm_init(bool ch1_P, bool ch1_N, bool ch2_P,  bool ch2_N, uint32_t frequency, uint32_t dutyCycle_1, uint32_t dutyCycle_2)
{
    TMR1_OCConfig_T ocConfigStruct;
    TMR1_TimeBaseConfig_T timeBaseConfig;
    GPIO_Config_T gpioConfig;

    // 配置GPIO
    gpioConfig.mode = GPIO_MODE_OUT_PP;
    gpioConfig.speed = GPIO_SPEED_10MHz;
    gpioConfig.intEn = GPIO_EINT_DISABLE;
    gpioConfig.pin = GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
    GPIO_Config(GPIOD, &gpioConfig);

    // 定时器基本配置
    uint32_t systemClock = 24000000; // 时钟频率24MHz
    uint32_t prescaler = (systemClock / (frequency * 1000)) - 1; 
    uint16_t period = 1000; // 周期

 
    if (prescaler > 65535) {
        prescaler = 65535;
    }

    // 定时器基底
    timeBaseConfig.cntMode = TMR1_CNT_MODE_UP;
    timeBaseConfig.count = period;
    timeBaseConfig.divider = prescaler;
    timeBaseConfig.repetitionCount = 0;
    TMR1_ConfigTimerBase(TMR1A, &timeBaseConfig);

    // 配置通道
    
        ocConfigStruct.channel =  TMR1_CHANNEL_1;
        ocConfigStruct.count = (period * dutyCycle_1) / 100; // 占空比转化为计数值
        ocConfigStruct.mode = TMR1_OC_MODE_PWM1;
        ocConfigStruct.OCxIdleState = TMR1_OC_IDLE_RESET;
        ocConfigStruct.OCxNIdleState = TMR1_OC_IDLE_RESET;
        ocConfigStruct.OCxNOutputState = ch1_N ? TMR1_OC_OUTPUT_ENABLE : TMR1_OC_OUTPUT_DISABLE;
        ocConfigStruct.OCxOutputState = ch1_P ? TMR1_OC_OUTPUT_ENABLE : TMR1_OC_OUTPUT_DISABLE;
        ocConfigStruct.OCxNPolarity = TMR1_OC_POLARITY_HIGH;
        ocConfigStruct.OCxPolarity = TMR1_OC_POLARITY_HIGH;
        TMR1_ConfigOutputCompare(TMR1A, &ocConfigStruct);
    
		    ocConfigStruct.channel =  TMR1_CHANNEL_2;
        ocConfigStruct.count = (period * dutyCycle_2) / 100; // 占空比转化为计数值
        ocConfigStruct.mode = TMR1_OC_MODE_PWM1;
        ocConfigStruct.OCxIdleState = TMR1_OC_IDLE_RESET;
        ocConfigStruct.OCxNIdleState = TMR1_OC_IDLE_RESET;
        ocConfigStruct.OCxNOutputState = ch2_N ? TMR1_OC_OUTPUT_ENABLE : TMR1_OC_OUTPUT_DISABLE;
        ocConfigStruct.OCxOutputState = ch2_P ? TMR1_OC_OUTPUT_ENABLE : TMR1_OC_OUTPUT_DISABLE;
        ocConfigStruct.OCxNPolarity = TMR1_OC_POLARITY_HIGH;
        ocConfigStruct.OCxPolarity = TMR1_OC_POLARITY_HIGH;
        TMR1_ConfigOutputCompare(TMR1A, &ocConfigStruct);
				

    // 死区
    TMR1_SetDeadTime(TMR1A, 100);

    // 配置输出关闭状态
    TMR1_SelectOffStateInRunMode(TMR1A, TMR1_OSRM_DISABLE);
    TMR1_SelectOffStateInIdleMode(TMR1A, TMR1_OSIM_DISABLE);

    // 使能PWM输出
    TMR1_EnableOutputPWM(TMR1A);

    // 使能定时器
    TMR1_Enable(TMR1A);
}


