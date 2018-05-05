/*
 * LCDNokia5110.h
 *
 *  Created on: Jun 11, 2014
 *      Author: Luis
 */

#ifndef LCDNOKIA5110_H_
#define LCDNOKIA5110_H_

#include "DataTypeDefinitions.h"

#define SCREENW 84
#define SCREENH 48
#define LCD_X 84
#define LCD_Y 48
#define LCD_DATA 1
#define LCD_CMD 0
#define DATA_OR_CMD_PIN 3
#define RESET_PIN 0
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It configures the LCD
 	 \param[in]  void
 	 \return void
 */

void LCDNokia_init(void);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It writes a byte in the LCD memory. The place of writting is the last place that was indicated by LCDNokia_gotoXY. In the reset state
  	  	  	  the initial place is x=0 y=0
 	 \param[in]  DataOrCmd & Data
 	 \return void
 */

void LCDNokia_writeByte(uint8 DataOrCmd, uint8 data);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 it clears all the figures in the LCD
 	 \param[in]  void
 	 \return void
 */

void LCDNokia_clear(void);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It is used to indicate the place for writing a new character in the LCD. The values that x can take are 0 to 84 and y can take values
 	 	 	 from 0 to 5
 	 \param[in]  coordinate
 	 \return void
 */

void LCDNokia_gotoXY(uint8 x, uint8 y);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It allows to write a figure represented by constant array
 	 \param[in]  my_array that contains the image
 	 \return void
 */

void LCDNokia_bitmap(const uint8* my_array);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It write a character in the LCD
 	 \param[in]  character
 	 \return void
 */

void LCDNokia_sendChar(uint8 character);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It write a string into the LCD
 	 \param[in]  character
 	 \return void
 */

void LCDNokia_sendString(uint8* characters);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It used in the initialisation routine
 	 \param[in]  void
 	 \return void
 */


void LCD_delay(void);

void setCountDown(uint8 newCounter);

void StartCountDown();

#endif /* LCDNOKIA5110_H_ */
