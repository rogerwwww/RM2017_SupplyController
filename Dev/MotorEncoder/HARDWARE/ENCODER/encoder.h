#ifndef __ENCODER_H
#define __ENCODER_H
#include "config.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
#define ENCODER_TIM_PERIOD (uint16_t)(65535)   //���ɴ���65535 ��ΪF103�Ķ�ʱ����16λ�ġ�
#define COUNTER_RESET 10000   //��λ�ÿ������棬Ϊ���������д�������趨CNT�ĳ�ʼֵΪ10000�����ٶȿ������棬�ĳ�0����
void Encoder_Init_TIM2(void);
void Encoder_Init_TIM4(void);
int Read_Encoder(uint8_t TIMX);
#endif
