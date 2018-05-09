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


static uint8 SMS[SMS_LENGTH] = {FALSE}; /**Arreglo de caracteres que almacenara el mensaje a enviar*/

void MakePhoneCall_SIM808() {
	/**Envio del comando AT para la ejecución de la llamada*/
	UART_putString(UART_1, CALL_NUM);
}

void SendSMS_SIM808() {
	/**Comunicación serial con los comandos AT para el envio del mensaje de texto con el link de google maps*/
	UART_putString(UART_1, SMS_CONFIG);
	UART_putString(UART_1, SMS_NUM);
	set_SMS(get_GPSLink ());
	UART_putString(UART_1, SMS);
	UART_putChar(UART_1, CTRL_Z);
	UART_putString(UART_1, ENTER);
}

void HangUp_SIM808() {
	/**Envio del comando AT para detener la llamada ejecutada*/
	UART_putString(UART_1, HANGUP_COMMAND);
}


void set_SMS(uint8* SMS_Pointer){
	uint8 SMS_Counter=FALSE;
	/**Ciclo while que concatena al arreglo del SMS el link de google maps*/
	while(*SMS_Pointer){

		SMS[SMS_Counter]=*SMS_Pointer;
		SMS_Pointer++;
		SMS_Counter++;

	}


}
