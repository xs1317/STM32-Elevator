#include "led.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

//��ʼ��PF9��PF10Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED��BCD����ܵ� IO��ʼ��
void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;
  //ѡ��GPIO��F��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��

  //GPIOF9,F10��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_15 | GPIO_Pin_7;//LED0��LED1��ӦIO��
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����,���ź�ʱΪ�ߵ�ƽʹ��LED����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
	
	GPIO_SetBits(GPIOA,GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_15 |GPIO_Pin_7);//GPIOA9,A10���øߣ�����
  
	
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 |GPIO_Pin_13|GPIO_Pin_14 ;//LED0��LED1��ӦIO��
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����,���ź�ʱΪ�͵�ƽʹ��BCD����ܲ���
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIO
	GPIO_SetBits(GPIOA,GPIO_Pin_11);//��ʼΪ1
}

//�����߶�����ܵ�ֵ
void setSEG(int num)
{
	//�����������
	GPIOA->BSRRH = 0x7800;
	//set the BCDset
  num = num%16;
	GPIOA->BSRRL = num<<11;

}




