/*
 * PasswordDetector.h
 *
 *  Created on: Apr 17, 2018
 *      Author: david
 */

#ifndef PASSWORDDETECTOR_H_
#define PASSWORDDETECTOR_H_

#include "DataTypeDefinitions.h"
#include "UART.h"

#define PASS_H 0x48//Password

const static uint8 RealPassword=PASS_H;//Constant that contain the passworn

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	  This function verificte the real password with the received password
  	 \param[in] password detected
  	 \return void

  */
void passwordVerification(uint8 pass_detected);

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	  //Function to get get access the status
  	 \param[in] void
  	 \return uint8

  */
uint8 get_AccessStatus();

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	  //Function that clear the status
  	 \param[in] void
  	 \return void

  */
void clear_AccessStatus();



#endif /* PASSWORDDETECTOR_H_ */
