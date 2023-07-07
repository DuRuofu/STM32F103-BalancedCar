/*
 * @Author: DuRuofu duruofu@qq.com
 * @Date: 2023-07-07 15-48-49
 * @LastEditors: DuRuofu
 * @LastEditTime: 2023-07-07 19-40-08
 * @FilePath: \MDK-ARMd:\duruofu\Project\balancedVehicle\code\project\STM32code\User\Motor\motor.h
 * @Description: 
 * Copyright (c) 2023 by duruofu@foxmail.com All Rights Reserved. 
 */

#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"
#include "pwm.h"

void Motor_Init(void);
void Motor_Ctrl(int16_t pwm, uint8_t n);
void TB6612_Ctrl(uint8_t mode,uint8_t n);
uint16_t my_abs(int16_t n);

#endif // !__MOTOR_H


