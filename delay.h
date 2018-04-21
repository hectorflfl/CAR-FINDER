/*
 * delay.h
 *
 *  Created on: 20/09/2017
 *      Author: jlpe
 */

#ifndef DELAY_H_
#define DELAY_H_

#include "DataTypeDefinitions.h"

/*!
 	 \brief	 This function receives the numbers of clock cycles the the CPU will be delayed.

 	 \param[in]  Number of clock cycles.
 	 \return void
 	 \todo Nothing.
 */
void delay_cycles(uint32 cycles);

/*!
 	 \brief	 This function generates a delay based in the received arguments.

 	 \param[in] time: timer to delayed the CPU, It is an integer number.
 	 \param[in] systemClock: Clock frequency at what the CPU is running.
 	 \param[in] msOrus: If the argument is 1, the delay will be in microseconds, if the argument is 0 the delay will be in miliseconds
 	 \return void
 	 \todo Nothing.
 */
void delay_msOrus(uint16 time, uint32 systemClock, uint8 msOrus);



#endif /* DELAY_H_ */
