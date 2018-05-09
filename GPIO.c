/**
	\file
	\brief
		This is the source file for the GPIO device driver for Kinetis K64.
		It contains all the implementation for configuration functions and runtime functions.
		i.e., this is the application programming interface (API) for the GPIO peripheral.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	7/09/2014
	\todo
	    Interrupts are not implemented in this API implementation.
 */
#include "MK64F12.h"
#include "GPIO.h"
#include "NVIC.h"
#include "DataTypeDefinitions.h"
#include "PIT.h"
#define corrimiento_bit(pin) 1<<pin
#define corrimiento_state(Status,pin) Status<<pin
#define UNO 0x1
#define StateMotor 0x2
#define StateSignal 0x3
#define EJECUTA 0x4
#define BotonA 0xA
#define BotonB 0xB
#define SYSCLK 21000000
#define DELAY15S 30
static uint8 PortB_flag=0;

GPIO_pinControlRegisterType pinControlRegisterPORTCOFF = 0x0;

//Interrupción del puerto A (MOTOR)
void PORTA_IRQHandler(void){
		GPIO_clearIRQStatus(GPIO_A);		//Clear interrupt status
		GPIO_clearInterrupt(GPIO_A);		//Clear interrupt

	}
//Interrupción de los push buttons
void PORTB_IRQHandler(void){
		GPIO_clearIRQStatus(GPIO_B);		//Clear interrupt status
		GPIO_clearInterrupt(GPIO_B);		//Clear interrupt
		PIT_clear(PIT_3);					//Clear PIT
		PIT_delay(PIT_3, SYSCLK, DELAY15S);//Activate PIT to set the alarnm
		set_PortB_FlagIRQ();				//Set the flag of the portB

	}
//Interrupción del puerto C (SEÑALES)
void PORTC_IRQHandler(void){
		GPIO_clearIRQStatus(GPIO_C);		//Clear interrupt status
		GPIO_clearInterrupt(GPIO_C);		//Clear interrupt

	}


uint8 PortB_FlagIRQ(){
	return PortB_flag;
}

void set_PortB_FlagIRQ(){
	PortB_flag=TRUE;
}

uint8 get_PortB_FlagIRQ(){
	return PortB_flag;
}

void clear_PortB_FlagIRQ(){
	PortB_flag=FALSE;
}


GPIO_interruptFlags_t GPIO_intrStatusFlag;

uint8 GPIO_getIRQStatus(GPIO_portNameType gpio)
{
	switch (gpio) {
		case GPIO_A:
			return(GPIO_intrStatusFlag.flagPortA);
			break;
		case GPIO_B:
			return(GPIO_intrStatusFlag.flagPortB);
			break;
		case GPIO_C:
			return(GPIO_intrStatusFlag.flagPortC);
			break;
		case GPIO_D:
			return(GPIO_intrStatusFlag.flagPortD);
			break;
		case GPIO_E:
			return(GPIO_intrStatusFlag.flagPortE);
			break;
		default:
			return(ERROR);
			break;
	}

}




uint8 GPIO_clearIRQStatus(GPIO_portNameType gpio)
{
	switch (gpio) {
		case GPIO_A:
			GPIO_intrStatusFlag.flagPortA = FALSE;
			break;
		case GPIO_B:
			GPIO_intrStatusFlag.flagPortB = FALSE;
			break;
		case GPIO_C:
			GPIO_intrStatusFlag.flagPortC = FALSE;
			break;
		case GPIO_D:
			GPIO_intrStatusFlag.flagPortD = FALSE;
			break;
		case GPIO_E:
			GPIO_intrStatusFlag.flagPortE = FALSE;
			break;
		default:
			return(ERROR);
			break;
	}

	return(TRUE);

}


void GPIO_clearInterrupt(GPIO_portNameType portName)
{
	switch(portName)/** Selecting the GPIO for clock enabling*/
	{
		case GPIO_A: /** GPIO A is selected*/
			PORTA->ISFR=0xFFFFFFFF;
			break;
		case GPIO_B: /** GPIO B is selected*/
			PORTB->ISFR=0xFFFFFFFF;
			break;
		case GPIO_C: /** GPIO C is selected*/
			PORTC->ISFR = 0xFFFFFFFF;
			break;
		case GPIO_D: /** GPIO D is selected*/
			PORTD->ISFR=0xFFFFFFFF;
			break;
		default: /** GPIO E is selected*/
			PORTE->ISFR=0xFFFFFFFF;
			break;

	}// end switch
}
uint8 GPIO_clockGating(GPIO_portNameType portName)
{
	switch(portName)/** Selecting the GPIO for clock enabling*/
	{
		case GPIO_A: /** GPIO A is selected*/
			SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTA; /** Bit 9 of SIM_SCGC5 is  set*/
			break;
		case GPIO_B: /** GPIO B is selected*/
			SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTB; /** Bit 10 of SIM_SCGC5 is set*/
			break;
		case GPIO_C: /** GPIO C is selected*/
			SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTC; /** Bit 11 of SIM_SCGC5 is set*/
			break;
		case GPIO_D: /** GPIO D is selected*/
			SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTD; /** Bit 12 of SIM_SCGC5 is set*/
			break;
		case GPIO_E: /** GPIO E is selected*/
			SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTE; /** Bit 13 of SIM_SCGC5 is set*/
			break;
		default: /**If doesn't exist the option*/
			return(FALSE);
	}// end switch
	/**Successful configuration*/
	return(TRUE);
}// end function

uint8 GPIO_pinControlRegister(GPIO_portNameType portName,uint8 pin,const GPIO_pinControlRegisterType*  pinControlRegister)
{
	switch(portName)
		{
		case GPIO_A:/** GPIO A is selected*/
			PORTA->PCR[pin] = *pinControlRegister;
			break;
		case GPIO_B:/** GPIO B is selected*/
			PORTB->PCR[pin] = *pinControlRegister;
			break;
		case GPIO_C:/** GPIO C is selected*/
			PORTC->PCR[pin] = *pinControlRegister;
			break;
		case GPIO_D:/** GPIO D is selected*/
			PORTD->PCR[pin] = *pinControlRegister;
			break;
		case GPIO_E: /** GPIO E is selected*/
			PORTE->PCR[pin]= *pinControlRegister;
		default:/**If doesn't exist the option*/
			return(FALSE);
		break;
		}
	/**Successful configuration*/
	return(TRUE);
}

void GPIO_writePORT(GPIO_portNameType portName, uint32 Data )
{
	switch(portName)
		{
		case GPIO_A:/** GPIO A is selected*/
			GPIOA->PDOR=Data;
			break;
		case GPIO_B:/** GPIO B is selected*/
			GPIOB->PDOR=Data;
			break;
		case GPIO_C:/** GPIO C is selected*/
			GPIOC->PDOR=Data;
			break;
		case GPIO_D:/** GPIO D is selected*/
			GPIOD->PDOR=Data;
			break;
		case GPIO_E: /** GPIO E is selected*/
			GPIOE->PDOR=Data;
		default:/**If doesn't exist the option*/
			break;
		}
}

uint32 GPIO_readPORT(GPIO_portNameType portName)
{
	switch(portName)
		{
		case GPIO_A:/** GPIO A is selected*/
			return GPIOA->PDIR;
			break;
		case GPIO_B:/** GPIO B is selected*/
			return GPIOB->PDIR;
			break;
		case GPIO_C:/** GPIO C is selected*/
			return GPIOC->PDIR;
			break;
		case GPIO_D:/** GPIO D is selected*/
			return GPIOD->PDIR;
			break;
		case GPIO_E: /** GPIO E is selected*/
			return GPIOE->PDIR;
			break;
		default:/**If doesn't exist the option*/
			return FALSE;
			break;

		}

}

uint8 GPIO_readPIN(GPIO_portNameType portName, uint8 pin)
{
	switch(portName)
				{
				case GPIO_A:/** GPIO A is selected*/
					return ((corrimiento_bit(pin))&(GPIOA->PDIR))>>pin;
					break;
				case GPIO_B:/** GPIO B is selected*/
					return ((corrimiento_bit(pin))&(GPIOB->PDIR))>>pin;
					break;
				case GPIO_C:/** GPIO C is selected*/
					return ((corrimiento_bit(pin))&(GPIOC->PDIR))>>pin;
					break;
				case GPIO_D:/** GPIO D is selected*/
					return ((corrimiento_bit(pin))&(GPIOD->PDIR))>>pin;
					break;
				case GPIO_E: /** GPIO E is selected*/
					return ((corrimiento_bit(pin))&(GPIOE->PDIR))>>pin;
					break;
				default:/**If doesn't exist the option*/
					return FALSE;
					break;

				}

}

void GPIO_setPIN(GPIO_portNameType portName, uint8 pin)
{
	switch(portName)
		{
		case GPIO_A:/** GPIO A is selected*/
			GPIOA->PSOR |= corrimiento_bit(pin);
			break;
		case GPIO_B:/** GPIO B is selected*/
			GPIOB->PSOR |= corrimiento_bit(pin);
			break;
		case GPIO_C:/** GPIO C is selected*/
			GPIOC->PSOR |= corrimiento_bit(pin);
			break;
		case GPIO_D:/** GPIO D is selected*/
			GPIOD->PSOR |= corrimiento_bit(pin);
			break;
		case GPIO_E: /** GPIO E is selected*/
			GPIOE->PSOR |= corrimiento_bit(pin);
			break;
		default:/**If doesn't exist the option*/
			break;

		}
}

void GPIO_putPIN(GPIO_portNameType portName, uint32 pinAddress, uint8 value)
{
	switch(portName)
		{
		case GPIO_A:/** GPIO A is selected*/
			if(FALSE==value){
				GPIOA->PDOR &= ~(pinAddress);
			}
			else{
				GPIOA->PDOR |= pinAddress;
			}

			break;
		case GPIO_B:/** GPIO B is selected*/
			if(FALSE==value){
				GPIOB->PDOR &= ~(pinAddress);
			}
			else{
				GPIOB->PDOR |= pinAddress;
			}
			break;
		case GPIO_C:/** GPIO C is selected*/
			if(FALSE==value){
				GPIOC->PDOR &= ~(pinAddress);
			}
			else{
				GPIOC->PDOR |= pinAddress;
			}
			break;
		case GPIO_D:/** GPIO D is selected*/
			if(FALSE==value){
				GPIOD->PDOR &= ~(pinAddress);
			}
			else{
				GPIOD->PDOR |= pinAddress;
			}
			break;
		case GPIO_E: /** GPIO E is selected*/
			if(FALSE==value){
				GPIOD->PDOR &= ~(pinAddress);
			}
			else{
				GPIOD->PDOR |= pinAddress;
			}
			break;
		default:/**If doesn't exist the option*/
			break;

		}
}
void GPIO_clearPIN(GPIO_portNameType portName, uint8 pin)
{
	switch(portName)
			{
			case GPIO_A:/** GPIO A is selected*/
				GPIOA->PCOR |= corrimiento_bit(pin);
				break;
			case GPIO_B:/** GPIO B is selected*/
				GPIOB->PCOR |= corrimiento_bit(pin);
				break;
			case GPIO_C:/** GPIO C is selected*/
				GPIOC->PCOR |= corrimiento_bit(pin);
				break;
			case GPIO_D:/** GPIO D is selected*/
				GPIOD->PCOR |= corrimiento_bit(pin);
				break;
			case GPIO_E: /** GPIO E is selected*/
				GPIOE->PCOR |= corrimiento_bit(pin);
				break;
			default:/**If doesn't exist the option*/
				break;

			}
}

void GPIO_tooglePIN(GPIO_portNameType portName, uint8 pin){
	switch(portName)
			{
			case GPIO_A:/** GPIO A is selected*/
				GPIOA->PTOR |= corrimiento_bit(pin);
				break;
			case GPIO_B:/** GPIO B is selected*/
				GPIOB->PTOR |= corrimiento_bit(pin);
				break;
			case GPIO_C:/** GPIO C is selected*/
				GPIOC->PTOR |= corrimiento_bit(pin);
				break;
			case GPIO_D:/** GPIO D is selected*/
				GPIOD->PTOR |= corrimiento_bit(pin);
				break;
			case GPIO_E: /** GPIO E is selected*/
				GPIOE->PTOR |= corrimiento_bit(pin);
				break;
			default:/**If doesn't exist the option*/
				break;

			}
}

void GPIO_dataDirectionPORT(GPIO_portNameType portName ,uint32 direction)
{
	switch(portName)
				{
				case GPIO_A:/** GPIO A is selected*/
					GPIOA->PDDR |= direction;
					break;
				case GPIO_B:/** GPIO B is selected*/
					GPIOB->PDDR |= direction;
					break;
				case GPIO_C:/** GPIO C is selected*/
					GPIOC->PDDR |= direction;
					break;
				case GPIO_D:/** GPIO D is selected*/
					GPIOD->PDDR |= direction;
					break;
				case GPIO_E: /** GPIO E is selected*/
					GPIOE->PDDR |= direction;
					break;
				default:/**If doesn't exist the option*/
					break;

				}
}

void GPIO_dataDirectionPIN(GPIO_portNameType portName, uint8 State, uint8 pin)
{

	switch(portName)
				{
				case GPIO_A:/** GPIO A is selected*/
					if(FALSE==((GPIOA->PDDR>>pin)&(UNO))){
						GPIOA->PDDR|=State<<pin;
					}
					else if(FALSE==State){
						GPIOA->PDDR-=State<<pin;
					}

					break;
				case GPIO_B:/** GPIO B is selected*/
					if(FALSE==((GPIOB->PDDR>>pin)&(UNO))){
						GPIOB->PDDR|=State<<pin;
					}
					else if(FALSE==State){
						GPIOB->PDDR-=UNO<<pin;
					}
					break;
				case GPIO_C:/** GPIO C is selected*/
					if(FALSE==((GPIOC->PDDR>>pin)&(UNO))){
						GPIOC->PDDR|=State<<pin;
					}
					else if(FALSE==State){
						GPIOC->PDDR-=State<<pin;
					}
					break;
				case GPIO_D:/** GPIO D is selected*/
					if(FALSE==((GPIOD->PDDR>>pin)&(UNO))){
						GPIOD->PDDR|=State<<pin;
					}
					else if(FALSE==State){
						GPIOD->PDDR-=State<<pin;
					}
					break;
				case GPIO_E: /** GPIO E is selected*/
					if(FALSE==((GPIOB->PDDR>>pin)&(UNO))){
						GPIOB->PDDR|=State<<pin;
					}
					else if(FALSE==State){
						GPIOB->PDDR-=State<<pin;
					}
					break;
				default:/**If doesn't exist the option*/
					break;

				}
}

void GPIO_dataDirectionPORT2(GPIO_portNameType portName ,uint32 direction)
{
	switch(portName)
				{
				case GPIO_A:/** GPIO A is selected*/
					GPIOA->PDDR &= direction;
					break;
				case GPIO_B:/** GPIO B is selected*/
					GPIOB->PDDR &= direction;
					break;
				case GPIO_C:/** GPIO C is selected*/
					GPIOC->PDDR &= direction;
					break;
				case GPIO_D:/** GPIO D is selected*/
					GPIOD->PDDR &= direction;
					break;
				case GPIO_E: /** GPIO E is selected*/
					GPIOE->PDDR &= direction;
					break;
				default:/**If doesn't exist the option*/
					break;

				}
}

void GPIO_writePORT2(GPIO_portNameType portName, uint32 Data )
{
	switch(portName)
		{
		case GPIO_A:/** GPIO A is selected*/
			GPIOA->PDOR|=Data;
			break;
		case GPIO_B:/** GPIO B is selected*/
			GPIOB->PDOR|=Data;
			break;
		case GPIO_C:/** GPIO C is selected*/
			GPIOC->PDOR|=Data;
			break;
		case GPIO_D:/** GPIO D is selected*/
			GPIOD->PDOR|=Data;
			break;
		case GPIO_E: /** GPIO E is selected*/
			GPIOE->PDOR=Data;
		default:/**If doesn't exist the option*/
			break;
		}
}

void GPIO_writePORT3(GPIO_portNameType portName, uint32 Data )
{
	switch(portName)
		{
		case GPIO_A:/** GPIO A is selected*/
			GPIOA->PDOR&=Data;
			break;
		case GPIO_B:/** GPIO B is selected*/
			GPIOB->PDOR&=Data;
			break;
		case GPIO_C:/** GPIO C is selected*/
			GPIOC->PDOR&=Data;
			break;
		case GPIO_D:/** GPIO D is selected*/
			GPIOD->PDOR&=Data;
			break;
		case GPIO_E: /** GPIO E is selected*/
			GPIOE->PDOR&=Data;
		default:/**If doesn't exist the option*/
			break;
		}
}


void GPIO_dataDirectionPORT3(GPIO_portNameType portName ,uint32 direction)
{
	switch(portName)
				{
				case GPIO_A:/** GPIO A is selected*/
					GPIOA->PDDR = direction;
					break;
				case GPIO_B:/** GPIO B is selected*/
					GPIOB->PDDR = direction;
					break;
				case GPIO_C:/** GPIO C is selected*/
					GPIOC->PDDR = direction;
					break;
				case GPIO_D:/** GPIO D is selected*/
					GPIOD->PDDR = direction;
					break;
				case GPIO_E: /** GPIO E is selected*/
					GPIOE->PDDR = direction;
					break;
				default:/**If doesn't exist the option*/
					break;

				}
}
