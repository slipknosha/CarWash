/*
 * tasks.h
 *
 *  Created on: 10 нояб. 2020 г.
 *      Author: slipk
 */

#ifndef INC_TASKS_H_
#define INC_TASKS_H_

#include "main.h"
#include "tasks_interface.h"
#include "printf.h"
#include "pindetect.h"

extern char Words[][35];
extern xSemaphoreHandle Mutex;

extern volatile uint16_t WashPlace;
extern osMessageQId* TasksQueues[4];
extern xSemaphoreHandle Mutex;

/*Task's functions*/

void CarWash1(void const * argument);
void CarWash2(void const * argument);
void CarWash3(void const * argument);
void CarWash4(void const * argument);

#endif /* INC_TASKS_H_ */
