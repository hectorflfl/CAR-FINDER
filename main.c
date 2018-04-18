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

#define SYSCLK 21000000
#define BAUDRATE9600 9600
#define DELAY_1S 30


int main(void) {
	uint8 det=TRUE;
	UART_init(UART_1, SYSCLK, BAUDRATE9600);
	NVIC_enableInterruptAndPriotity(PIT_CH0_IRQ, PRIORITY_15);
	NVIC_enableInterruptAndPriotity(UART1_IRQ, PRIORITY_14);
	EnableInterrupts;
	ADC_init();
	PIT_clockGating();
	UART1->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);


    while(1) {


    	if(PIT_interruptFlagStatus(PIT_0)==TRUE){
    		PIT_clear(PIT_0);
    		PIT_disabled(PIT_0);
    		det=TRUE;
    		UART1_disable();
    		puts("TERMINO EL TIEMPO");
    	}

    	if(ADC_read16b()>60000 && det==TRUE){
    		PIT_delay(PIT_0, SYSCLK, DELAY_1S);
    		det=FALSE;
    		UART1_enable();

    	}



    }
    return 0 ;
}
