/*
 * GPS.c
 *
 *  Created on: Apr 28, 2018
 *      Author: david
 */

#include "GPS.h"
#include "GPIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TypesConverter.h"
#include "EPROM.h"

uint8 NMEA_PROTOCOL_INDEX = FALSE;
uint8 NMEA_Array[50] = { FALSE };
uint8 flag = FALSE;
uint8 NMEA_Link[54] = "https://maps.google.com/maps?q=\n";
uint8 enter[2] = "\n";
uint8 NMEA_Longitude[9] = { FALSE };
uint8 NMEA_Latitude[11] = { FALSE };
uint8 GPSActivated = FALSE;

void getGPS(uint8 gps_data) {

	flag = TRUE;

	if (NMEA_PROTOCOL_INDEX < 50) {
		NMEA_Array[NMEA_PROTOCOL_INDEX] = gps_data;
		NMEA_PROTOCOL_INDEX++;
		if (('G' == NMEA_Array[3]) && ('G' == NMEA_Array[4])
				&& ('A' == NMEA_Array[5]) && ('1' == NMEA_Array[43])) {
			GPSActivated = TRUE;
			GPIO_setPIN(GPIO_B, BIT19);
		}

	} else {

		if (GPSActivated == TRUE) {

			LinkGenerator_GPS();
			GPSActivated = FALSE;

		} else {
			if(('G' == NMEA_Array[3]) && ('G' == NMEA_Array[4])
							&& ('A' == NMEA_Array[5]) && ('1' != NMEA_Array[43])){
						GPIO_clearPIN(GPIO_B, BIT19);
			}
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

	uint8 shortvalue_string_latitude[6] = { FALSE };
	uint8 bigvalue_string_latitude[3] = { FALSE };

	uint8 shortvalue_string_longitude[6] = { FALSE };
	uint8 bigvalue_string_longitude[2] = { FALSE };

	NMEA_Longitude[0] = NMEA_Array[18];
	NMEA_Longitude[1] = NMEA_Array[19];

	NMEA_Longitude[2] = NMEA_Array[20];
	NMEA_Longitude[3] = NMEA_Array[21];
	NMEA_Longitude[4] = NMEA_Array[22];
	NMEA_Longitude[5] = NMEA_Array[23];
	NMEA_Longitude[6] = NMEA_Array[24];
	NMEA_Longitude[7] = NMEA_Array[25];
	NMEA_Longitude[8] = NMEA_Array[26];

	ArrayToFloat(NMEA_Longitude);
	bigvalue = (float) getIntegerValue();
	shortvalue = (float) getDecimalValue();
	shortvalue = shortvalue / 10000;
	longitude = bigvalue + shortvalue;

	bigvalue = (int) longitude / 100;
	shortvalue = (longitude / 100) - bigvalue;
	shortvalue = (shortvalue * 100) / 60;
	longitude = bigvalue + shortvalue;

	bigvalue = (int) longitude;
	shortvalue = longitude - bigvalue;
	shortvalue = (int) (shortvalue * 1000000);
	Integer_to_String(bigvalue_string_longitude, bigvalue);
	Integer_to_String(shortvalue_string_longitude, shortvalue);

	shortvalue = FALSE;
	bigvalue = FALSE;

	NMEA_Latitude[0] = NMEA_Array[30];
	NMEA_Latitude[1] = NMEA_Array[31];
	NMEA_Latitude[2] = NMEA_Array[32];
	NMEA_Latitude[3] = NMEA_Array[33];
	NMEA_Latitude[4] = NMEA_Array[34];
	NMEA_Latitude[5] = NMEA_Array[35];
	NMEA_Latitude[6] = NMEA_Array[36];
	NMEA_Latitude[7] = NMEA_Array[37];
	NMEA_Latitude[8] = NMEA_Array[38];
	NMEA_Latitude[9] = NMEA_Array[39];

	ArrayToFloat(&NMEA_Latitude[0]);
	bigvalue = (float) getIntegerValue();
	shortvalue = (float) getDecimalValue();
	shortvalue = shortvalue / 10000;
	latitude = bigvalue + shortvalue;

	bigvalue = (int) latitude / 100;
	shortvalue = (latitude / 100) - bigvalue;
	shortvalue = (shortvalue * 100) / 60;
	latitude = bigvalue + shortvalue;

	bigvalue = (int) latitude;
	shortvalue = latitude - bigvalue;
	shortvalue = (int) (shortvalue * 1000000);
	Integer_to_String(bigvalue_string_latitude, bigvalue);
	Integer_to_String(shortvalue_string_latitude, shortvalue);

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
	NMEA_Link[52] = enter[0];
	NMEA_Link[53] = enter[1];
	//SendSMS_SIM808();
	GPS_record();

}

void clearArray() {
	for (int NMEA_Counter = 0; NMEA_Counter < 53; NMEA_Counter++) {
		NMEA_Array[NMEA_Counter] = FALSE;
	}
}

uint8 getFlag() {
	return flag;
}

uint8* get_GPSLink() {
	return NMEA_Link;
}

void GPS_record() {
	uint16 EPROM_lastPosition_decoder = FALSE;
	uint8  linknumber=FALSE;

	EPROM_lastPosition_decoder = ReadEPROM(FALSE, FALSE);
	if (255 <= EPROM_lastPosition_decoder) {
		clear_GPSLink_record();
		EPROM_lastPosition_decoder = FALSE;
	}
	linknumber=EPROM_lastPosition_decoder;
	EPROM_lastPosition_decoder *= 54;
	if(FALSE==EPROM_lastPosition_decoder){
		writeString_EPROM(get_GPSLink(), 54, EPROM_lastPosition_decoder + 1);
	}else{
		writeString_EPROM(get_GPSLink(), 54, EPROM_lastPosition_decoder + 2);
	}
	linknumber++;
	writeEPROM(linknumber, FALSE, FALSE);

}

void clear_GPSLink_record() {
	writeEPROM(FALSE, FALSE, FALSE);

}

uint16 BytesNumberToRead(){

	return (ReadEPROM(FALSE, FALSE)*54);

}



uint16 LastLinkPosition(){
	uint16 LinksNumber=FALSE;
	LinksNumber=ReadEPROM(FALSE, FALSE);
	LinksNumber*=54;
	if(FALSE==LinksNumber){
		return FALSE;
	}
	else{
		if(LinksNumber>54){
			LinksNumber-=54;
			LinksNumber+=2;
		}else{
			LinksNumber-=54;
			LinksNumber++;
		}

		return LinksNumber;
	}



}

