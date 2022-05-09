#include "exti.h"
#include "delay.h" 
#include "led.h" 
#include "key.h"
#include "beep.h"
#include "delay.h"
#include "status.h"
//�ⲿ�ж�0�������,��������ݰ�ť����,ɨ��һ���ⲿ��ť
void EXTI0_IRQHandler(void)
{
		
	if(KEY_EX1==0)	 
	{
		//���ڰ�ť���
		//������������뵱ǰ¥��Ĺ�ϵ���뵽UP��DOWN����
		if(KEY_L1==0)
		{
			if(L==1)
			{
				if(know==1)
					UP[L]=1;
				else
					DOWN[L]=1;
			}
			else if(L>1)
			{
				DOWN[1]=1;
			}
			MIN = MIN<1?MIN:1;
			MAX = MAX<1?1:MAX;
		}
		
		if(KEY_L2==0)
		{
			if(L==2)
			{
				if(know==1)
					UP[L]=1;
				else
					DOWN[L]=1;
			}
			else if(L>2)
			{
				DOWN[2]=1;
			}
			else if(L<2)
			{
				UP[2]=1;
			}
			MIN = MIN<2?MIN:2;
			MAX = MAX<2?2:MAX;
			
		}
		
		if(KEY_L3==0)
		{			
			if(L==3)
			{
				if(know==1)
					UP[L]=1;
				else
					DOWN[L]=1;
			}
			else if(L>3)
			{
				DOWN[3]=1;
			}
			else if(L<3)
			{
				UP[3]=1;
			}
			MIN = MIN<3?MIN:3;
			MAX = MAX<3?3:MAX;
			
		}	
		
		if(KEY_L4==0)
		{			
			if(L==4)
			{
				if(know==1)
					UP[L]=1;
				else
					DOWN[L]=1;
			}
			else if(L>4)
			{
				DOWN[4]=1;
			}
			else if(L<4)
			{
				UP[4]=1;
			}
			MIN = MIN<4?MIN:4;
			MAX = MAX<4?4:MAX;
			
		}
		
		if(KEY_L5==0)
		{			
			if(L==5)
			{
				if(know==1)
					UP[L]=1;
				else
					DOWN[L]=1;
			}
			else if(L<5)
			{
				UP[5]=1;
			}
			MIN = MIN<5?MIN:5;
			MAX = MAX<5?5:MAX;
		}
		
		//���ⰴť���
		if(KEY_1U==0)
		{
			UP[1] = 1;
			MIN = MIN<1?MIN:1;
			MAX = MAX<1?1:MAX;
		}
		
		if(KEY_2U==0)
		{
		  UP[2] = 1;
			MIN = MIN<2?MIN:2;
			MAX = MAX<2?2:MAX;
		}
		
		if(KEY_3U==0)
		{
		  UP[3] = 1;
			MIN = MIN<3?MIN:3;
			MAX = MAX<3?3:MAX;
		}
		
		if(KEY_4U==0)
		{
			UP[4] = 1;
			MIN = MIN<4?MIN:4;
			MAX = MAX<4?4:MAX;
		}
		
		
		if(KEY_2D==0)
		{
			DOWN[2] = 1;
			MIN = MIN<2?MIN:2;
			MAX = MAX<2?2:MAX;
		}
		
		
		if(KEY_3D==0)
		{
		  DOWN[3] = 1;
			MIN = MIN<3?MIN:3;
			MAX = MAX<3?3:MAX;
		}
		
		if(KEY_4D==0)
		{
		  DOWN[4] = 1;
			MIN = MIN<4?MIN:4;
			MAX = MAX<4?4:MAX;
		}
		
		if(KEY_5D==0)
		{
		  DOWN[5] = 1;
			MIN = MIN<5?MIN:5;
			MAX = MAX<5?5:MAX;
		}
		
	}		 
	 EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ 
}	

//������ť�ж�
void EXTI1_IRQHandler(void)
{
	static int stop = 0;

	//���º�������죬����ά�ֵ�ǰ״̬
	if(stop==0)
	{
		//�رն�ʱ���жϺͰ����ж�
		LED3 = 0;
		BEEP = 1;
	  EXTI->IMR &= ~(EXTI_Line0);
		TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE);
		
		
		stop = 1;
	}
	else
	{
		//������ʱ���жϺͰ����ж�
		LED3 = 1;
		BEEP = 0;
		EXTI->IMR |= EXTI_Line0;
		TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
		
		stop = 0;
	}
	EXTI_ClearITPendingBit(EXTI_Line1); 
}
	   
//�ⲿ�жϳ�ʼ������
//��ʼ��PE2~4,PA0Ϊ�ж�����.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //������Ӧ��IO�ڳ�ʼ��
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);//PE0 ���ӵ��ж���0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource1);//PE1 ���ӵ��ж���1
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line0|EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
	
	//�����ȡ���дθߵ����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//�ⲿ�ж�0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����

	//������ť
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//�ⲿ�ж�1
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
	
}












