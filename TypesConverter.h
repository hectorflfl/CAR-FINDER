/*
 * TypesConverer.h
 *
 *  Created on: May 3, 2018
 *      Author: david
 */

#ifndef TYPESCONVERTER_H_
#define TYPESCONVERTER_H_

#define OFFSET_ASCII 48
#define TEN_VALUE 10
#define DECIMAL_COUNTER_INIT -1

uint32 TenPow(uint32 data, uint8 pow);
void ArrayToFloat(uint8*dataPointer);
uint16 getIntegerValue();
uint32 getDecimalValue();

#endif /* TYPESCONVERTER_H_ */
