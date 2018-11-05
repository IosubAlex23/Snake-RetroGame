/*
 * GPIO.h
 *
 *  Created on: Nov 1, 2018
 *      Author: Alex
 */

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_


/*----------------------------------------------------------------------------*/
/*                                  Includes                                  */
/*----------------------------------------------------------------------------*/
#include "types.h"
/*----------------------------------------------------------------------------*/
/*                             Defines and macros                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                                 Data types                                 */
/*----------------------------------------------------------------------------*/
typedef enum
{
	PIN_OUTPUT = 0u,
	PIN_INPUT,
} tPinDirectionType;

/* Use this way:
 * bits [7:5] represents the GPIO port; GPIOA = 1; GPIOB = 2; GPIOC = 3;
 * bits [4:0] represents the pin ID from the GPIO register;
 */
typedef uint8 tPinPortType;
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
 * \brief     This is the initialization function of the GPIO module.
 * \param     None.
 * \return    None.
 */
void GPIO_vInit();

/**
 * \brief     This function is used to set a pin direction.
 * \param     pin - Represents target pin.
 * 			  direction - New pin direction (PIN_INPUT / PIN_OUTPUT).
 * \return    None.
 */
void GPIO_vSetPinDirection(tPinPortType pin, tPinDirectionType direction);

/**
 * \brief     This function is used to set a pin level.
 * \param     pin - Represents target pin.
 * 			  level - Pin level to be set.
 * \return    None.
 */
void GPIO_vSetPinLevel(tPinPortType pin, tPinLevelType level);

/**
 * \brief     This function is used to read a pin level
 * \param     pin - Represents target pin
 * \return    tPinLevelType: STD_LOW or STD_HIGH
 */
tPinLevelType GPIO_uiGetPinLevel(tPinPortType pin);

#endif /* GPIO_GPIO_H_ */
