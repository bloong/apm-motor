
/* Includes */
#include "beep.h"

#include <stdio.h>
 
StateMachine g_beep_sm;


// 辅助函数：模拟蜂鸣器鸣响
void beep()
{
    printf("Beep!\n");
}

// 辅助函数：模拟蜂鸣器静音
void silent()
{
    printf("Silent\n");
}

// 处理静音状态
void handle_silent(StateMachine *sm, Input input)
{
    switch (input)
    {
    case INPUT_SET_SILENT:
        sm->current_state = STATE_SILENT;
        break;
    case INPUT_SET_CONTINUOUS_BEEP:
        sm->current_state = STATE_CONTINUOUS_BEEP;
        break;
    case INPUT_SET_INTERMITTENT_BEEP:
        sm->current_state = STATE_INTERMITTENT_BEEP;
        break;
    case INPUT_SET_FAST_BEEP:
        sm->current_state = STATE_FAST_BEEP;
        break;
    }
    sm->handle_input = handle_silent;
}

// 处理连续鸣响状态
void handle_continuous_beep(StateMachine *sm, Input input)
{
    beep();
    switch (input)
    {
    case INPUT_SET_SILENT:
        sm->current_state = STATE_SILENT;
        break;
    case INPUT_SET_CONTINUOUS_BEEP:
        sm->current_state = STATE_CONTINUOUS_BEEP;
        break;
    case INPUT_SET_INTERMITTENT_BEEP:
        sm->current_state = STATE_INTERMITTENT_BEEP;
        break;
    case INPUT_SET_FAST_BEEP:
        sm->current_state = STATE_FAST_BEEP;
        break;
    }
    sm->handle_input = handle_continuous_beep;
}

// 处理间歇鸣响状态
void handle_intermittent_beep(StateMachine *sm, Input input)
{
    static int counter = 0;
    if (counter < sm->config.count)
    {
        beep();
        counter++;
    }
    else
    {
        counter = 0;
    }
  //  usleep(sm->config.frequency_ms * 1000);
    switch (input)
    {
    case INPUT_SET_SILENT:
        sm->current_state = STATE_SILENT;
        break;
    case INPUT_SET_CONTINUOUS_BEEP:
        sm->current_state = STATE_CONTINUOUS_BEEP;
        break;
    case INPUT_SET_INTERMITTENT_BEEP:
        sm->current_state = STATE_INTERMITTENT_BEEP;
        break;
    case INPUT_SET_FAST_BEEP:
        sm->current_state = STATE_FAST_BEEP;
        break;
    }
    sm->handle_input = handle_intermittent_beep;
}

// 处理快速鸣响状态
void handle_fast_beep(StateMachine *sm, Input input)
{
    static int counter = 0;
    if (counter < sm->config.count)
    {
        beep();
        counter++;
    }
    else
    {
        counter = 0;
    }
  //  usleep(sm->config.frequency_ms * 1000);
    switch (input)
    {
    case INPUT_SET_SILENT:
        sm->current_state = STATE_SILENT;
        break;
    case INPUT_SET_CONTINUOUS_BEEP:
        sm->current_state = STATE_CONTINUOUS_BEEP;
        break;
    case INPUT_SET_INTERMITTENT_BEEP:
        sm->current_state = STATE_INTERMITTENT_BEEP;
        break;
    case INPUT_SET_FAST_BEEP:
        sm->current_state = STATE_FAST_BEEP;
        break;
    }
    sm->handle_input = handle_fast_beep;
}

// 初始化状态机
void init_beep(StateMachine *sm)
{
    sm->current_state = STATE_SILENT;
    sm->config.frequency_ms = 1000; // 默认1秒
    sm->config.count = 1;           // 默认1次
    sm->handle_input = handle_silent;
	
	  TMR2_Init(4000);

}

// 主循环 100ms 调用一次
void beep_loop(StateMachine *sm)
{
    Input input = INPUT_SET_CONTINUOUS_BEEP; // 你可以在这里改变输入
   // sm->handle_input(sm, input);
}

// 设置蜂鸣器配置
void set_beeper_config(StateMachine *sm, int frequency_ms, int count)
{
    sm->config.frequency_ms = frequency_ms;
    sm->config.count = count;
}

 
/*!
 * @brief       TMR2 Init
 *
 * @param       None
 *
 * @retval      None
 */



void TMR2_Init(uint32_t pwm_frequency)
{
    TMR2_OCConfig_T ocConfigStruct;
    GPIO_Config_T gpio_struct;

    // 配置GPIO
    gpio_struct.pin = GPIO_PIN_3;
    gpio_struct.speed = GPIO_SPEED_10MHz;
    gpio_struct.mode = GPIO_MODE_OUT_PP;
    gpio_struct.intEn = GPIO_EINT_DISABLE;

    GPIO_Config(GPIOA, &gpio_struct);

    // 假设系统时钟为24MHz
    uint32_t system_clock = 24000000; // 24 MHz
    uint32_t prescaler = 23; // 预分频器值
    uint32_t timer_clock = system_clock / (prescaler + 1); // 计算定时器时钟

    // 计算计数器周期值
    uint16_t period = (timer_clock / pwm_frequency) - 1;

    // 配置定时器基底
    TMR2_ConfigTimerBase(prescaler, period);

    // 配置通道3为PWM模式
    ocConfigStruct.channel = TMR2_CHANNEL_3;
    ocConfigStruct.count = period / 2; // 占空比为50%
    ocConfigStruct.mode = TMR2_OC_MODE_PWM1;
    ocConfigStruct.OCxOutputState = TMR2_OC_OUTPUT_ENABLE;
    ocConfigStruct.OCxPolarity = TMR2_OC_POLARITY_HIGH;

    TMR2_ConfigOutputCompare(&ocConfigStruct);

    // 启用TMR2
    TMR2_Enable();
}


// int main() {
//     StateMachine sm;
//     init_state_machine(&sm);

//     // 设置蜂鸣器配置
//     set_beeper_config(&sm, 500, 3); // 500毫秒间隔，鸣响3次

//     state_machine_loop(&sm);

//     return 0;
// }