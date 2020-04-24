#include "i2c.h"
#include "delay.h"
//初始化IIC
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_GPIO_I2C1, ENABLE );	//使能GPIOB时钟
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_I2C1_SCL|GPIO_I2C1_SDA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_GROUP_I2C1, &GPIO_InitStructure);
	GPIO_SetBits(GPIO_GROUP_I2C1,GPIO_I2C1_SCL|GPIO_I2C1_SDA); 	//PB6,PB7 输出高
}

void SDA_OUT(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_I2C1_SDA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
  GPIO_Init(GPIO_GROUP_I2C1, &GPIO_InitStructure);
	GPIO_SetBits(GPIO_GROUP_I2C1,GPIO_I2C1_SDA);
  
}
void SDA_IN(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_I2C1_SDA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIO_GROUP_I2C1, &GPIO_InitStructure);
	GPIO_SetBits(GPIO_GROUP_I2C1,GPIO_I2C1_SDA);
  
}
//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	I2C1_SDA_H;	  	  
	I2C1_SCL_H;
	delay_us(4);
 	I2C1_SDA_L;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	I2C1_SCL_L;//钳住I2C总线，准备发送或接收数据 
}

//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	I2C1_SCL_L;
	I2C1_SDA_L;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	I2C1_SCL_H; 
	I2C1_SDA_H;//发送I2C总线结束信号
	delay_us(4);							   	
}

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	I2C1_SDA_H;delay_us(1);	   
	I2C1_SCL_H;delay_us(1);	 
	while(READ_I2C1_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	I2C1_SCL_L;//时钟输出0 	   
	return 0;  
}
//产生ACK应答
void IIC_Ack(void)
{
	I2C1_SCL_L;
	SDA_OUT();
	I2C1_SDA_L;
	delay_us(2);
	I2C1_SCL_H;
	delay_us(2);
	I2C1_SCL_L;
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	I2C1_SCL_L;
	SDA_OUT();
	I2C1_SDA_H;
	delay_us(2);
	I2C1_SCL_H;
	delay_us(2);
	I2C1_SCL_L;
}	
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
  u8 t;   
  SDA_OUT(); 	    
  I2C1_SCL_L;//拉低时钟开始数据传输
  for(t=0;t<8;t++)
  {              
      //IIC_SDA=(txd&0x80)>>7;
  if((txd&0x80)>>7)
    I2C1_SDA_H;
  else
    I2C1_SDA_L;
  txd<<=1; 	  
  delay_us(2);   //对TEA5767这三个延时都是必须的
  I2C1_SCL_H;
  delay_us(2); 
  I2C1_SCL_L;	
  delay_us(2);
  }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	  {
      I2C1_SCL_L; 
      delay_us(2);
      I2C1_SCL_H;
      receive<<=1;
      if(READ_I2C1_SDA)receive++;   
      delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}



//硬件I2C实现
void I2C2_Device_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  I2C_InitTypeDef I2C_InitStructure;  
	RCC_APB2PeriphClockCmd(RCC_GPIO_I2C2|RCC_APB1Periph_I2C2, ENABLE );	//使能GPIOB时钟
	
  
	GPIO_InitStructure.GPIO_Pin = GPIO_I2C2_SCL|GPIO_I2C2_SDA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_GROUP_I2C2, &GPIO_InitStructure);
	GPIO_SetBits(GPIO_GROUP_I2C2,GPIO_I2C2_SCL|GPIO_I2C2_SDA);

  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = I2C2_Device_Address;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = I2C2_SPEED;
  I2C_Init(I2C2, &I2C_InitStructure);
  
  I2C_Cmd(I2C2, ENABLE);
}

