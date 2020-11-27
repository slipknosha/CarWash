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
#include "stdarg.h"
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


osThreadId defaultTaskHandle; //main task handle
/* USER CODE BEGIN PV */

osThreadId CarWash1Handle, CarWash2Handle, CarWash3Handle, CarWash4Handle; //handles for creating tasks
osMessageQId CarWash1Queue, CarWash2Queue, CarWash3Queue, CarWash4Queue; //handles for creating queues
xSemaphoreHandle Mutex;
xSemaphoreHandle SemaphoreFromISR; //Changing from ISR (MainButtonStatus)
volatile unsigned char Protect[4] = {1, 1, 1, 1,}; //Protect flags that program cant send message to car wasning tasks again while this tasks is running
volatile uint8_t AccesToDefaultTask = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void StartDefaultTask(void const * argument);

/* USER CODE BEGIN PFP */
void SendMessageToWashingTask(uint8_t Task, uint8_t WashingPlace, osMessageQId* CarWashQueue);
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
  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  Mutex = xSemaphoreCreateMutex(); /*mutex - using for protect critical part of code. In this program it is UART transmit (=*/
  SemaphoreFromISR = xSemaphoreCreateBinary();
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */

  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  osMessageQDef(CarWash1Queue, 1, uint16_t);
  CarWash1Queue = osMessageCreate(osMessageQ(CarWash1Queue), NULL);

  osMessageQDef(CarWash2Queue, 1, uint16_t);
  CarWash2Queue = osMessageCreate(osMessageQ(CarWash2Queue), NULL);

  osMessageQDef(CarWash3Queue, 1, uint16_t);
  CarWash3Queue = osMessageCreate(osMessageQ(CarWash3Queue), NULL);

  osMessageQDef(CarWash4Queue, 1, uint16_t);
  CarWash4Queue = osMessageCreate(osMessageQ(CarWash4Queue), NULL);
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
void SendMessageToWashingTask(uint8_t Task, uint8_t WashingPlace, osMessageQId* CarWashQueue)
{
  if(Protect[Task] && (HAL_GPIO_ReadPin(GPIOC, WashingPlace) == GPIO_PIN_SET))
  {
    osMessagePut(*CarWashQueue, 1, portMAX_DELAY);
    Protect[Task] = TASK_PROTECTED;
  }
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument) /*Deafult task. This task creates new tasks for new cars*/
{
  /* USER CODE BEGIN 5 */
  /*Creating 4 washings tasks*/
  osThreadDef(carwash1, CarWash1, osPriorityNormal, 0, 1280);
  CarWash1Handle = osThreadCreate(osThread(carwash1), NULL);

  osThreadDef(carwash2, CarWash2, osPriorityNormal, 0, 1280);
  CarWash2Handle = osThreadCreate(osThread(carwash2), NULL);

  osThreadDef(carwash3, CarWash3, osPriorityNormal, 0, 1280);
  CarWash3Handle = osThreadCreate(osThread(carwash3), NULL);

  osThreadDef(carwash4, CarWash4, osPriorityNormal, 0, 1280);
  CarWash4Handle = osThreadCreate(osThread(carwash4), NULL);


  /*This algorithm check the main button, then if last one is NOT ZERO check the protect flags and pin status(washing place)*/
  /*Then it send just 1 byte(logical 1) to tasks and "lock the door" to the checking one of 4 tasks pin*/


  for(;;)
  {
    if(xSemaphoreTake(SemaphoreFromISR, portMAX_DELAY))
    {
      AccesToDefaultTask != AccesToDefaultTask;
    }
    if(AccesToDefaultTask)
	{
      osDelay(30);
      if(AccesToDefaultTask)
	  {
        SendMessageToWashingTask(THE_FIRST_TASK, FIRST_WASHING_PLACE, &CarWash1Queue);
        SendMessageToWashingTask(THE_SECOND_TASK, SECOND_WASHING_PLACE, &CarWash2Queue);
        SendMessageToWashingTask(THE_THIRD_TASK, THIRD_WASHING_PLACE, &CarWash3Queue);
        SendMessageToWashingTask(THE_FOURTH_TASK, FOURTH_WASHIN_PLACE, &CarWash4Queue);
      }
    }
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
    osDelay(1);
  }
}
  /* USER CODE END 5 */

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
