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

#define FROM_FIRST_CAR_WASH_TASK_CALLED (uint8_t)1
#define FROM_SECOND_CAR_WASH_TASK_CALLED (uint8_t)2
#define FROM_THIRD_CAR_WASH_TASK_CALLED (uint8_t)3
#define FROM_FOUTRH_CAR_WASH_TASK_CALLED (uint8_t)4

extern char Words[][35];
extern xSemaphoreHandle Mutex;
extern volatile unsigned char Protect[4];

extern osMessageQId CarWash1Queue;
extern osMessageQId CarWash2Queue;
extern osMessageQId CarWash3Queue;
extern osMessageQId CarWash4Queue;

/*Task's functions*/

void CarWash1(void const * argument);
void CarWash2(void const * argument);
void CarWash3(void const * argument);
void CarWash4(void const * argument);

#endif /* INC_TASKS_H_ */
