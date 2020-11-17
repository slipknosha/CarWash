/*
 * tasks_interface.c
 *
 *  Created on: 10 нояб. 2020 г.
 *      Author: slipk
 */


#include "tasks_interface.h"

void Process(uint8_t Process, unsigned char WashPlace, uint32_t Delay, uint8_t FirstWord)
{
	osDelay(Delay);
	xSemaphoreTake(Mutex, portMAX_DELAY);
	PrintF("%s car it took %llu sec in the %lu wahsing place\r\n", Words[FirstWord], Delay/1000, WashPlace);
	xSemaphoreGive(Mutex);
}

void TaskCreate(void (*CarsWash)(void const * argument), osThreadId* Handle, char* Tsk, uint8_t Copies, uint16_t StackSize, osPriority Priority)
{
	osThreadDef(Tsk, CarsWash, Priority, Copies, StackSize);
    *Handle = osThreadCreate(osThread(Tsk), NULL);
}
