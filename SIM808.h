/*
 * SIM808.h
 *
 *  Created on: Apr 22, 2018
 *      Author: david
 */

#ifndef SIM808_H_
#define SIM808_H_

#include "DataTypeDefinitions.h"
#define HANGUP_COMMAND "ATH;\n"
#define CALL_NUM "ATD3929270291;\n"
#define SMS_CONFIG "AT+CMGF=1\r\n"
#define SMS_NUM "AT+CMGS=\"3929270291\"\n"
//#define SMS "SOMEONE TRIES TO STOLE YOUR CAR\n"

#define ENTER "\n"
#define CTRL_Z 26

void MakePhoneCall_SIM808();

void SendSMS_SIM808();

void HangUp_SIM808();

void set_SMS(uint8* SMS_Pointer);

#endif /* SIM808_H_ */
