/*
 * Button.h
 *
 *  Created on: Nov 18, 2018
 *      Author: Alex
 */

#ifndef BUTTON_BUTTON_H_
#define BUTTON_BUTTON_H_

/*----------------------------------------------------------------------------*/
/*                                  Includes                                  */
/*----------------------------------------------------------------------------*/
#include "GPIO.h"
/*----------------------------------------------------------------------------*/
/*                             Defines and macros                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                                 Data types                                 */
/*----------------------------------------------------------------------------*/
typedef enum
{
	BUTTON_PRESSED = 0u, BUTTON_NOT_PRESSED
} tButtonState;

typedef struct
{
	tPinPortType portAndPin;
	uint8 debounceCounter;
	tButtonState btnState;
	tButtonState btnOldState;
} tButtonType;

/*----------------------------------------------------------------------------*/
/*                 External declaration of global RAM-Variables               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                 External declaration of global ROM-Variables               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                  External declaration of global functions                  */
/*----------------------------------------------------------------------------*/

/**
 * \brief     This is the initialization function of the Button module.
 * \param     None.
 * \return    None.
 */
void Button_vInit();

/**
 * \brief     In this function state of buttons is read, debounce is realised and the state of the button is saved.
 * \param     None.
 * \return    None.
 */
void Button_vMainFunction();
/**
 * \brief     This function returns the state of a button.
 * \param     btnId - id of the button from the
 * 					"static tButtonType Button_State[BUTTONS_NO_OF_BUTTONS]" array located
 * 					in Button.c source file.
 * \return    tButtonState - the state of the button.
 */
tButtonState Button_tGetButtonState(uint8 btnId);
/**
 * \brief     This function returns the previous state of the button for which the debounce
 * 			  was made.
 * \param     btnId - id of the button from the
 * 					"static tButtonType Button_State[BUTTONS_NO_OF_BUTTONS]" array located
 * 					in Button.c source file.
 * \return    tButtonState - the state of the button.
 */
tButtonState Button_tGetButtonDebounceOldState(uint8 btnId);

#endif /* BUTTON_BUTTON_H_ */
