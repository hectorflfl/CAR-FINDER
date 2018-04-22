/*
 * SIM808.c
 *
 *  Created on: Apr 22, 2018
 *      Author: David Gálvez Sahagún
 */

#include "SIM808.h"
#include "UART.h"


void MakePhoneCall_SIM808() {
	UART_putString(UART_1, CALL_NUM);
}

void SendSMS_SIM808() {

	UART_putString(UART_1, SMS_CONFIG);
	UART_putString(UART_1, SMS_NUM);
	UART_putString(UART_1, SMS);
	UART_putChar(UART_1, CTRL_Z);
	UART_putString(UART_1, ENTER);
}

void HangUp_SIM808() {

	UART_putString(UART_1, HANGUP_COMMAND);
}

