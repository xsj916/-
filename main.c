#include "system.h"
#include "SysTick.h"
#include "led.h"
#include "usart.h"
#include "wifi.h"
#include "ds18b20.h"
#include "smg.h"
#include "beep.h"
#include "adc.h"
#define Q 0.01  // 过程噪声方差
#define R 0.1   // 测量噪声方差

char get_ad(A) {
    // 替换为实际的获取模拟输入值的函数
    // 这里简单地返回一个固定值作为示例
    return A;
}

float kalman_filter(int measurement) {
    static float estimate = 0;  // 估计状态
    static float error_covariance = 1;  // 误差协方差

    // 预测步骤
    float predicted_estimate = estimate;
    float predicted_error_covariance = error_covariance + Q;

    // 更新步骤
    float kalman_gain = predicted_error_covariance / (predicted_error_covariance + R);
    estimate = predicted_estimate + kalman_gain * (measurement - predicted_estimate);
    error_covariance = (1 - kalman_gain) * predicted_error_covariance;

    return estimate;
}

int Alarm_temper=32;	//报警温度
int temper,i=0,j=0;
int main()
{	
	u16 value=0;
	BEEP_Init();
	ADCx_Init();
	SysTick_Init(72);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断优先级分组分2组
	USART3_Init(115200);
	LED_Init();
	delay_ms(500);		// 延时确保WIFI模块完全启动 如果无法配置成功可以加大延时
	WIFI_Config();		// 配置WIFI模块
	DS18B20_Init();
	DS18B20_GetTemperture();
	delay_ms(30);
	temper=DS18B20_GetTemperture()*10;	//获取温度
	while(1)
	{	
		i++;

		if(i >= 250)	//2s 向wifi模块发送温度数据
		{
			i = 0;
			value=Get_ADC_Value(ADC_Channel_9,1);
			value=get_ad(value);
			printf("AT+CIPSEND=0,11\r\n");	//准备向wifi发送数据
			delay_ms(10);	//等待模块稳定
			temper=DS18B20_GetTemperture()*10;	//获取温度
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

		// 达到报警温度 响起蜂鸣器
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
