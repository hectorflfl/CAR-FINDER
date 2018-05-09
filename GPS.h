/*
 * GPS.c
 *
 *  Created on: Apr 28, 2018
 *      Author: David Gálvez Sahagún
 */


#ifndef GPS_H_
#define GPS_H_

#include "DataTypeDefinitions.h"
#include "UART.h"

#define ARRAYLENGTH 50 /** Tamaño del buffer para el NMEA*/
#define LONG_LENGTH 9 /** Tamaño del buffer para la longitud*/
#define LAT_LENGTH 11/** Tamaño del buffer para la latitud*/
#define DENOMINATOR_NMEA 60/** Denominador necesario para la conversión de NMEA--> google maps*/
#define LINK_LENGTH 54/** Tamaño del arreglo que almacena el link de google maps*/
#define DEC_2 2
#define ONE_MILLON 1000000
#define TEN_THOUSAND 10000
#define ONE_HUNDRED 100

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 Esta función obtiene el GPGGA del GPS
  	 \param[in] uint8 gps_data
  	 \return void

  */
void getGPS(uint8 gps_data);


/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 Esta función genera el link de google maps, luego de decodificar el protocolo NMEA
  	 \param[in] void
  	 \return void

  */
void LinkGenerator_GPS(void);


/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 Esta función limpia el buffer en donde se almacenan los datos del NMEA
  	 \param[in] void
  	 \return void

  */
void clearArray(void);


/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	Esta función retona el valor de la bandera del GPS, la cual indica si esta mandando datos correctos
  	 	UP501.
  	 \param[in] void
  	 \return uint8

  */
uint8 getFlag(void);


/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 Esta función retorna un puntero el cual indica al punta al link de google maps
  	 \param[in] void.
  	 \return uint8

  */
uint8* get_GPSLink ();


/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	Esta función almacena en la memoria EPROM los link de google maps generados.
  	 \param[in] void
  	 \return void

  */
void GPS_record();


/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 Este función limpia el la el numero de links que se han generado.
  	 \param[in] void.
  	 \return void

  */
void clear_GPSLink_record();


/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	  Este función retorna la cantidad de bytes utilizados por la memoria EPROM,es decir, el peso de todos
  	 	  los links de google maps almacenados.
  	 \param[in] void
  	 \return uint16

  */
uint16 BytesNumberToRead();



#endif /* GPS_H_ */
