#include "mytask.h"
#include "led.h"
#include "ST_timer.h"
void systerm_Init(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  delay_init(168);
  uart_init(115200);
  LED_Init();
}
//中断任务
#define INTERRUPT_TASK_PRIO 2 //任务优先级
#define INTERRUPT_STK_SIZE  256 //任务堆栈大小
TaskHandle_t INTERRUPTTask_Handler;  //任务句柄
void interrupt_task(void *p_arg)   
{
  static u32 total_num = 0;
  
  while(1)
  {
    total_num+=1;
    if(total_num==5)
    {
      printf("关闭中断......\r\n");
      portDISABLE_INTERRUPTS();  //关闭中断
      delay_ms(5000);
      printf("打开中断......\r\n");
      portENABLE_INTERRUPTS();
    }
    LED0 = ~LED0;
    vTaskDelay(1000);
  }
}

#define START_TASK_PRIO 1 //任务优先级
#define START_STK_SIZE  256 //任务堆栈大小
TaskHandle_t StartTask_Handler;  //任务句柄
 //任务函数
void start_task(void *p_arg)   
{
  taskENTER_CRITICAL();  //进入临界区
  //创建LED0任务
   xTaskCreate((TaskFunction_t) interrupt_task,        //任务函数
              (const char*   )"interrupt_task",      //任务名称
              (uint16_t      )INTERRUPT_STK_SIZE,    //任务堆栈大小
              (void*         )NULL,              //传递给任务函数的参数
              (UBaseType_t   )INTERRUPT_TASK_PRIO,   //任务优先级
              (TaskHandle_t* )&INTERRUPTTask_Handler); //任务句柄 
  
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
