#ifndef __MOTOR_H
#define __MOTOR_H
#include "config.h"

#define PWMA   TIM1->CCR1
#define AIN2   PBout(15)
#define AIN1   PBout(14)
#define BIN1   PBout(13)
#define BIN2   PBout(12)
#define PWMB   TIM1->CCR4
void MiniBalance_PWM_Init(void);
void MiniBalance_Motor_Init(void);
#endif
