/*
 * UART.c
 *
 *  Created on: Apr 1, 2018
 *      Author: Hector Flores & David
 */

#include "UART.h"
#include "PasswordDetector.h"
#include "MK64F12.h"
#include "GlobalFunctions.h"



#define UNO 0x01
#define GET8 0x08

/**This is mail box to received the information from the serial port*/
UART_MailBoxType UART0_MailBox;
UART_MailBoxType UART1_MailBox;

/*Función que nos ayuda a limpiar la bandera y asignar a mailbox*/
void UART0_RX_TX_IRQHandler(void)
{
	while(FALSE == (UNO & (UART0->S1 >> UART_S1_RDRF_SHIFT)));
	UART0_MailBox.mailBox = UART0->D;/*Reads return the contents of the read-only receive data register*/
	UART0_MailBox.flag = TRUE;		/*Assign cero to the flag*/

}

void UART1_RX_TX_IRQHandler(void)
{
	while(FALSE == (UNO & (UART1->S1 >> UART_S1_RDRF_SHIFT)));
	UART1_MailBox.mailBox = UART1->D;/*Reads return the contents of the read-only receive data register*/
	UART1_MailBox.flag = TRUE;		/*Assign cero to the flag*/
	passwordVerification(UART1_MailBox.mailBox);

}

/*Función que inicializa la UART*/
void UART_init(UART_ChannelType uartChannel, uint32 systemClk, UART_BaudRateType baudRate)
{


	uint16 UART_BuadRate = systemClk/(16*baudRate); /*Calculamos el baud rate*/

	switch(uartChannel)
	{
		case UART_0:

			/**Configures the pin control register of pin16 in PortB as UART RX*/

			SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;/*Activamos el reloj de la UART0*/
			PORTB->PCR[16] = PORT_PCR_MUX(3);
					/**Configures the pin control register of pin16 in PortB as UART TX*/
			PORTB->PCR[17] = PORT_PCR_MUX(3);
			UART0->C2  &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);/*Deshabilita el transmisor y el receptor de la UART en el registro UART0_C2 */
			UART0->BDH |= UART_BDH_SBR_MASK & (UART_BuadRate >> GET8);/*Copiar los bits uartBaudRate[12:8] a los bits SRB del registro UARTx_BDH */
			UART0->BDL &= ~(UART_BDL_SBR_MASK);
			UART0->BDL |= (uint8)UART_BuadRate;/*Copiar los bits uartBaudRate[7:0] al registro UARTx_BDL */
			UART0->C2  |= (UART_C2_TE_MASK | UART_C2_RE_MASK);/*Habilitar el transmisor y el receptor de la UART en el registro UARTx_C2 */
		break;

		case UART_1:
			SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
			SIM->SCGC4 |= SIM_SCGC4_UART1_MASK;
		/**Configures the pin control register of pin3 in PortC as UART RX*/
			PORTC->PCR[3] = PORT_PCR_MUX(3);
			/**Configures the pin control register of pin4 in PortC as UART TX*/
			PORTC->PCR[4] = PORT_PCR_MUX(3);
			UART1->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);/*Deshabilita el transmisor y el receptor de la UART en el registro UART1_C2 */
			UART1->BDH |= UART_BDH_SBR_MASK & (UART_BuadRate >> GET8);/*Copiar los bits uartBaudRate[12:8] a los bits SRB del registro UARTx_BDH */
			UART1->BDL &= ~(UART_BDL_SBR_MASK);
			UART1->BDL |= (uint8)UART_BuadRate;/*Copiar los bits uartBaudRate[7:0] al registro UARTx_BDL */
			UART1->C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK);/*Habilitar el transmisor y el receptor de la UART en el registro UARTx_C2 */
		break;

		case UART_2:
			SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;/*Activamos el reloj de la UART2*/
			UART2->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);/*Deshabilita el transmisor y el receptor de la UART en el registro UART2_C2 */
			UART2->BDH |= UART_BDH_SBR_MASK & (UART_BuadRate >> GET8);/*Copiar los bits uartBaudRate[12:8] a los bits SRB del registro UARTx_BDH */
			UART2->BDL &= ~(UART_BDL_SBR_MASK);
			UART2->BDL |= (uint8)UART_BuadRate;/*Copiar los bits uartBaudRate[7:0] al registro UARTx_BDL */
			UART2->C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK);/*Habilitar el transmisor y el receptor de la UART en el registro UARTx_C2 */
		break;

		case UART_3:
			SIM->SCGC4 |= SIM_SCGC4_UART3_MASK;/*Activamos el reloj de la UART3*/
			UART3->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);/*Deshabilita el transmisor y el receptor de la UART en el registro UART3_C2 */
			UART3->BDH |= UART_BDH_SBR_MASK & (UART_BuadRate >> GET8);/*Copiar los bits uartBaudRate[12:8] a los bits SRB del registro UARTx_BDH */
			UART3->BDL &= ~(UART_BDL_SBR_MASK);
			UART3->BDL |= (uint8)UART_BuadRate;/*Copiar los bits uartBaudRate[7:0] al registro UARTx_BDL */
			UART3->C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK);/*Habilitar el transmisor y el receptor de la UART en el registro UARTx_C2 */
		break;

		case UART_4:
			SIM->SCGC1 |= SIM_SCGC1_UART4_MASK;/*Activamos el reloj de la UART4*/
			UART4->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);/*Deshabilita el transmisor y el receptor de la UART en el registro UART4_C2 */
			UART4->BDH |= UART_BDH_SBR_MASK & (UART_BuadRate >> GET8);/*Copiar los bits uartBaudRate[12:8] a los bits SRB del registro UARTx_BDH */
			UART4->BDL &= ~(UART_BDL_SBR_MASK);
			UART4->BDL |= (uint8)UART_BuadRate;/*Copiar los bits uartBaudRate[7:0] al registro UARTx_BDL */
			UART4->C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK);/*Habilitar el transmisor y el receptor de la UART en el registro UARTx_C2 */
		break;

		case UART_5:
			SIM->SCGC1 |= SIM_SCGC1_UART5_MASK;/*Activamos el reloj de la UART5*/
			UART5->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);/*Deshabilita el transmisor y el receptor de la UART en el registro UART5_C2 */
			UART5->BDH |= UART_BDH_SBR_MASK & (UART_BuadRate >> GET8);/*Copiar los bits uartBaudRate[12:8] a los bits SRB del registro UARTx_BDH */
			UART5->BDL &= ~(UART_BDL_SBR_MASK);
			UART5->BDL |= (uint8)UART_BuadRate;/*Copiar los bits uartBaudRate[7:0] al registro UARTx_BDL */
			UART5->C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK);/*Habilitar el transmisor y el receptor de la UART en el registro UARTx_C2 */
		break;
	}
}

/*Funcion para habilitar las interrupciones*/
void UART0_interruptEnable(UART_ChannelType uartChannel)
{
	switch(uartChannel)
	{
		case UART_0:
			UART0->C2 |= UART_C2_RIE_MASK;/*RDRF interrupt or DMA transfer requests enabled.*/
		break;

		case UART_1:
			UART1->C2 |= UART_C2_RIE_MASK;/*RDRF interrupt or DMA transfer requests enabled.*/
		break;

		case UART_2:
			UART2->C2 |= UART_C2_RIE_MASK;/*RDRF interrupt or DMA transfer requests enabled.*/
		break;

		case UART_3:
			UART3->C2 |= UART_C2_RIE_MASK;/*RDRF interrupt or DMA transfer requests enabled.*/
		break;

		case UART_4:
			UART4->C2 |= UART_C2_RIE_MASK;/*RDRF interrupt or DMA transfer requests enabled.*/
		break;

		case UART_5:
			UART5->C2 |= UART_C2_RIE_MASK;/*RDRF interrupt or DMA transfer requests enabled.*/
		break;
	}
}

/*Funcion para pasar un caracter*/
void UART_putChar(UART_ChannelType uartChannel, uint8 character)
{
	switch(uartChannel)
	{
		case UART_0:
			while(!(UART0->S1 & UART_S1_TC_MASK));
			UART0->D = character;
		break;

		case UART_1:
			while(!(UART1->S1 & UART_S1_TC_MASK));
			UART1->D = character;
		break;

		case UART_2:
			while(!(UART2->S1 & UART_S1_TC_MASK));
			UART2->D = character;
		break;

		case UART_3:
			while(!(UART3->S1 & UART_S1_TC_MASK));
			UART3->D = character;
		break;

		case UART_4:
			while(!(UART4->S1 & UART_S1_TC_MASK));
			UART4->D = character;
			break;

		case UART_5:
			while(!(UART5->S1 & UART_S1_TC_MASK));
			UART5->D = character;
			break;
	}
}

void UART_putString(UART_ChannelType uartChannel, sint8* string)
{
	/**Transmit each char until the end symbol is found*/
	while (*string)
	{
		//delay(800);
		/**Transmit one char*/
		UART_putChar(uartChannel, *string++);
	}
}

void UART1_disable(){
	UART1->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);
}

void UART1_enable(){
	UART1->C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK);
}
