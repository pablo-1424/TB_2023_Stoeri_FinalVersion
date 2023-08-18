/*
 * bma400func.h
 *
 *  Created on: 30 juin 2023
 *      Author: pablo
 */

#ifndef INC_BMA400FUNC_H_
#define INC_BMA400FUNC_H_

#include "i2c.h"
#include "stdio.h"
#include "it_sdk/logger/logger.h"
#include "string.h"
#include "math.h"

// Configuration of BMA400
void bma400_InitConfig();

// Read the fifo of BMA400
uint8_t dataCheck();

#endif /* INC_BMA400FUNC_H_ */
