/*
 * tasks.c
 *
 *  Created on: 10 нояб. 2020 г.
 *      Author: slipk
 */


#include "tasks.h"

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
