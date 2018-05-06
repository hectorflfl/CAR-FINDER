/*
 * EPROM.h
 *
 *  Created on: Apr 6, 2018
 *      Author: David Gálvez Sahagún
 */

#ifndef EPROM_H_
#define EPROM_H_


#define CONTROL_WRITE_MEM 0XA0 //**Clave de control para escritura en la EPROM*/
#define CONTROL_READ_MEM 0XA1//**Clave de control para lectura en la EPROM*/
#define SHIFT4 4 //**Constate 4 que sirve para realizar barridos de bits*/
#define FOURBITS 0XF//**Mascara para los primeros cuatro bits menos significativos*/
#define THREEBITS 7//**Mascara para los primeros tres bits menos significativos*/
#define PAGESIZE 500//**Tamaño del arreglo que almacena los datos leidos de la EPROM*/
#define DELAY_800 800//**Conteo de 800*/
#define NULL_0 0X0//**Valor Nulo*/

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief
 Esta función lee solo un byte de la memoria EPROM
 \param[in] uint8 highAddress -- Parte alta de la dirección a leer
 \param[in] uint8 lowAddress -- Parte baja de la dirección a leer
 \return void

 */
uint8 ReadEPROM(uint8 highAddress, uint8 lowAddress);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief
 Esta función escribe solo un byte de la memoria EPROM
 \param[in] uint8 highAddress -- Parte alta de la dirección a escribir
 \param[in] uint8 lowAddress -- Parte baja de la dirección a escribir
 \param[in] uint8 data -- Byte(dato) que se escribe en memoria
 \return void

 */
void writeEPROM(uint8 data, uint8 highAddress, uint8 lowAddress);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief
 Esta función escribe una cadena de caracteres en la memoria EPROM
 \param[in] uint8 Address -- Direccion de la memoria EPROM en donde se va a escibir
 \param[in] uint8 BytesNum -- Numeros de bytes a escribir
 \param[in] uint8 data_pointer -- Dirección de momeoria del string a escribir
 \return void

 */
void writeString_EPROM(uint8 *data_pointer, uint8 BytesNum, uint8 Address);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief
 Esta función lee una cadena de caracteres de la memoria EPROM
 \param[in] uint8 Address -- Direccion de la memoria EPROM en donde se comenzara leer
 \param[in] uint8 BytesNum -- Numeros de bytes a leer

 \return uint8*

 */
uint8* ReadString_EPROM(uint8 BytesNum, uint8 Address);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief
 Esta función limpia el arreglo que contiene los valores leido de la EPROM (Cada que se lee un String se debe limpiar la memoria)
 \return void

 */
void cleanMemory();

#endif /* EPROM_H_ */
