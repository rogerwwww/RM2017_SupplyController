#include "config.h"
/**
  * @brief  Configure PB14, PB15 in OD output mode and PB6 in PWM output mode.
  * @param  None
  * @retval None
  */
void MiniBalance_Motor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* GPIOB clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	/* Configure PB14, PB15 in output open drain mode */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* Configure PB6(TIM4_CH1) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
}

/**
  * @brief  Call MiniBalance_Motor_Init to initiate motor output pins, 
            initiate TIM4 for PWM. 
  * @param  None
  * @retval None
  */
void MiniBalance_PWM_Init(void)
{	
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef	TIM_OCInitStructure;
	uint16_t PrescalerValue = 0;
	
	/* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	MiniBalance_Motor_Init();	//Initiate needed Motor IOs
	
	/* Compute the prescaler value, config TIM4 counter clock at 84MHz */
	PrescalerValue = (uint16_t) ((SystemCoreClock /2) / 84000000) - 1;

	/* Time base configuration, config PWM output cycle at 10kHz */
	TIM_TimeBaseStructure.TIM_Period = 8399;
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM4, ENABLE);

  /* TIM4 enable counter */
  TIM_Cmd(TIM4, ENABLE);


//	
//	RCC->APB2ENR|=1<<11;			 //使能TIM1时钟		
//	RCC->APB2ENR|=1<<2;				//PORTA时钟使能		 
//	//BSRRH changed from CRH
//	GPIOA->BSRRH&=0XFFFF0FF0;		//PORTA8 11复用输出
//	GPIOA->BSRRH|=0X0000B00B;		//PORTA8 11复用输出
//	TIM1->ARR=arr;						 //设定计数器自动重装值 
//	TIM1->PSC=psc;						 //预分频器不分频
//	TIM1->CCMR2|=6<<12;				//CH4 PWM1模式	
//	TIM1->CCMR1|=6<<4;				 //CH1 PWM1模式	
//	TIM1->CCMR2|=1<<11;				//CH4预装载使能	 
//	TIM1->CCMR1|=1<<3;				 //CH1预装载使能		
//	TIM1->CCER|=1<<12;				 //CH4输出使能		 
//	TIM1->CCER|=1<<0;					//CH1输出使能	
//	TIM1->BDTR |= 1<<15;			 //TIM1必须要这句话才能输出PWM
//	TIM1->CR1=0x8000;					//ARPE使能 
//	TIM1->CR1|=0x01;					//使能定时器1 												
} 

