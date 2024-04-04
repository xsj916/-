#include "wifi.h"

//以下可以根据需求来修改
#define WiFiName "ESP01"		//Wifi名称
#define PassWord "12345678"		//WiFi密码
#define IP "192.168.4.1"		//模块IP
#define Port "8088"				//模块端口

//Wifi配置
void WIFI_Config(void)
{
    printf("AT+CWMODE_DEF=2\r\n");  //开启AP模式
	while(ReceiveFlag != 2);
	ReceiveFlag = 0;
    delay_ms(100);
    printf("AT+CWSAP_DEF=\"%s\",\"%s\",11,4\r\n",WiFiName,PassWord);  //热点名称
	while(ReceiveFlag != 2);
	ReceiveFlag = 0;
    delay_ms(100);
    printf("AT+CIPAP_DEF=\"%s\"\r\n",IP); 	//IP
	while(ReceiveFlag != 2);
	ReceiveFlag = 0;
    delay_ms(100);
    printf("AT+CIPMUX=1\r\n");              //设置多连接来开启服务器
	while(ReceiveFlag != 2);
	ReceiveFlag = 0;
    delay_ms(100);
    printf("AT+CIPSERVER=1,%s\r\n",Port);   //开启模块服务器端口
	while(ReceiveFlag != 2);
	ReceiveFlag = 0;
    delay_ms(100);
}
