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
//����2  �б�����
#define TASK2_TASK_PRIO 3 //�������ȼ�
#define TASK2_STK_SIZE  128 //�����ջ��С
TaskHandle_t Task2Task_Handler;  //������
void task2_task(void *p_arg)   
{
  vListInitialise(&TestList);
  vListInitialiseItem(&ListItem1);
  vListInitialiseItem(&ListItem2);
  vListInitialiseItem(&ListItem3);
  
  ListItem1.xItemValue = 40;
  ListItem2.xItemValue = 60;
  ListItem3.xItemValue = 50;
  
  printf("******�б���б����ַ*************\r\n");
  printf("��Ŀ                             ��ַ      \r\n");
  printf("TestList                         %#x      \r\n",(int)&TestList);
  printf("TestList->pxIndex                %#x      \r\n",(int)&TestList.pxIndex);
  printf("TestList->xListEnd               %#x      \r\n",(int)&TestList.xListEnd);
  printf("ListItem1                        %#x      \r\n",(int)&ListItem1);
  printf("ListItem2                        %#x      \r\n",(int)&ListItem2);
  printf("ListItem3                        %#x      \r\n",(int)&ListItem3);
  printf("****************����******************\r\n");
  printf("����KEY_UP������!\r\n");
  while(KEY_Scan(0)!=WKUP_PRES) delay_ms(10);
  
  //����
  vListInsert(&TestList,&ListItem1);
  printf("*************���ListItem1*************\r\n");
  printf("��Ŀ                             ��ַ      \r\n");
  printf("TestList->xListEnd->pxNext       %#x      \r\n",(int)&TestList.xListEnd.pxNext);
  printf("ListItem1->pxNext                %#x      \r\n",(int)&ListItem1.pxNext);
  printf("****************ǰ�������ӷָ���***********\r\n");
  printf("TestList->xListEnd->pxPrevious   %#x      \r\n",(int)&TestList.xListEnd.pxPrevious);
  printf("ListItem1->pxPrevious            %#x      \r\n",(int)&ListItem1.pxPrevious);
  printf("*****************����*********************\r\n");
  printf("����KEY_UP������!\r\n");
  while(KEY_Scan(0)!=WKUP_PRES) delay_ms(10);
  
  vListInsert(&TestList,&ListItem2);
  printf("*************���ListItem2*************\r\n");
  printf("��Ŀ                             ��ַ      \r\n");
  printf("TestList->xListEnd->pxNext       %#x      \r\n",(int)&TestList.xListEnd.pxNext);
  printf("ListItem1->pxNext                %#x      \r\n",(int)&ListItem1.pxNext);
  printf("ListItem2->pxNext                %#x      \r\n",(int)&ListItem2.pxNext);
  printf("****************ǰ�������ӷָ���***********\r\n");
  printf("TestList->xListEnd->pxPrevious   %#x      \r\n",(int)&TestList.xListEnd.pxPrevious);
  printf("ListItem1->pxPrevious            %#x      \r\n",(int)&ListItem1.pxPrevious);
  printf("ListItem2->pxPrevious            %#x      \r\n",(int)&ListItem2.pxPrevious);
  printf("*****************����*********************\r\n");
  printf("����KEY_UP������!\r\n");
  while(KEY_Scan(0)!=WKUP_PRES) delay_ms(10);
  
  vListInsert(&TestList,&ListItem3);
  printf("*************���ListItem3*************\r\n");
  printf("��Ŀ                             ��ַ      \r\n");
  printf("TestList->xListEnd->pxNext       %#x      \r\n",(int)&TestList.xListEnd.pxNext);
  printf("ListItem1->pxNext                %#x      \r\n",(int)&ListItem1.pxNext);
  printf("ListItem2->pxNext                %#x      \r\n",(int)&ListItem2.pxNext);
  printf("ListItem3->pxNext                %#x      \r\n",(int)&ListItem3.pxNext);
  printf("****************ǰ�������ӷָ���***********\r\n");
  printf("TestList->xListEnd->pxPrevious   %#x      \r\n",(int)&TestList.xListEnd.pxPrevious);
  printf("ListItem1->pxPrevious            %#x      \r\n",(int)&ListItem1.pxPrevious);
  printf("ListItem2->pxPrevious            %#x      \r\n",(int)&ListItem2.pxPrevious);
  printf("ListItem3->pxPrevious            %#x      \r\n",(int)&ListItem3.pxPrevious);
  printf("*****************����*********************\r\n");
  printf("����KEY_UP������!\r\n");
  while(KEY_Scan(0)!=WKUP_PRES) delay_ms(10);
  
  uxListRemove(&ListItem2);
  printf("*************ɾ��ListItem2*************\r\n");
  printf("��Ŀ                             ��ַ      \r\n");
  printf("TestList->xListEnd->pxNext       %#x      \r\n",(int)&TestList.xListEnd.pxNext);
  printf("ListItem1->pxNext                %#x      \r\n",(int)&ListItem1.pxNext);
  //printf("ListItem2->pxNext                %#x      \r\n",(int)&ListItem2.pxNext);
  printf("ListItem3->pxNext                %#x      \r\n",(int)&ListItem3.pxNext);
  printf("****************ǰ�������ӷָ���***********\r\n");
  printf("TestList->xListEnd->pxPrevious   %#x      \r\n",(int)&TestList.xListEnd.pxPrevious);
  printf("ListItem1->pxPrevious            %#x      \r\n",(int)&ListItem1.pxPrevious);
  //printf("ListItem2->pxPrevious            %#x      \r\n",(int)&ListItem2.pxPrevious);
  printf("ListItem3->pxPrevious            %#x      \r\n",(int)&ListItem3.pxPrevious);
  printf("*****************����*********************\r\n");
  printf("����KEY_UP������!\r\n");
  while(KEY_Scan(0)!=WKUP_PRES) delay_ms(10);
  while(1)
  {
    LED1 = !LED1;
    vTaskDelay(1000);
  }
}
//����1
#define TASK1_TASK_PRIO 2 //�������ȼ�
#define TASK1_STK_SIZE  128 //�����ջ��С
TaskHandle_t Task1Task_Handler;  //������
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
    printf("����1�Ѿ�ִ��: %d��\r\n", task1_num);
    if(task1_num == 5)
    {
      vTaskDelete(Task2Task_Handler);  //ɾ������2
      printf("����1ɾ��������2!\r\n");
    }
    LCD_Fill(6, 131, 114, 313, lcd_color[task1_num%14]);
    LCD_ShowxNum(86, 111, task1_num, 3, 16, 0x80);
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
