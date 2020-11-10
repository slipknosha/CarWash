/*
 * tasks_interface.c
 *
 *  Created on: 10 нояб. 2020 г.
 *      Author: slipk
 */


#include "tasks_interface.h"

void Process(uint8_t Process, char Words[][35], unsigned char WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay)
{
	osDelay(Delay);
	PrintF(Process, Words, WashPlace, Mutex, Delay);
}

void TaskCreate(void (*CarsWash)(void const * argument), osThreadId* Handle, char* Tsk, uint8_t Copies, uint16_t StackSize, osPriority Priority)
{
	osThreadDef(Tsk, CarsWash, Priority, Copies, StackSize);
    *Handle = osThreadCreate(osThread(Tsk), NULL);
}
