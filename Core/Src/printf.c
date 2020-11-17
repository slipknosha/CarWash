/*
 * printf.c
 *
 *  Created on: 10 нояб. 2020 г.
 *      Author: slipk
 */


#include "printf.h"

void PrintF(uint8_t Process, char Words[][35], uint16_t WashPlace, uint32_t Delay)
{
	switch(Process)
	{
		case 1:;
			/*Foam applied to the [first, second, third, fourth] car it took X sec in the Y washing place*/
			printf("%s %s %s %lu %s %s %d %s", Words[Process - 1], Words[3 + WashPlace], Words[8] , Delay/1000, Words[9], Words[10], WashPlace, Words[11]);
			break;
		case 2:;
			/*Brushing the  [first, second, third, fourth] car it took X sec in the Y washing place*/
			printf("%s %s %s %lu %s %s %d %s", Words[Process - 1], Words[3 + WashPlace], Words[8] , Delay/1000, Words[9], Words[10], WashPlace, Words[11]);
			break;
		case 3:;
			/*Washing the  [first, second, third, fourth] car it took X sec in the Y washing place*/
			printf("%s %s %s %lu %s %s %d %s", Words[Process - 1], Words[3 + WashPlace], Words[8] , Delay/1000, Words[9], Words[10], WashPlace, Words[11]);
			break;
		case 4:;
			/*Drying the  [first, second, third, fourth] car it took X sec in the Y washing place*/
			printf("%s %s %s %lu %s %s %d %s", Words[Process - 1], Words[3 + WashPlace], Words[8] , Delay/1000, Words[9], Words[10], WashPlace, Words[11]);
			break;
		default:;
			break;
	}
}
