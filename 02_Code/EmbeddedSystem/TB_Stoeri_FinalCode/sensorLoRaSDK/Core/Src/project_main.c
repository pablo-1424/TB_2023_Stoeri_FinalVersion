/* ==========================================================
 * project_main.c - 
 * Project : Disk91 SDK
 * ----------------------------------------------------------
 * Created on: 6 sept. 2018
 *     Author: Paul Pinault aka Disk91
 * ----------------------------------------------------------
 * Copyright (C) 2018 Disk91
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU LESSER General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------
 * 
 * Add a such file in the main Src directory for executing
 * you own workload.
 *
 * ==========================================================
 */
#include <it_sdk/config.h>
#include <it_sdk/itsdk.h>
#include <it_sdk/time/time.h>
#include <it_sdk/logger/logger.h>
#include <it_sdk/sched/scheduler.h>
#include <it_sdk/statemachine/statemachine.h>
#include <it_sdk/eeprom/eeprom.h>
#include <it_sdk/eeprom/sdk_config.h>

#include <it_sdk/lorawan/lorawan.h>
#include <it_sdk/encrypt/encrypt.h>
#include <it_sdk/eeprom/securestore.h>
#include <it_sdk/lowpower/lowpower.h>
#include <drivers/sx1276/sx1276.h>
#include "bma400func.h"


#define COMFREQS	(2*60*1000)
#define TASKDELAYMS	(500)

struct state {
	uint8_t 		led;
	uint32_t  		loops;
	int32_t			lastComMS;
	itsdk_bool_e	setup;
} s_state;


#define LED1_PORT 	__BANK_B
#define LED1_PIN 	__LP_GPIO_5
#define LED2_PORT 	__BANK_A
#define LED2_PIN 	__LP_GPIO_5
#define LED3_PORT 	__BANK_B
#define LED3_PIN 	__LP_GPIO_6
#define LED4_PORT 	__BANK_B
#define LED4_PIN 	__LP_GPIO_7
#define BUTTON_PORT	__BANK_B
#define BUTTON_PIN 	__LP_GPIO_2

uint8_t loRaSendVal(uint8_t *valToTransmit){
	uint8_t i = 0;
	uint8_t devEui[8] = {0};
	itsdk_lorawan_getDeviceEUI(devEui);

	log_info("Init LoRawan Stack ");
	itsdk_lorawan_init_t r;
	#ifdef ITSDK_LORAWAN_CHANNEL
		static itsdk_lorawan_channelInit_t channels= ITSDK_LORAWAN_CHANNEL;
		r = itsdk_lorawan_setup(itsdk_config.sdk.activeRegion,&channels);
	#else
		r = itsdk_lorawan_setup(itsdk_config.sdk.activeRegion,NULL);
	#endif
	if ( r == LORAWAN_INIT_SUCESS ) {
		log_info("success\r\n");
	} else {
		log_info("failed\r\n");
	}

	uint8_t t[20] = {valToTransmit[1],valToTransmit[0],0,0xFF,0,0x88,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	if ( !itsdk_lorawan_hasjoined() ) {
		log_info("Connecting LoRaWAN ");
		//try that
//		while ( !itsdk_lorawan_hasjoined() ) {
//			itsdk_lorawan_join_sync();
//		}

		if ( itsdk_lorawan_join_sync() == LORAWAN_JOIN_SUCCESS ) {
			log_info("success\r\n");
			log_info("Fire a LoRaWAN message ");
			uint8_t port;
			uint8_t size=16;
			uint8_t rx[16];
			itsdk_lorawan_send_t r = itsdk_lorawan_send_sync(
				t,						// Payload
				16,						// Payload size
				1,						// Port
				__LORAWAN_DR_5,			// Speed
				LORAWAN_SEND_CONFIRMED,	// With a ack
				ITSDK_LORAWAN_CNF_RETRY,// And default retry
				&port,					// In case of reception - Port (uint8_t)
				&size,					// In case of reception - Size (uint8_t) - init with buffer max size
				rx,						// In case of recpetion - Data (uint8_t[] bcopied)
				PAYLOAD_ENCRYPT_NONE	// End to End encryption mode
			);
//			itsdk_lorawan_send_t r = lorawan_driver_LORA_Send(
//					t, 16, 1, LO, __LORAWAN_DR_5, 1, runMode, rPort, rSize, rData);
			if ( r == LORAWAN_SEND_SENT || r == LORAWAN_SEND_ACKED ) {
				log_info("success\r\n",r);
				return 1;
			} else {
				return 0;
				log_info("failed (%d)\r\n",r);
			}
		}else {
			log_info("failed\r\n");
		}
	} else {
		log_info("Fire a LoRaWAN message ");
		uint8_t port;
		uint8_t size=16;
		uint8_t rx[16];
		itsdk_lorawan_send_t r = itsdk_lorawan_send_sync(
				t,						// Payload
				16,						// Payload size
				1,						// Port
				__LORAWAN_DR_5,			// Speed
				LORAWAN_SEND_CONFIRMED,	// With a ack
				ITSDK_LORAWAN_CNF_RETRY,// And default retry
				&port,					// In case of reception - Port (uint8_t)
				&size,					// In case of reception - Size (uint8_t) - init with buffer max size
				rx,						// In case of recpetion - Data (uint8_t[] bcopied)
				PAYLOAD_ENCRYPT_NONE	// End to End encryption mode
		);
		if ( r == LORAWAN_SEND_SENT || r == LORAWAN_SEND_ACKED ) {
			log_info("success\r\n",r);
			return 1;
		} else {
			log_info("failed (%d)\r\n",r);
			return 0;
		}
	}
}


// =====================================================================
// Setup

void project_setup() {

	//SX1276InitLowPower();

	log_info("Hello Boss let's setup \r\n");
	SX1276SetRfTxPower(20);
	bma400_InitConfig();

	//s_state.led = __GPIO_VAL_RESET;
	s_state.loops = 0;
	s_state.lastComMS = COMFREQS;
	s_state.setup = BOOL_FALSE;

}


/**
 * Project loop may not contain functional stuff
 * Keep in this loop only really short operations
 */
void project_loop() {
    itsdk_lorawan_loop();
}

