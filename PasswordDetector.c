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

static uint8 AccessStatus = FALSE;		//Variable that contain the access status

void passwordVerification(uint8 pass_detected) {//Function to verificate the password

	if (pass_detected == RealPassword) {//If password detected and is the real stop count down
		AccessStatus = TRUE;			//Access status enable
		setCountDown(FALSE);			//Set count down false to stop counting
		LCDNokia_clear();				//Clear LCD NOKIA
		LCDNokia_bitmap(get_welcomeLogo());//Print bitmap
	} else {
		AccessStatus = FALSE;			//Disbale the access status
	}

}

uint8 get_AccessStatus() {//Function that return access status
	return AccessStatus;
}
void clear_AccessStatus() {//Clear the access status
	AccessStatus = FALSE;
}

