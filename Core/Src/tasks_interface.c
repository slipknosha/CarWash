/*
 * tasks_interface.c
 *
 *  Created on: 10 нояб. 2020 г.
 *      Author: slipk
 */


#include "tasks_interface.h"

/*Simulation of real processes of washing the car*/

/*Delay is the realtime process. PrintF - output the string to UART*/

void Foam(uint8_t Task)
{
  osDelay(30000);
  PrintF("Foam applied to the car it took 30 sec in the %lu wahsing place\r\n", Task);
}

void Brushing(uint8_t Task)
{
  osDelay(30000);
  PrintF("Brushing the car it took 30 sec in the %lu wahsing place\r\n", Task);
}

void Washing(uint8_t Task)
{
  osDelay(60000);
  PrintF("Washing the car it took 60 sec in the %lu wahsing place\r\n", Task);
}

void Drying(uint8_t Task)
{
  osDelay(30000);
  PrintF("Drying the car it took 30 sec in the %lu wahsing place\r\n", Task);
}



