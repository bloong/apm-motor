 
/* Define to prevent recursive inclusion */
#ifndef __BEEP_H
#define __BEEP_H

#include "main.h"

void init_beep(StateMachine *sm);
void beep_loop(StateMachine *sm);
void set_beeper_config(StateMachine *sm, int frequency_ms, int count);


  

#endif /*__BEEP_H */
