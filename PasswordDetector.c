/*
 * PasswordDetector.c
 *
 *  Created on: Apr 17, 2018
 *      Author: david
 */
#include "PasswordDetector.h"
#include "stdio.h"

static uint8 AccessStatus=FALSE;
uint8 counter1 = FALSE;
uint8 data1[70] = {FALSE};
uint8 flag = FALSE;
uint8 GPSActivated = FALSE;
void passwordVerification(uint8 pass_detected){

	if(pass_detected == RealPassword){
		AccessStatus= TRUE;
		puts("CONTRASEÑA CORRECTA");

	}else{
		AccessStatus=FALSE;
	}


}

void getGPS(uint8 gps){
	flag = TRUE;

	if(counter1 < 50){
		data1[counter1] = gps;
		counter1++;
			if((0x52 == data1[3]) && (0x4d == data1[4]) && (0x43 == data1[5]) && (0x41 == gps || 0x56 == gps)){
				GPSActivated = TRUE;
			}



	}else{
		if(GPSActivated == TRUE){
			GPSActivated = FALSE;
		}else{
			flag = FALSE;
			counter1 = FALSE;
			clearArray();
		}
	}
}

void clearArray(){
	for(int i = 0;i<69;i++){
		data1[i] = FALSE;
	}
}

uint8 get_AccessStatus(){
	return AccessStatus;
}
void clear_AccessStatus(){
	AccessStatus=FALSE;
}

uint8 getFlag(){
	return flag;
}
