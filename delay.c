#include "delay.h"
//������11.0592Mhz����Ƶ�ʣ��ǵ�ѡ��
void delay_tus(unsigned int tus)//@11.0592MHz
{
	unsigned char i;
	i = tus;
	while (--i);
}

void delay_tms(unsigned int tms)
{
	unsigned char i, j;
	unsigned int ttt;
  for(ttt=tms;ttt>0;ttt--)
	{	
	  i = 15;
		j = 90;
		do
		{
			while (--j);
		} while (--i);
	}
}

