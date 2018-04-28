/*
 * GPS.c
 *
 *  Created on: Apr 28, 2018
 *      Author: david
 */

#include "GPS.h"

uint8 NMEA_PROTOCOL_INDEX = FALSE;
uint8 NMEA_Array[70] = { FALSE };
uint8 flag = FALSE;
uint8 NMEA_Link[52] = "https://maps.google.com/maps?q=";
uint8 NMEA_Longitude[8] = { FALSE };
uint8 GPSActivated = FALSE;

void getGPS(uint8 gps_data) {

	flag = TRUE;

	if (NMEA_PROTOCOL_INDEX < 50) {
		NMEA_Array[NMEA_PROTOCOL_INDEX] = gps_data;
		NMEA_PROTOCOL_INDEX++;
		if ((0x52 == NMEA_Array[3]) && (0x4d == NMEA_Array[4]) && (0x43 == NMEA_Array[5]) && (0x41 == gps_data || 0x56 == gps_data)) {
			GPSActivated = TRUE;
		}

	} else {

		if (GPSActivated == TRUE) {

			LinkGenerator_GPS();
			GPSActivated = FALSE;

		} else {
			flag = FALSE;
			NMEA_PROTOCOL_INDEX = FALSE;
			clearArray();
		}
	}
}

void LinkGenerator_GPS() {

	//LONGITUD
	NMEA_Link[31] = NMEA_Array[16];
	NMEA_Link[32] = NMEA_Array[17];
	NMEA_Link[33] = '.';
	NMEA_Link[34] = NMEA_Array[18];
	NMEA_Link[35] = NMEA_Array[19];
	NMEA_Link[36] = NMEA_Array[21];
	NMEA_Link[37] = NMEA_Array[22];
	NMEA_Link[38] = NMEA_Array[23];

	//SIGNO MAS
	NMEA_Link[39] = '+';
	//SIGNO MENOS
	NMEA_Link[40] = '-';

	//LATITUD
	NMEA_Link[41] = NMEA_Array[27];
	NMEA_Link[42] = NMEA_Array[28];
	NMEA_Link[43] = NMEA_Array[29];
	NMEA_Link[44] = '.';
	NMEA_Link[45] = NMEA_Array[30];
	NMEA_Link[46] = NMEA_Array[31];
	NMEA_Link[47] = NMEA_Array[33];
	NMEA_Link[48] = NMEA_Array[34];
	NMEA_Link[49] = NMEA_Array[35];
	NMEA_Link[50] =  92;
	NMEA_Link[51] =  'n';
}


uint8* get_GPSLink (){
	return NMEA_Link;
}


void clearArray() {
	for (int NMEA_Counter = 0; NMEA_Counter < 69; NMEA_Counter++) {
		NMEA_Array[NMEA_Counter] = FALSE;
	}
}

uint8 getFlag() {
	return flag;
}

