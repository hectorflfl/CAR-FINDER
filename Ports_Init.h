/**
	\file
		Ports_Init.h
	\brief
		This is the source file that help us to initialize the
		ports and the interrupts
	\author Hector Flores, ie703475@iteso.mx
	\date	Mar 16, 2018
 */
#ifndef PORTS_INIT_H_
#define PORTS_INIT_H_

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function initialize the ports lik GPIO

 \param[in]  void
 \return void
 */
void pins_initialize();

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 \brief	 This function enable set the interrupts

 \param[in]  void
 \return void
 */
void pins_interrupts();

#endif /* PORTS_INIT_H_ */
