#ifndef __PWM_H
#define __PWM_H

#include "main.h"
#include "tim.h"

void PWM_Init(void);
void PWMA_Set(uint16_t pwm_d);
void PWMB_Set(uint16_t pwm_d);

#endif // !__PWM_H

