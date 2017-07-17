#include "control.h"	
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
int Target_position=10000;    //��ʼֵ��10000��Ŀ��ֵ��10000
//int TIM4_IRQHandler(void)  
//{    
//	if(TIM4->SR&0X0001)//10ms��ʱ�ж�
//	{   
//		  TIM4->SR&=~(1<<0);                                         //===�����ʱ��1�жϱ�־λ		 
//		  Encoder=Read_Encoder(2);                                  //===��ȡ��������λ������ ��ʼֵ��10000�����encoder.c ��encoder.h
//  		Led_Flash(100);                                           //===LED��˸;ָʾ��Ƭ����������	
//		  Moto1=Position_PID(Encoder,Target_position);              //===λ��PID������
//		  Xianfu_Pwm();                                             //===PWM�޷�
//    	Set_Pwm(Moto1);                                          //===��ֵ��PWM�Ĵ���  
//	}       	
//	 return 0;	  
//} 

/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
��ڲ�����PWM
����  ֵ����
**************************************************************************/
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

/**************************************************************************
�������ܣ�����PWM��ֵ 
��ڲ�������
����  ֵ����
**************************************************************************/
void Xianfu_Pwm(void)
{	
	int Amplitude=8000;    //===PWM������8400 ������8000
  if(Moto1<-Amplitude) Moto1=-Amplitude;	
	if(Moto1>Amplitude)  Moto1=Amplitude;	
}

/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
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
