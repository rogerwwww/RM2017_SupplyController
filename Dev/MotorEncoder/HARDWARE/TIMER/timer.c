#include "timer.h"
//#include "led.h"
/**************************************************************************
函数功能：定时中断初始化
入口参数：arr：自动重装值  psc：时钟预分频数 
返回  值：无
**************************************************************************/
void Timer4_Init(u16 arr,u16 psc)  
{  
	RCC->APB1ENR|=1<<1;//TIM4时钟使能    
 	TIM4->ARR=arr;      //设定计数器自动重装值   
	TIM4->PSC=psc;      //预分频器7200,得到10Khz的计数时钟
	TIM4->DIER|=1<<0;   //允许更新中断				
	TIM4->DIER|=1<<6;   //允许触发中断	   
	TIM4->CR1|=0x01;    //使能定时器
	//MY_NVIC_Init(1,3,TIM3_IRQn,2);
	NVIC->ISER[TIM4_IRQn / 32] |= (1 << TIM4_IRQn % 32);//!!Priority here of TIM4_IRQn may should be configured
}  
