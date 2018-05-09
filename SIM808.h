/*
 * SIM808.h
 *
 *  Created on: Apr 22, 2018
 *      Author: david
 */

#ifndef SIM808_H_
#define SIM808_H_

#include "DataTypeDefinitions.h"

#define HANGUP_COMMAND "ATH;\n" /**Comando AT que detiene la llamda ejecutada*/
#define CALL_NUM "ATD3929270291;\n" /**Comando AT que contiene el número al que se le realizara la llamda*/
#define SMS_CONFIG "AT+CMGF=1\r\n" /**Comando AT que configura la SIM808 en modo de SMS*/
#define SMS_NUM "AT+CMGS=\"3929270291\"\n"/**Comando AT que contiene el número al que se le enviara el mensaje de SMS*/
#define ENTER "\n"/**Enter necesario para los comandos AT*/
#define CTRL_Z 26/**CTRLZ necesario para el envio del SMS*/
#define SMS_LENGTH 54

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 Esta función realiza una llamada telefónica al número que se asignó como predeterminado
  	 \param[in] void
  	 \return void

  */
void MakePhoneCall_SIM808();

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 Esta función manda por SMS el link de google maps para observar la ubicación GPS
  	 \param[in] void
  	 \return void

  */
void SendSMS_SIM808();

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 Esta función cuelga la llamada que se esta ejecutando
  	 \param[in] void
  	 \return void

  */
void HangUp_SIM808();

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	 Esta función asigna a la cadena del SMS el link de google maps
  	 \param[in] uint8* SMS_Pointer
  	 \return void

  */
void set_SMS(uint8* SMS_Pointer);

#endif /* SIM808_H_ */
