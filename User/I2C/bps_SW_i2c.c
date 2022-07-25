#include "bps_SW_i2c.h"


void delay_ms(int n)//延时函数
{
	int i;
	while (n--)
	{
		for(i=0;i<5520;i++);
	}
}

void I2C_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 

	/* 使能与 I2C 有关的时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
	//打开GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
    
  /* I2C_SCL、I2C_SDA*/
  GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       // 开漏输出
  GPIO_Init(EEPROM_I2C_SCL_PORT, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SDA_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       // 开漏输出
  GPIO_Init(EEPROM_I2C_SDA_PORT, &GPIO_InitStructure);	
	
}

void I2C_config(void)
{
	I2C_InitTypeDef I2C_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
	//配置I2C
	I2C_InitStruct.I2C_ClockSpeed=400000;//配置传输速率
	I2C_InitStruct.I2C_Mode=I2C_Mode_I2C;//配置模式
	I2C_InitStruct.I2C_DutyCycle=I2C_DutyCycle_2 ;//配置时钟占空比
	I2C_InitStruct.I2C_OwnAddress1=0x01;//配置stm32自己的地址
	I2C_InitStruct.I2C_Ack=I2C_Ack_Enable;//应答使能
	I2C_InitStruct.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;//使用七位地址模式
	I2C_Init(I2C1,&I2C_InitStruct);
	
	I2C_Cmd(I2C1,ENABLE);
}

void start(void)
{
	SDA(1);
	SCL(1);
	delay_ms(1);
	SDA(0);
	delay_ms(1);
	SCL(0);
}

void stop(void)
{
	SDA(0);
	SCL(1);
	delay_ms(1);
	SDA(1);
}


void I2C_sentdata(uint8_t byte)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		SCL(0);
		if((byte&(0x80>>i)))
		{
			SDA(1);
		}
		else
		{
			SDA(0);
		}
		SCL(1);
		delay_ms(2);
		SCL(0);
		delay_ms(2);
	}
	SCL(0);
	SDA(1);
}

uint8_t I2C_receivedata(void)
{
//	uint8_t Data=0x00;
//	uint8_t i=0;
//	SCL(0)
//	delay_ms(2);
//	for(i=0;i<8;i++)
//	{
//		SCL(1);
//		if((GPIOB->IDR&GPIO_Pin_7))
//		{
//			Data|=0x80>>i;
//		}
//		
//		delay_ms(2);
//		SCL(0);
//	}
//	return Data;
	
	uint8_t i;
	uint8_t value;

	/* 读到第1个bit为数据的bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		SCL(1);
		delay_ms(1);
		if ((GPIOB->IDR&GPIO_Pin_7))
		{
			value++;
		}
		SCL(0);
		delay_ms(1);
	}
	return value;

	
}

void I2C_sentACK(uint8_t ACK)
{
	SCL(0);
	if(ACK==1)
	{
		SDA(0);
	}
	else
	{
		SDA(1);
	}
	SCL(1);
	delay_ms(2);
	SCL(0);
	SDA(1);
}


uint8_t I2C_receiveACK(void)
{
	SDA(1);
	delay_ms(2);
	SCL(1);
	delay_ms(2);
	if((GPIOB->IDR&0x0080)==0)
	{
		return 1;
	}
	
	delay_ms(2);
	SCL(0);
	return 0;
}




