#ifndef _I2C_H
#define _I2C_H
#include "sys.h"

//软件模拟
#define GPIO_GROUP_I2C1  GPIOB
#define RCC_GPIO_I2C1    RCC_APB2Periph_GPIOB
#define GPIO_I2C1_SCL    GPIO_Pin_6
#define GPIO_I2C1_SDA    GPIO_Pin_7               
#define READ_I2C1_SDA    GPIO_ReadInputDataBit(GPIO_GROUP_I2C1,GPIO_I2C1_SDA)  
//I2C 电平定义
#define  I2C1_SCL_H      GPIO_SetBits(GPIO_GROUP_I2C1,GPIO_I2C1_SCL)
#define  I2C1_SCL_L      GPIO_ResetBits(GPIO_GROUP_I2C1,GPIO_I2C1_SCL)
#define  I2C1_SDA_H      GPIO_SetBits(GPIO_GROUP_I2C1,GPIO_I2C1_SDA)
#define  I2C1_SDA_L      GPIO_ResetBits(GPIO_GROUP_I2C1,GPIO_I2C1_SDA)

void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	




//硬件I2C的实现
#define GPIO_GROUP_I2C2  GPIOB
#define RCC_GPIO_I2C2    RCC_APB2Periph_GPIOB
#define GPIO_I2C2_SCL    GPIO_Pin_10
#define GPIO_I2C2_SDA    GPIO_Pin_11 
#define I2C2_Device_Address 0x00
#define I2C2_SPEED          100000

void I2C2_Device_Init(void);

#endif
