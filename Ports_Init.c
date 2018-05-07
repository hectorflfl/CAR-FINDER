/**
	\file
		Ports_Init.c
	\brief
		This is the source file that help us to initialize the
		ports and the interrupts
	\author Hector Flores, ie703475@iteso.mx
	\date	Mar 16, 2018
 */

/*Incluimos los diferentes modulos a utilizar*/
#include <stdio.h>
#include "MK64F12.h"
#include "DataTypeDefinitions.h"
#include "GPIO.h"
#include "PIT.h"
#include "NVIC.h"
#include "UART.h"
/*Función que inicializa los puertos y el clock gating de los mismos*/
void pins_initialize() {
	/*Activamos GPIO clock gating*/
	GPIO_clockGating(GPIO_A);
	GPIO_clockGating(GPIO_B);
	GPIO_clockGating(GPIO_C);
	GPIO_clockGating(GPIO_D);
	GPIO_clockGating(GPIO_E);
	//Activamos el reloj del PIT
	PIT_clockGating();

	/*Declaramos variables con sus respectivas configuraciones para los puertos*/
	GPIO_pinControlRegisterType pinControlRegisterPORTB = GPIO_MUX1;
	GPIO_pinControlRegisterType pinControlRegisterP_pin26 = GPIO_MUX1 |INTR_FALLING_EDGE;
	GPIO_pinControlRegisterType pin7_ControlRegister = GPIO_MUX1;
	GPIO_pinControlRegisterType pinControlRegisterPORTC = GPIO_MUX1 ;
	/*PushButton lock */
	GPIO_pinControlRegister(GPIO_B, BIT18, &pin7_ControlRegister);
	GPIO_dataDirectionPIN(GPIO_B, GPIO_OUTPUT, BIT18);
	/*PushButton GPS*/
	GPIO_pinControlRegister(GPIO_B, BIT19, &pin7_ControlRegister);
	GPIO_dataDirectionPIN(GPIO_B, GPIO_OUTPUT, BIT19);

	GPIO_pinControlRegister(GPIO_B, BIT23, &pinControlRegisterP_pin26);
	GPIO_dataDirectionPIN(GPIO_B, GPIO_INPUT, BIT23);


	/*Pin de alarma-BUZZ*/
	GPIO_pinControlRegister(GPIO_C, BIT7, &pin7_ControlRegister);
	GPIO_dataDirectionPIN(GPIO_C, GPIO_OUTPUT, BIT7);
	//PIN PIR
	GPIO_pinControlRegister(GPIO_C, BIT0, &pinControlRegisterPORTC);
	GPIO_dataDirectionPIN(GPIO_C, GPIO_INPUT, BIT0);
}

/*Función que nos permite habilitar las interrupciones del PIT y del puerto B*/
void pins_interrupts() {

	//Asignamos las prioeridades de las interrupciones
	//Interrupciones por desbordamiento
	NVIC_enableInterruptAndPriotity(PIT_CH0_IRQ, PRIORITY_5);
	NVIC_enableInterruptAndPriotity(PIT_CH1_IRQ, PRIORITY_7);
	NVIC_enableInterruptAndPriotity(PIT_CH3_IRQ, PRIORITY_8);
	NVIC_enableInterruptAndPriotity(PORTB_IRQ, PRIORITY_6);
	NVIC_enableInterruptAndPriotity(UART4_IRQ, PRIORITY_4);
	NVIC_enableInterruptAndPriotity(UART0_IRQ, PRIORITY_15);
	NVIC_enableInterruptAndPriotity(UART1_IRQ, PRIORITY_1);
	NVIC_enableInterruptAndPriotity(UART3_IRQ, PRIORITY_2);

	/*Habilitamos interrupciones*/
	EnableInterrupts;
}
