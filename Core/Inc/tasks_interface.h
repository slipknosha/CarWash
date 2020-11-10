/*
 * tasks_interface.h
 *
 *  Created on: 10 нояб. 2020 г.
 *      Author: slipk
 */

#ifndef INC_TASKS_INTERFACE_H_
#define INC_TASKS_INTERFACE_H_

#include "main.h"

void Process(uint8_t Process, char Words[][35], unsigned char WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay);
void (*Foam)(uint8_t Process, char Words[][35], unsigned char WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay);
void (*Brushing)(uint8_t Process, char Words[][35], unsigned char WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay);
void (*Washing)(uint8_t Process, char Words[][35], unsigned char WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay);
void (*Drying)(uint8_t Process, char Words[][35], unsigned char WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay);
void TaskCreate(void (*CarsWash)(void const * argument), osThreadId* Handle, char* Tsk, uint8_t Copies, uint16_t StackSize, osPriority Priority);


#endif /* INC_TASKS_INTERFACE_H_ */
