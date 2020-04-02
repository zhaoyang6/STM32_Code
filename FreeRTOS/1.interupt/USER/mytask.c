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
//�ж�����
#define INTERRUPT_TASK_PRIO 2 //�������ȼ�
#define INTERRUPT_STK_SIZE  256 //�����ջ��С
TaskHandle_t INTERRUPTTask_Handler;  //������
void interrupt_task(void *p_arg)   
{
  static u32 total_num = 0;
  
  while(1)
  {
    total_num+=1;
    if(total_num==5)
    {
      printf("�ر��ж�......\r\n");
      portDISABLE_INTERRUPTS();  //�ر��ж�
      delay_ms(5000);
      printf("���ж�......\r\n");
      portENABLE_INTERRUPTS();
    }
    LED0 = ~LED0;
    vTaskDelay(1000);
  }
}

#define START_TASK_PRIO 1 //�������ȼ�
#define START_STK_SIZE  256 //�����ջ��С
TaskHandle_t StartTask_Handler;  //������
 //������
void start_task(void *p_arg)   
{
  taskENTER_CRITICAL();  //�����ٽ���
  //����LED0����
   xTaskCreate((TaskFunction_t) interrupt_task,        //������
              (const char*   )"interrupt_task",      //��������
              (uint16_t      )INTERRUPT_STK_SIZE,    //�����ջ��С
              (void*         )NULL,              //���ݸ��������Ĳ���
              (UBaseType_t   )INTERRUPT_TASK_PRIO,   //�������ȼ�
              (TaskHandle_t* )&INTERRUPTTask_Handler); //������ 
  
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
