/*
 * interrupts.c
 *
 *  Created on: Jun 26, 2023
 *      Author: pablo
 */

#include "interrupts.h"
uint8_t serialBuf[SER_BUF_SIZE] = {'\0'};

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim == &htim6){
		secondsOn++;
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == SENSOR_INT_Pin){
		strcpy((char*)serialBuf, "IntYey\r\n");
		HAL_UART_Transmit(&huart2, serialBuf, sizeof(serialBuf), HAL_MAX_DELAY);
	}
}
