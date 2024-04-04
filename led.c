#include "led.h"

/*******************************************************************************
* �� �� ��         : LED_Init
* ��������		   : LED��ʼ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����
	
	RCC_APB2PeriphClockCmd(LED0_PORT_RCC,ENABLE);
	RCC_APB2PeriphClockCmd(LED1_PORT_RCC,ENABLE);
	RCC_APB2PeriphClockCmd(LED2_PORT_RCC,ENABLE);
	RCC_APB2PeriphClockCmd(LED3_PORT_RCC,ENABLE);
	RCC_APB2PeriphClockCmd(LED4_PORT_RCC,ENABLE);
	RCC_APB2PeriphClockCmd(LED5_PORT_RCC,ENABLE);
	RCC_APB2PeriphClockCmd(LED6_PORT_RCC,ENABLE);
	RCC_APB2PeriphClockCmd(LED7_PORT_RCC,ENABLE);
	RCC_APB2PeriphClockCmd(LED8_PORT_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=LED0_PIN;  //ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(LED0_PORT,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	GPIO_SetBits(LED0_PORT,LED0_PIN);   //��LED�˿����ߣ�Ϩ������LED
	
	GPIO_InitStructure.GPIO_Pin=LED1_PIN; 
	GPIO_Init(LED1_PORT,&GPIO_InitStructure);
	GPIO_SetBits(LED1_PORT,LED1_PIN);
	
	GPIO_InitStructure.GPIO_Pin=LED2_PIN; 
	GPIO_Init(LED2_PORT,&GPIO_InitStructure);
	GPIO_SetBits(LED2_PORT,LED2_PIN);
	
	GPIO_InitStructure.GPIO_Pin=LED3_PIN; 
	GPIO_Init(LED3_PORT,&GPIO_InitStructure);
	GPIO_SetBits(LED3_PORT,LED3_PIN);
	
	GPIO_InitStructure.GPIO_Pin=LED4_PIN; 
	GPIO_Init(LED4_PORT,&GPIO_InitStructure);
	GPIO_SetBits(LED4_PORT,LED4_PIN);
	
	GPIO_InitStructure.GPIO_Pin=LED5_PIN; 
	GPIO_Init(LED5_PORT,&GPIO_InitStructure);
	GPIO_SetBits(LED5_PORT,LED5_PIN);
	
	GPIO_InitStructure.GPIO_Pin=LED6_PIN; 
	GPIO_Init(LED6_PORT,&GPIO_InitStructure);
	GPIO_SetBits(LED6_PORT,LED6_PIN);
	
	GPIO_InitStructure.GPIO_Pin=LED7_PIN; 
	GPIO_Init(LED7_PORT,&GPIO_InitStructure);
	GPIO_SetBits(LED7_PORT,LED7_PIN);
	
	GPIO_InitStructure.GPIO_Pin=LED8_PIN; 
	GPIO_Init(LED8_PORT,&GPIO_InitStructure);
	GPIO_SetBits(LED8_PORT,LED8_PIN);
}

//LED�˿�8λ����ͬʱ��������Ӱ���λ
//д�����ݵ�8λ�˿ڣ����ݵ�λ��Ӧ�˿ڵ�����
//GPIO_Pin��8λ�˿ڵ�λ����
//data��д������
void LED_Write_Data(u16 GPIO_Pin,u8 data)
{
	u8 i,j=GPIO_Pin;    
	for(i=0;i<8;i++)
	{
		if(data&0x01)
			GPIO_WriteBit(GPIOA, j<<i ,Bit_SET); 
		else
			GPIO_WriteBit(GPIOA, j<<i ,Bit_RESET); 
		data = data >> 1 ; 
	}
}



