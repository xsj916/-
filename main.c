#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "wifi.h"
#include "ds18b20.h"
#include "smg.h"
#include "beep.h"
#include "adc.h"
#define Q 0.01  // ������������
#define R 0.1   // ������������

char get_ad(A) {
    // �滻Ϊʵ�ʵĻ�ȡģ������ֵ�ĺ���
    // ����򵥵ط���һ���̶�ֵ��Ϊʾ��
    return A;
}

float kalman_filter(int measurement) {
    static float estimate = 0;  // ����״̬
    static float error_covariance = 1;  // ���Э����

    // Ԥ�ⲽ��
    float predicted_estimate = estimate;
    float predicted_error_covariance = error_covariance + Q;

    // ���²���
    float kalman_gain = predicted_error_covariance / (predicted_error_covariance + R);
    estimate = predicted_estimate + kalman_gain * (measurement - predicted_estimate);
    error_covariance = (1 - kalman_gain) * predicted_error_covariance;

    return estimate;
}

int Alarm_temper=32;	//�����¶�
int temper,i=0,j=0;
int main()
{	
	u16 value=0;
	BEEP_Init();
	ADCx_Init();
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //�ж����ȼ������2��
	USART3_Init(115200);
	LED_Init();
	delay_ms(500);		// ��ʱȷ��WIFIģ����ȫ���� ����޷����óɹ����ԼӴ���ʱ
	WIFI_Config();		// ����WIFIģ��
	DS18B20_Init();
	DS18B20_GetTemperture();
	delay_ms(30);
	temper=DS18B20_GetTemperture()*10;	//��ȡ�¶�
	while(1)
	{	
		i++;

		if(i >= 250)	//2s ��wifiģ�鷢���¶�����
		{
			i = 0;
			value=Get_ADC_Value(ADC_Channel_9,1);
			value=get_ad(value);
			printf("AT+CIPSEND=0,11\r\n");	//׼����wifi��������
			delay_ms(10);	//�ȴ�ģ���ȶ�
			temper=DS18B20_GetTemperture()*10;	//��ȡ�¶�
			if(temper<0)
			{
				printf("-");
			}
			else
			{
				printf(" ");
			}
			delay_ms(3000);
			printf("%2.1f,%4.d\r\n",(float)temper/10,value);//kalman_filter()
		}

		// �ﵽ�����¶� ���������
		if(temper >= Alarm_temper)
		{
			j++;
			if(j < 50)
			{
				//BEEP_Alarm(40,240);
			}
			if(j > 100)
			{
				j = 0;
			}
		}else
		{
			j = 0;
		}
	}
}
