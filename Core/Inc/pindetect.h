/*
 * pindetect.h
 *
 *  Created on: 10 нояб. 2020 г.
 *      Author: slipk
 */

#ifndef INC_PINDETECT_H_
#define INC_PINDETECT_H_

#include "main.h"

uint16_t PinDetect(GPIO_TypeDef* Port, uint16_t* PIN, uint8_t PinRange);

#endif /* INC_PINDETECT_H_ */
