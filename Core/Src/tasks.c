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
		GetMessageFromTask = osMessageGet(*TasksQueues[0], 100);
		if((GetMessageFromTask.status == osEventMessage) &&
		    GetMessageFromTask.value.v)
		{
			GetMessageFromTask.status = osOK;
			GetMessageFromTask.value.v = 0;
			Foam(1, Words, WashPlace, 30000);
			Brushing(2, Words, WashPlace, 30000);
			Washing(3, Words, WashPlace, 60000);
			Drying(4, Words, WashPlace, 30000);
			WashPlace--;
			osMessagePut(*TasksQueues[0], 1, 100);
		}

	}
}

void CarWash2(void const * argument)
{
	osEvent GetMessageFromTask;
	for(;;)
	{
		GetMessageFromTask = osMessageGet(*TasksQueues[1], 100);
		if((GetMessageFromTask.status == osEventMessage) &&
		    GetMessageFromTask.value.v)
		{
			GetMessageFromTask.status = osOK;
			GetMessageFromTask.value.v = 0;
			Foam(1, Words, WashPlace, 30000);
			Brushing(2, Words, WashPlace, 30000);
			Washing(3, Words, WashPlace, 60000);
			Drying(4, Words, WashPlace, 30000);
			WashPlace--;
			osMessagePut(*TasksQueues[1], 1, 100);
		}

	}
}


void CarWash3(void const * argument)
{
	osEvent GetMessageFromTask;
	for(;;)
	{
		GetMessageFromTask = osMessageGet(*TasksQueues[2], 100);
		if((GetMessageFromTask.status == osEventMessage) &&
		    GetMessageFromTask.value.v)
		{
			GetMessageFromTask.status = osOK;
			GetMessageFromTask.value.v = 0;
			Foam(1, Words, WashPlace, 30000);
			Brushing(2, Words, WashPlace, 30000);
			Washing(3, Words, WashPlace, 60000);
			Drying(4, Words, WashPlace, 30000);
			WashPlace--;
			osMessagePut(*TasksQueues[2], 1, 100);
		}

	}
}

void CarWash4(void const * argument)
{
	osEvent GetMessageFromTask;
	for(;;)
	{
		GetMessageFromTask = osMessageGet(*TasksQueues[3], 100);
		if((GetMessageFromTask.status == osEventMessage) &&
		    GetMessageFromTask.value.v)
		{
			GetMessageFromTask.status = osOK;
			GetMessageFromTask.value.v = 0;
			Foam(1, Words, WashPlace, 30000);
			Brushing(2, Words, WashPlace, 30000);
			Washing(3, Words, WashPlace, 60000);
			Drying(4, Words, WashPlace, 30000);
			WashPlace--;
			osMessagePut(*TasksQueues[3], 1, 100);
		}

	}
}
