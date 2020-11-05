/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "usb_host.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdint.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "inttypes.h"
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
I2C_HandleTypeDef hi2c1;

I2S_HandleTypeDef hi2s3;

SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart2;

osThreadId defaultTaskHandle;
osMessageQId USART_QueueHandle;
/* USER CODE BEGIN PV */
char str1[120];
osThreadId Foam1Handle, Foam2Handle, Foam3Handle, Foam4Handle;
osThreadId Brushes1Handle, Brushes2Handle, Brushes3Handle, Brushes4Handle;
osThreadId Washing1Handle, Washing2Handle, Washing3Handle, Washing4Handle;
osThreadId Drying1Handle, Drying2Handle, Drying3Handle, Drying4Handle;
osSemaphoreId SemHandle;
osMessageQId pushNumber;
volatile xSemaphoreHandle xMutex;
//int flag=1;
volatile unsigned char buttonPush;
volatile unsigned char status;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2S3_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART2_UART_Init(void);
void StartDefaultTask(void const * argument);

/* USER CODE BEGIN PFP */
void Foam1(void const * argument);
void Foam2(void const * argument);
void Foam3(void const * argument);
void Foam4(void const * argument);
void Brushes1(void const * argument);
void Brushes2(void const * argument);
void Brushes3(void const * argument);
void Brushes4(void const * argument);
void Washing1(void const * argument);
void Washing2(void const * argument);
void Washing3(void const * argument);
void Washing4(void const * argument);
void Drying1(void const * argument);
void Drying2(void const * argument);
void Drying3(void const * argument);
void Drying4(void const * argument);
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
  MX_I2C1_Init();
  MX_I2S3_Init();
  MX_SPI1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  xMutex = xSemaphoreCreateMutex();
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */

  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */


  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */

  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 1280);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */

  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
  PeriphClkInitStruct.PLLI2S.PLLI2SN = 192;
  PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2S3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2S3_Init(void)
{

  /* USER CODE BEGIN I2S3_Init 0 */

  /* USER CODE END I2S3_Init 0 */

  /* USER CODE BEGIN I2S3_Init 1 */

  /* USER CODE END I2S3_Init 1 */
  hi2s3.Instance = SPI3;
  hi2s3.Init.Mode = I2S_MODE_MASTER_TX;
  hi2s3.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s3.Init.DataFormat = I2S_DATAFORMAT_16B;
  hi2s3.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
  hi2s3.Init.AudioFreq = I2S_AUDIOFREQ_96K;
  hi2s3.Init.CPOL = I2S_CPOL_LOW;
  hi2s3.Init.ClockSource = I2S_CLOCK_PLL;
  hi2s3.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;
  if (HAL_I2S_Init(&hi2s3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2S3_Init 2 */

  /* USER CODE END I2S3_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
                          |Audio_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : CS_I2C_SPI_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CS_I2C_SPI_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OTG_FS_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PDM_OUT_Pin */
  GPIO_InitStruct.Pin = PDM_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(PDM_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT1_Pin */
  GPIO_InitStruct.Pin = BOOT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CLK_IN_Pin */
  GPIO_InitStruct.Pin = CLK_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(CLK_IN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin
                           Audio_RST_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin
                          |Audio_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_FS_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : MEMS_INT2_Pin */
  GPIO_InitStruct.Pin = MEMS_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MEMS_INT2_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

}

/* USER CODE BEGIN 4 */
void Foam1(void const * argument)
{
	uint32_t tickcount = osKernelSysTick();
	for(;;)
	{
		sprintf(str1, "Foam applied to the first car, it took 30 sec\r\n");
		osDelayUntil(&tickcount, 30000);
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		xSemaphoreTake(xMutex, portMAX_DELAY);
		HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),strlen(str1)+1);
		xSemaphoreGive(xMutex);
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		osThreadDef(brushes1, Brushes1, osPriorityNormal, 0, 256);
		Brushes1Handle = osThreadCreate(osThread(brushes1), NULL);
		osThreadTerminate(NULL);
	}
}

void Foam2(void const * argument)
{
	uint32_t tickcount = osKernelSysTick();
	for(;;)
	{
		sprintf(str1, "Foam applied to the second car, it took 30 sec\r\n");
		osDelayUntil(&tickcount, 30000);
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		xSemaphoreTake(xMutex, portMAX_DELAY);
		HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),strlen(str1)+1);
		xSemaphoreGive(xMutex);
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		osThreadDef(brushes2, Brushes2, osPriorityNormal, 0, 256);
		Brushes2Handle = osThreadCreate(osThread(brushes2), NULL);
		osThreadTerminate(NULL);
	}
}

void Foam3(void const * argument)
{
	uint32_t tickcount = osKernelSysTick();
	for(;;)
	{
		sprintf(str1, "Foam applied to the third car, it took 30 sec\r\n");
		osDelayUntil(&tickcount, 30000);
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		xSemaphoreTake(xMutex, portMAX_DELAY);
		HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),strlen(str1)+1);
		xSemaphoreGive(xMutex);
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	    osThreadDef(brushes3, Brushes3, osPriorityNormal, 0, 256);
	    Brushes3Handle = osThreadCreate(osThread(brushes3), NULL);
	    osThreadTerminate(NULL);
	}
}

void Foam4(void const * argument)
{
	uint32_t tickcount = osKernelSysTick();
	for(;;)
	{
		sprintf(str1, "Foam applied to the fourth car, it took 30 sec\r\n");
		osDelayUntil(&tickcount, 30000);
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		xSemaphoreTake(xMutex, portMAX_DELAY);
		HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),strlen(str1)+1);
		xSemaphoreGive(xMutex);
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	    osThreadDef(brushes4, Brushes4, osPriorityNormal, 0, 256);
	    Brushes4Handle = osThreadCreate(osThread(brushes4), NULL);
	    osThreadTerminate(NULL);
	}
}

void Brushes1(void const * argument)
{
	uint32_t tickcount = osKernelSysTick();
	for(;;)
	{
		sprintf(str1, "Brushing the first car is completed it took 30 sec\r\n");
		osDelayUntil(&tickcount, 30000);
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		xSemaphoreTake(xMutex, portMAX_DELAY);
		HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),strlen(str1)+1);
		xSemaphoreGive(xMutex);
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		osThreadDef(washing1, Washing1, osPriorityNormal, 0, 256);
		Washing1Handle = osThreadCreate(osThread(washing1), NULL);
		osThreadTerminate(NULL);
	}
}

void Brushes2(void const * argument)
{
	uint32_t tickcount = osKernelSysTick();
	for(;;)
	{
		sprintf(str1, "Brushing the second car is completed it took 30 sec\r\n");
		osDelayUntil(&tickcount, 30000);
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		xSemaphoreTake(xMutex, portMAX_DELAY);
		HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),strlen(str1)+1);
		xSemaphoreGive(xMutex);
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		osThreadDef(washing2, Washing2, osPriorityNormal, 0, 256);
		Washing2Handle = osThreadCreate(osThread(washing2), NULL);
		osThreadTerminate(NULL);
	}
}


void Brushes3(void const * argument)
{
	uint32_t tickcount = osKernelSysTick();
	for(;;)
	{
		sprintf(str1, "Brushing the third car is completed it took 30 sec\r\n");
		osDelayUntil(&tickcount, 30000);
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		xSemaphoreTake(xMutex, portMAX_DELAY);
		HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),strlen(str1)+1);
		xSemaphoreGive(xMutex);
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		osThreadDef(washing3, Washing3, osPriorityNormal, 0, 256);
		Washing3Handle = osThreadCreate(osThread(washing3), NULL);
		osThreadTerminate(NULL);
	}
}


void Brushes4(void const * argument)
{
	uint32_t tickcount = osKernelSysTick();
	for(;;)
	{
		sprintf(str1, "Brushing the forth car is completed it took 30 sec\r\n");
		osDelayUntil(&tickcount, 30000);
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		xSemaphoreTake(xMutex, portMAX_DELAY);
		HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),strlen(str1)+1);
		xSemaphoreGive(xMutex);
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		osSemaphoreRelease(SemHandle);
		osThreadDef(washing4, Washing4, osPriorityNormal, 0, 256);
		Washing4Handle = osThreadCreate(osThread(washing4), NULL);
		osThreadTerminate(NULL);
	}
}


void Washing1(void const * argument)
{
	uint32_t tickcount = osKernelSysTick();
	for(;;)
	{
		sprintf(str1, "Washing the first car is completed it took 60 sec\r\n");
		osDelayUntil(&tickcount, 60000);
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		xSemaphoreTake(xMutex, portMAX_DELAY);
		HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),strlen(str1)+1);
		xSemaphoreGive(xMutex);
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		osThreadDef(drying1, Drying1, osPriorityNormal, 0, 256);
		Drying1Handle = osThreadCreate(osThread(drying1), NULL);
		osThreadTerminate(NULL);
	}
}

void Washing2(void const * argument)
{
	uint32_t tickcount = osKernelSysTick();
	for(;;)
	{
		sprintf(str1, "Washing the second car is completed it took 60 sec\r\n");
		osDelayUntil(&tickcount, 60000);
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		xSemaphoreTake(xMutex, portMAX_DELAY);
		HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),strlen(str1)+1);
		xSemaphoreGive(xMutex);
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		osThreadDef(drying2, Drying2, osPriorityNormal, 0, 256);
		Drying2Handle = osThreadCreate(osThread(drying2), NULL);
		osThreadTerminate(NULL);
	}
}

void Washing3(void const * argument)
{
	uint32_t tickcount = osKernelSysTick();
	for(;;)
	{
		sprintf(str1, "Washing the third car is completed it took 60 sec\r\n");
		osDelayUntil(&tickcount, 60000);
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		xSemaphoreTake(xMutex, portMAX_DELAY);
		HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),strlen(str1)+1);
		xSemaphoreGive(xMutex);
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		osThreadDef(drying3, Drying3, osPriorityNormal, 0, 256);
		Drying3Handle = osThreadCreate(osThread(drying3), NULL);
		osThreadTerminate(NULL);
	}
}

void Washing4(void const * argument)
{
	uint32_t tickcount = osKernelSysTick();
	for(;;)
	{
		sprintf(str1, "Washing the fourth car is completed it took 60 sec\r\n");
		osDelayUntil(&tickcount, 60000);
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		xSemaphoreTake(xMutex, portMAX_DELAY);
		HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),strlen(str1)+1);
		xSemaphoreGive(xMutex);
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		osThreadDef(drying4, Drying4, osPriorityNormal, 0, 256);
		Drying4Handle = osThreadCreate(osThread(drying4), NULL);
		osThreadTerminate(NULL);
	}
}

void Drying1(void const * argument)
{
	uint32_t tickcount = osKernelSysTick();
	for(;;)
	{
		sprintf(str1, "Drying the first car is completed it took 30 sec\r\n");
		osDelayUntil(&tickcount, 30000);
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		xSemaphoreTake(xMutex, portMAX_DELAY);
		HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),strlen(str1)+1);
		xSemaphoreGive(xMutex);
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		osThreadTerminate(NULL);
	}
}

void Drying2(void const * argument)
{
	uint32_t tickcount = osKernelSysTick();
	for(;;)
	{
		sprintf(str1, "Drying the second car is completed it took 30 sec\r\n");
		osDelayUntil(&tickcount, 30000);
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		xSemaphoreTake(xMutex, portMAX_DELAY);
		HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),strlen(str1)+1);
		xSemaphoreGive(xMutex);
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		osThreadTerminate(NULL);
	}
}

void Drying3(void const * argument)
{
	uint32_t tickcount = osKernelSysTick();
	for(;;)
	{
		sprintf(str1, "Drying the third car is completed it took 30 sec\r\n");
		osDelayUntil(&tickcount, 30000);
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		xSemaphoreTake(xMutex, portMAX_DELAY);
		HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),strlen(str1)+1);
		xSemaphoreGive(xMutex);
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		osThreadTerminate(NULL);
	}
}

void Drying4(void const * argument)
{
	uint32_t tickcount = osKernelSysTick();
	for(;;)
	{
		sprintf(str1, "Drying the fouth car is completed it took 30 sec\r\n");
		osDelayUntil(&tickcount, 30000);
		HAL_NVIC_DisableIRQ(EXTI0_IRQn);
		xSemaphoreTake(xMutex, portMAX_DELAY);
		HAL_UART_Transmit(&huart2,(uint8_t*)str1,strlen(str1),strlen(str1)+1);
		xSemaphoreGive(xMutex);
		HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		osThreadTerminate(NULL);
	}
}

void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	  HAL_UART_Transmit(&huart2,"p\r\n",3,5);
	  if (buttonPush == 4) buttonPush = 0;
	  buttonPush++;
	  status = 1;
  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */

  /* USER CODE END EXTI0_IRQn 1 */
}

//---------------------------------------------------------------
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* init code for USB_HOST */
  MX_USB_HOST_Init();
  /* USER CODE BEGIN 5 */
	  /* Infinite loop */
	  for(;;)
	  {
		  if (status)
		  {
			  status = 0;
			  osDelay(30);
			  switch(buttonPush)
			  {
			  	  case 1: ;
			  	  	  osThreadDef(foam1, Foam1, osPriorityNormal, 0, 256);
			  	  	  Foam1Handle = osThreadCreate(osThread(foam1), NULL);
			  	  	  break;
			  	  case 2: ;
			  	  	  osThreadDef(foam2, Foam2, osPriorityNormal, 0, 256);
			  	  	  Foam2Handle = osThreadCreate(osThread(foam2), NULL);
			  	  	  break;
			  	  case 3: ;
			  	  	  osThreadDef(foam3, Foam3, osPriorityNormal, 0, 256);
			  	  	  Foam3Handle = osThreadCreate(osThread(foam3), NULL);
			  	  	  break;
			  	  case 4: ;
			  	  	  osThreadDef(foam4, Foam4, osPriorityNormal, 0, 256);
			  	  	  Foam4Handle = osThreadCreate(osThread(foam4), NULL);
			  	  	  break;
			  	  default: ;
			  	  	  break;
			 	}
			  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		  }
		  osDelay(1);
		}
	  }
  /* USER CODE END 5 */


/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM2 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM2) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
