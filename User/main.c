#include "stm32f10x.h"                  // Device header
#include "bps_led.h"
#include "bps_usart.h"
#include "bps_HW_i2c.h"
#include "bps_SW_i2c.h"
#include <stdio.h>
uint8_t a[10]={0};
uint8_t b[8]={1,2,3,4,5,6,7,8};
uint8_t n=0;



int main()
{
	

	USART_Config();
	I2C_config();
	I2C_GPIO_Config();			
	I2C_WriteByte(0x12,0x55);
//	delay_ms(10);
//	I2C_WriteByte(0x12,0x78);
//	delay_ms(10);
	
//	I2C_Write_Page_Byte(0,b,8);
//	delay_ms(10);
//	I2C_ReadByte(0,a,8);
//	printf("I2C通讯测试\n");
//	for(i=0;i<8;i++)
//	{
//		printf("%d\n",a[i]);
//	}

	
//软件模拟（有问题无法实现）
//写操作
//	start();
//	delay_ms(2);
//	I2C_sentdata(EEPROM_ADDR_W);
//	delay_ms(2);
//	I2C_receiveACK();
//	
//	I2C_sentdata(0x12);//要写入的地址
//	delay_ms(2);
//	while(I2C_receiveACK()==0);
//	
//	I2C_sentdata(0x25);
//	delay_ms(2);
//	while(I2C_receiveACK()==0);
//	
//	stop();
//	
//	delay_ms(100);
	
	
//读操作
//	start();
//	delay_ms(2);
//	I2C_sentdata(EEPROM_ADDR_W);
//	delay_ms(2);
//	I2C_receiveACK();
//	
//	I2C_sentdata(0x12);//要读出的地址
//	delay_ms(2);
//	I2C_receiveACK();
//	
//	start();
//	I2C_sentdata(EEPROM_ADDR_R);
//	delay_ms(2);
//	I2C_receiveACK();
//	
//	n=I2C_receivedata();
//	I2C_sentACK(0);
//	stop();

//	I2C_ReadByte(0x12,a,1);
//	printf("%x\n",n);

}







//接收触发中断函数
//void DEBUG_USART_IRQHandler(void)
//{
//	uint8_t temp;
//	if((USART1->SR&0x20)==0x20)
//	{
//		temp=USART_ReceiveData(USART1);
//		USART_SendData(USART1,temp);
//		while (!USART_GetFlagStatus(USART1,USART_FLAG_TXE));
//	}
//}	



