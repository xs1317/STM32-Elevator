#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 


/*����ķ�ʽ��ͨ��ֱ�Ӳ����⺯����ʽ��ȡIO*/
#define KEY_1U		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0) 
#define KEY_2U 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)	
#define KEY_3U 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2) 
#define KEY_4U   	GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)	
#define KEY_2D   	GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)	
#define KEY_3D   	GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5)	
#define KEY_4D   	GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)	
#define KEY_5D   	GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)	


#define KEY_EX1   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)	
#define KEY_EX2   GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)	

#define KEY_L1    GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_8)	
#define KEY_L2    GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_9)	
#define KEY_L3    GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_10)	
#define KEY_L4    GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_11)	
#define KEY_L5    GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12)	


/*���淽ʽ��ͨ��λ��������ʽ��ȡIO*/
/*
#define KEY0 		PEin(4)   	//PE4
#define KEY1 		PEin(3)		//PE3 
#define KEY2 		PEin(2)		//P32
#define WK_UP 	PAin(0)		//PA0
*/



void KEY_Init(void);	//IO��ʼ��
u8 KEY_Scan(u8);  		//����ɨ�躯��	

#endif
