#include "encoder.h"
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
/**************************************************************************
函数功能：把TIM2初始化为编码器接口模式
入口参数：无
返回  值：无
**************************************************************************/
void Encoder_Init_TIM2(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
//  NVIC_InitTypeDef NVIC_InitStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
 
  
  //GPIO_StructInit(&GPIO_InitStructure);
  /* Configure PA0,PA1 as encoder input */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2);
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM2);
  
  /* Enable the TIM2 Update Interrupt */
//  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
  
  /* Timer configuration in Encoder mode */ 
  //TIM_DeInit(TIM2);
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0; // No prescaling 
  TIM_TimeBaseStructure.TIM_Period = 60000; 
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  
  TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI1, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 0;
  TIM_ICInit(TIM2, &TIM_ICInitStructure);
  
  // Clear all pending interrupts
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  //Reset counter
  TIM2->CNT = 10000;
  
  // ENC_Clear_Speed_Buffer();
  
  TIM_Cmd(TIM2, ENABLE);
}
/**************************************************************************
函数功能：把TIM4初始化为编码器接口模式
入口参数：无
返回  值：无
**************************************************************************/
//void Encoder_Init_TIM4(void)
//{
//	RCC->APB1ENR|=1<<2;     //TIM4时钟使能
//	RCC->APB2ENR|=1<<3;    //使能PORTb时钟
//	//BSRRL changed from CRL
//	GPIOB->BSRRL&=0X00FFFFFF;//PB6 PB7
//	GPIOB->BSRRL|=0X44000000;//浮空输入
//	/* 把定时器初始化为编码器模式 */ 
//	TIM4->PSC = 0x0;//预分频器
//	TIM4->ARR = ENCODER_TIM_PERIOD-1;//设定计数器自动重装值 
//  TIM4->CCMR1 |= 1<<0;          //输入模式，IC1FP1映射到TI1上
//  TIM4->CCMR1 |= 1<<8;          //输入模式，IC2FP2映射到TI2上
//  TIM4->CCER |= 0<<1;           //IC1不反向
//  TIM4->CCER |= 0<<5;           //IC2不反向
//	TIM4->SMCR |= 3<<0;	          //SMS='011' 所有的输入均在上升沿和下降沿有效
//	TIM4->CR1 |= 0x01;    //CEN=1，使能定时器
//}
/**************************************************************************
函数功能：单位时间读取编码器计数
入口参数：定时器
返回  值：速度值
**************************************************************************/
int Read_Encoder(uint8_t TIMX)
{
   int Encoder_TIM;    
   switch(TIMX)
	 {
	   case 2:  Encoder_TIM= (short)TIM2 -> CNT; break;
		 case 3:  Encoder_TIM= (short)TIM3 -> CNT; break;	
		 case 4:  Encoder_TIM= (short)TIM4 -> CNT; break;	
		 default:  Encoder_TIM=0;
	 }
		return Encoder_TIM;
}


