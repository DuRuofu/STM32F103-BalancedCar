#include "app.h"

//编码器计数值
int16_t car_speed_1 = 0;
int16_t car_speed_2 = 0;

float pitch,roll,yaw; 		    //欧拉角
short aacx,aacy,aacz;			//加速度传感器原始数据
short gyrox,gyroy,gyroz;		//陀螺仪原始数据
float temp;					    //温度

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


    //MPU_Init();//MPU6050初始化
    while(MPU_Init()!=0){printf("MPU初始化\r\n");}//DMP库初始化
    while(mpu_dmp_init()!=0){printf("DMP库初始化:%d\r\n",mpu_dmp_init());}//DMP库初始化

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
    OLED_ShowSignedNum(2,1,roll,5);
    OLED_ShowSignedNum(2,6,pitch,5);
    OLED_ShowSignedNum(2,11,yaw,5);
    OLED_ShowSignedNum(3,1,temp,5);

    // // mpu6050任务
    while(mpu_dmp_get_data(&pitch, &roll, &yaw));	//必须要用while等待，才能读取成功
    MPU_Get_Accelerometer(&aacx,&aacy, &aacz);		//得到加速度传感器数据
    MPU_Get_Gyroscope(&gyrox, &gyroy, &gyroz);		//得到陀螺仪数据
    temp=MPU_Get_Temperature();						//得到温度信息
    printf("X:%.1f°  Y:%.1f°  Z:%.1f°  %.2f°C\r\n",roll,pitch,yaw,temp/100);//串口1输出采集信息
    HAL_Delay(10);
}


//定时器中断回调函数(2ms一次)
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
        //小车运动任务

   }
}



//pid部分
//小车机械零点
int32_t Car_zero=1.5f; 
//直立环Kp,Kd     
int32_t Upright_Kp=1.5f;  
int32_t Upright_Kd=1.5f;  

//直立环
//平衡车控制*
//函数功能：控制小车保持直立
//Angle：采集到的实际角度值
//Gyro： 采集到的实际角速度值
int PID_Upright(float Angle,float Gyro)
{  
   float err;
    int pwm_zhili;
    err=Car_zero-Angle;    //期望值-实际值，这里期望小车平衡，因此期望值就是机械中值       
    pwm_zhili=Upright_Kp*err+Gyro*Upright_Kd;//计算平衡控制的电机PWM
    return pwm_zhili;
}

//速度环


//转向环


