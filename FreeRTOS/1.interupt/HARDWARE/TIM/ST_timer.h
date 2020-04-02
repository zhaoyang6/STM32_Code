#ifndef _ST_TIMER_H
#define _ST_TIMER_H
#include "sys.h"
#include "delay.h"
#include "FreeRTOS.h"
#include "usart.h"

void TIM3_Int_Init(u16 arr, u16 psc);
void TIM5_Int_Init(u16 arr, u16 psc);
#endif
