#include "control.h"	

extern int Target_position;

/**
  * @brief  Set the motor PWM output and two digital signals that controls
	*         the direction of the motor.
  * @param  moto1: the PID result for motor control.
  * @retval None
  */
void Set_Pwm(int moto1)
{
	if(moto1 < 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_14);
		GPIO_ResetBits(GPIOB, GPIO_Pin_15);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_14);
		GPIO_SetBits(GPIOB, GPIO_Pin_15);
	}
	TIM_SetCompare1(TIM4, myabs(moto1));
}

/**
  * @brief  Restrict the PWM pulse width within the maximum value.
  * @param  None
  * @retval None
  */
void Xianfu_Pwm(void)
{	
	//The maximum value of PWM width is 8400, and we restrict it within 8000
	int Amplitude=8000;    
  if(Moto1<-Amplitude) Moto1=-Amplitude;	
	if(Moto1>Amplitude)  Moto1=Amplitude;	
}

/**
  * @brief  Calculate absolute value.
  * @param  a: input int.
  * @retval Absolute value of a.
  */
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/**************************************************************************
函数功能：位置式PID控制器
入口参数：编码器测量位置信息，目标位置
返回  值：电机PWM
根据位置式离散PID公式 
pwm=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,,k;
pwm代表输出
**************************************************************************/
/**
  * @brief  Position PID controller.
  * @note   pwm=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
  * @note   e(k) stands for the difference of this sampling
  * @note   e(k-1) stands for the difference of last sampling
  * @note   ∑e(k) stands for the sum of all previous differences.
  * @param  Encoder: the current position read from encoder.
  * @param  Target: target position of the PID controller.
  * @retval PWM value for motor output.
  */
int Position_PID (int Encoder,int Target)
{ 	
	 float Position_KP=120,Position_KI=0.1,Position_KD=500;
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Pwm;                                           //增量输出
}
