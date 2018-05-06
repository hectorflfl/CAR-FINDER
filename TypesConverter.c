/*
 * TypesConverter.c
 *
 *  Created on: May 3, 2018
 *      Author: david
 */

#include "DataTypeDefinitions.h"
#include "TypesConverter.h"

static uint8 unidad = FALSE;		/*Variable que contendra las unidades de la frecuencia*/
static uint8 decena = FALSE;		/*Variable que contendra las decenas de la frecuencia*/
static uint8 centena = FALSE;		/*Variable que contendra las centenas de la frecuencia*/
static uint8 unidadmillar = FALSE; /*Variable que contendra las unidades de milar de la frecuencia*/
static uint8 decenamillar = FALSE; /*Variable que contendra las unidades de millar de la frecuencia*/
static uint8 centenamillar = FALSE;
static uint8 unidadmillon = FALSE;
static uint8 decenamillon = FALSE;



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
	sint8 DecimalCounter = DECIMAL_COUNTER_INIT;
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




void obtenvalor(uint32 valor) {


	if ((valor / DECENAMILLON_VALOR) != FALSE) {
			decenamillon = valor / DECENAMILLON_VALOR;
		} else {
			decenamillon = FALSE;
		}
	if ((valor / UNIDADMILLON_VALOR) != FALSE) {
		valor = valor - (DECENAMILLON_VALOR * decenamillon);
		unidadmillon = valor / UNIDADMILLON_VALOR;

		} else {
			unidadmillon = FALSE;
		}
	if ((valor / CENTENAMILLAR_VALOR) != FALSE) {
		valor = valor - (UNIDADMILLON_VALOR * unidadmillon);
		centenamillar = valor / CENTENAMILLAR_VALOR;

		} else {
			centenamillar = FALSE;
		}
	if ((valor / DECENAMILLAR_VALOR) != FALSE) {
		valor = valor - (CENTENAMILLAR_VALOR * centenamillar);
		decenamillar = valor / DECENAMILLAR_VALOR;

	} else {
		decenamillar = FALSE;
	}
	/*Se obtiene la unidad de millar*/
	if ((valor / UNIDADMILLAR_VALOR) != FALSE) {
		valor = valor - (DECENAMILLAR_VALOR * decenamillar);
		unidadmillar = valor / UNIDADMILLAR_VALOR;
	} else {
		unidadmillar = FALSE;
	}
	/*Se obtiene la centena*/
	if ((valor / CENTENA_VALOR) != FALSE) {
		valor = valor - (UNIDADMILLAR_VALOR * unidadmillar);
		centena = valor / CENTENA_VALOR;
	} else {
		centena = FALSE;
	}
	/*Se obtiene la decena*/
	if ((valor / DECENA_VALOR) != FALSE) {
		valor = valor - (CENTENA_VALOR * centena);
		decena = valor / DECENA_VALOR;
	} else {
		decena = FALSE;
	}
	/*Se obtiene la unidad*/
	if (valor != FALSE) {
		unidad = valor - (DECENA_VALOR * decena);

	} else {
		unidad = FALSE;
	}

}

/*FunciÃ³n para ontener las unidades*/
uint8 getUnidad() {
	return unidad;
}

/*FunciÃ³n para ontener las decenas*/
uint8 getDecena() {
	return decena;
}

/*FunciÃ³n para ontener las centenas*/
uint8 getCentena() {
	return centena;
}

/*FunciÃ³n para ontener las unidades de millar*/
uint8 getUnidadMillar() {
	return unidadmillar;
}

/*FunciÃ³n para ontener las decenas de millar*/
uint8 getDecenaMillar() {
	return decenamillar;
}


void Integer_to_String(uint8* direccion, int num){

	int position = FALSE;

	obtenvalor(num);
	if(FALSE != decenamillon){direccion[position] = decenamillon+OFFSET_ASCII;position++;}
	if(FALSE != unidadmillon || FALSE != decenamillon){direccion[position] = unidadmillon+OFFSET_ASCII;position++;}
	if(FALSE != centenamillar || FALSE != decenamillon || FALSE != unidadmillon){direccion[position] = centenamillar+OFFSET_ASCII;position++;}
	if(FALSE != decenamillar || FALSE != decenamillon || FALSE != unidadmillon || FALSE != centenamillar){direccion[position] = decenamillar+OFFSET_ASCII;position++;}
	if(FALSE != unidadmillar || FALSE != decenamillon || FALSE != unidadmillon || FALSE != centenamillar || FALSE != decenamillar){direccion[position] = unidadmillar+OFFSET_ASCII;position++;}
	if(FALSE != centena || FALSE != decenamillon || FALSE != unidadmillon || FALSE != centenamillar || FALSE != decenamillar || FALSE != unidadmillar){direccion[position] = centena+OFFSET_ASCII;position++;}
	if(FALSE != decena || FALSE != decenamillon || FALSE != unidadmillon || FALSE != centenamillar || FALSE != decenamillar || FALSE != unidadmillar || FALSE != centena){direccion[position] = decena+OFFSET_ASCII;position++;}
	direccion[position] = unidad+OFFSET_ASCII;

}


