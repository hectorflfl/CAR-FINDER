/*
 *
 * PIT.c
 *
 *  Created on: Feb 21, 2018
 *      Author: carlo
 */

#include "MK64F12.h"
#include "PIT.h"
#include "NVIC.h"

#define PIT_CLOCK_GATING 0x800000
#define DISABLED 		 0x1
#define FIRSTBIT		0x1
#define PIT_MCR 		 0x2
#define ENABLE			 0
#define DISABLE_TIETEN    ~(0x3)
#define DISABLE_TIF    ~(0x1)

void PIT0_IRQHandler() {
	PIT->CHANNEL[PIT_0].TCTRL;
	PIT->CHANNEL[PIT_0].TCTRL &= ~(PIT_TCTRL_TIE_MASK);
	PIT->CHANNEL[PIT_0].TCTRL &= ~(PIT_TCTRL_TEN_MASK);
	PIT->CHANNEL[PIT_0].TCTRL &= ~(PIT_TCTRL_TEN_MASK);
	PIT->CHANNEL[PIT_0].TFLG &= ~(PIT_TFLG_TIF_MASK);

}
void PIT1_IRQHandler() {
	PIT->CHANNEL[PIT_1].TCTRL;
	PIT->CHANNEL[PIT_1].TCTRL &= ~(PIT_TCTRL_TIE_MASK);
	PIT->CHANNEL[PIT_1].TCTRL &= ~(PIT_TCTRL_TEN_MASK);
	PIT->CHANNEL[PIT_1].TCTRL &= ~(PIT_TCTRL_TEN_MASK);
	PIT->CHANNEL[PIT_1].TFLG &= ~(PIT_TFLG_TIF_MASK);

}
void PIT2_IRQHandler() {
	PIT->CHANNEL[PIT_2].TCTRL;
	PIT->CHANNEL[PIT_2].TCTRL &= ~(PIT_TCTRL_TIE_MASK);
	PIT->CHANNEL[PIT_2].TCTRL &= ~(PIT_TCTRL_TEN_MASK);
	PIT->CHANNEL[PIT_2].TCTRL &= ~(PIT_TCTRL_TEN_MASK);
	PIT->CHANNEL[PIT_2].TFLG &= ~(PIT_TFLG_TIF_MASK);

}

void PIT3_IRQHandler() {
	PIT->CHANNEL[PIT_3].TCTRL;
	PIT->CHANNEL[PIT_3].TCTRL &= ~(PIT_TCTRL_TIE_MASK);
	PIT->CHANNEL[PIT_3].TCTRL &= ~(PIT_TCTRL_TEN_MASK);
	PIT->CHANNEL[PIT_3].TCTRL &= ~(PIT_TCTRL_TEN_MASK);
	PIT->CHANNEL[PIT_3].TFLG &= ~(PIT_TFLG_TIF_MASK);

}

void PIT_clockGating() {
	SIM->SCGC6 |= PIT_CLOCK_GATING;
}
uint8 PIT_interruptFlagStatus(PIT_Timer_t pitTimer) {

	return (PIT->CHANNEL[pitTimer].TFLG);

}

void PIT_delay(PIT_Timer_t pitTimer, float systemClock, float perior) {
	PIT->MCR = ENABLE;
	PIT->CHANNEL[pitTimer].LDVAL = (uint32) (systemClock * perior) / 2;
	PIT->CHANNEL[pitTimer].TCTRL |= PIT_TCTRL_TIE_MASK;
	PIT->CHANNEL[pitTimer].TCTRL |= PIT_TCTRL_TEN_MASK;

}
uint32 PIT_getIntrStatus(PIT_Timer_t pitTimer) {
	return (PIT->CHANNEL[pitTimer].TFLG);

}

uint32 PIT_getTimerValue(PIT_Timer_t pitTimer) {
	return (PIT->CHANNEL[pitTimer].CVAL);
}

void PIT_clear(PIT_Timer_t pitTimer) {

	PIT->CHANNEL[pitTimer].TFLG |= PIT_TFLG_TIF_MASK;

}
void PIT_disabled(PIT_Timer_t pitTimer) {
	PIT->CHANNEL[pitTimer].TCTRL=FALSE;

}

