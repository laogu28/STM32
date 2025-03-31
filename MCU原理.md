# mcu简介
mcu是一种嵌入式系统，在单一芯片上包括了cpu，记忆体，输入输出接口I/O，计时器的一个小型电脑。中央处理器也就是mcu的核心，负责执行程序。cpu会处理各种数据并进行运算来决定下一步要做什么。记忆体：微控制器里通常会有一个快取记忆体RAM和固化程式码的闪存记忆体ROM 。在启动时ROM会将程式码载入到RAM中，在RAM中执行这些指令，原因是RAM运行速度较快。ROM是一种非挥发性的记忆体，会把数据永久储存。FLASH也是一样，但是可以将数据删除也可以写入新的程序。I/O：MCU有各种接口，比如GPIO，通讯接口常用的有UART，SPI,I2C。这些接口。这写接口会允许MCU和外部设备或传感器进行数据交换。计时器：mcu计时计数的单元，可以用于定时中断，计算时间间隔，产生精确时序信号。
实际流程：微控制器启动，将ROM中的启动程序码载入到RAM中，CPU从RAM中读取程序码的指令来执行各种操作，运行的时候CPU会根据这些数据储存在记忆体中，或者是从输入输出接口与外设进行数据交换，计时器可以产生中断信号让cpu在特定的时间点或是特定事件发生时暂停CPU的操作。
总体来说微控制器就是一台高度集成的计算机，具有控制，运算和连接外部设备的能力。

| 缩写 | 中文名称/含义 | 功能说明 |
|------|-----------------|---------------------------------------------------------------|
| Cortex-M3 CPU | ARM Cortex-M3 处理器内核 | STM32F103 系列的中央处理单元，负责执行指令。 |
| NVIC (Nested Vectored Interrupt Controller) | 嵌套向量中断控制器 | 负责管理和处理各种中断请求，并支持优先级和嵌套。 |
| TPIU (Trace Port Interface Unit) | 跟踪端口接口单元 | 用于向外输出调试/跟踪信息，和 SWD/JTAG 等调试接口配合使用。 |
| SWD/JTAG/ITM/Trace | - SWD (Serial Wire Debug)：串行线调试接口<br>- JTAG (Joint Test Action Group)：JTAG 调试接口<br>- ITM (Instrumentation Trace Macrocell)：调试数据输出模块<br>- Trace：跟踪功能 | 提供调试和跟踪功能，用于实时监测 CPU 运行状况，输出调试信息。 |
| GP DMA (General-Purpose Direct Memory Access) | 通用 DMA（直接存储器访问） | 在外设和存储器之间、存储器与存储器之间进行数据搬运，减轻 CPU 负担。 |
| SRAM | 静态随机存取存储器 | 芯片内部的易失性存储器，用于存放临时数据。 |
| Flash | 片上 Flash 存储器 | 用于存储用户程序和常量数据。 |
| PVD / POR / BOR (Power supervision / Power-On Reset / Brown-Out Reset) | - PVD：可编程电压检测器<br>- POR：上电复位<br>- BOR：欠压复位 | 负责检测电源电压状态并执行复位，保证系统安全。 |
| RCC (Reset and Clock Control) | 复位与时钟控制 | 管理各种时钟源 (HSI, HSE, LSI, LSE, PLL 等) 并向各外设分配时钟，同时控制复位信号。 |
| Backup registers / BKP / VBAT | 备份寄存器 / VBAT 电池供电 | 在主电源断电时由电池供电，用于存储 RTC 和备份寄存器数据。 |
| RTC (Real-Time Clock) | 实时时钟 | 低功耗实时时钟，可使用外部 32.768 kHz 晶振或内部低速时钟。 |
| TIM (Timer) | 定时器 | 包括高级、通用和基本定时器，可用于测量脉冲宽度、输出 PWM 等功能。 |
| USART / UART (Universal Synchronous/Asynchronous Receiver/Transmitter) | 通用同步/异步收发器 | 串口通讯接口，支持同步或异步方式。 |
| SPI (Serial Peripheral Interface) | 串行外设接口 | 高速串行接口，常用于与 Flash、传感器等外设通信。 |
| I2C (Inter-Integrated Circuit) | 集成电路间通信总线 | 双线串行总线，常用于低速外围设备（传感器、EEPROM 等）。 |
| USB (Universal Serial Bus) | 通用串行总线 | 某些型号带有 USB 外设，可实现 USB 设备等功能。 |
| CAN (Controller Area Network) | 控制器局域网 | 工业或汽车领域常用的总线通信。 |
| ADC (Analog-to-Digital Converter) | 模数转换器 | 将模拟电压信号转换为数字值。 |
| DAC (Digital-to-Analog Converter) | 数模转换器 | 将数字值转换为模拟电压输出。（STM32F103 部分子系列不一定带有此功能） |
| WWDG (Window Watchdog) | 窗口看门狗 | 通过设置时间窗口，若程序未在正确的窗口内“喂狗”则复位系统。 |
| IWDG (Independent Watchdog) | 独立看门狗 | 独立于主时钟的看门狗，用于防止系统卡死。 |
| AFIO (Alternate Function I/O) | 复用功能 I/O | 管理管脚复用功能，比如将某些管脚复用为 USART/SPI/I2C 等功能。 |
| APB / AHB (Advanced Peripheral Bus / Advanced High-performance Bus) | - APB：外设总线<br>- AHB：高速总线 | CPU、DMA、存储器和外设间通过不同总线互连，AHB 通常速度更快。 |
