#include "usart.h"		 

u8 ReceiveData;
u8 ReceiveFlag;	//2:���յ�OK

int fputc(int ch,FILE *p)  //����Ĭ�ϵģ���ʹ��printf����ʱ�Զ�����
{
	USART_SendData(USART3,(u8)ch);	
	while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
	return ch;
}

int fgetc(FILE *stream)
{
	while(!(USART3->SR & (1 << 5))){};//�ȴ����ݽ������
	return USART3->DR;
}

/*******************************************************************************
* �� �� ��         : USART3_Init
* ��������		   : USART3��ʼ������
* ��    ��         : bound:������
* ��    ��         : ��
*******************************************************************************/ 
void USART3_Init(u32 bound)
{
   //GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
 
	
	/*  ����GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//TX			   //�������PB10
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //�����������
	GPIO_Init(GPIOB,&GPIO_InitStructure);  /* ��ʼ����������IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;//RX			 //��������PB9
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //ģ������
	GPIO_Init(GPIOB,&GPIO_InitStructure); /* ��ʼ��GPIO */
	
	/*WIFIģ����������*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	    //�������
	GPIO_Init(GPIOB,&GPIO_InitStructure);  /* ��ʼ����������IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	    //�������
	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* ��ʼ����������IO */
	
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	GPIO_SetBits(GPIOA,GPIO_Pin_15);

	//USART3 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART3, &USART_InitStructure); //��ʼ������1
	
	USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���1 
	
	USART_ClearFlag(USART3, USART_FLAG_TC);
		
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//��������ж�

	//USART3 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����	
}

/*******************************************************************************
* �� �� ��         : USART3_IRQHandler
* ��������		   : USART3�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/ 
void USART3_IRQHandler(void)                	//����3�жϷ������
{
	static u16 ReceiveCount = 0,temp = 0,tempFlag = 0;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�
	{
		ReceiveData = USART_ReceiveData(USART3);//(USART3->DR);	//��ȡ���յ�������
		if(ReceiveFlag == 0 && ReceiveData == 'O')	//�ȴ����յ�OK
		{
			ReceiveFlag = 1;
		}
		if(ReceiveFlag == 1 && ReceiveData == 'K')
		{
			ReceiveFlag = 2;
		}
		// �����ֻ��������޸ı����¶�����
		if(ReceiveData == 't' || ReceiveData == 'e' || ReceiveData == 'm' || ReceiveData == 'p' || ReceiveData == '=')
		{
			ReceiveCount++;
		}else if(ReceiveCount < 5)	//δ���յ������� temp= �����¿�ʼ����
		{
			ReceiveCount = 0;
			temp = 0;
			tempFlag = 0;
		}else	//�ѽ��յ�temp=
		{
			if(ReceiveData != '.')	//�洢�¶� ����С����
			{
				temp *= 10;
				temp += ReceiveData - '0';
				tempFlag++;
			}
			if(tempFlag == 3)
			{
				tempFlag = 0;
				ReceiveCount = 0;
				Alarm_temper = temp;	//��Ҫ�޸ĵı����¶ȴ洢����
				temp = 0;
			}
		}
		USART_ClearITPendingBit(USART3, USART_IT_RXNE); //�ֶ����һ������жϱ�־λ
	} 
}
