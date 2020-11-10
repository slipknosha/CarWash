/*
 * printf.h
 *
 *  Created on: 10 нояб. 2020 г.
 *      Author: slipk
 */

#ifndef INC_PRINTF_H_
#define INC_PRINTF_H_

#include "main.h"

void PrintF(uint8_t Process, char Words[][35], uint16_t WashPlace, xSemaphoreHandle* Mutex, uint32_t Delay);

#endif /* INC_PRINTF_H_ */
