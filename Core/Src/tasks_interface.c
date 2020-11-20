/*
 * tasks_interface.c
 *
 *  Created on: 10 нояб. 2020 г.
 *      Author: slipk
 */


#include "tasks_interface.h"

void Foam(uint8_t Task)
{
  osDelay(30000);
  PrintF("%s car it took %llu sec in the %lu wahsing place\r\n", Words[0], 30, Task);
}

void Brushing(uint8_t Task)
{
  osDelay(30000);
  PrintF("%s car it took %llu sec in the %lu wahsing place\r\n", Words[1], 30, Task);
}

void Washing(uint8_t Task)
{
  osDelay(60000);
  PrintF("%s car it took %llu sec in the %lu wahsing place\r\n", Words[2], 60, Task);
}

void Drying(uint8_t Task)
{
  osDelay(30000);
  PrintF("%s car it took %llu sec in the %lu wahsing place\r\n", Words[3], 30, Task);
}



