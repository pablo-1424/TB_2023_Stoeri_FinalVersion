/*
 * interrupts.h
 *
 *  Created on: Jun 26, 2023
 *      Author: pablo
 */

#ifndef INC_INTERRUPTS_H_
#define INC_INTERRUPTS_H_


#include "main.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif /* INC_INTERRUPTS_H_ */
