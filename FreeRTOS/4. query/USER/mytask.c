#include "mytask.h"
#include "led.h"
#include "ST_timer.h"
#include "lcd.h"
#include "key.h"
int lcd_color[14] = {
  WHITE, BLACK, BLUE, BRED, GRED, GBLUE, RED,
  MAGENTA, GREEN, CYAN, YELLOW, BROWN, BRRED, GRAY
};

//定义测试列表及列表项
List_t TestList;  //测试列表
ListItem_t ListItem1; //测试用列表项1
ListItem_t ListItem2; //测试用列表项2
ListItem_t ListItem3; //测试用列表项3

void systerm_Init(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  delay_init(168);
  uart_init(115200);
  LED_Init();
  LCD_Init();
  
  POINT_COLOR = RED;
  LCD_ShowString(30, 10, 200, 16, 16, "ATK STM32F407_USER");
  LCD_ShowString(30, 30, 200, 16, 16, "FreeRTOS task_deal");
  LCD_ShowString(30, 50, 200, 16, 16, "List and ListItem");
}
//任务2  查询任务
#define TASK2_TASK_PRIO 3 //任务优先级
#define TASK2_STK_SIZE  256 //任务堆栈大小
TaskHandle_t Task2Task_Handler;  //任务句柄
void task2_task(void *p_arg)   
{
  u32 TotalRunTime;
  UBaseType_t ArraySize, x;
  TaskStatus_t *StatusArray;
  printf("************第一步：函数uxTaskGetSystemState()使用********\r\n");
  ArraySize = uxTaskGetNumberOfTasks();
  Sta
  while(1)
  {
 
  }
}
//任务1
#define TASK1_TASK_PRIO 2 //任务优先级
#define TASK1_STK_SIZE  128 //任务堆栈大小
TaskHandle_t Task1Task_Handler;  //任务句柄
void task1_task(void *p_arg)   
{
    while(1)
    {
      LED0 = !LED0;
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
  //创建任务1
   xTaskCreate((TaskFunction_t) task1_task,        //任务函数
              (const char*   )"task1_task",      //任务名称
              (uint16_t      )TASK1_STK_SIZE,    //任务堆栈大小
              (void*         )NULL,              //传递给任务函数的参数
              (UBaseType_t   )TASK1_TASK_PRIO,   //任务优先级
              (TaskHandle_t* )&Task1Task_Handler); //任务句柄 
     //创建任务2
   xTaskCreate((TaskFunction_t) task2_task,        //任务函数
              (const char*   )"task2_task",      //任务名称
              (uint16_t      )TASK2_STK_SIZE,    //任务堆栈大小
              (void*         )NULL,              //传递给任务函数的参数
              (UBaseType_t   )TASK2_TASK_PRIO,   //任务优先级
              (TaskHandle_t* )&Task1Task_Handler); //任务句柄 
  
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
