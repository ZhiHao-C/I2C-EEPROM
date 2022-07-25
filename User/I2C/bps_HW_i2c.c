#include "bps_HW_i2c.h"

void I2C_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	I2C_InitTypeDef I2C_InitStruct;
	//打开APB1下的I2C1时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
	//打开GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//配置I2C
	I2C_InitStruct.I2C_ClockSpeed=400000;//配置传输速率
	I2C_InitStruct.I2C_Mode=I2C_Mode_I2C;//配置模式
	I2C_InitStruct.I2C_DutyCycle=I2C_DutyCycle_2 ;//配置时钟占空比
	I2C_InitStruct.I2C_OwnAddress1=I2C_OWN_ADDRESS;//配置stm32自己的地址
	I2C_InitStruct.I2C_Ack=I2C_Ack_Enable;//应答使能
	I2C_InitStruct.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;//使用七位地址模式
	I2C_Init(I2C1,&I2C_InitStruct);
	//配置GPIO
	GPIO_InitStruct.GPIO_Pin=EEPROM_I2C_SCL_GPIO_PIN|EEPROM_I2C_SDA_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_OD;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	//使能I2C
	I2C_Cmd(I2C1,ENABLE);
}



void I2C_WriteByte(uint8_t addr,uint8_t Data)
{
	//发送起始标志
	I2C_GenerateSTART(I2C1,ENABLE);
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)==ERROR);
	//发送从机地址
	I2C_Send7bitAddress(I2C1,EEPROM_ADDR_W,I2C_Direction_Transmitter);
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)==ERROR);
	//发送一个数据（要在从机哪个位置写数据的地址）
	I2C_SendData(I2C1,addr);
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTING)==ERROR);
	//发送写入的数据
	I2C_SendData(I2C1,Data);
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED)==ERROR);
	//发送停止标志
	I2C_GenerateSTOP(I2C1,ENABLE);
}

void I2C_Write_Page_Byte(uint8_t addr,uint8_t *Data,uint8_t n)//连续读写是addr必须满足addr%8=0
{
	uint8_t i;
	//发送起始标志
	I2C_GenerateSTART(I2C1,ENABLE);
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)==ERROR);//判断EV事件等待准备完毕
	//发送从机地址
	I2C_Send7bitAddress(I2C1,EEPROM_ADDR_W,I2C_Direction_Transmitter);
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)==ERROR);
	//发送一个数据（要在从机哪个位置写数据的地址）
	I2C_SendData(I2C1,addr);
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTING)==ERROR);
	//发送写入的数据
	for(i=0;i<n;i++)
	{
		I2C_SendData(I2C1,*(Data+i));
		while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTED)==ERROR);
	}
	
	//发送停止标志
	I2C_GenerateSTOP(I2C1,ENABLE);
}


//连续读取n个数据
void I2C_ReadByte(uint8_t addr,uint8_t *Data,uint8_t n)
{
	uint8_t i;
	//发送起始标志
	I2C_GenerateSTART(I2C1,ENABLE);
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)==ERROR);
	//发送从机地址
	I2C_Send7bitAddress(I2C1,EEPROM_ADDR_W,I2C_Direction_Transmitter);
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)==ERROR);
	//发送一个数据（要在从机哪个位置写数据的地址）
	I2C_SendData(I2C1,addr);
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_TRANSMITTING)==ERROR);
	//第二次发送起始标志
	I2C_GenerateSTART(I2C1,ENABLE);
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_MODE_SELECT)==ERROR);
	//发送从机地址（读）
	I2C_Send7bitAddress(I2C1,EEPROM_ADDR_R,I2C_Direction_Receiver);
	while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)==ERROR);
	//读取一个字节数据
	for(i=0;i<n;i++)
	{
		while(I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED)==ERROR);//判断数据寄存器是否为空，不为空时读取数据
		if(i==n-1)//最后一个数据从机通过IC2传到主机时候，主机要给一个非应答
		{
			I2C_AcknowledgeConfig(I2C1,DISABLE);
			*(Data+i)=I2C_ReceiveData(I2C1);
		}
		else
		{
			*(Data+i)=I2C_ReceiveData(I2C1);
		}
	}
	I2C_GenerateSTOP(I2C1,ENABLE);//停止标志
	I2C_AcknowledgeConfig(I2C1,ENABLE);
}

