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
    	log_info("Com Check error 1");
    } else {
  	  hStat = HAL_I2C_Master_Receive(&hi2c1, ACC_ADDR, i2cBufRet, 2, HAL_MAX_DELAY);
  	  if(hStat != HAL_OK){
  		log_info("Com Check error 2");
  	  } else {
  		log_info("CtrlVal : %x\r\n", i2cBufRet[0]);
  	  }
    }
    HAL_Delay(1);

    //==========			Go out of sleep mode			==========

    i2cBuf[0] = 0b00000010;
    hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_ACC_CONFIG0, 1, i2cBuf, 1, HAL_MAX_DELAY);
    i2cBuf[0] = 0x00;
    if(hStat != HAL_OK){
    	log_info("Out of sleep error 1");
    } else {
  	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_ACC_CONFIG0, 1, i2cBufRet, 8, HAL_MAX_DELAY);
  	  if(hStat != HAL_OK){
  		log_info("Out of sleep error 2");
  	  } else {
  		 log_info("OutSlp  : %x\r\n", i2cBufRet[0]);
  	  }
    }
    HAL_Delay(1);

    //==========			Go in 2g mode and 800 Hz		==========

	i2cBuf[0] = 0x3b;
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_ACC_CONFIG1, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
		log_info("2g/800Hz error 1");
	} else {
	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_ACC_CONFIG1, 1, i2cBufRet, 8, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  log_info("2g/800Hz error 2");
	  } else {
		  log_info("2gMode  : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_Delay(1);

	//==========		x,y,z in fifo and 12 bit			==========

	i2cBuf[0] = 0xE0;
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_FIFO_CONFIG0, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
		log_info("fifo/12bit error 1");
	} else {
		hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_FIFO_CONFIG0, 1, i2cBufRet, 1, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  log_info("2g/800Hz error 2");
	  } else {
		  log_info("xyz md  : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_Delay(1);

	//==========			INT1 Map gen1 int1				==========

	i2cBuf[0] = 0x04;
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_INT1_MAP, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
		log_info("INT1Map error 1");
	} else {
	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_INT1_MAP, 1, i2cBufRet, 1, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  log_info("INT1Map error 2");
	  } else {
		  log_info("INT1Map : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_Delay(1);

	//==========			ACTCH to interrupt				==========
	i2cBuf[0] = 0x00; //Probably 10 for activity
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_INT_CONFIG1, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
		log_info("fifo/12bit error 1");
	} else {
	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_INT_CONFIG1, 1, i2cBufRet, 1, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  log_info("fifo/12bit error 1");
	  } else {
		  log_info("INT1Conf : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_Delay(1);

	//==========				INT1 high active			==========

	i2cBuf[0] = 0x02;
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_INT12_IO_CTRL, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
		log_info("fifo/12bit error 1");
	} else {
	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_INT12_IO_CTRL, 1, i2cBufRet, 1, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  log_info("fifo/12bit error 1");
	  } else {
		  log_info("INT12IO : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_Delay(1);

	//==========				GEN1INT_CONFIG0				==========

	i2cBuf[0] = 0xFB;
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_GEN1INT_CONFIG0, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
		log_info("fifo/12bit error 1");
	} else {
	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_GEN1INT_CONFIG0, 1, i2cBufRet, 1, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  log_info("fifo/12bit error 1");
	  } else {
		  log_info("actch0 : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_Delay(1);

	//==========	OR with the 3 axis and detect activity	==========
	i2cBuf[0] = 0x02;
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_GEN1INT_CONFIG1, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
		log_info("fifo/12bit error 1");
	} else {
	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_GEN1INT_CONFIG1, 1, i2cBufRet, 1, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  log_info("fifo/12bit error 1");
	  } else {
		  log_info("int1en1 : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_Delay(1);

	//==========

	i2cBuf[0] = 0x03; // If it don't detect : 0x02 or 0x01
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_GEN1INT_CONFIG2, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
		log_info("fifo/12bit error 1");
	} else {
	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_GEN1INT_CONFIG2, 1, i2cBufRet, 1, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  log_info("fifo/12bit error 1");
	  } else {
		  log_info("int1en2 : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_Delay(1);

	//==========

	i2cBuf[0] = 0x00;
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_GEN1INT_CONFIG3, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
		log_info("fifo/12bit error 1");
	} else {
	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_GEN1INT_CONFIG3, 1, i2cBufRet, 1, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  log_info("fifo/12bit error 1");
	  } else {
		  log_info("int1en3 : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_Delay(1);

	//==========

	i2cBuf[0] = 0x01;
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_GEN1INT_CONFIG31, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
		log_info("fifo/12bit error 1");
	} else {
	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_GEN1INT_CONFIG31, 1, i2cBufRet, 1, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  log_info("fifo/12bit error 1");
	  } else {
		  log_info("int1en31 : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_Delay(1);

	//==========			INT1 enable						==========

	i2cBuf[0] = 0x04;
	hStat = HAL_I2C_Mem_Write(&hi2c1, ACC_ADDR, REG_INT_CONFIG0, 1, i2cBuf, 1, HAL_MAX_DELAY);
	i2cBuf[0] = 0x00;
	if(hStat != HAL_OK){
		log_info("fifo/12bit error 1");
	} else {
	  hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_INT_CONFIG0, 1, i2cBufRet, 1, HAL_MAX_DELAY);
	  if(hStat != HAL_OK){
		  log_info("fifo/12bit error 1");
	  } else {
		  log_info("IntConf0 : %x\r\n", i2cBufRet[0]);
	  }
	}
	HAL_Delay(1);
}

//======================================================================
				/*	Datacheck function	*/
//======================================================================

uint16_t nbrOverSize = 0;
uint16_t currentMemPos = 0;
int16_t myVal[F_SAMP] = {0};
uint8_t waterOn = 0;
uint8_t i2cBuff[FIFO_SIZE]={0};

uint8_t dataCheck(){
	log_info("in datacheck\r\n");
	int16_t fifoBytes = 0;
	int16_t rawVal[3]={0};
	HAL_StatusTypeDef hStat;


		HAL_I2C_StateTypeDef i2cSt = HAL_I2C_GetState(&hi2c1);
		hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_FIFO_LENGTH0, 1, i2cBuff, 1,HAL_MAX_DELAY);
		if(hStat != HAL_OK){
		  log_info("Read fifo error 1 : %d\r\n", hStat);
		} else {
		  fifoBytes = i2cBuff[0];
		}
		hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_FIFO_LENGTH1, 1, i2cBuff, 1,HAL_MAX_DELAY);
		if(hStat != HAL_OK){
		  log_info("Read fifo error 2\r\n");
		} else {
		  fifoBytes = fifoBytes | i2cBuff[0]<<8;
		}
		hStat = HAL_I2C_Mem_Read(&hi2c1, ACC_ADDR, REG_FIFO_DATA, 1, i2cBuff, fifoBytes,HAL_MAX_DELAY);
		if(hStat != HAL_OK){
		  log_info("Read fifo error 3\r\n");
		} else {
		  for(uint8_t i = 0; i<(fifoBytes/7); i++){
			  if(currentMemPos >= F_SAMP){
				  currentMemPos = 0;
				  nbrOverSize++;
			  }
			  for(uint8_t j = 0; j<3; j++){
				  rawVal[j] = i2cBuff[1+i*7+j*2] | i2cBuff[2+i*7+j*2]<<4;
				  if(i2cBuff[2+i*7+j*2]>0x80){
					  rawVal[j] = rawVal[j] | 0xF<<12;
				  }
			  }
			  myVal[currentMemPos] = sqrt(pow(rawVal[0],2) + pow(rawVal[1],2) + pow(rawVal[2],2));
			  currentMemPos++;
		  }
		  uint8_t detection_count = 0;
		  for(uint16_t i = 0; i < F_SAMP; i++){
			  if(myVal[i] < MIDDLE_VAL + THRESHOLD && myVal[i] > MIDDLE_VAL - THRESHOLD){
				  waterOn = 0;
			  } else {
				  detection_count++;
				  if(detection_count >= MIN_COUNT){
					  waterOn = 1;
					  break;
				  }
			  }
		  }
		}

		if(currentMemPos == F_SAMP){
	//	  log_info("%d,%d,%d%d\r\n", waterOn, myVal[F_SAMP - 1], secondsOn, currentMemPos+800*nbrOverSize);
			log_info("WaterOn : %d\r\n", waterOn);
		} else {
	//	  log_info("%d,%d,%d,%d\r\n", waterOn, myVal[currentMemPos], secondsOn, currentMemPos+800*nbrOverSize);
			log_info("WaterOn : %d\r\n", waterOn);
		}
		return waterOn;
}

