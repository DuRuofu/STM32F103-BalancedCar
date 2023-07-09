# STM32-BalancedCar



### 代码结构：

``` 
STM32code:
		 - Core       //包含了与 STM32 微控制器核心相关的代码
          - Drivers   //包含了 STM32 微控制器的外设驱动程序
          - MDK-ARM   //该目录包含了 Keil MDK（Microcontroller Development Kit）的项目文件和设置。
          - Output    //该目录用于存放编译生成的目标文件、可执行文件或者其他生成的输出文件
          - User      //该目录是用户自定义的代码目录，您可以在此处添加自己的应用程序代码或者其他自定义功能实现。
          - .gitignore //该文件是 Git 版本控制系统使用的配置文件，用于指定 Git 忽略哪些文件或目录的变更。
          - keilkill.bat  //清除编译输出的批处理文件
          - STM32code.ioc //该文件是 STM32CubeMX 的项目文件
```

### 资源分配：

#### 串口：

串口1：debug

#### 定时器：

定时器1：产生两路PWM
定时器2：编码器测速
定时器3：编码器测速
定时器4：
