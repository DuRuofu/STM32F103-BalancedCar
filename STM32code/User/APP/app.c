#include "app.h"


//编码器计数值
int16_t encoder_speed_1 = 0;
int16_t encoder_speed_2 = 0;


/**
 * @description: 系统应用初始化
 * @return {*}
 */
void App_Init(void)
{
    OLED_Init();                        //0.96oled初始化
    Motor_Init();                       //电机初始化
    USART_IT_Config();                  //总串口接收初始化
    Encoder_Count_Init();               //编码器计数初始化
    HAL_TIM_Base_Start_IT(&htim4);      //启动定时器4  
    OLED_ShowString( 1, 1, "Hello World!");
    //测试电机
    Motor_Ctrl(300,1);
    Motor_Ctrl(300,2);
}


/**
 * @description: 系统应用循环任务
 * @return {*}
 */
void App_Task(void)
{
    //LED_Toggle();//测试LED
    //HAL_Delay(100);
    //测试串口
    DEBUG_info("main","Hello World"); 
    //显示电机速度
    OLED_ShowSignedNum(2,1,encoder_speed_1,5);
    OLED_ShowSignedNum(2,8,encoder_speed_2,5);
    //电机速度控制

}





uint16_t encoder_count=0;
//定时器中断回调函数(1ms一次)
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){   
   if(htim == &htim4)  //判断中断是否来自于定时器4
   {
        //编码器测试任务
        encoder_count++;
        if(encoder_count==10)
        {
            //读取编码器速度
            encoder_speed_1 = Encoder_Value(1);
            encoder_speed_2 = Encoder_Value(2);
            //放大10倍
            encoder_speed_1=encoder_speed_1*10;
            encoder_speed_2=encoder_speed_2*10;
            //清零编码器计数值
            Encoder_Count_Clear(1);
            Encoder_Count_Clear(2);
            //计数值清零
            encoder_count=0;
        }
   }
}


