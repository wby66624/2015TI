#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

void TIM2_PWM_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr,u16 psc);
void TIM3_Int_Init(u16 arr,u16 psc);
void TIM4_IRQHandler(void);
#endif
