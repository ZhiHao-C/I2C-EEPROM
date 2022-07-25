#ifndef __BPS_HW_I2C_H__
#define __BPS_HW_I2C_H__

#include "stm32f10x.h" 


#define EEPROM_I2C                    I2C1
#define EEPROM_I2C_CLK                RCC_APB1Periph_I2C1
#define EEPROM_I2C_APBxClkCmd         RCC_APB1PeriphClockCmd
#define EEPROM_I2C_Speed              400000
#define EEPROM_I2C_SCL_GPIO_CLK       (RCC_APB2Periph_GPIOB)
#define EEPROM_I2C_SDA_GPIO_CLK       (RCC_APB2Periph_GPIOB)
#define EEPROM_I2C_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
#define EEPROM_I2C_SCL_GPIO_PORT      GPIOB
#define EEPROM_I2C_SCL_GPIO_PIN       GPIO_Pin_6
#define EEPROM_I2C_SDA_GPIO_PORT      GPIOB
#define EEPROM_I2C_SDA_GPIO_PIN       GPIO_Pin_7


#define EEPROM_ADDR_W                 0XA0
#define EEPROM_ADDR_R                 0XA1


#define I2C_OWN_ADDRESS               0X1E

void I2C_Config(void);
void I2C_WriteByte(uint8_t addr,uint8_t Data);
void I2C_ReadByte(uint8_t addr,uint8_t *Data,uint8_t n);
void I2C_Write_Page_Byte(uint8_t addr,uint8_t *Data,uint8_t n);
#endif
