#ifndef __LED_H
#define __LED_H
#include "sys.h"


//LED�˿ڶ���
#define LED0 PAout(9)	// DS0
#define LED1 PAout(10)	// DS1	 
#define LED2 PAout(15) //DS2
#define LED3 PAout(7) 
//����BCD�˿�
#define BCD0 PAout(11)
#define BCD1 PAout(12)
#define BCD2 PAout(13)
#define BCD3 PAout(14)

//��ʾLED״̬

void setSEG(int num);
void LED_Init(void);//��ʼ��		 		
#endif
