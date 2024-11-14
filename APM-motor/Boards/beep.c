
/* Includes */
#include "beep.h"

#include <stdio.h>
#include <unistd.h> // for sleep function

StateMachine g_beep_sm;

// 定义状态
typedef enum
{
    STATE_SILENT,
    STATE_CONTINUOUS_BEEP,
    STATE_INTERMITTENT_BEEP,
    STATE_FAST_BEEP
} State;

// 定义输入
typedef enum
{
    INPUT_SET_SILENT,
    INPUT_SET_CONTINUOUS_BEEP,
    INPUT_SET_INTERMITTENT_BEEP,
    INPUT_SET_FAST_BEEP
} Input;

// 蜂鸣器配置结构体
typedef struct
{
    int frequency_ms; // 鸣响间隔（毫秒）
    int count;        // 鸣响次数
} BeeperConfig;

// 状态机结构体
typedef struct
{
    State current_state;
    BeeperConfig config;
    void (*handle_input)(struct StateMachine *sm, Input input);
} StateMachine;

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
    usleep(sm->config.frequency_ms * 1000);
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
    usleep(sm->config.frequency_ms * 1000);
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
}

// 主循环 100ms 调用一次
void beep_loop(StateMachine *sm)
{
    Input input = INPUT_SET_CONTINUOUS_BEEP; // 你可以在这里改变输入
    sm->handle_input(sm, input);
}

// 设置蜂鸣器配置
void set_beeper_config(StateMachine *sm, int frequency_ms, int count)
{
    sm->config.frequency_ms = frequency_ms;
    sm->config.count = count;
}

 

// int main() {
//     StateMachine sm;
//     init_state_machine(&sm);

//     // 设置蜂鸣器配置
//     set_beeper_config(&sm, 500, 3); // 500毫秒间隔，鸣响3次

//     state_machine_loop(&sm);

//     return 0;
// }