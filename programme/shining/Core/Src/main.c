/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_Delay(1000);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
    HAL_Delay(1000);//ѭ���壬reset���õ�ƽ��set���øߵ�ƽ��delayΪ�ߵ͵�ƽ��Ӽ��
		
		/* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) //we have to add a systemclock to use delay
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
//I don't know what is the meaning of these code,even if invalid them the system till work
//Answer: these codes are uesd to initialize the voltage of pin���ڳ�ʼ����ƽ

	/*Configure GPIO pin : PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/*
static void MX_GPIO_Init(void) ������ ��ʼ�� GPIO �������� �ĺ�����������������£�

1. ���ܽ���
ʹ�� GPIO ʱ��
__HAL_RCC_GPIOA_CLK_ENABLE();  // ʹ�� GPIOA ʱ��
__HAL_RCC_GPIOB_CLK_ENABLE();  // ʹ�� GPIOB ʱ��
STM32 �����裨�� GPIO����ʹ��ǰ�������ö�Ӧ��ʱ�ӣ������޷������Ĵ�����

���� GPIO ���Ų���
GPIO_InitStruct.Pin = GPIO_PIN_5;                  // ѡ������ PB5
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;        // �������ģʽ
GPIO_InitStruct.Pull = GPIO_NOPULL;                // ������������
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;       // ����ٶ���Ϊ����
HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);            // Ӧ������
�� PB5 ����Ϊ�������ģʽ���������� LED �����衣

���ó�ʼ��ƽ����ѡ��
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET); // ��ʼ��ƽ����
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);   // ��ʼ��ƽ����
��δ�������������� PB5 �ĳ�ʼ״̬����������ѭ���л᲻���л���ƽ��HAL_GPIO_WritePin����ʵ�ʻᱻ�����������ǣ����ע�͵���Ӱ�칦�ܡ�

2. Ϊ��ע�͵���ƽ�������ܹ�����
��ѭ�����ǳ�ʼֵ��
�������е� while(1) ѭ������ 1 �����л� PB5 ��ƽ��GPIO_PIN_RESET �� GPIO_PIN_SET������ʼ��ƽ��Ӱ���ϵ�˲���״̬�����������Ḳ�ǳ�ʼֵ��

������������ģʽ���ã�
GPIO �� ����ģʽ�������ģʽ���� �������������ٶȡ������������ǹؼ�����ƽ�������ڸ��Ӳ�����

3. �ؼ��ܽ�
�������ã����� GPIO ���ŵĹ���ģʽ������/������������������ٶȡ�����������ȷ�����谴Ԥ�����С�

��Ҫ���ã����ó�ʼ��ƽ����Ӱ���ϵ�˲�䣬�Ǳ��裩��

���ͳ��������� LED��������⡢ͨ�Žӿڣ��� UART_TX��������ʱ��������ô˺�����ʼ�����š�

4. ��չ����
���Լ��ɣ���ɾ�� MX_GPIO_Init()��PB5 ������Ĭ��״̬��ͨ��Ϊ�������룩�������޷����� LED��

�Ż����룺��ɾ���ظ��ĵ�ƽ���ã�HAL_GPIO_WritePin ���ε��ã���������ģʽ���ò��֡�
 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */


void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
