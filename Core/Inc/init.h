/*
 * init.h
 *
 *  Created on: Nov 6, 2020
 *      Author: slipk
 */

#ifndef INC_INIT_H_
#define INC_INIT_H_

#include "main.h"

UART_HandleTypeDef huart2;

void MX_USART2_UART_Init(void);
void MX_GPIO_Init(void);
void SystemClock_Config(void);

#endif /* INC_INIT_H_ */
