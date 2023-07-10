#include "encoder.h"

//编码器计数初始化
void Encoder_Count_Init(void)
{
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);

}

//编码器数据读取
int32_t Encoder_Value(uint8_t n)
{
    if (n == 1)
    {
        return (int32_t)(__HAL_TIM_GET_COUNTER(&htim2));
    }
    else if (n == 2)
    {
        return (int32_t)(__HAL_TIM_GET_COUNTER(&htim3));
    }
    else
    {
        return 0;
    }
}

//编码器清零
void Encoder_Count_Clear(uint8_t n)
{
    if (n == 1)
    {
        __HAL_TIM_SET_COUNTER(&htim2, 0);
    }
    else if (n == 2)
    {
        __HAL_TIM_SET_COUNTER(&htim3, 0);
    }
}


