/**
	\file	UART_TERMINAL.c
	\brief
		Este módulo nos ayuda para imprimir en la terminal los diferentes
		menus y además, implementa la lógica de la transición de estados
	\author J. Hector Flores(ie703475@iteso.mx) & David Galvez(ie703984)
	\date	Apr 7, 2018
 */

/*Librerias*/
#include <stdio.h>
#include "UART.h"
#include <stdlib.h>
#include "UART_TERMINAL.h"
#include "GPS.h"
#include "EPROM.h"
#include "DataTypeDefinitions.h"



/*Función que imprime en la terminal el menu principal*/
void show_menu(){
	UART_putString(UART_0,"\033[0;37;47m");/*0 = Reset all atributes, 37 = White, 47 = white*/
	UART_putString(UART_0,"\033[2J");/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[0;30;47m");/** VT100 command for text in red and background in green*/
	UART_putString(UART_0,"\033[1;10H");/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0, "Bienvenido a CARFINDER\r");/*Write a sentence*/
	UART_putString(UART_0,"\033[1;10H");/** VT100 command for positioning the cursor in x and y position*/
	UART_putString(UART_0, "Presiona ENTER para mostrar el historial de las ubicaciones\r");/*Write a sentence*/
}
/********************************************************************************************************/
/********************************************************************************************************/
/******************Paquete de funciones para que comprenden el menu de leer memoria**********************/

/*Función que imprime en la terminal la primera parte del submenu de leer memoria*/
void showmemory(){
	UART_putString(UART_0,"\033[0;37;47m");/*0 = Reset all atributes, 37 = White, 47 = white*/
	UART_putString(UART_0,"\033[2J");/*VT100 command for clearing the screen*/
	UART_putString(UART_0,"\033[0;30;47m");/** VT100 command for text in red and background in green*/
	UART_putString(UART_0,"\033[5;10H");/** VT100 command for positioning the cursor in x and y position*/
	UART_WriteLink(UART_0, ReadString_EPROM(162, 53),162);
}



