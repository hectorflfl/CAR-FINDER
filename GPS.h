/*
 * GPS.h
 *
 *  Created on: Apr 28, 2018
 *      Author: david
 */

#ifndef GPS_H_
#define GPS_H_

#include "DataTypeDefinitions.h"
#include "UART.h"

#define LETTER_A 0x41
#define LETTER_V 0x56

void getGPS(uint8 gps_data);
void LinkGenerator_GPS(void);
void clearArray(void);
uint8 getFlag(void);
uint8* get_GPSLink ();
void GPS_record();
void clear_GPSLink_record();
uint16 BytesNumberToRead();
uint16 LastLinkPosition();

#endif /* GPS_H_ */
