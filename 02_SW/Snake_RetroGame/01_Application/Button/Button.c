/*
 * Button.c
 *
 *  Created on: Nov 18, 2018
 *      Author: Alex
 */

/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include "Button.h"
#include "delay.h"
/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/
#define BUTTONS_NO_OF_BUTTONS		(1u)
#define BUTTON_DEBOUNCE_TIME		(10u)
#define PTH2						(0x3Au) /* 001 = GPIOB, 11010 = bit with index 26*/
/*----------------------------------------------------------------------------*/
/*                              Local data types                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Global data at RAM                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Global data at ROM                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Local data at RAM                              */
/*----------------------------------------------------------------------------*/
static tButtonType Button_State[BUTTONS_NO_OF_BUTTONS] =
{
		/** button should be initialised with {x,y,BUTTON_PRESSED, BUTTON_NOT_PRESSED}
		 ** otherwise first button push will not be read
		 **/
		{ PTH2, BUTTON_DEBOUNCE_TIME, BUTTON_PRESSED, BUTTON_NOT_PRESSED }
};
/*----------------------------------------------------------------------------*/
/*                             Local data at ROM                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                       Declaration of local functions                       */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/
void Button_vInit()
{
	uint8 index;
	for (index = 0; index < BUTTONS_NO_OF_BUTTONS; index++)
	{
		GPIO_vSetPinDirection(Button_State[index].portAndPin, PIN_INPUT);
		Button_State[index].debounceCounter = 0;
	}
}

void Button_vMainFunction()
{
	tPinLevelType actualState;
	uint8 index;
	for (index = 0; index < BUTTONS_NO_OF_BUTTONS; index++)
	{
		actualState = GPIO_uiGetPinLevel(Button_State[index].portAndPin);
		/* actualState == STD_LOW because btn has pull up resistor */
		if ((actualState == STD_LOW)
				&& (Button_State[index].btnState == BUTTON_NOT_PRESSED) && (BUTTON_PRESSED == Button_State[index].btnOldState))
		{

			Button_State[index].debounceCounter++;
			if (Button_State[index].debounceCounter >= BUTTON_DEBOUNCE_TIME)
			{
				Button_State[index].btnState = BUTTON_PRESSED;
				Button_State[index].debounceCounter = 0u;
			}
		}
		else if ((actualState == STD_HIGH)
				&& (Button_State[index].btnState == BUTTON_PRESSED) && (BUTTON_NOT_PRESSED == Button_State[index].btnOldState))
		{
			Button_State[index].debounceCounter++;
			if (Button_State[index].debounceCounter >= BUTTON_DEBOUNCE_TIME)
			{
				Button_State[index].btnState = BUTTON_NOT_PRESSED;
				Button_State[index].debounceCounter = 0u;
			}
		}
		else
		{
			Button_State[index].debounceCounter = 0;
		}
		Button_State[index].btnOldState = actualState;
	}
	delay_ms(1);
}

tButtonState Button_tGetButtonState(uint8 btnId)
{
	return Button_State[btnId].btnState;
}

tButtonState Button_tGetButtonDebounceOldState(uint8 btnId)
{
	return Button_State[btnId].btnOldState;
}
/*----------------------------------------------------------------------------*/
/*                     Implementation of local functions                      */
/*----------------------------------------------------------------------------*/

