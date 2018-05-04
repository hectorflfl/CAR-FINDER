/*
 * GPS.c
 *
 *  Created on: Apr 28, 2018
 *      Author: david
 */

#include "GPS.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TypesConverter.h"

uint8 NMEA_PROTOCOL_INDEX = FALSE;
uint8 NMEA_Array[70] = { FALSE };
uint8 flag = FALSE;
uint8 NMEA_Link[54] = "https://maps.google.com/maps?q=\n";
uint8 NMEA_Longitude[9] = { FALSE };
uint8 NMEA_Latitude[11] = { FALSE };
uint8 GPSActivated = FALSE;

void getGPS(uint8 gps_data) {

	flag = TRUE;

	if (NMEA_PROTOCOL_INDEX < 50) {
		NMEA_Array[NMEA_PROTOCOL_INDEX] = gps_data;
		NMEA_PROTOCOL_INDEX++;
		if ((0x52 == NMEA_Array[3]) && (0x4d == NMEA_Array[4]) && (0x43 == NMEA_Array[5]) && (0x41 == gps_data)) {
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
	float bigvalue = FALSE;
	float shortvalue = FALSE;
	float longitude = FALSE;
	float latitude = FALSE;
	uint8 enter_1 = NMEA_Link[31];
	uint8 enter_2 = NMEA_Link[32];

	uint8 shortvalue_string_latitude[6] = { FALSE };
	uint8 bigvalue_string_latitude[3] = { FALSE };

	uint8 shortvalue_string_longitude[6] = { FALSE };
	uint8 bigvalue_string_longitude[2] = { FALSE };

	NMEA_Longitude[0] = NMEA_Array[20];
	NMEA_Longitude[1] = NMEA_Array[21];

	NMEA_Longitude[2] = NMEA_Array[22];
	NMEA_Longitude[3] = NMEA_Array[23];
	NMEA_Longitude[4] = NMEA_Array[24];
	NMEA_Longitude[5] = NMEA_Array[25];
	NMEA_Longitude[6] = NMEA_Array[26];
	NMEA_Longitude[7] = NMEA_Array[27];
	NMEA_Longitude[8] = NMEA_Array[28];



	 ArrayToFloat(NMEA_Longitude);
	 bigvalue=(float)getIntegerValue();
	 shortvalue=(float)getDecimalValue();
	 shortvalue = (shortvalue * 100) / 60;
	 longitude=bigvalue+shortvalue;

	/*longitude = atof(NMEA_Longitude);
	bigvalue = (int) longitude / 100;
	shortvalue = (longitude / 100) - bigvalue;
	shortvalue = (shortvalue * 100) / 60;
	longitude = bigvalue + shortvalue;
	 */
	bigvalue = (int) longitude;
	shortvalue = longitude - bigvalue;
	shortvalue = (int) (shortvalue * 1000000);
	itoa(bigvalue, bigvalue_string_longitude, 10);
	itoa(shortvalue, shortvalue_string_longitude, 10);

	shortvalue = FALSE;
	bigvalue = FALSE;

	NMEA_Latitude[0] = NMEA_Array[32];
	NMEA_Latitude[1] = NMEA_Array[33];
	NMEA_Latitude[2] = NMEA_Array[34];
	NMEA_Latitude[3] = NMEA_Array[35];
	NMEA_Latitude[4] = NMEA_Array[36];
	NMEA_Latitude[5] = NMEA_Array[37];
	NMEA_Latitude[6] = NMEA_Array[38];
	NMEA_Latitude[7] = NMEA_Array[39];
	NMEA_Latitude[8] = NMEA_Array[40];
	NMEA_Latitude[9] = NMEA_Array[41];
	NMEA_Latitude[10] = NMEA_Array[42];



	ArrayToFloat(NMEA_Latitude);
	bigvalue=(float)getIntegerValue();
	shortvalue=(float)getDecimalValue();
	shortvalue = (shortvalue * 100) / 60;
	latitude=bigvalue+shortvalue;

	/*latitude = atof(NMEA_Latitude);
	bigvalue = (int) latitude / 100;
	shortvalue = (latitude / 100) - bigvalue;
	shortvalue = (shortvalue * 100) / 60;
	latitude = bigvalue + shortvalue;*/

	bigvalue = (int) latitude;
	shortvalue = latitude - bigvalue;
	shortvalue = (int) (shortvalue * 1000000);
	itoa(bigvalue, bigvalue_string_latitude, 10);
	itoa(shortvalue, shortvalue_string_latitude, 10);

	//LONGITUD
	NMEA_Link[31] = bigvalue_string_longitude[0];
	NMEA_Link[32] = bigvalue_string_longitude[1];
	NMEA_Link[33] = '.';
	NMEA_Link[34] = shortvalue_string_longitude[0];
	NMEA_Link[35] = shortvalue_string_longitude[1];
	NMEA_Link[36] = shortvalue_string_longitude[2];
	NMEA_Link[37] = shortvalue_string_longitude[3];
	NMEA_Link[38] = shortvalue_string_longitude[4];
	NMEA_Link[39] = shortvalue_string_longitude[5];

	//SIGNO MAS
	NMEA_Link[40] = '+';
	//SIGNO MENOS
	NMEA_Link[41] = '-';

	//LATITUD
	NMEA_Link[42] = bigvalue_string_latitude[0];
	NMEA_Link[43] = bigvalue_string_latitude[1];
	NMEA_Link[44] = bigvalue_string_latitude[2];
	NMEA_Link[45] = '.';
	NMEA_Link[46] = shortvalue_string_latitude[0];
	NMEA_Link[47] = shortvalue_string_latitude[1];
	NMEA_Link[48] = shortvalue_string_latitude[2];
	NMEA_Link[49] = shortvalue_string_latitude[3];
	NMEA_Link[50] = shortvalue_string_latitude[4];
	NMEA_Link[51] = shortvalue_string_latitude[5];
	NMEA_Link[52] = enter_1;
	NMEA_Link[53] = enter_2;

}

void clearArray() {
	for (int NMEA_Counter = 0; NMEA_Counter < 69; NMEA_Counter++) {
		NMEA_Array[NMEA_Counter] = FALSE;
	}
}

uint8 getFlag() {
	return flag;
}

