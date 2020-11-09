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
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void StartDefaultTask(void const * argument);

/* USER CODE BEGIN PFP */
void PrintF(uint8_t Process, char Words[][35], uint16_t WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay);
uint16_t PinDetect(GPIO_TypeDef* Port, uint16_t* PIN, uint8_t PinRange);

void CarWash1(void const * argument);
void CarWash2(void const * argument);
void CarWash3(void const * argument);
void CarWash4(void const * argument);

//void Process(uint8_t Process, char Words[][35], unsigned char WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay);
void Foam(uint8_t Process, char Words[][35], unsigned char WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay);
void Brushing(uint8_t Process, char Words[][35], unsigned char WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay);
void Washing(uint8_t Process, char Words[][35], unsigned char WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay);
void Drying(uint8_t Process, char Words[][35], unsigned char WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void (*CarsWash[])(void const * argument) = {&CarWash1, &CarWash2, &CarWash3, &CarWash4};
//void (*Foam)(uint8_t Process, char Words[][35], unsigned char WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay);
//void (*Brushing)(uint8_t Process, char Words[][35], unsigned char WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay);
//void (*Washing)(uint8_t Process, char Words[][35], unsigned char WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay);
//void (*Drying)(uint8_t Process, char Words[][35], unsigned char WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay);
void TaskCreate(void (*CarsWash)(void const * argument), osThreadId* Handle, char* Tsk, uint8_t Copies, uint16_t StackSize, osPriority Priority);

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


void PrintF(uint8_t Process, char Words[][35], uint16_t WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay)
{
	xSemaphoreTake(*Mutex, portMAX_DELAY);
	switch(Process)
	{
		case 1:;
			printf("%s %s %s %lu %s %s %d %s", Words[Process - 1], Words[3 + WashPlace], Words[8] , Delay/1000, Words[9], Words[10], WashPlace, Words[11]);
			break;
		case 2:;
			printf("%s %s %s %lu %s %s %d %s", Words[Process - 1], Words[3 + WashPlace], Words[8] , Delay/1000, Words[9], Words[10], WashPlace, Words[11]);
			break;
		case 3:;
			printf("%s %s %s %lu %s %s %d %s", Words[Process - 1], Words[3 + WashPlace], Words[8] , Delay/1000, Words[9], Words[10], WashPlace, Words[11]);
			break;
		case 4:;
			printf("%s %s %s %lu %s %s %d %s", Words[Process - 1], Words[3 + WashPlace], Words[8] , Delay/1000, Words[9], Words[10], WashPlace, Words[11]);
			break;
		default:;
			break;
	}
	xSemaphoreGive(*Mutex);
}

void TaskCreate(void (*CarsWash)(void const * argument), osThreadId* Handle, char* Tsk, uint8_t Copies, uint16_t StackSize, osPriority Priority)
{
	osThreadDef(Tsk, CarsWash, Priority, Copies, StackSize);
    *Handle = osThreadCreate(osThread(Tsk), NULL);
}

uint16_t PinDetect(GPIO_TypeDef* Port, uint16_t* Pin, uint8_t PinRange)
{
	uint16_t* PtrPin = Pin;
	uint8_t ReturnedValue = 1;
	while(1)
	{
		if(HAL_GPIO_ReadPin(Port, *PtrPin)==GPIO_PIN_SET)
		{
			return ReturnedValue;
		}
		if(PtrPin == Pin + PinRange)
		{
			PtrPin = Pin;
			ReturnedValue = 1;
	    }
		PtrPin++;
		ReturnedValue++;
	}
}

void Foam(uint8_t Process, char Words[][35], unsigned char WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay)
{
	osDelay(Delay);
	PrintF(Process, Words, WashPlace, Mutex, Delay);
}

void Brushing(uint8_t Process, char Words[][35], unsigned char WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay)
{
	osDelay(Delay);
	PrintF(Process, Words, WashPlace, Mutex, Delay);
}

void Washing(uint8_t Process, char Words[][35], unsigned char WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay)
{
	osDelay(Delay);
	PrintF(Process, Words, WashPlace, Mutex, Delay);
}

void Drying(uint8_t Process, char Words[][35], unsigned char WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay)
{
	osDelay(Delay);
	PrintF(Process, Words, WashPlace, Mutex, Delay);
}
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	printf("Pushing\r\n");
    MainButtonStatus = !MainButtonStatus;
  /* USER CODE END EXTI0_IRQn 0 */
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */

  /* USER CODE END EXTI0_IRQn 1 */
}

void CarWash1(void const * argument)
{
	for(;;)
	{
		Foam(1, Words, WashPlace, &Mutex, 30000);
		Brushing(2, Words, WashPlace, &Mutex, 30000);
		Washing(3, Words, WashPlace, &Mutex, 60000);
		Drying(4, Words, WashPlace, &Mutex, 30000);
		WashPlace--;
		TaskProtect |= 0x01;
		osThreadTerminate(NULL);
	}
}

void CarWash2(void const * argument)
{
	for(;;)
	{
		Foam(1, Words, WashPlace, &Mutex, 30000);
		Brushing(2, Words, WashPlace, &Mutex, 30000);
		Washing(3, Words, WashPlace, &Mutex, 60000);
		Drying(4, Words, WashPlace, &Mutex, 30000);
		TaskProtect |= 0x02;
		WashPlace--;
		osThreadTerminate(NULL);
	}
}

void CarWash3(void const * argument)
{
	for(;;)
	{
		Foam(1, Words, WashPlace, &Mutex, 30000);
		Brushing(2, Words, WashPlace, &Mutex, 30000);
		Washing(3, Words, WashPlace, &Mutex, 60000);
		Drying(4, Words, WashPlace, &Mutex, 30000);
		WashPlace--;
		TaskProtect |= 0x04;
		osThreadTerminate(NULL);
	}
}

void CarWash4(void const * argument)
{
	for(;;)
	{
		Foam(1, Words, WashPlace, &Mutex, 30000);
		Brushing(2, Words, WashPlace, &Mutex, 30000);
		Washing(3, Words, WashPlace, &Mutex, 60000);
		Drying(4, Words, WashPlace, &Mutex, 30000);
		WashPlace--;
		TaskProtect |= 0x08;
		osThreadTerminate(NULL);
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
