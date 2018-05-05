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

#define SYSCLK 21000000
#define BAUDRATE9600 9600
#define DELAY_1S 30
#define DELAY_3S 3000
#define PIR_MAX 62000
#define ASCII_CONVERT 0x30
#define COUNTDOWN 15
#define  DELAY_10S 20

extern const uint8 WELCOME[];
extern const uint8 BLOQUED[];
uint8 PIR_Unlocked = TRUE;
uint8 Alarm =FALSE;
int counter = COUNTDOWN;

int main(void) {
	const SPI_ConfigType SPI_Config = { SPI_DISABLE_FIFO, SPI_LOW_POLARITY,
												SPI_LOW_PHASE,
												SPI_MSB,
												SPI_0,
												SPI_MASTER,
												GPIO_MUX2,
												SPI_BAUD_RATE_2,
												SPI_FSIZE_8,
												{ GPIO_D, BIT1, BIT2 } };
	pins_initialize();/**Inicialización de los pines */
	pins_interrupts();/**Habilitación de las interrupciones de los pines */
	//UART1----PUERTO C



	UART_init(UART_1, SYSCLK, BD_9600);//UART1 SIM808
	UART_interruptEnable(UART_1);

	UART_init(UART_3, SYSCLK, BD_9600);//UART3 BLUETOOTH
	UART_interruptEnable(UART_3);

	EnableInterrupts;
	ADC_init();
	PIT_clockGating();
	SPI_init(&SPI_Config);/**Inicialización del SPI */
	LCDNokia_init();/**Inicialización del LCD NOKIA */


	//LAMAR
//UART_putString(UART_1,"ATD3929270291;\n");
//	UART_putString(UART_1,"ATD3929270291;\n");
//	UART1->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);

	//UART_putString(UART_1,"AT+CMGF=1\r\n");
	//UART_putString(UART_1,"AT+CMGS=\"3929270291\"\n");
	//UART_putString(UART_1,"YES\n");
	//UART_putChar(UART_1,26);
	//UART_putString(UART_1,"\n");


    while(TRUE ) {



////////////////////////////PIT FOR COUNTDOWN OF THE LCD//////////////////////////////
   	if (TRUE == PIT_interruptFlagStatus(PIT_1)) {
   		StartCountDown();
   		PIT_clear(PIT_1);//Clear PIT
   		PIT_delay(PIT_1, SYSCLK, DELAY1S);//Reactivate PIT
   	}

   	if (TRUE == PIT_interruptFlagStatus(PIT_3)) {
   		if(FALSE == PIR_Unlocked && TRUE == get_PortB_FlagIRQ()){
   			PIR_Unlocked = TRUE;
   			clear_AccessStatus();
   		}
   		set_PortB_FlagIRQ();

	}


   	//----------------------------------------PARTE DE LOS TIEMPOS DEL PIR----------------------------------------------

	if (PIT_interruptFlagStatus(PIT_0) == TRUE) {//Una vez que se cumplen los 15 seg para decir la contraseÃ±a
		PIT_clear(PIT_0);
		PIT_disabled(PIT_0);


		if (FALSE == get_AccessStatus()) {
			MakePhoneCall_SIM808();
			delay_msOrus(DELAY_3S, SYSCLK, FALSE);
			SendSMS_SIM808();
			Alarm=TRUE;
		}
	}



	if ((ADC_read16b() > PIR_MAX) && (TRUE == PIR_Unlocked)) { /**Comprueba si el PIR esta encendido */
		PIT_delay(PIT_1, SYSCLK, DELAY1S);/**Se activa el PIT1 para referescar la pantalla */
		PIT_delay(PIT_0, SYSCLK, DELAY_1S);/**Se activa el PIT0 para dar una ventana de tiempo para la contraseÃ±a*/
		PIR_Unlocked = FALSE;
		UART0_enable();
	}

	if(TRUE==Alarm){


		if(TRUE == get_AccessStatus()){
			//AQUI SE APAGARA LA ALARMA
			Alarm=FALSE;
			PIT_disabled(PIT_2);//Apago el pit que esta mandando la ubicacion gps
			GPIO_setPIN(GPIO_B,2);//Turn on led to show that is somebody in the car
			GPIO_clearPIN(GPIO_C, BIT7);
		}else{
			//AQUI SE ACTIVARA UN PIT DE 2 SEG PARA ESTAR MANDANDO LA UBICACION
			PIT_delay(PIT_2, SYSCLK, DELAY_10S);

		}
	}


	if (PIT_interruptFlagStatus(PIT_2) == TRUE){

		SendSMS_SIM808();
		PIT_clear(PIT_2);
		PIT_delay(PIT_2, SYSCLK, DELAY_10S);



	}




   	}
    return 0 ;
    }


