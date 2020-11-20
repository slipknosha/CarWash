/*
 * printf.c
 *
 *  Created on: 10 нояб. 2020 г.
 *      Author: slipk
 */


#include "printf.h"

void PrintF(char* format, ...)
{
  xSemaphoreTake(Mutex, portMAX_DELAY);
  char bufer[BUFER_SIZE];
  va_list args;
  va_start(args, format);
  vsnprintf(bufer, BUFER_SIZE, format, args);
  printf((char*)bufer);
  va_end(args);
  xSemaphoreGive(Mutex);
}
