/*
 * pindetect.c
 *
 *  Created on: 10 нояб. 2020 г.
 *      Author: slipk
 */


#include "pindetect.h"

uint16_t PinDetect(GPIO_TypeDef* Port, uint16_t* Pin, uint8_t PinRange)
{
	uint16_t* PtrPin = Pin;
	uint8_t ReturnedValue = 1;
	while(1)
	{
		if(HAL_GPIO_ReadPin(Port, *PtrPin)==GPIO_PIN_SET)
		{
			return ReturnedValue;
		}
		if(PtrPin == Pin + PinRange)
		{
			PtrPin = Pin;
			ReturnedValue = 1;
	    }
		PtrPin++;
		ReturnedValue++;
	}
}
