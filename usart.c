#include "usart.h"		 

u8 ReceiveData;
u8 ReceiveFlag;	//2:接收到OK

int fputc(int ch,FILE *p)  //函数默认的，在使用printf函数时自动调用
{
	USART_SendData(USART3,(u8)ch);	
	while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET);
	return ch;
}

int fgetc(FILE *stream)
{
	while(!(USART3->SR & (1 << 5))){};//等待数据接收完成
	return USART3->DR;
}

/*******************************************************************************
* 函 数 名         : USART3_Init
* 函数功能		   : USART3初始化函数
* 输    入         : bound:波特率
* 输    出         : 无
*******************************************************************************/ 
void USART3_Init(u32 bound)
{
   //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
 
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//TX			   //串口输出PB10
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //复用推挽输出
	GPIO_Init(GPIOB,&GPIO_InitStructure);  /* 初始化串口输入IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;//RX			 //串口输入PB9
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //模拟输入
	GPIO_Init(GPIOB,&GPIO_InitStructure); /* 初始化GPIO */
	
	/*WIFI模块引脚配置*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	    //推挽输出
	GPIO_Init(GPIOB,&GPIO_InitStructure);  /* 初始化串口输入IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	    //推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* 初始化串口输入IO */
	
	GPIO_SetBits(GPIOB,GPIO_Pin_2);
	GPIO_SetBits(GPIOA,GPIO_Pin_15);

	//USART3 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART3, &USART_InitStructure); //初始化串口1
	
	USART_Cmd(USART3, ENABLE);  //使能串口1 
	
	USART_ClearFlag(USART3, USART_FLAG_TC);
		
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启相关中断

	//USART3 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、	
}

/*******************************************************************************
* 函 数 名         : USART3_IRQHandler
* 函数功能		   : USART3中断函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/ 
void USART3_IRQHandler(void)                	//串口3中断服务程序
{
	static u16 ReceiveCount = 0,temp = 0,tempFlag = 0;
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断
	{
		ReceiveData = USART_ReceiveData(USART3);//(USART3->DR);	//读取接收到的数据
		if(ReceiveFlag == 0 && ReceiveData == 'O')	//等待接收到OK
		{
			ReceiveFlag = 1;
		}
		if(ReceiveFlag == 1 && ReceiveData == 'K')
		{
			ReceiveFlag = 2;
		}
		// 接收手机发来的修改报警温度命令
		if(ReceiveData == 't' || ReceiveData == 'e' || ReceiveData == 'm' || ReceiveData == 'p' || ReceiveData == '=')
		{
			ReceiveCount++;
		}else if(ReceiveCount < 5)	//未接收到完整的 temp= 就重新开始接收
		{
			ReceiveCount = 0;
			temp = 0;
			tempFlag = 0;
		}else	//已接收到temp=
		{
			if(ReceiveData != '.')	//存储温度 忽略小数点
			{
				temp *= 10;
				temp += ReceiveData - '0';
				tempFlag++;
			}
			if(tempFlag == 3)
			{
				tempFlag = 0;
				ReceiveCount = 0;
				Alarm_temper = temp;	//将要修改的报警温度存储起来
				temp = 0;
			}
		}
		USART_ClearITPendingBit(USART3, USART_IT_RXNE); //手动清除一遍接收中断标志位
	} 
}
