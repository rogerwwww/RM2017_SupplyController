#ifndef __ENCODER_H
#define __ENCODER_H
#include "config.h"

#define ENCODER_TIM_PERIOD (uint16_t)(65535)   //no larger than 65535
#define COUNTER_RESET 10000   //configure the counter reset number
void Encoder_Init_TIM2(void);
void Encoder_Init_TIM4(void);
int Read_Encoder(uint8_t TIMX);
#endif
