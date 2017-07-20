#ifndef __CONTROL_H
#define __CONTROL_H
#include "config.h"

#define PI 3.14159265
extern uint32_t Encoder;
extern int Moto1;

//int TIM3_IRQHandler(void);  
void Set_Pwm(int moto1);
void Xianfu_Pwm(void);
int myabs(int a);
int Position_PID (int Encoder,int Target);
#endif
