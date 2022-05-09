#include "timer.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "status.h"


//ͨ�ö�ʱ��3�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��3
	
	//�����㷨���ȼ����������ȡ�����Ա�����
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//��ʱ��3�жϿ��Ƶ��ݵ��ݵ��Ⱥ��ƶ�
void TIM3_IRQHandler(void)
{
	/*
	int i;
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{

		switch(STATUS)
		{
			case 0:                      //ֹͣ״̬
				
				if(know==1)                  
				{
					if(UP[L]==0)           //��鵱ǰ¥���Ƿ�������  
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
						else if(L==MAX && MAX>MIN)        //�ﵽ��߲�,��MAX=MIN��ά����ֹͣ״̬����MAX>MIN˵����Ҫǰ����¥�㣬ִ���½�����
						{
							//����MAX
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
							//����MIN
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
				
			case 1:                       //����״̬
					L += 1;
					setSEG(L);
					if(UP[L]==1 || L==MAX)               //�ò��������ﵽMAX
					{
						UP[L]=0;
					  LED0=0;LED1=1;
						STATUS = 0;
					}
				break;
				
			case 2:                        //�½�״̬
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
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}
