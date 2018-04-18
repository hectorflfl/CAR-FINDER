/*
 * I2C.c
 *
 *  Created on: Apr 6, 2018
 *      Author: David Gálvez
 */

#include "MK64F12.h"
#include "DataTypeDefinitions.h"
#include "I2C.h"
#include "GPIO.h"
#define SHIFT7 7
#define FREQUENCY_DIVIDER 128

const GPIO_pinControlRegisterType PortB_ControlRegister = GPIO_MUX2;

void I2C_init(I2C_ChannelType channel) {

	/**Configures the pin control register of pin2 in PortB as I2C0 SCL*/
	//PORTB->PCR[2] = PORT_PCR_MUX(2);
	/**Configures the pin control register of pin2 in PortB as I2C0 SCL*/
	GPIO_pinControlRegister(GPIO_B, BIT2, &PortB_ControlRegister);
	/**Configures the pin control register of pin3 in PortB as I2C0 SDA*/
	GPIO_pinControlRegister(GPIO_B, BIT3, &PortB_ControlRegister);
	//PORTB->PCR[3] = PORT_PCR_MUX(2);

	switch (channel) {
	case I2C_0:
		SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;/*Is Activated the I2C0 Clock*/
		I2C0->F = FREQUENCY_DIVIDER;/*Is configured the frequency divider Register of I2C0*/
		I2C0->C1 = I2C_C1_IICEN_MASK;/*I2C0 is enable*/

		break;

	case I2C_1:
		SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;/*Is Activated the I2C1 Clock*/
		I2C1->F = FREQUENCY_DIVIDER;/*Is configured the frequency divider Register of I2C1*/
		I2C1->C1 = I2C_C1_IICEN_MASK;/*I2C1 is enable*/

		break;

	case I2C_2:
		SIM->SCGC1 |= SIM_SCGC1_I2C2_MASK;/*Is Activated the I2C2 Clock*/
		I2C1->F = FREQUENCY_DIVIDER;/*Is configured the frequency divider Register of I2C2*/
		I2C1->C1 = I2C_C1_IICEN_MASK;/*I2C2 is enable*/

		break;

	}

}

void I2C_enable(I2C_ChannelType channel) {

	switch (channel) {

	case I2C_0:
		I2C0->C1 |= I2C_C1_IICEN(TRUE); //I2C0 is enable
		break;

	case I2C_1:
		I2C1->C1 |= I2C_C1_IICEN(TRUE); //I2C1 is enable
		break;

	case I2C_2:
		I2C2->C1 |= I2C_C1_IICEN(TRUE); //I2C2 is enable
		break;

	default:
		I2C0->C1 |= I2C_C1_IICEN(TRUE); //I2C0 is enable
		break;

	}

}

void I2C_repeted_Start(I2C_ChannelType channel) {

	switch (channel) {

	case I2C_0:
		I2C0->C1 |= I2C_C1_RSTA(TRUE); // It generates a repeated start that is needed when master reads data.
		break;

	case I2C_1:
		I2C1->C1 |= I2C_C1_RSTA(TRUE); // It generates a repeated start that is needed when master reads data.
		break;

	case I2C_2:
		I2C2->C1 |= I2C_C1_RSTA(TRUE); // It generates a repeated start that is needed when master reads data.
		break;

	default:
		I2C0->C1 |= I2C_C1_IICEN(TRUE); //I2C0 is enable
		break;

	}

}

void I2C_MST_OrSLV_Mode(I2C_ChannelType channel, uint8 Master_Slave) {

	switch (channel) {

	case I2C_0:
		if (TRUE == Master_Slave) {
			I2C0->C1 |= I2C_C1_MST_MASK; //Master mode is selected

		} else {
			I2C0->C1 &= ~I2C_C1_MST_MASK; //Slave mode is selected
		}
		break;

	case I2C_1:
		if (TRUE == Master_Slave) {
			I2C1->C1 |= I2C_C1_MST_MASK; //Master mode is selected

		} else {
			I2C1->C1 &= ~I2C_C1_MST_MASK; //Slave mode is selected
		}
		break;

	case I2C_2:
		if (TRUE == Master_Slave) {
			I2C2->C1 |= I2C_C1_MST_MASK; //Master mode is selected

		} else {
			I2C2->C1 &= ~I2C_C1_MST_MASK; //Slave mode is selected
		}
		break;

	default:
		if (TRUE == Master_Slave) {
			I2C0->C1 |= I2C_C1_MST_MASK; //Master mode is selected

		} else {
			I2C0->C1 &= ~I2C_C1_MST_MASK; //Slave mode is selected
		}
		break;

	}

}

uint16 I2C_get_ACK(I2C_ChannelType channel) {

	switch (channel) {

	case I2C_0:
		return I2C0->S & I2C_S_RXAK_MASK; // returns if receive Acknowledge or not
		break;

	case I2C_1:
		return I2C1->S & I2C_S_RXAK_MASK; // returns if receive Acknowledge or not
		break;

	case I2C_2:
		return I2C2->S & I2C_S_RXAK_MASK; // returns if receive Acknowledge or not
		break;

	default:
		return I2C0->S & I2C_S_RXAK_MASK; // returns if receive Acknowledge or not
		break;

	}

}
void I2C_wait(I2C_ChannelType channel) {

	switch (channel) {

	case I2C_0:
		while (FALSE == ((I2C0->S & I2C_S_TCF_MASK))); //Wait until the process finishes
		break;

	case I2C_1:
		while (FALSE == ((I2C1->S & I2C_S_TCF_MASK))); //Wait until the process finishes
		break;

	case I2C_2:
		while (FALSE == ((I2C2->S & I2C_S_TCF_MASK))); //Wait until the process finishes
		break;

	default:
		while (FALSE == ((I2C0->S & I2C_S_TCF_MASK))); //Wait until the process finishes
		break;

	}

}

void I2C_TX_RX_Mode(I2C_ChannelType channel, uint8 Tx_Rx) {

	switch (channel) {

	case I2C_0:
		if (TRUE == Tx_Rx) {
			I2C0->C1 |= I2C_C1_TX_MASK; //Tx mode is selected

		} else {
			I2C0->C1 &= ~I2C_C1_TX_MASK; //Rx mode is selected
		}
		break;

	case I2C_1:
		if (TRUE == Tx_Rx) {
			I2C1->C1 |= I2C_C1_TX_MASK; //Tx mode is selected

		} else {
			I2C1->C1 &= ~I2C_C1_TX_MASK; //Rx mode is selected
		}
		break;

	case I2C_2:
		if (TRUE == Tx_Rx) {
			I2C2->C1 |= I2C_C1_TX_MASK; //Tx mode is selected

		} else {
			I2C2->C1 &= ~I2C_C1_TX_MASK; //Rx mode is selected
		}
		break;

	default:
		if (TRUE == Tx_Rx) {
			I2C0->C1 |= I2C_C1_TX_MASK; //Tx mode is selected

		} else {
			I2C0->C1 &= ~I2C_C1_TX_MASK; //Rx mode is selected
		}
		break;

	}

}

void I2C_NACK(I2C_ChannelType channel) {

	switch (channel) {

	case I2C_0:
		I2C0->C1 |= I2C_C1_TXAK(TRUE); //No acknowledge signal is sent to the bus
		break;

	case I2C_1:
		I2C1->C1 |= I2C_C1_TXAK(TRUE); //No acknowledge signal is sent to the bus
		break;

	case I2C_2:
		I2C2->C1 |= I2C_C1_TXAK(TRUE); //No acknowledge signal is sent to the bus
		break;

	default:
		I2C0->C1 |= I2C_C1_TXAK(TRUE); //No acknowledge signal is sent to the bus
		break;

	}

}

void I2C_start(I2C_ChannelType channel) {
	// 0 Slave Mode  1 Master Mode

	switch (channel) {

	case I2C_0:
		I2C_MST_OrSLV_Mode(I2C_0, TRUE); //Master mode is selected
		I2C_TX_RX_Mode(I2C_0, TRUE); //Tx mode is selected
		break;

	case I2C_1:
		I2C_MST_OrSLV_Mode(I2C_1, TRUE); //Master mode is selected
		I2C_TX_RX_Mode(I2C_1, TRUE); //Tx mode is selected
		break;

	case I2C_2:
		I2C_MST_OrSLV_Mode(I2C_2, TRUE); //Master mode is selected
		I2C_TX_RX_Mode(I2C_2, TRUE); //Tx mode is selected
		break;

	default:
		I2C_MST_OrSLV_Mode(I2C_0, TRUE); //Master mode is selected
		I2C_TX_RX_Mode(I2C_0, TRUE); //Tx mode is selected
		break;

	}

}

void I2C_stop(I2C_ChannelType channel) {
	// 0 Slave Mode  1 Master Mode

	switch (channel) {

	case I2C_0:
		I2C_MST_OrSLV_Mode(I2C_0, FALSE); //Slave mode is selected
		I2C_TX_RX_Mode(I2C_0, FALSE); //Rx mode is selected
		break;

	case I2C_1:
		I2C_MST_OrSLV_Mode(I2C_1, FALSE); //Slave mode is selected
		I2C_TX_RX_Mode(I2C_1, FALSE); //Rx mode is selected
		break;

	case I2C_2:
		I2C_MST_OrSLV_Mode(I2C_2, FALSE); //Slave mode is selected
		I2C_TX_RX_Mode(I2C_2, FALSE); //Rx mode is selected
		break;

	default:
		I2C_MST_OrSLV_Mode(I2C_0, FALSE); //Slave mode is selected
		I2C_TX_RX_Mode(I2C_0, FALSE); //Rx mode is selected
		break;

	}

}

uint8 I2C_busy(I2C_ChannelType channel) {
	// 0 Bus is idle ;  1 Bus is busy

	switch (channel) {

	case I2C_0:
		return (I2C0->S & I2C_S_BUSY_MASK) >> I2C_S_BUSY_SHIFT; //Returns status of the  SDA
		break;

	case I2C_1:
		return (I2C1->S & I2C_S_BUSY_MASK) >> I2C_S_BUSY_SHIFT; //Returns status of the  SDA
		break;

	case I2C_2:
		return (I2C2->S & I2C_S_BUSY_MASK) >> I2C_S_BUSY_SHIFT; //Returns status of the  SDA
		break;

	default:
		return (I2C0->S & I2C_S_BUSY_MASK) >> I2C_S_BUSY_SHIFT; //Returns status of the  SDA
		break;

	}

}

void I2C_write_Byte(I2C_ChannelType channel, uint8 data) {
	switch (channel) {

	case I2C_0:
		I2C0->D = data; //Write data into the register D
		break;

	case I2C_1:
		I2C1->D = data; //Write data into the register D
		break;

	case I2C_2:
		I2C1->D = data; //Write data into the register D
		break;

	default:
		I2C0->D = data; //Write data into the register D
		break;

	}

}

uint8 I2C_read_Byte(I2C_ChannelType channel) {

	switch (channel) {

	case I2C_0:
		return I2C0->D; //Read the data
		break;

	case I2C_1:
		return I2C1->D; //Read the data
		break;

	case I2C_2:
		return I2C2->D; //Read the data
		break;

	default:
		return I2C0->D; //Read the data
		break;

	}

}
