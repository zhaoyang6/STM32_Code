#ifndef _I2C_H
#define _I2C_H
#include "sys.h"

//���ģ��
#define GPIO_GROUP_I2C1  GPIOB
#define RCC_GPIO_I2C1    RCC_APB2Periph_GPIOB
#define GPIO_I2C1_SCL    GPIO_Pin_6
#define GPIO_I2C1_SDA    GPIO_Pin_7               
#define READ_I2C1_SDA    GPIO_ReadInputDataBit(GPIO_GROUP_I2C1,GPIO_I2C1_SDA)  
//I2C ��ƽ����
#define  I2C1_SCL_H      GPIO_SetBits(GPIO_GROUP_I2C1,GPIO_I2C1_SCL)
#define  I2C1_SCL_L      GPIO_ResetBits(GPIO_GROUP_I2C1,GPIO_I2C1_SCL)
#define  I2C1_SDA_H      GPIO_SetBits(GPIO_GROUP_I2C1,GPIO_I2C1_SDA)
#define  I2C1_SDA_L      GPIO_ResetBits(GPIO_GROUP_I2C1,GPIO_I2C1_SDA)

void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	




//Ӳ��I2C��ʵ��
#define GPIO_GROUP_I2C2  GPIOB
#define RCC_GPIO_I2C2    RCC_APB2Periph_GPIOB
#define GPIO_I2C2_SCL    GPIO_Pin_10
#define GPIO_I2C2_SDA    GPIO_Pin_11 
#define I2C2_Device_Address 0x00
#define I2C2_SPEED          100000

void I2C2_Device_Init(void);

#endif
