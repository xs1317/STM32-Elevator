#include "exti.h"
#include "delay.h" 
#include "led.h" 
#include "key.h"
#include "beep.h"
#include "delay.h"
#include "status.h"
//外部中断0服务程序,有厢外呼梯按钮按下,扫描一遍外部按钮
void EXTI0_IRQHandler(void)
{
		
	if(KEY_EX1==0)	 
	{
		//厢内按钮检查
		//厢内请求根据与当前楼层的关系插入到UP或DOWN序列
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
		
		//厢外按钮检查
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
	 EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位 
}	

//紧急按钮中断
void EXTI1_IRQHandler(void)
{
	static int stop = 0;

	//按下后蜂鸣器响，电梯维持当前状态
	if(stop==0)
	{
		//关闭定时器中断和按键中断
		LED3 = 0;
		BEEP = 1;
	  EXTI->IMR &= ~(EXTI_Line0);
		TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE);
		
		
		stop = 1;
	}
	else
	{
		//开启定时器中断和按键中断
		LED3 = 1;
		BEEP = 0;
		EXTI->IMR |= EXTI_Line0;
		TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
		
		stop = 0;
	}
	EXTI_ClearITPendingBit(EXTI_Line1); 
}
	   
//外部中断初始化程序
//初始化PE2~4,PA0为中断输入.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //按键对应的IO口初始化
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);//PE0 连接到中断线0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource1);//PE1 连接到中断线1
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line0|EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
	
	//输入获取具有次高的优先级
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置

	//紧急按钮
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//外部中断1
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	
}












