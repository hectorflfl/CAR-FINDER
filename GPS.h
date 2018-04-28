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


void getGPS(uint8 gps_data);
void LinkGenerator_GPS(void);
void clearArray(void);
uint8 getFlag(void);
uint8* get_GPSLink ();

#endif /* GPS_H_ */
