#ifndef _usart_H
#define _usart_H

#include "system.h" 
#include "stdio.h" 

extern u8 ReceiveData;
extern u8 ReceiveFlag;
extern int Alarm_temper;

void USART3_Init(u32 bound);

#endif


