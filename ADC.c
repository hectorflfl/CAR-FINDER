/*
 * ADC.c
 *
 *  Created on: Mar 20, 2018
 *      Author: david
 */

#include "MK64F12.h"
#include "DataTypeDefinitions.h"
#include "ADC.h"
#include "GPIO.h"
#define RESOLUTION (0x3)
#define CHANNEL14 14
#define ENABLE_AVGE 0xF
#define CONF_MODE 3
#define A 0



void ADC_ClockGating(ADC_Enum AnalogtoDigital) {


	switch (AnalogtoDigital) {
	case ADC_0:
		SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;/** Habilitación el clock gating del ADC0*/
		break;
	case ADC_1:
		SIM->SCGC3 |= SIM_SCGC3_ADC1_MASK;/** Habilitación el clock gating del ADC1*/
		break;
	default:
		SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;/** Habilitación el clock gating del ADC0*/

	}
}

//ADC_configurationMode=0xc Para que el mode se ponga en 11 y se active una resolusion de 16 bits
void ADC_MODE(ADC_Enum AnalogtoDigital, uint8 ADC_configurationMode) {

	switch (AnalogtoDigital) {
	case ADC_0:
		ADC0->CFG1 |= ADC_CFG1_MODE(CONF_MODE);/** Ingresa al registro CFG1 del ADC0 el valor de tres que corresponde a 16 bits de resolución*/
		break;
	case ADC_1:
		ADC1->CFG1 |= ADC_CFG1_MODE(CONF_MODE);/** Ingresa al registro CFG1 del ADC1 el valor de tres que corresponde a 16 bits de resolución*/
		break;
	default:
		ADC0->CFG1 = ADC_CFG1_MODE(CONF_MODE);/** Ingresa al registro CFG1 del ADC0 el valor de tres que corresponde a 16 bits de resolución*/
	}

}

void ADC_Disable(ADC_Enum AnalogtoDigital) {
	switch (AnalogtoDigital) {
	case ADC_0:
		ADC0->SC1[A] |= ADC_SC1_ADCH(MODULE_DISABLED);/** Deshabilita el ADC0*/
		break;
	case ADC_1:
		ADC1->SC1[A] |= ADC_SC1_ADCH(MODULE_DISABLED);/** Deshabilita el ADC1*/
		break;
	default:
		ADC0->SC1[A] |= ADC_SC1_ADCH(MODULE_DISABLED);/** Deshabilita el ADC0*/
	}

}

uint16 ADC_read16b(void) {
	//Write to SC1A to start conversion
	setChannel();
	while (ADC0->SC2 & ADC_SC2_ADACT_MASK);  			/** Se mantiene mientras la conversión esta en proceso*/
	enable_AVGE();										/** Deshabilta el promediador por HW*/
	while (!(ADC0->SC1[A] & ADC_SC1_COCO_MASK));
	disable_AVGE();										/** Habilita el promediador por HW*/
	return ADC0->R[A];									/** Retorna el valor del ADC0*/
}

void setChannel() {
	ADC0->SC1[A] = CHANNEL14 & ADC_SC1_ADCH_MASK;		/** Se selecciona el canal 14 - PTC0*/
}

void enable_AVGE() {
	ADC0->SC3 |= ENABLE_AVGE;							/** Se habilita el promediador por HW*/
}

void disable_AVGE() {
	ADC0->SC3 = FALSE;									/** Se deshabilita el promediador por HW*/
}

void ADC_init() {

	ADC_ClockGating(ADC_0);/*Habilita el clock del ADC0*/
	ADC_MODE(ADC_0, RESOLUTION);/*16bits ADC*/
	ADC_Disable(ADC_0);/*Disable EL ADC0 */

}
