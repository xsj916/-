#ifndef _NEO_6M_
			#define _NEO_6M_
 
			#include "system.h" 
			#include "stdio.h" 
			#include "SysTick.h"
			
			//UBLOX NEO-6M 配置(清除,保存,加载等)结构体
			__packed typedef struct  
			{										    
				unsigned short header;					//cfg header,固定为0X62B5(小端模式)
				unsigned short id;						//CFG CFG ID:0X0906 (小端模式)
				unsigned short dlength;				//数据长度 12/13
				unsigned int clearmask;				//子区域清除掩码(1有效)
				unsigned int savemask;				//子区域保存掩码
				unsigned int loadmask;				//子区域加载掩码
				unsigned char devicemask; 		  	//目标器件选择掩码	b0:BK RAM;b1:FLASH;b2,EEPROM;b4,SPI FLASH
				unsigned char  cka;		 			//校验CK_A 							 	 
				unsigned char  ckb;			 		//校验CK_B							 	 
			}_ublox_cfg_cfg; 
			
			//UBLOX NEO-6M UART端口设置结构体
			__packed typedef struct  
			{										    
				unsigned short header;					//cfg header,固定为0X62B5(小端模式)
				unsigned short id;						//CFG PRT ID:0X0006 (小端模式)
				unsigned short dlength;				//数据长度 20
				unsigned char  portid;					//端口号,0=IIC;1=UART1;2=UART2;3=USB;4=SPI;
				unsigned char  reserved;				//保留,设置为0
				unsigned short txready;				//TX Ready引脚设置,默认为0
				unsigned int mode;					//串口工作模式设置,奇偶校验,停止位,字节长度等的设置.
				unsigned int baudrate;				//波特率设置
				unsigned short inprotomask;		 	//输入协议激活屏蔽位  默认设置为0X07 0X00即可.
				unsigned short outprotomask;		 	//输出协议激活屏蔽位  默认设置为0X07 0X00即可.
				unsigned short reserved4; 				//保留,设置为0
				unsigned short reserved5; 				//保留,设置为0 
				unsigned char  cka;			 		//校验CK_A 							 	 
				unsigned char  ckb;			    	//校验CK_B							 	 
			}_ublox_cfg_prt; 
			
			//UBLOX NEO-6M 刷新速率配置结构体
			__packed typedef struct  
			{										    
				unsigned short header;					//cfg header,固定为0X62B5(小端模式)
				unsigned short id;						//CFG RATE ID:0X0806 (小端模式)
				unsigned short dlength;				//数据长度
				unsigned short measrate;				//测量时间间隔，单位为ms，最少不能小于200ms（5Hz）
				unsigned short navrate;				//导航速率（周期），固定为1
				unsigned short timeref;				//参考时间：0=UTC Time；1=GPS Time；
				unsigned char  cka;					//校验CK_A 							 	 
				unsigned char  ckb;					//校验CK_B							 	 
			}_ublox_cfg_rate; 			
			
			unsigned char Ublox_Cfg_Prt(unsigned int baudrate);
			unsigned char Ublox_Cfg_Cfg_Save(void);
			void Ublox_Send_Date(unsigned char* dbuf,unsigned short len);
			void NMEA_GPGGA_Analysis(GPS_PacketTypeDef *GPS_Packet,unsigned char *buf);
			unsigned char Ublox_Cfg_Rate(unsigned short measrate,unsigned char reftime);
			u8 GPS_Check(u8 *buff);
#endif
 
			
			
