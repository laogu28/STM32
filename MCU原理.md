# MCU（Microcontroller Unit，微控制器）

MCU 是一种集成了处理器核心、存储器、输入/输出外设和其他功能模块的微型计算机系统。它广泛应用于嵌入式系统中，用于控制和执行特定任务。

## 一、MCU 的硬件结构

### 1. 处理器核心（CPU）
- **功能**：执行指令、逻辑运算和数据处理。
- **组成**：
  - **算术逻辑单元（ALU）**：负责数学运算（加减乘除）和逻辑操作（与、或、非）。
  - **寄存器组**：存储临时数据（如通用寄存器、程序计数器 PC、状态寄存器 SR）。
  - **控制单元**：解码指令并协调各模块工作。

### 2. 存储器系统
- **Flash ROM**：存储程序代码（只读，掉电不丢失）。
- **SRAM**：存储运行时变量和堆栈数据（读写，掉电丢失）。
- **EEPROM（可选）**：存储用户配置数据（可擦写，掉电不丢失）。

### 3. 总线系统
- **地址总线**：传输存储器或外设的地址信息。
- **数据总线**：传输实际数据（如指令或外设数据）。
- **控制总线**：传输控制信号（如读/写使能、中断请求）。

### 4. 外设模块
- **通用输入输出（GPIO）**：控制引脚电平（输入检测按键、输出驱动 LED）。
- **定时器/计数器（TIM）**：生成精确延时、PWM 波形或捕获外部信号。
- **通信接口**：如 UART（串口）、SPI、I2C、CAN 等，用于设备间通信。
- **模数转换器（ADC）**：将模拟信号（如温度传感器输出）转换为数字信号。
- **中断控制器（如 NVIC）**：管理多个中断源的优先级和响应。

### 5. 时钟系统
- **时钟源**：内部 RC 振荡器（HSI）、外部晶振（HSE）或锁相环（PLL）。
- **时钟分配**：通过分频/倍频为 CPU 和外设提供不同频率的时钟信号。

### 6. 电源管理
- **供电模块**：支持多种电压（如 3.3V/5V）。
- **低功耗模式**：睡眠模式、停机模式等，降低能耗。

## 二、MCU 运行流程详解

### 1. 上电复位
- MCU 复位后，从固定地址（如 `0x00000000`）读取初始堆栈指针和程序计数器。

### 2. 启动初始化
- 执行启动代码（如 `startup_stm32f103xx.s`），配置系统时钟、初始化 SRAM 和外设。

### 3. 主程序循环
- 运行用户编写的 `main()` 函数，处理任务（如读取传感器、控制外设）。

### 4. 中断处理
- 若发生中断（如按键按下、定时器溢出）：
  1. 暂停当前任务，保存 CPU 寄存器状态（压栈）。
  2. 跳转到中断服务程序（ISR）执行特定操作。
  3. 恢复现场，返回主程序继续运行。

### 5. 低功耗模式
- 根据需求进入低功耗状态，等待外部事件唤醒（如按键或定时器中断）。


# Stm32f103xx增强型模块框图

![image](https://github.com/user-attachments/assets/e7625864-c6d9-4676-ab51-bd330fb2bf54)

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
