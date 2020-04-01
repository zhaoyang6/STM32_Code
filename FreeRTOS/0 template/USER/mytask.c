#include "mytask.h"
#include "led.h"
void systerm_Init(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  delay_init(168);
  uart_init(115200);
  LED_Init();
}
//任务1
#define LED0_TASK_PRIO 2 //任务优先级
#define LED0_STK_SIZE  50 //任务堆栈大小
TaskHandle_t LED0Task_Handler;  //任务句柄
 //任务函数
void LED0_task(void *p_arg)   
{
  while(1)
  {
    LED0 = 0;
    vTaskDelay(200);
    LED0 = 1;
    vTaskDelay(200);
  }
}

//任务2
#define FLOAT_TASK_PRIO  4
#define FLOAT_STK_SIZE   128
TaskHandle_t FLOATTask_Handler;
void float_task(void *p_arg)
{
  static float float_num = 0.00;
  while(1)
  {
    float_num+=0.01f;
    printf("float_num 的值为：%.4f\r\n", float_num);
    vTaskDelay(1000);
  }
}

#define START_TASK_PRIO 1 //任务优先级
#define START_STK_SIZE  128 //任务堆栈大小
TaskHandle_t StartTask_Handler;  //任务句柄
 //任务函数
void start_task(void *p_arg)   
{
  taskENTER_CRITICAL();  //进入临界区
  //创建LED0任务
   xTaskCreate((TaskFunction_t) LED0_task,        //任务函数
              (const char*   )"LED0_task",      //任务名称
              (uint16_t      )LED0_STK_SIZE,    //任务堆栈大小
              (void*         )NULL,              //传递给任务函数的参数
              (UBaseType_t   )LED0_TASK_PRIO,   //任务优先级
              (TaskHandle_t* )&LED0Task_Handler); //任务句柄 
   //创建浮点测试任务
   xTaskCreate((TaskFunction_t) float_task,        //任务函数
              (const char*   )"float_task",      //任务名称
              (uint16_t      )FLOAT_STK_SIZE,    //任务堆栈大小
              (void*         )NULL,              //传递给任务函数的参数
              (UBaseType_t   )FLOAT_TASK_PRIO,   //任务优先级
              (TaskHandle_t* )&FLOATTask_Handler); //任务句柄 
  vTaskDelete(StartTask_Handler);                  //删除开始任务
  taskEXIT_CRITICAL();                             //退出临界区
}

void task_logic(void)
{
  xTaskCreate((TaskFunction_t)start_task,        //任务函数
              (const char*   )"start_task",      //任务名称
              (uint16_t      )START_STK_SIZE,    //任务堆栈大小
              (void*         )NULL,              //传递给任务函数的参数
              (UBaseType_t   )START_TASK_PRIO,   //任务优先级
              (TaskHandle_t* )&StartTask_Handler); //任务句柄 
  vTaskStartScheduler();                         //开启任务调度
}
