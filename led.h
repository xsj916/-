#ifndef _led_H
#define _led_H

#include "system.h"

/*  LED时钟端口、引脚定义 */
#define LED0_PORT 			GPIOC  
#define LED0_PIN 			GPIO_Pin_13
#define LED0_PORT_RCC		RCC_APB2Periph_GPIOC

#define LED1_PORT 			GPIOA  
#define LED1_PIN 			GPIO_Pin_0
#define LED1_PORT_RCC		RCC_APB2Periph_GPIOA

#define LED2_PORT 			GPIOA  
#define LED2_PIN 			GPIO_Pin_1
#define LED2_PORT_RCC		RCC_APB2Periph_GPIOA

#define LED3_PORT 			GPIOA  
#define LED3_PIN 			GPIO_Pin_2
#define LED3_PORT_RCC		RCC_APB2Periph_GPIOA

#define LED4_PORT 			GPIOA  
#define LED4_PIN 			GPIO_Pin_3
#define LED4_PORT_RCC		RCC_APB2Periph_GPIOA

#define LED5_PORT 			GPIOA  
#define LED5_PIN 			GPIO_Pin_4
#define LED5_PORT_RCC		RCC_APB2Periph_GPIOA

#define LED6_PORT 			GPIOA  
#define LED6_PIN 			GPIO_Pin_5
#define LED6_PORT_RCC		RCC_APB2Periph_GPIOA

#define LED7_PORT 			GPIOA  
#define LED7_PIN 			GPIO_Pin_6
#define LED7_PORT_RCC		RCC_APB2Periph_GPIOA

#define LED8_PORT 			GPIOA  
#define LED8_PIN 			GPIO_Pin_7
#define LED8_PORT_RCC		RCC_APB2Periph_GPIOA


//位带定义
#define LED0 	PCout(13)
#define LED1 	PAout(0)  
#define LED2 	PAout(1) 
#define LED3 	PAout(2)  
#define LED4 	PAout(3)
#define LED5 	PAout(4)  
#define LED6 	PAout(5)
#define LED7 	PAout(6)  
#define LED8 	PAout(7)


//函数声明
void LED_Init(void);
void LED_Write_Data(u16 GPIO_Pin,u8 data);

#endif
