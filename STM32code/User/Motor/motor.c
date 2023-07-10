/*
 * @Author: DuRuofu
 * @Date: 2023-07-07 15-48-41
 * @LastEditors: DuRuofu
 * @LastEditTime: 2023-07-10 11-01-38
 * @FilePath: \MDK-ARMd:\duruofu\Project\balancedVehicle\code\project\STM32code\User\Motor\motor.c
 * @Description: 电机驱动模块(使用TB6612)
 * Copyright (c) 2023 by duruofu@foxmail.com All Rights Reserved. 
 */

#include "motor.h"



// 定义控制脚,如果使用cubemx生成,设置TB6612的四个控制引脚的用户标签分别为AIN1,AIN2,BIN1,BIN2,下面的宏定义注释即可。
// #define AIN1_Pin GPIO_PIN_14
// #define AIN1_GPIO_Port GPIOC
// #define AIN2_Pin GPIO_PIN_15
// #define AIN2_GPIO_Port GPIOC
// #define BIN1_Pin GPIO_PIN_14
// #define BIN1_GPIO_Port GPIOB
// #define BIN2_Pin GPIO_PIN_15
// #define BIN2_GPIO_Port GPIOB



/**
 * @description: 电机初始化,让电机不乱动
 * @return {*}
 */
void Motor_Init(void)
{
    //控制引脚初始化：
    /*Init_code  不使用cubemx可自行添加*/
    //PWM初始化
    PWM_Init();
    //关闭两个电机
    TB6612_Ctrl(2,1);
    TB6612_Ctrl(2,2);
}


/**
 * @description: 进行电机控制
 * @param {int8_t} pwm  期望的PWM
 * @param {uint8_t} n   第几个电机
 * @return {*}
 */
void Motor_Ctrl(int16_t pwm, uint8_t n)
{
    uint16_t pwm_num=0;
	pwm_num = my_abs(pwm);
    
    switch (n)
    {
    case 1:
        if(pwm >= 0)
        {
            TB6612_Ctrl(1,1);
        }
        else
        {
            TB6612_Ctrl(0,1);
        }
        PWMA_Set(pwm_num);
        break;
    case 2:
        if(pwm >= 0)
        {
            TB6612_Ctrl(1,2);

        }
        else
        {
            TB6612_Ctrl(0,2);
        }
        PWMB_Set(pwm_num);
        break;    
    default:
        break;
    }
}


/**
 * @description: 控制TB6612驱动芯片驱动模式,
 * @param {uint8_t} mode 0:反转  1:正转  2：制动
 * @param {uint8_t} n
 * @return {*}
 */
void TB6612_Ctrl(uint8_t mode,uint8_t n)
{
    switch (mode)
    {
    case 0:
        if (n ==1 ) // 1 0  反转
        {
            HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
        }
        if (n ==2 )
        {
            HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET);
            HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
        }
        break;
    case 1:
        if (n ==1 ) //0 1 正转
        {
            HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);
        }
        if (n ==2 )
        {
            HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_SET);
        }
        break; 
    case 2: // 0 0 制动
        if (n ==1 )
        {
            HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
        }
        if (n ==2 )
        {
            HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
        }
        break;    
    default: // 模式错误 制动
        if (n ==1 )
        {
            HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
        }
        if (n ==2 )
        {
            HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
        }
        break;
    }
}



//***********绝对值函数
uint16_t my_abs(int16_t n)
{
    uint16_t a =0;
    if(n<0){a=(-n);}
    if(n>=0){a=n;}
    return a;
}

