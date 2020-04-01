#include "mytask.h"
#include "led.h"
void systerm_Init(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  delay_init(168);
  uart_init(115200);
  LED_Init();
}
//����1
#define LED0_TASK_PRIO 2 //�������ȼ�
#define LED0_STK_SIZE  50 //�����ջ��С
TaskHandle_t LED0Task_Handler;  //������
 //������
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

//����2
#define FLOAT_TASK_PRIO  4
#define FLOAT_STK_SIZE   128
TaskHandle_t FLOATTask_Handler;
void float_task(void *p_arg)
{
  static float float_num = 0.00;
  while(1)
  {
    float_num+=0.01f;
    printf("float_num ��ֵΪ��%.4f\r\n", float_num);
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
  //����LED0����
   xTaskCreate((TaskFunction_t) LED0_task,        //������
              (const char*   )"LED0_task",      //��������
              (uint16_t      )LED0_STK_SIZE,    //�����ջ��С
              (void*         )NULL,              //���ݸ��������Ĳ���
              (UBaseType_t   )LED0_TASK_PRIO,   //�������ȼ�
              (TaskHandle_t* )&LED0Task_Handler); //������ 
   //���������������
   xTaskCreate((TaskFunction_t) float_task,        //������
              (const char*   )"float_task",      //��������
              (uint16_t      )FLOAT_STK_SIZE,    //�����ջ��С
              (void*         )NULL,              //���ݸ��������Ĳ���
              (UBaseType_t   )FLOAT_TASK_PRIO,   //�������ȼ�
              (TaskHandle_t* )&FLOATTask_Handler); //������ 
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
