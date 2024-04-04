#ifndef _beep_H
#define _beep_H

#include "system.h"

/*  ������ʱ�Ӷ˿ڡ����Ŷ��� */
#define BEEP_PORT 			GPIOB   
#define BEEP_PIN 			GPIO_Pin_0
#define BEEP_PORT_RCC		RCC_APB2Periph_GPIOB

#define BEEP PBout(0)

//��������
void BEEP_Init(void);
void BEEP_Alarm(u8 times,u16 us);

#endif
