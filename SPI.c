#include "SPI.h"
#include "GPIO.h"
#include "MK64F12.h"

#define ENABLE 1
#define DISABLE 0
#define CERO 0

static void SPI_setMaster(SPI_ChannelType channel, SPI_MasterType masterOrSlave) { //listo
	switch (channel) {

	case SPI_0:
		SPI0->MCR |= SPI_MCR_MSTR_MASK;
		break;

	case SPI_1:
		SPI1->MCR |= SPI_MCR_MSTR_MASK;
		break;

	case SPI_2:
		SPI2->MCR |= SPI_MCR_MSTR_MASK;
		break;
	default:

		break;
	}
}

static void SPI_fIFO(SPI_ChannelType channel,
		SPI_EnableFIFOType enableOrDisable) { //Listo

	switch (channel) {

	case SPI_0:

		if (ENABLE == enableOrDisable) {
			SPI0->MCR &= ~SPI_MCR_DIS_TXF_MASK;
			SPI0->MCR &= ~SPI_MCR_DIS_RXF_MASK;
		} else {
			SPI0->MCR |= SPI_MCR_DIS_TXF_MASK;
			SPI0->MCR |= SPI_MCR_DIS_RXF_MASK;
		}

		break;

	case SPI_1:
		if (ENABLE == enableOrDisable) {
			SPI1->MCR &= ~SPI_MCR_DIS_TXF_MASK;
			SPI1->MCR &= ~SPI_MCR_DIS_RXF_MASK;
		} else {
			SPI1->MCR |= SPI_MCR_DIS_TXF_MASK;
			SPI1->MCR |= SPI_MCR_DIS_RXF_MASK;
		}
		break;

	case SPI_2:
		if (ENABLE == enableOrDisable) {
			SPI2->MCR &= ~SPI_MCR_DIS_TXF_MASK;
			SPI2->MCR &= ~SPI_MCR_DIS_RXF_MASK;
		} else {
			SPI2->MCR |= SPI_MCR_DIS_TXF_MASK;
			SPI2->MCR |= SPI_MCR_DIS_RXF_MASK;
		}
		break;
	default:

		break;
	}
}

static void SPI_frameSize(SPI_ChannelType channel, uint32 frameSize) { //LISTO
	switch (channel) {

	case SPI_0:
		SPI0->CTAR[0] &= ~SPI_CTAR_FMSZ_MASK;
		SPI0->CTAR[0] |= frameSize;
		break;

	case SPI_1:
		SPI1->CTAR[0] &= ~SPI_CTAR_FMSZ_MASK;
		SPI1->CTAR[0] |= frameSize;
		break;

	case SPI_2:
		SPI2->CTAR[0] &= ~SPI_CTAR_FMSZ_MASK;
		SPI2->CTAR[0] |= frameSize;
		break;
	default:

		break;
	}
}

static void SPI_baudRate(SPI_ChannelType channel, uint32 baudRate) { //LISTO
	switch (channel) {

	case SPI_0:
		SPI0->CTAR[0] &= ~SPI_CTAR_BR_MASK;
		SPI0->CTAR[0] |= baudRate;
		break;

	case SPI_1:
		SPI1->CTAR[0] &= ~SPI_CTAR_BR_MASK;
		SPI1->CTAR[0] |= baudRate;
		break;

	case SPI_2:
		SPI2->CTAR[0] &= ~SPI_CTAR_BR_MASK;
		SPI2->CTAR[0] |= baudRate;
		break;
	default:

		break;
	}
}

void SPI_startTranference(SPI_ChannelType channel) {
	switch (channel) {

	case SPI_0:
		SPI0->MCR &= ~SPI_MCR_HALT_MASK;
		SPI0->MCR &= ~SPI_MCR_FRZ_MASK;
		break;

	case SPI_1:
		SPI1->MCR &= ~SPI_MCR_HALT_MASK;
		SPI1->MCR &= ~SPI_MCR_FRZ_MASK;
		break;

	case SPI_2:
		SPI2->MCR &= ~SPI_MCR_HALT_MASK;
		SPI2->MCR &= ~SPI_MCR_FRZ_MASK;
		break;
	default:

		break;
	}
}

void SPI_stopTranference(SPI_ChannelType channel) {
	switch (channel) {

	case SPI_0:
		SPI0->MCR |= SPI_MCR_HALT_MASK;
		break;

	case SPI_1:
		SPI1->MCR |= SPI_MCR_HALT_MASK;
		break;

	case SPI_2:
		SPI2->MCR |= SPI_MCR_HALT_MASK;
		break;
	default:

		break;
	}
}

void SPI_sendOneByte(SPI_ChannelType channel, uint8 Data) {
	switch (channel) {

	case SPI_0:
		SPI0->PUSHR = (Data);
		while (CERO == (SPI0->SR & SPI_SR_TCF_MASK))
			;
		SPI0->SR |= SPI_SR_TCF_MASK;
		break;

	case SPI_1:
		SPI1->PUSHR = (Data);
		while (CERO == (SPI1->SR & SPI_SR_TCF_MASK))
			;
		SPI1->SR |= SPI_SR_TCF_MASK;
		break;

	case SPI_2:
		SPI2->PUSHR = (Data);
		while (CERO == (SPI2->SR & SPI_SR_TCF_MASK))
			;
		SPI2->SR |= SPI_SR_TCF_MASK;
		break;
	default:

		break;
	}

}

static void SPI_mSBFirst(SPI_ChannelType channel, SPI_LSMorMSBType msb) {

	switch (channel) {

	case SPI_0:
		if (SPI_MSB == msb) {
			SPI0->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);
		} else {
			SPI0->CTAR[0] |= (SPI_CTAR_LSBFE_MASK);
		}
		break;

	case SPI_1:
		if (SPI_MSB == msb) {
			SPI1->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);
		} else {
			SPI1->CTAR[0] |= (SPI_CTAR_LSBFE_MASK);
		}
		break;

	case SPI_2:
		if (SPI_MSB == msb) {
			SPI2->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);
		} else {
			SPI2->CTAR[0] |= (SPI_CTAR_LSBFE_MASK);
		}
		break;
	default:
		if (SPI_MSB == msb) {
			SPI0->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);
		} else {
			SPI0->CTAR[0] |= (SPI_CTAR_LSBFE_MASK);
		}

	}
}

void SPI_init(const SPI_ConfigType* SPI_Config) {
	SPI_clk(SPI_Config->SPI_Channel);
	GPIO_clockGating(SPI_Config->GPIOForSPI.GPIO_portName);
	GPIO_pinControlRegister(SPI_Config->GPIOForSPI.GPIO_portName,
	SPI_Config->GPIOForSPI.SPI_clk,&(SPI_Config->pinConttrolRegisterPORTD));
	GPIO_pinControlRegister(SPI_Config->GPIOForSPI.GPIO_portName,
	SPI_Config->GPIOForSPI.SPI_Sout,&(SPI_Config->pinConttrolRegisterPORTD));
	SPI_setMaster(SPI_Config->SPI_Channel, SPI_Config->SPI_Master);
	SPI_fIFO(SPI_Config->SPI_Channel, SPI_Config->SPI_EnableFIFO);
	SPI_enable(SPI_Config->SPI_Channel);
	SPI_clockPolarity(SPI_Config->SPI_Channel, SPI_Config->SPI_Polarity);
	SPI_frameSize(SPI_Config->SPI_Channel, SPI_Config->frameSize);
	SPI_clockPhase(SPI_Config->SPI_Channel, SPI_Config->SPI_Phase);
	SPI_baudRate(SPI_Config->SPI_Channel, SPI_Config->baudrate);
	SPI_mSBFirst(SPI_Config->SPI_Channel, SPI_MSB);

}

static void SPI_clockPhase(SPI_ChannelType channel, SPI_PhaseType cpha) {

	switch (channel) {

	case SPI_0:
		if (SPI_LOW_PHASE == cpha) {
			SPI0->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);

		} else {
			SPI0->CTAR[0] |= SPI_CTAR_CPHA_MASK;
		}
		break;

	case SPI_1:
		if (SPI_LOW_PHASE == cpha) {
			SPI1->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);

		} else {
			SPI1->CTAR[0] |= SPI_CTAR_CPHA_MASK;
		}
		break;

	case SPI_2:
		if (SPI_LOW_PHASE == cpha) {
			SPI2->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);

		} else {
			SPI2->CTAR[0] |= SPI_CTAR_CPHA_MASK;
		}
		break;

	default:
		if (SPI_LOW_PHASE == cpha) {
			SPI0->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);

		} else {
			SPI0->CTAR[0] |= SPI_CTAR_CPHA_MASK;
		}
		break;

	}

}

static void SPI_enable(SPI_ChannelType channel) {
	switch (channel) {

	case SPI_0:
		SPI0->MCR &= ~(SPI_MCR_MDIS_MASK);
		break;

	case SPI_1:
		SPI1->MCR &= ~(SPI_MCR_MDIS_MASK);
		break;

	case SPI_2:
		SPI2->MCR &= ~(SPI_MCR_MDIS_MASK);
		break;
	default:
		SPI0->MCR &= ~(SPI_MCR_MDIS_MASK);

	}

}

static void SPI_clk(SPI_ChannelType channel) {

	switch (channel) {

	case SPI_0:
		SIM->SCGC6 |= SIM_SCGC6_SPI0_MASK;
		break;

	case SPI_1:
		SIM->SCGC6 |= SIM_SCGC6_SPI1_MASK;
		break;

	case SPI_2:
		SIM->SCGC3 |= SIM_SCGC3_SPI2_MASK;
		break;

	default:
		SIM->SCGC6 |= SIM_SCGC6_SPI0_MASK;

	}
}

static void SPI_clockPolarity(SPI_ChannelType channel, SPI_PolarityType cpol) {

	switch (channel) {

	case SPI_0:
		if (SPI_LOW_POLARITY == cpol) {
			SPI0->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);
		} else {
			SPI0->CTAR[0] |= (SPI_CTAR_CPOL_MASK);
		}

		break;

	case SPI_1:
		if (SPI_LOW_POLARITY == cpol) {
			SPI1->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);
		} else {
			SPI1->CTAR[0] |= (SPI_CTAR_CPOL_MASK);
		}
		break;

	case SPI_2:
		if (SPI_LOW_POLARITY == cpol) {
			SPI2->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);
		} else {
			SPI2->CTAR[0] |= (SPI_CTAR_CPOL_MASK);
		}
		break;

	default:

		if (SPI_LOW_POLARITY == cpol) {
			SPI0->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);
		} else {
			SPI0->CTAR[0] |= (SPI_CTAR_CPOL_MASK);
		}

		break;

	}

}
