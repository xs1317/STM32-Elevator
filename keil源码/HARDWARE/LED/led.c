#include "led.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

//初始化PF9和PF10为输出口.并使能这两个口的时钟		    
//LED和BCD数码管的 IO初始化
void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;
  //选择GPIO的F组
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟

  //GPIOF9,F10初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_15 | GPIO_Pin_7;//LED0和LED1对应IO口
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉,无信号时为高电平使得LED不亮
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	
	GPIO_SetBits(GPIOA,GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_15 |GPIO_Pin_7);//GPIOA9,A10设置高，灯灭
  
	
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 |GPIO_Pin_13|GPIO_Pin_14 ;//LED0和LED1对应IO口
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉,无信号时为低电平使得BCD数码管不亮
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	GPIO_SetBits(GPIOA,GPIO_Pin_11);//初始为1
}

//设置七段数码管的值
void setSEG(int num)
{
	//先重置数码管
	GPIOA->BSRRH = 0x7800;
	//set the BCDset
  num = num%16;
	GPIOA->BSRRL = num<<11;

}




