#ifndef SYSTICK_H_INCLUDED
#define SYSTICK_H_INCLUDED

#include "user_types.h"

#define BIT_ENABLE    0
#define BIT_TICKINT   1
#define BIT_CLKSOURCE 2

void systick_set_control(bool enable, bool tickint, bool clksource);
void systick_set_reload(u32 reload);

void SysTick_Handler(void);

#endif
