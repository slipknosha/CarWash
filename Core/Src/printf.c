/*
 * printf.c
 *
 *  Created on: 10 нояб. 2020 г.
 *      Author: slipk
 */


#include "printf.h"

void PrintF(uint8_t Process, char Words[][35], uint16_t WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay)
{
	xSemaphoreTake(*Mutex, portMAX_DELAY);
	switch(Process)
	{
		case 1:;
			printf("%s %s %s %lu %s %s %d %s", Words[Process - 1], Words[3 + WashPlace], Words[8] , Delay/1000, Words[9], Words[10], WashPlace, Words[11]);
			break;
		case 2:;
			printf("%s %s %s %lu %s %s %d %s", Words[Process - 1], Words[3 + WashPlace], Words[8] , Delay/1000, Words[9], Words[10], WashPlace, Words[11]);
			break;
		case 3:;
			printf("%s %s %s %lu %s %s %d %s", Words[Process - 1], Words[3 + WashPlace], Words[8] , Delay/1000, Words[9], Words[10], WashPlace, Words[11]);
			break;
		case 4:;
			printf("%s %s %s %lu %s %s %d %s", Words[Process - 1], Words[3 + WashPlace], Words[8] , Delay/1000, Words[9], Words[10], WashPlace, Words[11]);
			break;
		default:;
			break;
	}
	xSemaphoreGive(*Mutex);
}
