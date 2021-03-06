/*
 * TypesConverer.h
 *
 *  Created on: May 3, 2018
 *      Author: david
 */

#ifndef TYPESCONVERTER_H_
#define TYPESCONVERTER_H_

#define DECIFRA_VALOR_H_
#define DECENA_VALOR 10				/*numero para referirnos a las decenas*/
#define CENTENA_VALOR 100			/*numero para referirnos a las centenas*/
#define UNIDADMILLAR_VALOR 1000		/*numero para referirnos a las unidades de millar*/
#define DECENAMILLAR_VALOR 10000	/*numero para referirnos a las decenas de millar*/
#define CENTENAMILLAR_VALOR 100000 /*numero para referirnos a las centenas de millar*/
#define UNIDADMILLON_VALOR 1000000/*numero para referirnos a las unidades de millon*/
#define DECENAMILLON_VALOR 10000000/*numero para referirnos a las decenas de millon*/
#define OFFSET_ASCII 48				/*Oscii offset*/
#define TEN_VALUE 10				/*10 VALUE*/
#define DECIMAL_COUNTER_INIT -1		/*Counter init*/



/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	  Function to pow a number
  	 \param[in] data and pow
  	 \return uint32

  */
uint32 TenPow(uint32 data, uint8 pow);

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	  Function to pass from an array to float
  	 \param[in] data pointer
  	 \return void

  */
void ArrayToFloat(uint8* dataPointer);

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	  Function to get the integer value
  	 \param[in] void
  	 \return uint16

  */
uint16 getIntegerValue();

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	  Function to get the decimal value
  	 \param[in] data and pow
  	 \return uint32

  */
uint32 getDecimalValue();

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	  Function to spread a value
  	 \param[in] value
  	 \return void

  */
void obtenvalor(uint32 valor);

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	  Function to get units
  	 \param[in] void
  	 \return uint8

  */
uint8 getUnidad();

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	  Function to get dec
  	 \param[in] void
  	 \return uint8

  */
uint8 getDecena();

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	  Function to get hundred
  	 \param[in] void
  	 \return uint8

  */
uint8 getCentena();

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	  Function to get millar units
  	 \param[in] void
  	 \return uint8

  */
uint8 getUnidadMillar();

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	  Function to get millar dec
  	 \param[in] void
  	 \return uint8

  */
uint8 getDecenaMillar();

/********************************************************************************************/
 /********************************************************************************************/
 /********************************************************************************************/
 /*!
  	 \brief
  	 	  Function to pass from a integer to string
  	 \param[in] direction and number
  	 \return void

  */
void Integer_to_String(uint8* direccion, int num);


#endif /* TYPESCONVERTER_H_ */
