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
		Foam(1, Words, WashPlace, 30000);
		Brushing(2, Words, WashPlace, 30000);
		Washing(3, Words, WashPlace, 60000);
		Drying(4, Words, WashPlace, 30000);
		WashPlace--;
	}
}

void CarWash2(void const * argument)
{
	for(;;)
	{
		Foam(1, Words, WashPlace, 30000);
		Brushing(2, Words, WashPlace, 30000);
		Washing(3, Words, WashPlace, 60000);
		Drying(4, Words, WashPlace, 30000);
		WashPlace--;
	}
}

void CarWash3(void const * argument)
{
	for(;;)
	{
		Foam(1, Words, WashPlace, 30000);
		Brushing(2, Words, WashPlace, 30000);
		Washing(3, Words, WashPlace, 60000);
		Drying(4, Words, WashPlace, 30000);
		WashPlace--;
	}
}

void CarWash4(void const * argument)
{
	for(;;)
	{
		Foam(1, Words, WashPlace, 30000);
		Brushing(2, Words, WashPlace, 30000);
		Washing(3, Words, WashPlace, 60000);
		Drying(4, Words, WashPlace, 30000);
		WashPlace--;

	}
}
