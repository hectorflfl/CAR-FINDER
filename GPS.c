/*
 * GPS.c
 *
 *  Created on: Apr 28, 2018
 *      Author: David Gálvez Sahagún
 */

#include "GPS.h"
#include "GPIO.h"
#include "TypesConverter.h"
#include "EPROM.h"

uint8 NMEA_Protocol_Index = FALSE;	/**Contador para el buffer del NMEA */
uint8 NMEA_Array[ARRAYLENGTH] = { FALSE };	/**Arreglo del NMEA*/
uint8 flagGPS = FALSE;	/**Bandera del GPS, que indica si tiene datos validos*/
uint8 NMEA_Link[LINK_LENGTH] = "https://maps.google.com/maps?q=\n";	/**Cadena que almacenara el link de google maps*/
uint8 enter[DEC_2] = "\n";	/**Cadena que almacena el enter para mandar el SMS*/
uint8 NMEA_Longitude[LONG_LENGTH] = { FALSE };/**Arreglo que almacena la longitud*/
uint8 NMEA_Latitude[LAT_LENGTH] = { FALSE };/**Arreglo que almacena la latitud*/
uint8 GPSActivated = FALSE;/**Variable que indica cuando el GPS esta activo*/



void getGPS(uint8 gps_data) {

	flagGPS = TRUE;

	if (NMEA_Protocol_Index < ARRAYLENGTH) {/** Preguntamos si ya se lleno el buffer del NMEA*/
		NMEA_Array[NMEA_Protocol_Index] = gps_data;
		NMEA_Protocol_Index++;
		if (('G' == NMEA_Array[3]) && ('G' == NMEA_Array[4]) && ('A' == NMEA_Array[5]) && ('1' == NMEA_Array[43])) {/** Comprobamos si el buffer tiene guardado el dato GPGGA, el cual nos da la latitud y longitud*/
			GPSActivated = TRUE;
			GPIO_setPIN(GPIO_B, BIT19);/** Encendemos el led si hay señal GPS*/
		}

	} else {

		if (GPSActivated == TRUE) {

			LinkGenerator_GPS();/** Una vez que se llena el buffer y almacenamos el GPGGA, procedemos a generar el link de google maps*/
			GPSActivated = FALSE;

		} else {
			if (('G' == NMEA_Array[3]) && ('G' == NMEA_Array[4]) && ('A' == NMEA_Array[5]) && ('1' != NMEA_Array[43])) {
				GPIO_clearPIN(GPIO_B, BIT19);/** Apagamos el led si no hay señal GPS*/
			}
			flagGPS = FALSE;
			NMEA_Protocol_Index = FALSE;
			clearArray();/**Limpiamos el buffer del NMEA para almacenar nuevos datos*/
		}
	}
}

void LinkGenerator_GPS() {

	float bigvalue = FALSE;/** flotante que almacenara la parte alta de la latitud y longitud*/
	float shortvalue = FALSE;/** flotante que almacenara la parte baja de la latitud y longitud*/
	float longitude = FALSE;/** flotante que almacenara el valor de la longitud*/
	float latitude = FALSE;/** flotante que almacenara la latitud */

	uint8 shortvalue_string_latitude[6] = { FALSE };/**String que guardara la parte baja en ascii de la latitud*/
	uint8 bigvalue_string_latitude[3] = { FALSE };/**String que guardara la parte alta en ascii de la latitud*/

	uint8 shortvalue_string_longitude[6] = { FALSE };/**String que guardara la parte baja en ascii de la longitud*/
	uint8 bigvalue_string_longitude[2] = { FALSE };/**String que guardara la parte alta en ascii de la longitud*/


	/**Capturamos la longitud que arroja el GPGGA*/
	NMEA_Longitude[0] = NMEA_Array[18];
	NMEA_Longitude[1] = NMEA_Array[19];

	NMEA_Longitude[2] = NMEA_Array[20];
	NMEA_Longitude[3] = NMEA_Array[21];
	NMEA_Longitude[4] = NMEA_Array[22];
	NMEA_Longitude[5] = NMEA_Array[23];
	NMEA_Longitude[6] = NMEA_Array[24];
	NMEA_Longitude[7] = NMEA_Array[25];
	NMEA_Longitude[8] = NMEA_Array[26];


	/**Convertimos la el arreglo de la longitud en un flotante*/
	ArrayToFloat(NMEA_Longitude);
	bigvalue = (float) getIntegerValue();
	shortvalue = (float) getDecimalValue();
	shortvalue = shortvalue / TEN_THOUSAND;
	longitude = bigvalue + shortvalue;

	/**Relizamos la conversión de la longitud del GPGGA en la longitud que se va mostrar en el link de google maps*/
	bigvalue = (int) longitude / ONE_HUNDRED;
	shortvalue = (longitude / ONE_HUNDRED) - bigvalue;
	shortvalue = (shortvalue * ONE_HUNDRED) / DENOMINATOR_NMEA;
	longitude = bigvalue + shortvalue;

	/**Convertimos el valor flotante en un string para poder mandarlo como cadena de caracteres*/
	bigvalue = (int) longitude;
	shortvalue = longitude - bigvalue;
	shortvalue = (int) (shortvalue * ONE_MILLON);
	Integer_to_String(bigvalue_string_longitude, bigvalue);
	Integer_to_String(shortvalue_string_longitude, shortvalue);

	shortvalue = FALSE;
	bigvalue = FALSE;


	/**Capturamos la latitud que arroja el GPGGA*/
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


	/**Convertimos la el arreglo de la latitud en un flotante*/
	ArrayToFloat(&NMEA_Latitude[0]);
	bigvalue = (float) getIntegerValue();
	shortvalue = (float) getDecimalValue();
	shortvalue = shortvalue / TEN_THOUSAND;
	latitude = bigvalue + shortvalue;


	/**Relizamos la conversión de la longitud del GPGGA en la latitud que se va mostrar en el link de google maps*/
	bigvalue = (int) latitude / ONE_HUNDRED;
	shortvalue = (latitude / ONE_HUNDRED) - bigvalue;
	shortvalue = (shortvalue * ONE_HUNDRED) / DENOMINATOR_NMEA;
	latitude = bigvalue + shortvalue;

	/**Convertimos el valor flotante en un string para poder mandarlo como cadena de caracteres*/
	bigvalue = (int) latitude;
	shortvalue = latitude - bigvalue;
	shortvalue = (int) (shortvalue * TEN_THOUSAND);
	Integer_to_String(bigvalue_string_latitude, bigvalue);
	Integer_to_String(shortvalue_string_latitude, shortvalue);

	/**Prodecemos a concatenar el valor real de la longitud en el link de google maps*/
	NMEA_Link[31] = bigvalue_string_longitude[0];
	NMEA_Link[32] = bigvalue_string_longitude[1];
	NMEA_Link[33] = '.';
	NMEA_Link[34] = shortvalue_string_longitude[0];
	NMEA_Link[35] = shortvalue_string_longitude[1];
	NMEA_Link[36] = shortvalue_string_longitude[2];
	NMEA_Link[37] = shortvalue_string_longitude[3];
	NMEA_Link[38] = shortvalue_string_longitude[4];
	NMEA_Link[39] = shortvalue_string_longitude[5];


	NMEA_Link[40] = '+';

	NMEA_Link[41] = '-';

	/**Prodecemos a concatenar el valor real de la latitud en el link de google maps*/
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
	/**Al ultimo de la arreglo ingresamos un enter para poder mandar el mensaje SMS*/
	NMEA_Link[52] = enter[0];
	NMEA_Link[53] = enter[1];



}

void clearArray() {

	/**Ciclo for que itera el arreglo de NMEA y le asigna cero*/
	for (int NMEA_Counter = FALSE;  (LINK_LENGTH-TRUE) > NMEA_Counter; NMEA_Counter++) {
		NMEA_Array[NMEA_Counter] = FALSE;
	}
}

uint8 getFlag() {
	/*retorna la variable flagGPS*/
	return flagGPS;
}

uint8* get_GPSLink() {
	/**retorna la variable NMEA_Link*/
	return NMEA_Link;
}

void GPS_record() {
	uint16 EPROM_lastPosition_decoder = FALSE;
	uint8 linknumber = FALSE;

	/**Leemos en la primer posicíon de memeria que indica el numero de links almacenados*/
	EPROM_lastPosition_decoder = ReadEPROM(FALSE, FALSE);
	if (255 <= EPROM_lastPosition_decoder) {/**Comprobamos si el numero de de links excedio de 256*/
		clear_GPSLink_record();
		EPROM_lastPosition_decoder = FALSE;
	}
	linknumber = EPROM_lastPosition_decoder;
	EPROM_lastPosition_decoder *= LINK_LENGTH;
	/**Almacenamos el nuevo link en la memoria EPROM*/
	if (FALSE == EPROM_lastPosition_decoder) {
		writeString_EPROM(get_GPSLink(), LINK_LENGTH, EPROM_lastPosition_decoder + TRUE);
	} else {
		writeString_EPROM(get_GPSLink(), LINK_LENGTH, EPROM_lastPosition_decoder + DEC_2);
	}
	linknumber++;
	writeEPROM(linknumber, FALSE, FALSE);

}

void clear_GPSLink_record() {
	/**Limpiamos el numero de links en la memoria EPROM*/
	writeEPROM(FALSE, FALSE, FALSE);

}

uint16 BytesNumberToRead() {
	/**Leemos en numero de links y lo multiplicamos por el tamaño de cada uno para saber cuantos bytes se tienen que leer*/
	return (ReadEPROM(FALSE, FALSE) * LINK_LENGTH);

}


