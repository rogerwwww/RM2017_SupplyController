#include "timer.h"
//#include "led.h"
/**************************************************************************
�������ܣ���ʱ�жϳ�ʼ��
��ڲ�����arr���Զ���װֵ  psc��ʱ��Ԥ��Ƶ�� 
����  ֵ����
**************************************************************************/
void Timer4_Init(u16 arr,u16 psc)  
{  
	RCC->APB1ENR|=1<<1;//TIM4ʱ��ʹ��    
 	TIM4->ARR=arr;      //�趨�������Զ���װֵ   
	TIM4->PSC=psc;      //Ԥ��Ƶ��7200,�õ�10Khz�ļ���ʱ��
	TIM4->DIER|=1<<0;   //��������ж�				
	TIM4->DIER|=1<<6;   //�������ж�	   
	TIM4->CR1|=0x01;    //ʹ�ܶ�ʱ��
	//MY_NVIC_Init(1,3,TIM3_IRQn,2);
	NVIC->ISER[TIM4_IRQn / 32] |= (1 << TIM4_IRQn % 32);//!!Priority here of TIM4_IRQn may should be configured
}  
