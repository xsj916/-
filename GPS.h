#ifndef _NEO_6M_
			#define _NEO_6M_
 
			#include "system.h" 
			#include "stdio.h" 
			#include "SysTick.h"
			
			//UBLOX NEO-6M ����(���,����,���ص�)�ṹ��
			__packed typedef struct  
			{										    
				unsigned short header;					//cfg header,�̶�Ϊ0X62B5(С��ģʽ)
				unsigned short id;						//CFG CFG ID:0X0906 (С��ģʽ)
				unsigned short dlength;				//���ݳ��� 12/13
				unsigned int clearmask;				//�������������(1��Ч)
				unsigned int savemask;				//�����򱣴�����
				unsigned int loadmask;				//�������������
				unsigned char devicemask; 		  	//Ŀ������ѡ������	b0:BK RAM;b1:FLASH;b2,EEPROM;b4,SPI FLASH
				unsigned char  cka;		 			//У��CK_A 							 	 
				unsigned char  ckb;			 		//У��CK_B							 	 
			}_ublox_cfg_cfg; 
			
			//UBLOX NEO-6M UART�˿����ýṹ��
			__packed typedef struct  
			{										    
				unsigned short header;					//cfg header,�̶�Ϊ0X62B5(С��ģʽ)
				unsigned short id;						//CFG PRT ID:0X0006 (С��ģʽ)
				unsigned short dlength;				//���ݳ��� 20
				unsigned char  portid;					//�˿ں�,0=IIC;1=UART1;2=UART2;3=USB;4=SPI;
				unsigned char  reserved;				//����,����Ϊ0
				unsigned short txready;				//TX Ready��������,Ĭ��Ϊ0
				unsigned int mode;					//���ڹ���ģʽ����,��żУ��,ֹͣλ,�ֽڳ��ȵȵ�����.
				unsigned int baudrate;				//����������
				unsigned short inprotomask;		 	//����Э�鼤������λ  Ĭ������Ϊ0X07 0X00����.
				unsigned short outprotomask;		 	//���Э�鼤������λ  Ĭ������Ϊ0X07 0X00����.
				unsigned short reserved4; 				//����,����Ϊ0
				unsigned short reserved5; 				//����,����Ϊ0 
				unsigned char  cka;			 		//У��CK_A 							 	 
				unsigned char  ckb;			    	//У��CK_B							 	 
			}_ublox_cfg_prt; 
			
			//UBLOX NEO-6M ˢ���������ýṹ��
			__packed typedef struct  
			{										    
				unsigned short header;					//cfg header,�̶�Ϊ0X62B5(С��ģʽ)
				unsigned short id;						//CFG RATE ID:0X0806 (С��ģʽ)
				unsigned short dlength;				//���ݳ���
				unsigned short measrate;				//����ʱ��������λΪms�����ٲ���С��200ms��5Hz��
				unsigned short navrate;				//�������ʣ����ڣ����̶�Ϊ1
				unsigned short timeref;				//�ο�ʱ�䣺0=UTC Time��1=GPS Time��
				unsigned char  cka;					//У��CK_A 							 	 
				unsigned char  ckb;					//У��CK_B							 	 
			}_ublox_cfg_rate; 			
			
			unsigned char Ublox_Cfg_Prt(unsigned int baudrate);
			unsigned char Ublox_Cfg_Cfg_Save(void);
			void Ublox_Send_Date(unsigned char* dbuf,unsigned short len);
			void NMEA_GPGGA_Analysis(GPS_PacketTypeDef *GPS_Packet,unsigned char *buf);
			unsigned char Ublox_Cfg_Rate(unsigned short measrate,unsigned char reftime);
			u8 GPS_Check(u8 *buff);
#endif
 
			
			
