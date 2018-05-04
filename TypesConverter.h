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
#define DECIFRA_VALOR_H_

#define DECENA_VALOR 10				/*numero para referirnos a las decenas*/
#define CENTENA_VALOR 100			/*numero para referirnos a las centenas*/
#define UNIDADMILLAR_VALOR 1000		/*numero para referirnos a las unidades de millar*/
#define DECENAMILLAR_VALOR 10000	/*numero para referirnos a las decenas de millar*/
#define CENTENAMILLAR_VALOR 100000
#define UNIDADMILLON_VALOR 1000000
#define DECENAMILLON_VALOR 10000000


uint32 TenPow(uint32 data, uint8 pow);
void ArrayToFloat(uint8*dataPointer);
uint16 getIntegerValue();
uint32 getDecimalValue();


void obtenvalor(uint32 valor);
/*FunciÃ³n para ontener las unidades*/
uint8 getUnidad();

/*FunciÃ³n para ontener las decenas*/
uint8 getDecena();

/*FunciÃ³n para ontener las centenas*/
uint8 getCentena();

/*FunciÃ³n para ontener las unidades de millar*/
uint8 getUnidadMillar();

/*FunciÃ³n para ontener las decenas de millar*/
uint8 getDecenaMillar();


void Integer_to_String(uint8* direccion, int num);


#endif /* TYPESCONVERTER_H_ */
