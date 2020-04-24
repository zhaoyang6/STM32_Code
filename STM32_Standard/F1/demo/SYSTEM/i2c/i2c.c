#include "i2c.h"
#include "delay.h"
//��ʼ��IIC
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_GPIO_I2C1, ENABLE );	//ʹ��GPIOBʱ��
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_I2C1_SCL|GPIO_I2C1_SDA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_GROUP_I2C1, &GPIO_InitStructure);
	GPIO_SetBits(GPIO_GROUP_I2C1,GPIO_I2C1_SCL|GPIO_I2C1_SDA); 	//PB6,PB7 �����
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
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	I2C1_SDA_H;	  	  
	I2C1_SCL_H;
	delay_us(4);
 	I2C1_SDA_L;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	I2C1_SCL_L;//ǯסI2C���ߣ�׼�����ͻ�������� 
}

//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	I2C1_SCL_L;
	I2C1_SDA_L;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	I2C1_SCL_H; 
	I2C1_SDA_H;//����I2C���߽����ź�
	delay_us(4);							   	
}

//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
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
	I2C1_SCL_L;//ʱ�����0 	   
	return 0;  
}
//����ACKӦ��
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
//������ACKӦ��		    
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
  u8 t;   
  SDA_OUT(); 	    
  I2C1_SCL_L;//����ʱ�ӿ�ʼ���ݴ���
  for(t=0;t<8;t++)
  {              
      //IIC_SDA=(txd&0x80)>>7;
  if((txd&0x80)>>7)
    I2C1_SDA_H;
  else
    I2C1_SDA_L;
  txd<<=1; 	  
  delay_us(2);   //��TEA5767��������ʱ���Ǳ����
  I2C1_SCL_H;
  delay_us(2); 
  I2C1_SCL_L;	
  delay_us(2);
  }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
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
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}



//Ӳ��I2Cʵ��
void I2C2_Device_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  I2C_InitTypeDef I2C_InitStructure;  
	RCC_APB2PeriphClockCmd(RCC_GPIO_I2C2|RCC_APB1Periph_I2C2, ENABLE );	//ʹ��GPIOBʱ��
	
  
	GPIO_InitStructure.GPIO_Pin = GPIO_I2C2_SCL|GPIO_I2C2_SDA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD ;   //�������
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

