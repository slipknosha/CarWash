/*
 * tasks_interface.h
 *
 *  Created on: 10 нояб. 2020 г.
 *      Author: slipk
 */

#ifndef INC_TASKS_INTERFACE_H_
#define INC_TASKS_INTERFACE_H_

#include "main.h"

void Process(uint8_t Process, unsigned char WashPlace, uint32_t Delay, uint8_t FirstWord); //this is base fucntions for pointers below
void (*Foam)(uint8_t Process, unsigned char WashPlace, uint32_t Delay, uint8_t FirstWord);
void (*Brushing)(uint8_t Process, unsigned char WashPlace, uint32_t Delay, uint8_t FirstWord);
void (*Washing)(uint8_t Process, unsigned char WashPlace, uint32_t Delay, uint8_t FirstWord);
void (*Drying)(uint8_t Process, unsigned char WashPlace, uint32_t Delay, uint8_t FirstWord);
void TaskCreate(void (*CarsWash)(void const * argument), osThreadId* Handle, char* Tsk, uint8_t Copies, uint16_t StackSize, osPriority Priority);//easier creating of task


#endif /* INC_TASKS_INTERFACE_H_ */
