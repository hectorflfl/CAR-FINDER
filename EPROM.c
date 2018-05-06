/*
 * EPROM.c
 *
 *  Created on: Apr 6, 2018
 *      Author: David Gálvez Sahagún
 */

#include <stdio.h>

#include "MK64F12.h"
#include "DataTypeDefinitions.h"
#include "I2C.h"
#include "GPIO.h"
#include "GlobalFunctions.h"
#include "EPROM.h"



uint8 data = FALSE;//**Variable global que almacena byte por byte  el dato leido*/
uint8 readedData[PAGESIZE];//**Arreglo que almacena los datos leidos*/
uint8 ReadEPROM(uint8 highAddress, uint8 lowAddress) {

	I2C_TX_RX_Mode(I2C_0, TRUE); //**Se configura como TX*/
	delay(DELAY_800);//**Retado para evitar la mala interpretación de lectura*/
	I2C_start(I2C_0);//**Se configura como maestro y como TX*/
	I2C_write_Byte(I2C_0, CONTROL_WRITE_MEM);//**Escribe un byte en el registro D I2C0*/
	I2C_wait(I2C_0);//**Se espera hasta que el proceso finaliza*/
	I2C_get_ACK(I2C_0);//**Obtine el valor de la bandera RXAK para comprobar si se hizo un ACK*/

	//**Se escibe la parte alta de la dirección que se quiere leer */
	I2C_write_Byte(I2C_0, highAddress); //DIRECCION ALTA
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	//**Se escibe la parte alta de la dirección que se quiere leer */
	I2C_write_Byte(I2C_0, lowAddress); //DIRECCION BAJA
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	//**Se repite el inicio y se cambia la dirección de control para leer el dato*/
	I2C_repeted_Start(I2C_0);
	I2C_write_Byte(I2C_0, CONTROL_READ_MEM);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);
	delay(DELAY_800);

	//**Se configura como RX*/
	I2C_TX_RX_Mode(I2C_0, FALSE);
	I2C_NACK(I2C_0);

	data = I2C_read_Byte(I2C_0);
	I2C_wait(I2C_0);
	//**Se detiene el proceso y se lee el valor real*/
	I2C_stop(I2C_0);
	data = I2C_read_Byte(I2C_0);
	return data;

}

void writeEPROM(uint8 data, uint8 highAddress, uint8 lowAddress) {

	//**Se configura como maestro, en TX, e inicia el proceso de escritura */
	delay(DELAY_800);
	I2C_TX_RX_Mode(I2C_0, TRUE);
	I2C_start(I2C_0);
	I2C_write_Byte(I2C_0, CONTROL_WRITE_MEM);
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	//**Se escibe la parte alta de la dirección en donde se quiere escribir el dato */
	I2C_write_Byte(I2C_0, highAddress); //DIRECCION ALTA
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);

	//**Se escibe la parte alta de la dirección en donde se quiere escribir el dato */
	I2C_write_Byte(I2C_0, lowAddress); //DIRECCION BAJA
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);


	//**Se escibe el dato */
	I2C_write_Byte(I2C_0, data); //DATO A ESCRIBIR
	I2C_wait(I2C_0);
	I2C_get_ACK(I2C_0);
	I2C_stop(I2C_0);

}
void writeString_EPROM(uint8 *data_pointer, uint8 BytesNum, uint8 Address) {

	//**Se guarda la dirrección de donde se quiere leer en una variable local */
	uint8 address_aux = Address;

	//**Se realiza un ciclo para mandar byte por byte el arreglo que se quiere guardar */
	for (uint8 ByteCont = FALSE; ByteCont < BytesNum; ByteCont++) {


		//**Se realiza el mismo proceso de escritura de la función write_EPROM */
		delay(DELAY_800);
		I2C_TX_RX_Mode(I2C_0, TRUE); //TX

		I2C_start(I2C_0);
		I2C_write_Byte(I2C_0, CONTROL_WRITE_MEM);
		I2C_wait(I2C_0);
		I2C_get_ACK(I2C_0);

		I2C_write_Byte(I2C_0, (address_aux >> SHIFT4) & THREEBITS); //DIRECCION ALTA
		I2C_wait(I2C_0);
		I2C_get_ACK(I2C_0);

		I2C_write_Byte(I2C_0, address_aux & FOURBITS); //DIRECCION BAJA
		I2C_wait(I2C_0);
		I2C_get_ACK(I2C_0);

		I2C_write_Byte(I2C_0, *data_pointer); //DATO A ESCRIBIR
		I2C_wait(I2C_0);
		I2C_get_ACK(I2C_0);
		I2C_stop(I2C_0);

		//**Se incrementa la dirección de la memoria EPROM */
		address_aux++;

		//**Se incrementa la dirección de la memoria del arreglo a guardar */
		data_pointer++;

	}




}

uint8* ReadString_EPROM(uint8 BytesNum, uint8 Address) {

	//**Se guarda el la dirección que se quiere leer en la EPROM en una variable local*/
	uint8 address_aux = Address;
	//**Variable local que va guardar byte por byte */
	uint8 data = FALSE;
	//**Variable local que sirve para contar el numero de byte a leer */
	uint8 ByteCont = FALSE;

	//**Se realiza un ciclo para leer byte por byte y almacenarlo en un arreglo global */
	for (ByteCont = FALSE; ByteCont < BytesNum; ByteCont++) {

		I2C_TX_RX_Mode(I2C_0, TRUE); //TX
		delay(800);
		I2C_start(I2C_0);
		I2C_write_Byte(I2C_0, CONTROL_WRITE_MEM);
		I2C_wait(I2C_0);
		I2C_get_ACK(I2C_0);

		I2C_write_Byte(I2C_0, (address_aux >> SHIFT4) & THREEBITS); //DIRECCION ALTA
		I2C_wait(I2C_0);
		I2C_get_ACK(I2C_0);

		I2C_write_Byte(I2C_0, address_aux & FOURBITS); //DIRECCION BAJA
		I2C_wait(I2C_0);
		I2C_get_ACK(I2C_0);

		I2C_repeted_Start(I2C_0);
		I2C_write_Byte(I2C_0, CONTROL_READ_MEM);
		I2C_wait(I2C_0);
		I2C_get_ACK(I2C_0);
		delay(DELAY_800);

		I2C_TX_RX_Mode(I2C_0, FALSE); //RX
		I2C_NACK(I2C_0);

		data = I2C_read_Byte(I2C_0);
		I2C_wait(I2C_0);

		I2C_stop(I2C_0);
		data = I2C_read_Byte(I2C_0);

		//**Se guarda el byte leído en el indice ByteCont  */
		readedData[ByteCont] = data;
		//**Se incrementa la dirección de la EPROM  */
		address_aux++;

	}

	//**Retorna la dirección de memoria en donde estan almacenados los datos leidos */
	return readedData;

}

void cleanMemory() {
	//**Ciclo for que limpia el arreglo que almacena los datos leidos de la EPROM */
	for (uint8 lengthArray = FALSE; lengthArray < PAGESIZE; lengthArray++) {
		readedData[lengthArray] = NULL_0;
	}

}

