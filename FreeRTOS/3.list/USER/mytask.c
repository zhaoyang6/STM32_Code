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
//任务2  列表任务
#define TASK2_TASK_PRIO 3 //任务优先级
#define TASK2_STK_SIZE  128 //任务堆栈大小
TaskHandle_t Task2Task_Handler;  //任务句柄
void task2_task(void *p_arg)   
{
  vListInitialise(&TestList);
  vListInitialiseItem(&ListItem1);
  vListInitialiseItem(&ListItem2);
  vListInitialiseItem(&ListItem3);
  
  ListItem1.xItemValue = 40;
  ListItem2.xItemValue = 60;
  ListItem3.xItemValue = 50;
  
  printf("******列表和列表项地址*************\r\n");
  printf("项目                             地址      \r\n");
  printf("TestList                         %#x      \r\n",(int)&TestList);
  printf("TestList->pxIndex                %#x      \r\n",(int)&TestList.pxIndex);
  printf("TestList->xListEnd               %#x      \r\n",(int)&TestList.xListEnd);
  printf("ListItem1                        %#x      \r\n",(int)&ListItem1);
  printf("ListItem2                        %#x      \r\n",(int)&ListItem2);
  printf("ListItem3                        %#x      \r\n",(int)&ListItem3);
  printf("****************结束******************\r\n");
  printf("按下KEY_UP键继续!\r\n");
  while(KEY_Scan(0)!=WKUP_PRES) delay_ms(10);
  
  //插入
  vListInsert(&TestList,&ListItem1);
  printf("*************添加ListItem1*************\r\n");
  printf("项目                             地址      \r\n");
  printf("TestList->xListEnd->pxNext       %#x      \r\n",(int)&TestList.xListEnd.pxNext);
  printf("ListItem1->pxNext                %#x      \r\n",(int)&ListItem1.pxNext);
  printf("****************前后向连接分割线***********\r\n");
  printf("TestList->xListEnd->pxPrevious   %#x      \r\n",(int)&TestList.xListEnd.pxPrevious);
  printf("ListItem1->pxPrevious            %#x      \r\n",(int)&ListItem1.pxPrevious);
  printf("*****************结束*********************\r\n");
  printf("按下KEY_UP键继续!\r\n");
  while(KEY_Scan(0)!=WKUP_PRES) delay_ms(10);
  
  vListInsert(&TestList,&ListItem2);
  printf("*************添加ListItem2*************\r\n");
  printf("项目                             地址      \r\n");
  printf("TestList->xListEnd->pxNext       %#x      \r\n",(int)&TestList.xListEnd.pxNext);
  printf("ListItem1->pxNext                %#x      \r\n",(int)&ListItem1.pxNext);
  printf("ListItem2->pxNext                %#x      \r\n",(int)&ListItem2.pxNext);
  printf("****************前后向连接分割线***********\r\n");
  printf("TestList->xListEnd->pxPrevious   %#x      \r\n",(int)&TestList.xListEnd.pxPrevious);
  printf("ListItem1->pxPrevious            %#x      \r\n",(int)&ListItem1.pxPrevious);
  printf("ListItem2->pxPrevious            %#x      \r\n",(int)&ListItem2.pxPrevious);
  printf("*****************结束*********************\r\n");
  printf("按下KEY_UP键继续!\r\n");
  while(KEY_Scan(0)!=WKUP_PRES) delay_ms(10);
  
  vListInsert(&TestList,&ListItem3);
  printf("*************添加ListItem3*************\r\n");
  printf("项目                             地址      \r\n");
  printf("TestList->xListEnd->pxNext       %#x      \r\n",(int)&TestList.xListEnd.pxNext);
  printf("ListItem1->pxNext                %#x      \r\n",(int)&ListItem1.pxNext);
  printf("ListItem2->pxNext                %#x      \r\n",(int)&ListItem2.pxNext);
  printf("ListItem3->pxNext                %#x      \r\n",(int)&ListItem3.pxNext);
  printf("****************前后向连接分割线***********\r\n");
  printf("TestList->xListEnd->pxPrevious   %#x      \r\n",(int)&TestList.xListEnd.pxPrevious);
  printf("ListItem1->pxPrevious            %#x      \r\n",(int)&ListItem1.pxPrevious);
  printf("ListItem2->pxPrevious            %#x      \r\n",(int)&ListItem2.pxPrevious);
  printf("ListItem3->pxPrevious            %#x      \r\n",(int)&ListItem3.pxPrevious);
  printf("*****************结束*********************\r\n");
  printf("按下KEY_UP键继续!\r\n");
  while(KEY_Scan(0)!=WKUP_PRES) delay_ms(10);
  
  uxListRemove(&ListItem2);
  printf("*************删除ListItem2*************\r\n");
  printf("项目                             地址      \r\n");
  printf("TestList->xListEnd->pxNext       %#x      \r\n",(int)&TestList.xListEnd.pxNext);
  printf("ListItem1->pxNext                %#x      \r\n",(int)&ListItem1.pxNext);
  //printf("ListItem2->pxNext                %#x      \r\n",(int)&ListItem2.pxNext);
  printf("ListItem3->pxNext                %#x      \r\n",(int)&ListItem3.pxNext);
  printf("****************前后向连接分割线***********\r\n");
  printf("TestList->xListEnd->pxPrevious   %#x      \r\n",(int)&TestList.xListEnd.pxPrevious);
  printf("ListItem1->pxPrevious            %#x      \r\n",(int)&ListItem1.pxPrevious);
  //printf("ListItem2->pxPrevious            %#x      \r\n",(int)&ListItem2.pxPrevious);
  printf("ListItem3->pxPrevious            %#x      \r\n",(int)&ListItem3.pxPrevious);
  printf("*****************结束*********************\r\n");
  printf("按下KEY_UP键继续!\r\n");
  while(KEY_Scan(0)!=WKUP_PRES) delay_ms(10);
  while(1)
  {
    LED1 = !LED1;
    vTaskDelay(1000);
  }
}
//任务1
#define TASK1_TASK_PRIO 2 //任务优先级
#define TASK1_STK_SIZE  128 //任务堆栈大小
TaskHandle_t Task1Task_Handler;  //任务句柄
void task1_task(void *p_arg)   
{
  u8 task1_num =0;
  POINT_COLOR =BLACK;
  LCD_DrawRectangle(5, 110, 115, 314);
  LCD_DrawLine(5, 130, 115, 130);
  POINT_COLOR = BLUE;
  LCD_ShowString(6, 111, 110, 16, 16, "Task1 Run:000");
  
  while(1)
  {
    task1_num++;
    LED0 =!LED0;
    printf("任务1已经执行: %d次\r\n", task1_num);
    if(task1_num == 5)
    {
      vTaskDelete(Task2Task_Handler);  //删除任务2
      printf("任务1删除了任务2!\r\n");
    }
    LCD_Fill(6, 131, 114, 313, lcd_color[task1_num%14]);
    LCD_ShowxNum(86, 111, task1_num, 3, 16, 0x80);
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
