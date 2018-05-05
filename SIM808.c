/*
 * SIM808.c
 *
 *  Created on: Apr 22, 2018
 *      Author: David Gálvez Sahagún
 */

#include "SIM808.h"
#include "UART.h"
#include "DataTypeDefinitions.h"
#include "GPS.h"


uint8 SMS[54] = {FALSE};





void MakePhoneCall_SIM808() {
	UART_putString(UART_1, CALL_NUM);
}

void SendSMS_SIM808() {

	UART_putString(UART_1, SMS_CONFIG);
	UART_putString(UART_1, SMS_NUM);
	set_SMS(get_GPSLink ());
	UART_putString(UART_1, SMS);
	UART_putChar(UART_1, CTRL_Z);
	UART_putString(UART_1, ENTER);
}

void HangUp_SIM808() {

	UART_putString(UART_1, HANGUP_COMMAND);
}


void set_SMS(uint8* SMS_Pointer){
	uint8 SMS_Counter=FALSE;

	while(*SMS_Pointer){

		SMS[SMS_Counter]=*SMS_Pointer;
		SMS_Pointer++;
		SMS_Counter++;

	}


}
