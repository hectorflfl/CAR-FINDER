/* Extended GCC Assembly using constraints
 * 
 * 
 *	asm ( assembler template 
 *	           : output operands                  // optional 
 *	           : input operands                   // optional 
 *	           : list of clobbered registers      // optional 
 *	           );
 *	        
 *	           
 * Note: If there are a total of n operands (both input and output inclusive), 
 * then the first output operand is numbered 0, continuing in increasing order, 
 * and the last input operand is numbered n-1.
 *  
 * 
 * asm ("mov %0, %[test]" :/ No output s/ : "g" (rb) , [test] "g" (test));
 * asm ("mov %[rb], %[test]" :/ No outputs /: [rb] "g" (rb) , [test] "g" (test));					
 * asm ("mov %0, %1" :/ No outputs /: "g" (rb) , "g" (test));										
 * 
 * 
 */
#include "DataTypeDefinitions.h"


//ra=0x283128;

void delay_cycles(uint32 cycles){
	register int ra __asm ("r4");
	ra=cycles;
	__asm("LOOP1:");
	__asm ("cbz  r4,LOOP");
	__asm("ADD r4,-1");
	__asm("B LOOP1");
	__asm("LOOP:");

}

void delay_msOrus(uint16 time, uint32 systemClock, uint8 msOrus){
	float delay = FALSE;
	if(TRUE == msOrus){

		delay=time*0.000001;

	}else if(FALSE == msOrus){
		delay=time*0.001;
	}

	delay_cycles(delay*systemClock/7.972);


}
