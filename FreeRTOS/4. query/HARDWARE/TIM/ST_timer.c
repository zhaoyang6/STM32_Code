#include "ST_timer.h"
//ͨ�ö�ʱ��3�жϳ�ʼ��
//arr: �Զ���װֵ
// psc: ʱ��Ԥ��Ƶ��
// ��ʱ�����ʱ����㷽����Tout = (arr+1)*(psc+1)/Ft us
// Ft=��ʱ������Ƶ�ʣ���λ:MHz
void TIM3_Int_Init(u16 arr, u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  TIM_TimeBaseInitStructure.TIM_Period = arr;  //�Զ���װ��ֵ
  TIM_TimeBaseInitStructure.TIM_Prescaler = psc; //��ʱ����Ƶ
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
  
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure); //��ʼ��TIM3
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);  //����ʱ�������ж�
  TIM_Cmd(TIM3, ENABLE);
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //��ʱ���ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x04; //��ռ���ȼ�4
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;  //�����ȼ�
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM3,TIM_IT_Update) == SET) //����ж�
  {
    printf("TIM3 ���....\r\n");
  }
  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //����жϱ�־λ
}
//ͨ�ö�ʱ��5�жϳ�ʼ��
//arr: �Զ���װֵ
// psc: ʱ��Ԥ��Ƶ��
// ��ʱ�����ʱ����㷽����Tout = (arr+1)*(psc+1)/Ft us
// Ft=��ʱ������Ƶ�ʣ���λ:MHz
void TIM5_Int_Init(u16 arr, u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
  TIM_TimeBaseInitStructure.TIM_Period = arr;  //�Զ���װ��ֵ
  TIM_TimeBaseInitStructure.TIM_Prescaler = psc; //��ʱ����Ƶ
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
  
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStructure); //��ʼ��TIM3
  TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);  //����ʱ�������ж�
  TIM_Cmd(TIM5, ENABLE);
  
  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //��ʱ���ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x05; //��ռ���ȼ�4
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;  //�����ȼ�
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

//��ʱ��5�жϷ�����
void TIM5_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM5,TIM_IT_Update) == SET) //����ж�
  {
    printf("TIM5 ���....\r\n");
  }
  TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //����жϱ�־λ
}

