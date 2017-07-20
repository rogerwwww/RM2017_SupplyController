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
�������ܣ�λ��ʽPID������
��ڲ���������������λ����Ϣ��Ŀ��λ��
����  ֵ�����PWM
����λ��ʽ��ɢPID��ʽ 
pwm=Kp*e(k)+Ki*��e(k)+Kd[e��k��-e(k-1)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  
��e(k)����e(k)�Լ�֮ǰ��ƫ����ۻ���;����kΪ1,2,,k;
pwm�������
**************************************************************************/
/**
  * @brief  Position PID controller.
  * @note   pwm=Kp*e(k)+Ki*��e(k)+Kd[e��k��-e(k-1)]
  * @note   e(k) stands for the difference of this sampling
  * @note   e(k-1) stands for the difference of last sampling
  * @note   ��e(k) stands for the sum of all previous differences.
  * @param  Encoder: the current position read from encoder.
  * @param  Target: target position of the PID controller.
  * @retval PWM value for motor output.
  */
int Position_PID (int Encoder,int Target)
{ 	
	 float Position_KP=120,Position_KI=0.1,Position_KD=500;
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //����ƫ��
	 Integral_bias+=Bias;	                                 //���ƫ��Ļ���
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_Bias);       //λ��ʽPID������
	 Last_Bias=Bias;                                       //������һ��ƫ�� 
	 return Pwm;                                           //�������
}
