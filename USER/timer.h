#ifndef _TIMER_H
#define _TIMER_H

#include "stm32f10x.h"

typedef enum {OFF=0,ON=1} TIMxSwitch;


void TIM3_Init(u16 arr,u16 psc);
void TIM3_IRQHandler(void);
void TIM4_Init(u16 arr,u16 psc);
void TIM4_IRQHandler(void);
void TIMxOFF_ON(TIM_TypeDef *TIMx,TIMxSwitch State);
void EXTI_TIMxOFF_ON(TIM_TypeDef *TIMx,TIMxSwitch State);

void TIM4CapInit(u16 arr, u16 psc,u8 ICPolar);

#endif
