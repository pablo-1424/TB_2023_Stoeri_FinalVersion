/*
 * bma400func.c
 *
 *  Created on: 30 juin 2023
 *      Author: pablo
 */

#include "bma400func.h"

HAL_StatusTypeDef hStat;
uint8_t serialAccBuf[SER_BUF_SIZE] = {'\0'};
uint8_t i2cBufRet[FIFO_SIZE]={0};
uint8_t i2cBuf[8]={0};

void bma400_InitConfig(){

	//==========	Check that communication is correct		==========

    hStat = HAL_I2C_Master_Transmit(&hi2c1, ACC_ADDR, REG_CHIPID, 1, HAL_MAX_DELAY);
    if(hStat != HAL_OK){
  	  strcpy((char*)serialAccBuf, "Error Tx     \r\n");
    } else {
  	  hStat = HAL_I2C_Master_Receive(&hi2c1, ACC_ADDR, i2cBufRet, 2, HAL_MAX_DELAY);
  	  if(hStat != HAL_OK){
  		  strcpy((char*)serialAccBuf, "Error Rx     \r\n");
  	  } else {
  		  sprintf((char*)serialAccBuf, "CtrlVal : %x\r\n", i2cBufRet[0]);
  	  }
    }
    HAL_UART_Transmit(&huart2, serialAccBuf, sizeof(serialAccBuf), HAL_MAX_DELAY);
    HAL_Delay(500);

    //==========			Go out of sleep mode			==========

    i2cBuf[0] = 0b00000010;
    hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_ACC_CONFIG0, 1, i2cBuf, 1, HAL_MAX_DELAY);
    i2cBuf[0] = 0x00;
    if(hStat != HAL_OK){
  	  strcpy((char*)serialAccBuf, "Error Tx     \r\n");
    } else {
  	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_ACC_CONFIG0, 1, i2cBufRet, 8, HAL_MAX_DELAY);
  	  if(hStat != HAL_OK){
  		  strcpy((char*)serialAccBuf, "Error Rx     \r\n");
  	  } else {
  		  sprintf((char*)serialAccBuf, "OutSlp  : %x\r\n", i2cBufRet[0]);
  	  }
    }
    HAL_UART_Transmit(&huart2, serialAccBuf, sizeof(serialAccBuf), HAL_MAX_DELAY);
    HAL_Delay(500);

    //==========			Go in 2g mode and 800 Hz		==========

	i2cBuf[0] = 0x3b;
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_ACC_CONFIG1, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
	  strcpy((char*)serialAccBuf, "Error Tx     \r\n");
	} else {
	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_ACC_CONFIG1, 1, i2cBufRet, 8, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  strcpy((char*)serialAccBuf, "Error Rx     \r\n");
	  } else {
		  sprintf((char*)serialAccBuf, "4gMode  : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_UART_Transmit(&huart2, serialAccBuf, sizeof(serialAccBuf), HAL_MAX_DELAY);
	HAL_Delay(500);

	//==========		x,y,z in fifo and 12 bit			==========

	i2cBuf[0] = 0xE0;
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_FIFO_CONFIG0, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
	  strcpy((char*)serialAccBuf, "Error Tx     \r\n");
	} else {
	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_FIFO_CONFIG0, 1, i2cBufRet, 1, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  strcpy((char*)serialAccBuf, "Error Rx     \r\n");
	  } else {
		  sprintf((char*)serialAccBuf, "xyz md  : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_UART_Transmit(&huart2, serialAccBuf, sizeof(serialAccBuf), HAL_MAX_DELAY);
	HAL_Delay(500);

	//==========			INT1 Map gen1 int1				==========

	i2cBuf[0] = 0x04;
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_INT1_MAP, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
	  strcpy((char*)serialAccBuf, "Error Tx     \r\n");
	} else {
	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_INT1_MAP, 1, i2cBufRet, 1, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  strcpy((char*)serialAccBuf, "Error Rx     \r\n");
	  } else {
		  sprintf((char*)serialAccBuf, "intConf : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_UART_Transmit(&huart2, serialAccBuf, sizeof(serialAccBuf), HAL_MAX_DELAY);
	HAL_Delay(500);

	//==========			ACTCH to interrupt				==========
	i2cBuf[0] = 0x00; //Probably 10 for activity
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_INT_CONFIG1, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
	  strcpy((char*)serialAccBuf, "Error Tx     \r\n");
	} else {
	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_INT_CONFIG1, 1, i2cBufRet, 1, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  strcpy((char*)serialAccBuf, "Error Rx     \r\n");
	  } else {
		  sprintf((char*)serialAccBuf, "intConf : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_UART_Transmit(&huart2, serialAccBuf, sizeof(serialAccBuf), HAL_MAX_DELAY);
	HAL_Delay(500);

	//==========				INT1 high active			==========

	i2cBuf[0] = 0x02;
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_INT12_IO_CTRL, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
	  strcpy((char*)serialAccBuf, "Error Tx     \r\n");
	} else {
	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_INT12_IO_CTRL, 1, i2cBufRet, 1, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  strcpy((char*)serialAccBuf, "Error Rx     \r\n");
	  } else {
		  sprintf((char*)serialAccBuf, "int1act : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_UART_Transmit(&huart2, serialAccBuf, sizeof(serialAccBuf), HAL_MAX_DELAY);
	HAL_Delay(500);

	//==========				GEN1INT_CONFIG0				==========

	i2cBuf[0] = 0xFB;
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_GEN1INT_CONFIG0, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
	  strcpy((char*)serialAccBuf, "Error Tx     \r\n");
	} else {
	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_GEN1INT_CONFIG0, 1, i2cBufRet, 1, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  strcpy((char*)serialAccBuf, "Error Rx     \r\n");
	  } else {
		  sprintf((char*)serialAccBuf, "actch0  : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_UART_Transmit(&huart2, serialAccBuf, sizeof(serialAccBuf), HAL_MAX_DELAY);
	HAL_Delay(500);

	//==========	OR with the 3 axis and detect activity	==========
	i2cBuf[0] = 0x02;
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_GEN1INT_CONFIG1, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
	  strcpy((char*)serialAccBuf, "Error Tx     \r\n");
	} else {
	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_GEN1INT_CONFIG1, 1, i2cBufRet, 1, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  strcpy((char*)serialAccBuf, "Error Rx     \r\n");
	  } else {
		  sprintf((char*)serialAccBuf, "int1en  : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_UART_Transmit(&huart2, serialAccBuf, sizeof(serialAccBuf), HAL_MAX_DELAY);
	HAL_Delay(500);

	//==========

	i2cBuf[0] = 0x03;
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_GEN1INT_CONFIG2, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
	  strcpy((char*)serialAccBuf, "Error Tx     \r\n");
	} else {
	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_GEN1INT_CONFIG2, 1, i2cBufRet, 1, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  strcpy((char*)serialAccBuf, "Error Rx     \r\n");
	  } else {
		  sprintf((char*)serialAccBuf, "int1en  : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_UART_Transmit(&huart2, serialAccBuf, sizeof(serialAccBuf), HAL_MAX_DELAY);
	HAL_Delay(500);

	//==========

	i2cBuf[0] = 0x00;
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_GEN1INT_CONFIG3, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
	  strcpy((char*)serialAccBuf, "Error Tx     \r\n");
	} else {
	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_GEN1INT_CONFIG3, 1, i2cBufRet, 1, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  strcpy((char*)serialAccBuf, "Error Rx     \r\n");
	  } else {
		  sprintf((char*)serialAccBuf, "int1en  : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_UART_Transmit(&huart2, serialAccBuf, sizeof(serialAccBuf), HAL_MAX_DELAY);
	HAL_Delay(500);

	//==========

	i2cBuf[0] = 0x01;
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_GEN1INT_CONFIG31, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
	  strcpy((char*)serialAccBuf, "Error Tx     \r\n");
	} else {
	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_GEN1INT_CONFIG31, 1, i2cBufRet, 1, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  strcpy((char*)serialAccBuf, "Error Rx     \r\n");
	  } else {
		  sprintf((char*)serialAccBuf, "int1en  : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_UART_Transmit(&huart2, serialAccBuf, sizeof(serialAccBuf), HAL_MAX_DELAY);
	HAL_Delay(500);

	//==========			INT1 enable						==========

	i2cBuf[0] = 0x04;
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_INT_CONFIG0, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
	  strcpy((char*)serialAccBuf, "Error Tx     \r\n");
	} else {
	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_INT_CONFIG0, 1, i2cBufRet, 1, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  strcpy((char*)serialAccBuf, "Error Rx     \r\n");
	  } else {
		  sprintf((char*)serialAccBuf, "int1en  : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_UART_Transmit(&huart2, serialAccBuf, sizeof(serialAccBuf), HAL_MAX_DELAY);
	HAL_Delay(500);
}
