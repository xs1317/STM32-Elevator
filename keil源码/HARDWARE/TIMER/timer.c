#include "timer.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "status.h"


//通用定时器3中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM3,ENABLE); //使能定时器3
	
	//调度算法优先级低于输入获取，可以被抢断
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//定时器3中断控制电梯电梯调度和移动
void TIM3_IRQHandler(void)
{
	/*
	int i;
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{

		switch(STATUS)
		{
			case 0:                      //停止状态
				
				if(know==1)                  
				{
					if(UP[L]==0)           //检查当前楼层是否有请求  
					{
						if(L<MAX)
						{
							if(L==MIN)
							{
								for(i=1;i<=5;i++)
								{
									if(UP[i]==1 || DOWN[i]==1)
										MIN = i;
								}
							}
							STATUS = 1;
							LED0 = 1;
							LED1 = 0;
						}
						else if(L==MAX && MAX>MIN)        //达到最高层,若MAX=MIN则维持在停止状态；若MAX>MIN说明还要前往低楼层，执行下降过程
						{
							//更新MAX
							for(i=5;i>=1;i--)
							{
								if(UP[i]==1 || DOWN[i]==1)
									MAX = i;
							}
							LED0=1;LED2=0;
							STATUS = 2;
							know = 2;
						}
					}
					else
					{
						UP[L]=0;
					}
				}
			  
				if(know==2)
				{
					if(DOWN[L]==0)
					{
						if(L>MIN)
						{
							if(L==MAX)
							{
								for(i=5;i>=1;i--)
								{
									if(UP[i]==1 || DOWN[i]==1)
										MAX = i;
								}
							}
							STATUS = 2;
							LED0=1;
							LED2=0;
						}
						else if(L==MIN && MIN<MAX)
						{
							//更新MIN
							for(i=1;i<=5;i++)
							{
								if(UP[i]==1 || DOWN[i]==1)
									MIN = i;
							}
							LED0=1;LED1=0;
							STATUS=1;
							know=1;
						}
					}
					else
					{
						DOWN[L]=1;
					}
				}
				break;			
				
			case 1:                       //上升状态
					L += 1;
					setSEG(L);
					if(UP[L]==1 || L==MAX)               //该层有请求或达到MAX
					{
						UP[L]=0;
					  LED0=0;LED1=1;
						STATUS = 0;
					}
				break;
				
			case 2:                        //下降状态
					L-=1;
					setSEG(L);
					if(DOWN[L]==1 || L==MIN)
					{
						DOWN[L]=0;
						LED0=0;LED2=1;
						STATUS = 0;
					}
				break;
		}
		
	}
	*/
	T=1;
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}
