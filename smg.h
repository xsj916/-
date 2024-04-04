#ifndef _smg_H
#define _smg_H

#include "system.h"


//端口定义
#define LSA_PORT 				GPIOB  
#define LSA_PIN 				GPIO_Pin_5
#define LSA_PORT_RCC			RCC_APB2Periph_GPIOB

#define LSB_PORT 				GPIOB  
#define LSB_PIN 				GPIO_Pin_4
#define LSB_PORT_RCC			RCC_APB2Periph_GPIOB

#define LSC_PORT 				GPIOB  
#define LSC_PIN 				GPIO_Pin_3
#define LSC_PORT_RCC			RCC_APB2Periph_GPIOB

#define SMG_A_DP_PORT 			GPIOA  
#define SMG_A_DP_PIN 			GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7
#define SMG_A_DP_PORT_RCC		RCC_APB2Periph_GPIOA

//位带定义
#define LSA 	PBout(5)
#define LSB 	PBout(4)
#define LSC 	PBout(3)


extern u8 gsmg_code[17];

//函数声明
void SMG_Init(void);
void SMG_Display(u8 dat[],u8 pos);

#endif
