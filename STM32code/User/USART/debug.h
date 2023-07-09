#include <stdio.h>
#include "main.h"
#include "usart.h"
#ifndef __DEBUG_H
#define __DEBUG_H


#define DEBUG

#ifdef DEBUG
    #define DEBUG_printf(format, ...) printf(format "\r\n", ##__VA_ARGS__)
    #define DEBUG_info(tag,format, ...) printf("DEBUG_info["tag"]:" format "\r\n", ##__VA_ARGS__)
    #define DEBUG_warnig(tag,format, ...) printf("DEBUG_warnig["tag"]:" format "\r\n", ##__VA_ARGS__)
    #define DEBUG__error(tag,format, ...) printf("DEBUG__error["tag"]:" format "\r\n",##__VA_ARGS__)
#else
    #define DEBUG_printf(format, ...) printf(format "\r\n", ##__VA_ARGS__)
    #define DEBUG_info(tag,format, ...) 
    #define DEBUG_warnig(tag,format, ...)
    #define DEBUG__error(tag,format, ...) 
#endif

//串口1接收中断初始化
void Debug_Init(void);

//串口1接收完成回调函数
void UART1_RxCpltCallback(UART_HandleTypeDef *huart);

void UART1_ErrorCallback(UART_HandleTypeDef *huart);

#endif // !__DEBUG_H






