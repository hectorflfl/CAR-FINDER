/*
 * Copyright (c) 2017, NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    CarProtector.c
 * @brief   Application entry point.
 */

#include "MK64F12.h"
#include "UART.h"
#include "NVIC.h"
#include "PasswordDetector.h"
#include "stdio.h"
#include "DataTypeDefinitions.h"
#include "ADC.h"
#include "GPIO.h"
#include "PIT.h"
#include "delay.h"
#include "SPI.h"
#include "Ports_Init.h"
#include "LCDNokia5110.h"

#include "SIM808.h"
#include "LCDNokia5110Images.h"
#include "TypesConverter.h"
#include "UART_TERMINAL.h"
#include "I2C.h"

#define SYSCLK 21000000		//Macro that contain the system clock of the k64
#define BAUDRATE9600 9600	//Baud rate to serial comunication
#define DELAY_15S 30		//Macro that help us to set the counter of the PIT to 15 seconds
#define DELAY_30S 60		//Macro that help us to set the counter of the PIT to 30 seconds
#define DELAY_3S 3000		//Macro that help us to set the counter of the PIT to 1500 seconds
#define PIR_MAX 62000		//Macro that help us to use the sensor PIR
#define ASCII_CONVERT 0x30	//Macro that help us to convert from ascci
#define COUNTDOWN 15		////Macro that help us to set the count down
#define  DELAY_10S 20		//Macro that help us to delay the PIR

uint8 PIR_Unlocked = TRUE;	//Flag that help us to view if the PIR is locked or unlocked
uint8 Alarm = FALSE;		//Flag that help us if the alarm is activated
uint8 counter = COUNTDOWN;	//Variable that count down when the thief is in the car

int main(void) {



	const SPI_ConfigType SPI_Config = { //Structure that initialize the SPI for the NOKIA LCD
			SPI_DISABLE_FIFO, SPI_LOW_POLARITY,
			SPI_LOW_PHASE, SPI_MSB, SPI_0, SPI_MASTER,
			GPIO_MUX2,
			SPI_BAUD_RATE_2,
			SPI_FSIZE_8, { GPIO_D, BIT1, BIT2 } };

	pins_initialize();/**Inicialización de los pines */
	pins_interrupts();/**Habilitación de las interrupciones de los pines */


	UART_init (UART_0, SYSCLK, BD_9600);//UART0 TERATERM
	UART_interruptEnable(UART_0);		//Enable uart0 interrupt
	show_menu();

	UART_init(UART_1, SYSCLK, BD_9600); //UART1 SIM808
	UART_interruptEnable(UART_1);		//Enable uart1 interrupt

	UART_init(UART_3, SYSCLK, BD_9600); //UART3 GPS
	UART_interruptEnable(UART_3);		//Enable uart3 interrupt

	UART_init(UART_4, SYSCLK, BD_9600); //UART4 BLUETOOTH
	UART_interruptEnable(UART_4);		//Enable uart4 interrupt

	EnableInterrupts;					//Enable interrupts
	ADC_init();							//Initialize ADC that help us to detect the PIR sensor
	PIT_clockGating();					//Activate thte clock gating of the PIT
	SPI_init(&SPI_Config);				/**Initialize SPI SPI */
	LCDNokia_init();					/**Initialize the LCD NOKIA */
	I2C_init(FALSE);					/*Initialize the I2C*/
	UART4_disable();					/*DIsable the uart4 because we only want to use bluetooth when the systme detects somebody*/
	LCDNokia_clear();					/*Clear the LCD before is used*/


	while (TRUE) {

////////////////////////////PIT FOR COUNTDOWN OF THE LCD//////////////////////////////
		if (TRUE == PIT_interruptFlagStatus(PIT_1)) {
			StartCountDown();						//Function That counts down
			PIT_clear(PIT_1);						//Clear PIT
			PIT_delay(PIT_1, SYSCLK, DELAY1S);		//Reactivate
		}
		////////////////////////////PIT that count the time that the user has to desactivate the alarm///////////////
		if (TRUE == PIT_interruptFlagStatus(PIT_3)) {
			if (FALSE == PIR_Unlocked && TRUE == get_PortB_FlagIRQ()) {//Will entry if the PIR is locked
				PIR_Unlocked = TRUE;									//Unlocked the PIR
				clear_AccessStatus();									//Clear the access status
				PIT_disabled(PIT_3);									//Disable the PIT
				GPIO_clearPIN(GPIO_B, BIT18);							//Turn off led that means anybody is in the car
				LCDNokia_clear();										//Clear LCD NOKIA
				LCDNokia_bitmap(get_bloquedLogo());						//Show blocked image
			}
			clear_PortB_FlagIRQ();										//Clear the PORTB flag
		}

		////////////////////////////PIT that count the time that the user has to desactivate the alarm///////////////

		if (TRUE == PIT_interruptFlagStatus(PIT_0)) {//Una vez que se cumplen los 15 seg para decir la contraseÃ±a
			PIT_clear(PIT_0);					//Clear the PIT
			PIT_disabled(PIT_0);				//Disable the PIT

			if (FALSE == get_AccessStatus()) {	//Password incorrect
				MakePhoneCall_SIM808();			//Functions that make the phone call
				delay_msOrus(DELAY_3S, SYSCLK, FALSE);	//We use the delay to send the sms
				SendSMS_SIM808();				//Function that sends a message
				Alarm = TRUE;					//Activate alarm
				LCDNokia_clear();				//Clear the LCD
				LCDNokia_bitmap(get_bloquedLogo());	//Print bitmap of the logo



			} else {				//Password correct
				LCDNokia_clear();					//Clear the LCD NOKIA
				LCDNokia_bitmap(get_welcomeLogo()); //Print the bitmap of the logo


			}
			PIT_disabled(PIT_1);		//Disable PIT
			PIT_clear(PIT_1);			//Clear PIT
			clear_PortB_FlagIRQ();		//Clear portB Flag

		}

		if ((TRUE == GPIO_readPIN(GPIO_C, BIT0)) && (TRUE == PIR_Unlocked)) { //Check f the PIR is on
			setCountDown(15);					//Set the count down from 15 seconds
			PIT_delay(PIT_1, SYSCLK, DELAY1S);	//Set the LCD to refresh each second for the counting down
			PIT_delay(PIT_0, SYSCLK, DELAY_15S);//Set the PIR to count 15 senconds
			PIR_Unlocked = FALSE;				//Locked the PIR
			UART4_enable();						//Enable the uart to send the password by voice
			GPIO_setPIN(GPIO_B, BIT18);			//Led that indicates that somebody is in the car
		}

		if (TRUE == Alarm) {					//Entry in this conditional when alarm is activated

			if (TRUE == get_AccessStatus()) {	//If the access status is true the alarm will turn off
				Alarm = FALSE;					//Turn off the alarm
				PIT_disabled(PIT_2);			//Disable the PIT when the password is send and it is correct
				GPIO_clearPIN(GPIO_C, BIT7);	//Turn off the ALARM
				PIT_disabled(PIT_1);			//Disable the PIT
			} else {
				PIT_delay(PIT_2, SYSCLK, DELAY_30S);	//Activate the PIT that will send the location each 15 senconds

			}
		}
		////////////////////////////PIT that count 15 seconds and will send a message when the thief is once in the car///////////////
		if (TRUE == PIT_interruptFlagStatus(PIT_2)) {
			SendSMS_SIM808();							//Function that send the command to make call
			PIT_clear(PIT_2);							//Clear the PIT to reinitialize
			PIT_delay(PIT_2, SYSCLK, DELAY_30S);		//Configure the PIT that count other 15 seconds

		}

	}
	return 0;
}

