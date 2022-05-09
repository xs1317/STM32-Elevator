#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "status.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "exti.h"
#include "timer.h"
//״̬��ֵ����
int UP[6]={0,0,0,0,0,0};
int DOWN[6]={0,0,0,0,0,0};
int MAX = 1;
int MIN = 5;
int STATUS = 0;
int L=1;
int know=1;
int T=0;

//�ж�
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
  delay_init(168);		  //��ʼ����ʱ����
	LED_Init();		        //��ʼ��LED�˿�
	BEEP_Init();
	KEY_Init();
	EXTIX_Init(); 
	TIM3_Int_Init(900-1,8400-1);	//��Ϊ�����ٶ�������ʱ������Ϊ70ms����һ��
	LED0 = 0;
	LED1 = 1;
	LED2 = 1;
	LED3 = 1;
	BEEP = 0;
  while(1)
  {
		 	int i;
		if(T==1) //����ж�
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
		T=0;
		}
	}
	
}
	


