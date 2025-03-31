#ifndef __MYIIC_H
#define __MYIIC_H

#include "main.h"
#include "delay.h"

/* 引脚定义 */
#define IIC_SCL_GPIO_PORT GPIOB
#define SCL GPIO_PIN_6

#define IIC_SDA_GPIO_PORT GPIOB
#define SDA GPIO_PIN_7

/* SCL引脚设置宏定义 */
#define IIC_SCL(x) do{x ? \
                      HAL_GPIO_WritePin(IIC_SCL_GPIO_PORT, SCL, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(IIC_SCL_GPIO_PORT, SCL, GPIO_PIN_RESET); \
                     }while(0)

/* SDA引脚设置宏定义 */
#define IIC_SDA(x) do{x ? \
                      HAL_GPIO_WritePin(IIC_SDA_GPIO_PORT, SDA, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(IIC_SDA_GPIO_PORT, SDA, GPIO_PIN_RESET); \
                     }while(0)

#define IIC_READ_SDA HAL_GPIO_ReadPin(IIC_SDA_GPIO_PORT, GPIO_PIN_7)


void at24c02_write_one_byte(uint8_t addr, uint8_t data);
uint8_t at24c02_read_one_byte(uint8_t addr);

#endif

