 
/* Define to prevent recursive inclusion */
#ifndef __BEEP_H
#define __BEEP_H

#include "main.h"

// ����״̬
typedef enum
{
    STATE_SILENT,
    STATE_CONTINUOUS_BEEP,
    STATE_INTERMITTENT_BEEP,
    STATE_FAST_BEEP
} State;

// ��������
typedef enum
{
    INPUT_SET_SILENT,
    INPUT_SET_CONTINUOUS_BEEP,
    INPUT_SET_INTERMITTENT_BEEP,
    INPUT_SET_FAST_BEEP
} Input;

// ���������ýṹ��
typedef struct
{
    int frequency_ms; // �����������룩
    int count;        // �������
} BeeperConfig;

// ״̬���ṹ��
typedef struct
{
    State current_state;
    BeeperConfig config;
    void (*handle_input)(struct StateMachine *sm, Input input);
} StateMachine;


extern StateMachine g_beep_sm;


void init_beep(StateMachine *sm);
void beep_loop(StateMachine *sm);
void set_beeper_config(StateMachine *sm, int frequency_ms, int count);
void TMR2_Init(uint32_t pwm_frequency);


  

#endif /*__BEEP_H */
