#ifndef __APP_H
#define __APP_H

#include "main.h"
#include "tim.h"
#include "led.h"
#include "oled.h"
#include "motor.h"
#include "encoder.h"
#include "serial_it_config.h"


void App_Init(void);
void App_Task(void);

#endif // !__APP_H
