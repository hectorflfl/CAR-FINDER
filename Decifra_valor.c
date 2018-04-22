/*
 * Decifra_valor.c
 *
 *  Created on: Apr 7, 2018
 *      Author: carlo
 */


/*
 * Decifra_valor.c
 *
 *  Created on: Apr 7, 2018
 *      Author: carlo
 */

#include "DataTypeDefinitions.h"
#include "Decifra_valor.h"

uint8 unidad = FALSE;		/*Variable que contendra las unidades de la frecuencia*/
uint8 decena = FALSE;		/*Variable que contendra las decenas de la frecuencia*/
uint8 centena = FALSE;		/*Variable que contendra las centenas de la frecuencia*/
uint8 unidadmillar = FALSE;/*Variable que contendra las unidades de milar de la frecuencia*/
uint8 decenamillar = FALSE;/*Variable que contendra las unidades de millar de la frecuencia*/

void obtenvalor(uint32 valor) {
	if ((valor / DECENAMILLAR_VALOR) != FALSE) {
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

/*Función para ontener las unidades*/
uint8 getUnidad() {
	return unidad;
}

/*Función para ontener las decenas*/
uint8 getDecena() {
	return decena;
}

/*Función para ontener las centenas*/
uint8 getCentena() {
	return centena;
}

/*Función para ontener las unidades de millar*/
uint8 getUnidadMillar() {
	return unidadmillar;
}

/*Función para ontener las decenas de millar*/
uint8 getDecenaMillar() {
	return decenamillar;
}


