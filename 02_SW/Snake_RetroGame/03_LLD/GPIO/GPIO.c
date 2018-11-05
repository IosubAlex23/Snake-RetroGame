/*
 * GPIO.c
 *
 *  Created on: Nov 1, 2018
 *      Author: Alex
 */

/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include "GPIO.h"
/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/
#define PDDR_BASE_ADR		&GPIOA_PDDR
#define PCOR_BASE_ADR		&GPIOA_PCOR
#define PSOR_BASE_ADR		&GPIOA_PSOR
#define PDIR_BASE_ADR		&GPIOA_PDIR

/* This represents the offset between same type registers for different ports
 * ex: &GPIOB_PDDR - &GPIOA_PDDR = 0x40; */
#define GPIO_REGS_OFFSET	(0x40u)
/*
 * bits [7:5] represents the GPIO port; GPIOA = 1; GPIOB = 2; GPIOC = 3;
 * bits [4:0] represents the pin ID from the GPIO register;
 */
#define GPIO_PIN_MASK		 (0x1Fu)
/* Number of bits used above, representing the pin ID from the GPIO register; */
#define GPIO_BITS_FOR_PIN_ID (5u)
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

/*----------------------------------------------------------------------------*/
/*                             Local data at ROM                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                       Declaration of local functions                       */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/
void GPIO_vSetPinDirection(tPinPortType pin, tPinDirectionType direction)
{
	/* GPIO port; GPIOA = 1; GPIOB = 2; GPIOC = 3; */
	uint8 port = pin >> GPIO_BITS_FOR_PIN_ID;
	/* Calculates the address for the PDDR register according to port id */
	uint32 * targetAdress = ((uint32) PDDR_BASE_ADR + (GPIO_REGS_OFFSET * port));
	if (PIN_OUTPUT == direction)
	{
		*targetAdress |= (1 << (pin & GPIO_PIN_MASK)); /* Setting pin as output on PDDR */
	}
	else if (PIN_INPUT == direction)
	{
		*targetAdress &= ~(1 << (pin & GPIO_PIN_MASK)); /* Setting pin as input on PDDR */
		/* Calculating address for PIDR */
		targetAdress++;
		/* Pin is configured for General Purpose Input on PIDR
		 * If this is not set, the pin will be in Hi-Z state */
		*targetAdress &= ~(1 << (pin & GPIO_PIN_MASK));
	}
}

void GPIO_vSetPinLevel(tPinPortType pin, tPinLevelType level)
{
	uint8 port = pin >> GPIO_BITS_FOR_PIN_ID;
	uint32 * targetAdress;
	if (STD_HIGH == level)
	{
		/* If desired level is HIGH, calculate adress of GPIOx_PSOR */
		targetAdress = ((uint32) PSOR_BASE_ADR + (GPIO_REGS_OFFSET * port));
		/* Writing 1 to GPIOx_PSOR  will set the contents of the corresponding bit in the PDOR */
		*targetAdress |= (1 << (pin & GPIO_PIN_MASK)); /* PSOR */
	}
	else if (STD_LOW == level)
	{
		/* If desired level is HIGH, calculate adress of GPIOx_PCOR */
		targetAdress = ((uint32) PCOR_BASE_ADR + (GPIO_REGS_OFFSET * port));
		/* Writing 1 to GPIOx_PCOR  will clear the contents of the corresponding bit in the PDOR */
		*targetAdress |= (1 << (pin & GPIO_PIN_MASK)); /* PCOR */
	}
}

tPinLevelType GPIO_uiGetPinLevel(tPinPortType pin)
{
	uint8 port = pin >> GPIO_BITS_FOR_PIN_ID;
	uint32 * targetAdress;
	uint8 pinValue;
	tPinLevelType returnValue;
	/* Calculates the address for the PDIR register according to port id */
	targetAdress = ((uint32) PDIR_BASE_ADR + (GPIO_REGS_OFFSET * port));
	/* Getting pin value to the LSB bit of pinValue */
	pinValue = ((*targetAdress >> (pin & GPIO_PIN_MASK)) & 0x1);
	if (0x1 == pinValue)
	{
		returnValue = STD_HIGH;
	}
	else
	{
		returnValue = STD_LOW;
	}
	return returnValue;
}

/*----------------------------------------------------------------------------*/
/*                     Implementation of local functions                      */
/*----------------------------------------------------------------------------*/

