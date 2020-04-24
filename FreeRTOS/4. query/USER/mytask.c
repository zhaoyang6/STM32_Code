#include "mytask.h"
#include "led.h"
#include "ST_timer.h"
#include "lcd.h"
#include "key.h"
int lcd_color[14] = {
  WHITE, BLACK, BLUE, BRED, GRED, GBLUE, RED,
  MAGENTA, GREEN, CYAN, YELLOW, BROWN, BRRED, GRAY
};

//��������б��б���
List_t TestList;  //�����б�
ListItem_t ListItem1; //�������б���1
ListItem_t ListItem2; //�������б���2
ListItem_t ListItem3; //�������б���3

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
//����2  ��ѯ����
#define TASK2_TASK_PRIO 3 //�������ȼ�
#define TASK2_STK_SIZE  256 //�����ջ��С
TaskHandle_t Task2Task_Handler;  //������
void task2_task(void *p_arg)   
{
  u32 TotalRunTime;
  UBaseType_t ArraySize, x;
  TaskStatus_t *StatusArray;
  printf("************��һ��������uxTaskGetSystemState()ʹ��********\r\n");
  ArraySize = uxTaskGetNumberOfTasks();
  Sta
  while(1)
  {
 
  }
}
//����1
#define TASK1_TASK_PRIO 2 //�������ȼ�
#define TASK1_STK_SIZE  128 //�����ջ��С
TaskHandle_t Task1Task_Handler;  //������
void task1_task(void *p_arg)   
{
    while(1)
    {
      LED0 = !LED0;
      vTaskDelay(1000);
    }      
  
}

#define START_TASK_PRIO 1 //�������ȼ�
#define START_STK_SIZE  128 //�����ջ��С
TaskHandle_t StartTask_Handler;  //������
 //������
void start_task(void *p_arg)   
{
  taskENTER_CRITICAL();  //�����ٽ���
  //��������1
   xTaskCreate((TaskFunction_t) task1_task,        //������
              (const char*   )"task1_task",      //��������
              (uint16_t      )TASK1_STK_SIZE,    //�����ջ��С
              (void*         )NULL,              //���ݸ��������Ĳ���
              (UBaseType_t   )TASK1_TASK_PRIO,   //�������ȼ�
              (TaskHandle_t* )&Task1Task_Handler); //������ 
     //��������2
   xTaskCreate((TaskFunction_t) task2_task,        //������
              (const char*   )"task2_task",      //��������
              (uint16_t      )TASK2_STK_SIZE,    //�����ջ��С
              (void*         )NULL,              //���ݸ��������Ĳ���
              (UBaseType_t   )TASK2_TASK_PRIO,   //�������ȼ�
              (TaskHandle_t* )&Task1Task_Handler); //������ 
  
  vTaskDelete(StartTask_Handler);                  //ɾ����ʼ����
  taskEXIT_CRITICAL();                             //�˳��ٽ���
}

void task_logic(void)
{
  xTaskCreate((TaskFunction_t)start_task,        //������
              (const char*   )"start_task",      //��������
              (uint16_t      )START_STK_SIZE,    //�����ջ��С
              (void*         )NULL,              //���ݸ��������Ĳ���
              (UBaseType_t   )START_TASK_PRIO,   //�������ȼ�
              (TaskHandle_t* )&StartTask_Handler); //������ 
  vTaskStartScheduler();                         //�����������
}
