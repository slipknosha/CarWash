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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tasks.h"
#include "init.h"
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


osThreadId defaultTaskHandle;
/* USER CODE BEGIN PV */

uint16_t Pin[] = {
		GPIO_PIN_0,
		GPIO_PIN_1,
		GPIO_PIN_2,
		GPIO_PIN_3,
		GPIO_PIN_4,
		GPIO_PIN_5,
		GPIO_PIN_6,
		GPIO_PIN_7,
		GPIO_PIN_8,
		GPIO_PIN_9,
		GPIO_PIN_10,
		GPIO_PIN_11,
		GPIO_PIN_12,
		GPIO_PIN_13,
		GPIO_PIN_14,
		GPIO_PIN_15,
};

char Words[][35] = {
		"Foam applied to the",
		"Brushing the",
		"Washing the",
		"Drying the",
		"first",
		"second",
		"third",
		"fourth",
		"car is completed it took",
		"sec"
		"in the"
		"washing place\r\n",
};

char TaskName[][9] = {
		"carwash1",
		"carwash2",
		"carwash3",
		"carwash4"
};

osThreadId CarWash[4];

xSemaphoreHandle Mutex;
volatile unsigned char MainButtonStatus = 0;
volatile unsigned char TaskProtect = 0xFF;
volatile uint16_t WashPlace = 1;
void (*CarsWash[])(void const * argument) = {CarWash1, CarWash2, CarWash3, CarWash3};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void StartDefaultTask(void const * argument);

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

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */

  /* USER CODE BEGIN 2 */
  SystemClock_Config();
  MX_USART2_UART_Init();
  MX_GPIO_Init();
  Foam = Brushing = Washing = Drying = &Process;
  //Foam = Brushing = Washing = Drying = &Process;
  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  Mutex = xSemaphoreCreateMutex();
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


/* USER CODE BEGIN 4 */

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
  /* USER CODE BEGIN 5 */
	  /* Infinite loop */
	  for(;;)
	  {
		  if (MainButtonStatus)
		  {
			  osDelay(30);
			  switch(PinDetect(GPIOC, Pin, 3))
			  {
			  	  case 1: ;
			  	  	  if(TaskProtect & 0x01)
			  	  	  {
				  	  	  TaskCreate(CarsWash[0], &CarWash[0], TaskName[0], 0, 1280, osPriorityNormal);
				  	  	  TaskProtect &= 0xFE;
				  	  	  WashPlace++;
			  	  	  }
			  	  	  break;
			  	  case 2: ;
			  	  	  if(TaskProtect & 0x02)
			  	  	  {
				  	  	  TaskCreate(CarsWash[1], &CarWash[1], TaskName[1], 0, 1280, osPriorityNormal);
				  	  	  TaskProtect &= 0xFD;
				  	  	  WashPlace++;
			  	  	  }
			  	  	  break;
			  	  case 3: ;
			  	  	  if(TaskProtect & 0x04)
			  	  	  {
				  	  	  TaskCreate(CarsWash[2], &CarWash[2], TaskName[2], 0, 1280, osPriorityNormal);
				  	  	  TaskProtect &= 0xFB;
				  	  	  WashPlace++;

			  	  	  }
			  	  	  break;
			  	  case 4: ;
			  	  	  if(TaskProtect & 0x08)
			  	  	  {
			  	  		  TaskCreate(CarsWash[3], &CarWash[3], TaskName[3], 0, 1280, osPriorityNormal);
			  	  		  TaskProtect &= 0xF7;
			  	  		  WashPlace++;
			  	  	  }
			  	  	  break;
			  	  default: ;
			  	  	  break;
			 	}

		  }
		  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
		  osDelay(1);
		}

  /* USER CODE END 5 */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1) {
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
