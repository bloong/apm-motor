 
/* Define to prevent recursive inclusion */
#ifndef __PWM_H
#define __PWM_H

#include "main.h"
#include <stdbool.h>

#define FREQUENCY          20000

typedef struct {
    uint16_t channel;
    uint16_t dutyCycle; // ??? (0-100)
    bool enable; // ???????
} PWMChannelConfig_T;


//void TMR1_Init(void);
// 
//void pwm_Init(uint16_t frz, uint16_t pwm);

//void TMR1_Init(uint32_t frequency, PWMChannelConfig_T channels[], uint8_t numChannels);

void pwm_init(bool ch1_P, bool ch1_N, bool ch2_P,  bool ch2_N, uint32_t frequency, uint32_t dutyCycle_1, uint32_t dutyCycle_2);

#endif /*__PWM_H */
