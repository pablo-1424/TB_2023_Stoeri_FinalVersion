/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

extern TIM_HandleTypeDef htim6;
extern UART_HandleTypeDef huart2;
extern I2C_HandleTypeDef hi2c1;
extern uint16_t secondsOn;
extern uint8_t waterOn;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PA15_RESERVED_Pin GPIO_PIN_15
#define PA15_RESERVED_GPIO_Port GPIOA
#define PB3_RESERVED_Pin GPIO_PIN_3
#define PB3_RESERVED_GPIO_Port GPIOB
#define PA12_RESERVED_Pin GPIO_PIN_12
#define PA12_RESERVED_GPIO_Port GPIOA
#define PB4_RESERVED_Pin GPIO_PIN_4
#define PB4_RESERVED_GPIO_Port GPIOB
#define PB4_RESERVED_EXTI_IRQn EXTI4_15_IRQn
#define LED1_Pin GPIO_PIN_6
#define LED1_GPIO_Port GPIOB
#define PC13_RESERVED_Pin GPIO_PIN_13
#define PC13_RESERVED_GPIO_Port GPIOC
#define PC13_RESERVED_EXTI_IRQn EXTI4_15_IRQn
#define LED2_Pin GPIO_PIN_7
#define LED2_GPIO_Port GPIOB
#define PC1_RESERVED_Pin GPIO_PIN_1
#define PC1_RESERVED_GPIO_Port GPIOC
#define PC0_RESERVED_Pin GPIO_PIN_0
#define PC0_RESERVED_GPIO_Port GPIOC
#define PB1_RESERVED_Pin GPIO_PIN_1
#define PB1_RESERVED_GPIO_Port GPIOB
#define PB1_RESERVED_EXTI_IRQn EXTI0_1_IRQn
#define PC2_RESERVED_Pin GPIO_PIN_2
#define PC2_RESERVED_GPIO_Port GPIOC
#define PA7_RESERVED_Pin GPIO_PIN_7
#define PA7_RESERVED_GPIO_Port GPIOA
#define STLINK_RX_Pin GPIO_PIN_2
#define STLINK_RX_GPIO_Port GPIOA
#define SENSOR_INT_Pin GPIO_PIN_12
#define SENSOR_INT_GPIO_Port GPIOB
#define SENSOR_INT_EXTI_IRQn EXTI4_15_IRQn
#define PB0_RESERVED_Pin GPIO_PIN_0
#define PB0_RESERVED_GPIO_Port GPIOB
#define PB0_RESERVED_EXTI_IRQn EXTI0_1_IRQn
#define PA6_RESERVED_Pin GPIO_PIN_6
#define PA6_RESERVED_GPIO_Port GPIOA
#define STLINK_TX_Pin GPIO_PIN_3
#define STLINK_TX_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

#define SER_BUF_SIZE		20
#define F_SAMP 				800
#define FIFO_SIZE 			1024

//Accelerometer address
#define ACC_ADDR 			0b0010100<<1

//Registers off the accelerometer
#define REG_CHIPID 			0x00

#define REG_ACC_X_LSB		0x04
#define REG_ACC_X_MSB 		0x05
#define REG_ACC_Y_LSB 		0x06
#define REG_ACC_Y_MSB 		0x07
#define REG_ACC_Z_LSB 		0x08
#define REG_ACC_Z_MSB 		0x09

#define REG_FIFO_LENGTH0	0x12
#define REG_FIFO_LENGTH1	0x13
#define REG_FIFO_DATA		0x14

#define REG_ACC_CONFIG0		0x19
#define REG_ACC_CONFIG1		0x1A
#define REG_ACC_CONFIG2		0x1B

#define REG_INT_CONFIG0		0x1F
#define REG_INT_CONFIG1		0x20
#define REG_INT1_MAP		0x21
#define REG_INT12_IO_CTRL	0x24

#define REG_FIFO_CONFIG0	0x26

#define REG_GEN1INT_CONFIG0	0x3F
#define REG_GEN1INT_CONFIG1	0x40
#define REG_GEN1INT_CONFIG2	0x41
#define REG_GEN1INT_CONFIG3	0x42
#define REG_GEN1INT_CONFIG31	0x43

#define REG_ACTCHCONFIG0	0x55
#define REG_ACTCHCONFIG1	0x56

#define THRESHOLD			75
#define MIDDLE_VAL			1024
#define MIN_COUNT			16

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
