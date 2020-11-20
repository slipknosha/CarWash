/*
 * tasks.c
 *
 *  Created on: 10 нояб. 2020 г.
 *      Author: slipk
 */


#include "tasks.h"

void CarWash1(void const * argument)
{
  osEvent GetMessageFromTask;
  for(;;)
  {
    GetMessageFromTask = osMessageGet(CarWash1Queue, 100);
    if(GetMessageFromTask.value.v)
	{
      GetMessageFromTask.value.v = 0;
	  Foam(FROM_FIRST_CAR_WASH_TASK_CALLED);
	  Brushing(FROM_FIRST_CAR_WASH_TASK_CALLED);
	  Washing(FROM_FIRST_CAR_WASH_TASK_CALLED);
	  Drying(FROM_FIRST_CAR_WASH_TASK_CALLED);
	  Protect[THE_FIRST_TASK] = TASK_UNPROTECTED;
	}
  }
}

void CarWash2(void const * argument)
{
  osEvent GetMessageFromTask;
  for(;;)
  {
    GetMessageFromTask = osMessageGet(CarWash2Queue, 100);
    if(GetMessageFromTask.value.v)
	{
      GetMessageFromTask.value.v = 0;
	  Foam(FROM_SECOND_CAR_WASH_TASK_CALLED);
	  Brushing(FROM_SECOND_CAR_WASH_TASK_CALLED);
	  Washing(FROM_SECOND_CAR_WASH_TASK_CALLED);
	  Drying(FROM_SECOND_CAR_WASH_TASK_CALLED);
	  Protect[THE_SECOND_TASK] = TASK_UNPROTECTED;
	}
  }
}

void CarWash3(void const * argument)
{
  osEvent GetMessageFromTask;
  for(;;)
  {
    GetMessageFromTask = osMessageGet(CarWash3Queue, 100);
    if(GetMessageFromTask.value.v)
	{
      GetMessageFromTask.value.v = 0;
	  Foam(FROM_THIRD_CAR_WASH_TASK_CALLED);
	  Brushing(FROM_THIRD_CAR_WASH_TASK_CALLED);
	  Washing(FROM_THIRD_CAR_WASH_TASK_CALLED);
	  Drying(FROM_THIRD_CAR_WASH_TASK_CALLED);
	  Protect[THE_THIRD_TASK] = TASK_UNPROTECTED;
	}
  }
}

void CarWash4(void const * argument)
{
  osEvent GetMessageFromTask;
  for(;;)
  {
    GetMessageFromTask = osMessageGet(CarWash4Queue, 100);
    if(GetMessageFromTask.value.v)
	{
      GetMessageFromTask.value.v = 0;
	  Foam(FROM_FOUTRH_CAR_WASH_TASK_CALLED);
	  Brushing(FROM_FOUTRH_CAR_WASH_TASK_CALLED);
	  Washing(FROM_FOUTRH_CAR_WASH_TASK_CALLED);
	  Drying(FROM_FOUTRH_CAR_WASH_TASK_CALLED);
	  Protect[THE_FOURTH_TASK] = TASK_UNPROTECTED;
	}
  }
}
