#include "app.h"

//编码器计数值
int16_t car_speed_1 = 0;
int16_t car_speed_2 = 0;

short Acel[3];
short Gyro[3];
float Temp;

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
     
    //测试电机
    Motor_Ctrl(300,1);
    Motor_Ctrl(300,2);

    //硬件I2C初始化
	I2cMaster_Init();

	//MPU6050初始化
	MPU6050_Init();

    //开始数据采样
    HAL_TIM_Base_Start_IT(&htim4);      //启动定时器4 
}


/**
 * @description: 系统应用循环任务
 * @return {*}
 */
void App_Task(void)
{
    LED_Toggle();//测试LED
    //HAL_Delay(100);
    //测试串口
    //显示电机速度
    OLED_ShowSignedNum(1,1,car_speed_1,5);
    OLED_ShowSignedNum(1,8,car_speed_2,5);
    //MPU6050值
    OLED_ShowSignedNum(2,1,Acel[0],5);
    OLED_ShowSignedNum(2,6,Acel[1],5);
    OLED_ShowSignedNum(2,11,Acel[2],5);
    OLED_ShowSignedNum(3,1,Gyro[0],5);
    OLED_ShowSignedNum(3,6,Gyro[1],5);
    OLED_ShowSignedNum(3,11,Gyro[2],5);
    OLED_ShowSignedNum(4,1,Temp,5);
    // // mpu6050任务
     MPU6050ReadAcc(Acel);
     MPU6050ReadGyro(Gyro);

    //printf("加速度：%8d%8d%8d",Acel[0],Acel[1],Acel[2]);
    //printf("陀螺仪%8d%8d%8d",Gyro[0],Gyro[1],Gyro[2]);
    HAL_Delay(10);
}


//定时器中断回调函数(1ms一次)
uint16_t encoder_count=0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){   
   if(htim == &htim4)  //判断中断是否来自于定时器4
   {
        //编码器测速任务
        encoder_count++;
        if(encoder_count==5)
        {
            //计数值清零
            encoder_count=0;
            //读取编码器速度
            car_speed_1 = Encoder_Value(1);
            car_speed_2 = Encoder_Value(2);
            //放大10倍
            car_speed_1=car_speed_1*10;
            car_speed_2=car_speed_2*10;
            //清零编码器计数值
            Encoder_Count_Clear(1);
            Encoder_Count_Clear(2);
        }

        // MPU6050_ReturnTemp(&Temp);
        // mpu6050任务
        //MPU6050ReadAcc(Acel);
        //MPU6050ReadGyro(Gyro);
        //小车运动任务

   }
}


