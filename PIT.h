/*
 * PIT.h
 *
 *  Created on: 16/08/2017
 *      Author: jlpe
 */

#ifndef PIT_H_
#define PIT_H_

#include "DataTypeDefinitions.h"
#define DELAY1S 2

/*! This enumerated constant are used to select the PIT to be used*/
typedef enum {
	PIT_0, PIT_1, PIT_2, PIT_3
} PIT_Timer_t;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function configure the PIT to generate a delay base on the system clock.
 Internally it configures the clock gating and enables the PIT module.
 It is important to note that this strictly is not device driver since everything is
 contained in a single function, but in general you have to avoid this practices, this only
 for the propose of the homework

 \param[in]  portName Port to be configured.
 \return void
 */
void PIT_delay(PIT_Timer_t pitTimer, float systemClock, float perior);
uint32 PIT_getTimerValue(PIT_Timer_t pitTimer);
void PIT_clockGating(void);
uint8 getcandado_LEDS_TF(void);
uint8 PIT_interruptFlagStatus(PIT_Timer_t pitTimer);
uint32 PIT_getIntrStatus(PIT_Timer_t pitTimer);
void PIT_clear(PIT_Timer_t pitTimer);
void PIT_disabled(PIT_Timer_t pitTimer);

#endif /* PIT_H_ */
