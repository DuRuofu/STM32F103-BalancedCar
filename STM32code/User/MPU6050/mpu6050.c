/**
  ******************************************************************************
  * 文件名程: main.c 
  * 作    者: 硬石嵌入式开发团队
  * 版    本: V1.0
  * 编写日期: 2015-10-04
  * 功    能: MPU6050驱动程序
  ******************************************************************************
  * 说明：
  * 本例程配套硬石stm32开发板YS-F1Pro使用。
  * 
  * 淘宝：
  * 论坛：[url=http://www.ing10bbs.com]http://www.ing10bbs.com[/url]
  * 版权归硬石嵌入式开发团队所有，请勿商用。
  ******************************************************************************
  */
 
/* 包含头文件 ----------------------------------------------------------------*/
#include "mpu6050.h"
#include "bsp_i2c.h"
/* 私有类型定义 --------------------------------------------------------------*/
/* 私有宏定义 ----------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/
/* 扩展变量 ------------------------------------------------------------------*/
/* 私有函数原形 --------------------------------------------------------------*/
/* 函数体 --------------------------------------------------------------------*/
 
/**
  * 函数功能: 写数据到MPU6050寄存器
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
void MPU6050_WriteReg(uint8_t reg_add,uint8_t reg_dat)
{
        I2C_Start();
        I2C_SendByte(MPU6050_SLAVE_ADDRESS);
        I2C_WaitAck();
        I2C_SendByte(reg_add);
        I2C_WaitAck();
        I2C_SendByte(reg_dat);
        I2C_WaitAck();
        I2C_Stop();
}
 
/**
  * 函数功能: 从MPU6050寄存器读取数据
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
void MPU6050_ReadData(uint8_t reg_add,unsigned char *Read,uint8_t num)
{
        unsigned char i;
         
        I2C_Start();
        I2C_SendByte(MPU6050_SLAVE_ADDRESS);
        I2C_WaitAck();
        I2C_SendByte(reg_add);
        I2C_WaitAck();
         
        I2C_Start();
        I2C_SendByte(MPU6050_SLAVE_ADDRESS+1);
        I2C_WaitAck();
         
        for(i=0;i<(num-1);i++){
                *Read=I2C_ReadByte(1);
                Read++;
        }
        *Read=I2C_ReadByte(0);
        I2C_Stop();
}
 
/**
  * 函数功能: 初始化MPU6050芯片
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
void MPU6050_Init(void)
{
  int i=0,j=0;
  //在初始化之前要延时一段时间，若没有延时，则断电后再上电数据可能会出错
  for(i=0;i<1000;i++)
  {
    for(j=0;j<1000;j++)
    {
      ;
    }
  }
        MPU6050_WriteReg(MPU6050_RA_PWR_MGMT_1, 0x00);            //解除休眠状态
        MPU6050_WriteReg(MPU6050_RA_SMPLRT_DIV , 0x07);            //陀螺仪采样率，1KHz
        MPU6050_WriteReg(MPU6050_RA_CONFIG , 0x06);                //低通滤波器的设置，截止频率是1K，带宽是5K
        MPU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG , 0x00);          //配置加速度传感器工作在2G模式，不自检
        MPU6050_WriteReg(MPU6050_RA_GYRO_CONFIG, 0x18);     //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
}
 
/**
  * 函数功能: 读取MPU6050的ID
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
uint8_t MPU6050ReadID(void)
{
        unsigned char Re = 0;
    MPU6050_ReadData(MPU6050_RA_WHO_AM_I,&Re,1);    //读器件地址
        if(Re != 0x68)
        {
                //printf("MPU6050 dectected error!\r\n检测不到MPU6050模块，请检查模块与开发板的接线");
                return 0;
        }
        else
        {
                //printf("MPU6050 ID = %d\r\n",Re);
                return 1;
        }
                 
}
 
/**
  * 函数功能: 读取MPU6050的加速度数据
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
void MPU6050ReadAcc(short *accData)
{
    uint8_t buf[6];
    MPU6050_ReadData(MPU6050_ACC_OUT, buf, 6);
    accData[0] = (buf[0] << 8) | buf[1];
    accData[1] = (buf[2] << 8) | buf[3];
    accData[2] = (buf[4] << 8) | buf[5];
}
 
/**
  * 函数功能: 读取MPU6050的角速度数据
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
void MPU6050ReadGyro(short *gyroData)
{
    uint8_t buf[6];
    MPU6050_ReadData(MPU6050_GYRO_OUT,buf,6);
    gyroData[0] = (buf[0] << 8) | buf[1];
    gyroData[1] = (buf[2] << 8) | buf[3];
    gyroData[2] = (buf[4] << 8) | buf[5];
}
 
/**
  * 函数功能: 读取MPU6050的原始温度数据
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
void MPU6050ReadTemp(short *tempData)
{
        uint8_t buf[2];
    MPU6050_ReadData(MPU6050_RA_TEMP_OUT_H,buf,2);     //读取温度值
    *tempData = (buf[0] << 8) | buf[1];
}
 
/**
  * 函数功能: 读取MPU6050的温度数据，转化成摄氏度
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */
void MPU6050_ReturnTemp(short*Temperature)
{
        short temp3;
        uint8_t buf[2];
         
        MPU6050_ReadData(MPU6050_RA_TEMP_OUT_H,buf,2);     //读取温度值
  temp3= (buf[0] << 8) | buf[1];
        *Temperature=(((double) (temp3 + 13200)) / 280)-13;
}
 
/******************* (C) COPYRIGHT 2015-2020 硬石嵌入式开发团队 *****END OF FILE****/