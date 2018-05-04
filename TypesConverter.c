/*
 * TypesConverter.c
 *
 *  Created on: May 3, 2018
 *      Author: david
 */

#include "DataTypeDefinitions.h"
#include "TypesConverter.h"

#define OFFSET_ASCII 48
#define TEN_VALUE 10
#define DECIMAL_COUNTER_INIT -1

static uint16 integerValue;
static uint32 decimalValue;

uint16 getIntegerValue() {

	return integerValue;

}
uint32 getDecimalValue() {
	return decimalValue;
}

uint32 TenPow(uint32 data, uint8 pow) {

	while (TRUE != pow) {
		pow--;
		data = data * TEN_VALUE;
	}
	return data;

}

void ArrayToFloat(uint8*dataPointer) {
	integerValue=FALSE;
	decimalValue=FALSE;
	uint8 DecimalCounter = DECIMAL_COUNTER_INIT;
	uint8 IntegerCounter = FALSE;
	uint8 DotFlag = FALSE;
	uint8 ArrayLength = FALSE;


	while (*dataPointer) {
		if (('.' == *dataPointer) || (TRUE == DotFlag)) {
			DotFlag = TRUE;
			DecimalCounter++;
		} else {

			IntegerCounter++;

		}

		dataPointer++;
		ArrayLength++;
	}

	dataPointer -= ArrayLength;
	DotFlag = FALSE;

	while (*dataPointer) {

		if (TRUE == DotFlag) {

			decimalValue += TenPow(*dataPointer - OFFSET_ASCII, DecimalCounter);
			DecimalCounter--;

		} else {

			if (('.' == *dataPointer)) {

				DotFlag = TRUE;
			} else {

				integerValue += TenPow(*dataPointer - OFFSET_ASCII,IntegerCounter);
				IntegerCounter--;
			}

		}

		dataPointer++;

	}

}

