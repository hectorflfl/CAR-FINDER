/*
 * PasswordDetector.c
 *
 *  Created on: Apr 17, 2018
 *      Author: david
 */
#include "PasswordDetector.h"
#include "stdio.h"
#include "LCDNokia5110.h"
#include "GPIO.h"

static uint8 AccessStatus = FALSE;

void passwordVerification(uint8 pass_detected) {

	if (pass_detected == RealPassword) {
		AccessStatus = TRUE;
		setCountDown(FALSE);

		puts("CONTRASEÑA CORRECTA");

	} else {
		AccessStatus = FALSE;
	}

}

uint8 get_AccessStatus() {
	return AccessStatus;
}
void clear_AccessStatus() {
	AccessStatus = FALSE;
}

