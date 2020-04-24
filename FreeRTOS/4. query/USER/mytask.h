#ifndef _MYTASK_H
#define _MYTASK_H
#include "sys.h"
#include "usart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "delay.h"

void start_task(void *p_arg);
void task1_task(void *p_arg);
void task2_task(void *p_arg); 

void task_logic(void);
void systerm_Init(void);
#endif
