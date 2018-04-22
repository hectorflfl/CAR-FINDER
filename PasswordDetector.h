/*
 * PasswordDetector.h
 *
 *  Created on: Apr 17, 2018
 *      Author: david
 */

#ifndef PASSWORDDETECTOR_H_
#define PASSWORDDETECTOR_H_

#include "DataTypeDefinitions.h"
#include "UART.h"

#define PASS_H 0x48
const static uint8 RealPassword=PASS_H;

void passwordVerification(uint8 pass_detected);
uint8 get_AccessStatus();
void clear_AccessStatus();





#endif /* PASSWORDDETECTOR_H_ */
