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
#include "Decifra_valor.h"

#define SYSCLK 21000000
#define BAUDRATE9600 9600
#define DELAY_1S 30


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

	uint8 det=TRUE;

	UART_init(UART_1, SYSCLK, BD_9600);//UART1 SIM808
	UART_interruptEnable(UART_1);

	UART_init(UART_3, SYSCLK, BD_9600);//UART3 BLUETOOTH
	UART_interruptEnable(UART_3);

	NVIC_enableInterruptAndPriotity(PIT_CH0_IRQ, PRIORITY_15);
	NVIC_enableInterruptAndPriotity(PIT_CH1_IRQ, PRIORITY_12);
	NVIC_enableInterruptAndPriotity(UART1_IRQ, PRIORITY_14);
	NVIC_enableInterruptAndPriotity(UART3_IRQ, PRIORITY_13);

	EnableInterrupts;
	ADC_init();
	PIT_clockGating();

	SPI_init(&SPI_Config);/**Inicialización del SPI */
				LCDNokia_init();/**Inicialización del LCD NOKIA */
			/*Se habilita el PIT con 1 segundo de retardo*/

			int counter = 15;


	//LAMAR
//UART_putString(UART_1,"ATD3929270291;\n");
//	UART_putString(UART_1,"ATD3929270291;\n");
//	UART1->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);

	//UART_putString(UART_1,"AT+CMGF=1\r\n");
	//UART_putString(UART_1,"AT+CMGS=\"3929270291\"\n");
	//UART_putString(UART_1,"YES\n");
	//UART_putChar(UART_1,26);
	//UART_putString(UART_1,"\n");








    while(1) {
    	if (TRUE == PIT_interruptFlagStatus(PIT_1)) {

    	    		if(counter != 0){
    	    			counter--;
    	    		obtenvalor(counter);
    	    		LCDNokia_clear();		/*Limpiamos la pantalla para mostrar el siguiente menú*/
    				LCDNokia_gotoXY(20, 3); /*! It establishes the position to print the messages in the LCD*/
    				if(getDecena() != 0){
    				LCDNokia_sendChar(getDecena()+0x30); /*! It print a string stored in an array*/
    				}
    				LCDNokia_sendChar(getUnidad()+0x30); /*! It print a string stored in an array*/
    	    		}else{
    	    			LCDNokia_clear();		/*Limpiamos la pantalla para mostrar el siguiente menú*/
    	    			LCDNokia_gotoXY(0, 3); /*! It establishes the position to print the messages in the LCD*/
    	    			LCDNokia_sendString("INTRUZO");
    	    		}


    	    				PIT_clear(PIT_1);
    	    				/*Volvemos a contar*/
    	    				PIT_delay(PIT_1, SYSCLK, DELAY1S);
    	    			}

  if(PIT_interruptFlagStatus(PIT_0)==TRUE){
    		PIT_clear(PIT_0);
    		PIT_disabled(PIT_0);
    		det=TRUE;
    		UART3_disable();
    		puts("TERMINO EL TIEMPO");
    		if(FALSE==get_AccessStatus()){
    		UART_putString(UART_1,"ATD3929270291;\n");
    		}
    		clear_AccessStatus();

    	}

   if(ADC_read16b()>62000 && det==TRUE){
	   	   PIT_delay(PIT_1, SYSCLK, DELAY1S);/**Se activa el PIT0 para referescar la pantalla */
    		PIT_delay(PIT_0, SYSCLK, DELAY_1S);
    		det=FALSE;
    		UART3_enable();

    	}



    }
    return 0 ;
}


