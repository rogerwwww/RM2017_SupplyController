#include "sys.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
u8 Flag_Stop=1;                  //ֹͣ��־λ
int Encoder,Position=10000;      //���������������
long SHOW;
int Moto1;                 //���PWM���� Ӧ��Motor�� ��Moto�¾�	

int main(void)
{ 
	Stm32_Clock_Init(9);            //ϵͳʱ������
	delay_init(72);                 //��ʱ��ʼ��
	LED_Init();                     //��ʼ���� LED ���ӵ�Ӳ���ӿ�
	uart_init(72,115200);           //��ʼ������1
	MiniBalance_PWM_Init(7199,0);   //=====��ʼ��PWM 10KHZ ��Ƶ���Է�ֹ�����Ƶʱ�ļ����
	Encoder_Init_TIM2();            //��ʼ��������
  Timer3_Init(99,7199);           //=====10MS��һ���жϷ��������жϷ�������control.c
	while(1)
		{
			printf("Encoder:%d Position:%d \r\n",Encoder,Position);	
		} 
}
