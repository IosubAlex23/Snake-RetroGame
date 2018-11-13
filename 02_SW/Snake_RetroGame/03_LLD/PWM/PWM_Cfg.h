/*
 * PWM_Cfg.h
 *
 *  Created on: Nov 12, 2018
 *      Author: Alex
 */

#ifndef PWM_PWM_CFG_H_
#define PWM_PWM_CFG_H_

/*----------------------------------------------------------------------------*/
/*                                  Includes                                  */
/*----------------------------------------------------------------------------*/
#include "types.h"
/*----------------------------------------------------------------------------*/
/*                             Defines and macros                             */
/*----------------------------------------------------------------------------*/
#define NUMBER_OF_PWMS 1
/*----------------------------------------------------------------------------*/
/*                                 Data types                                 */
/*----------------------------------------------------------------------------*/
typedef struct
{
	uint32 SC_VAL;
	uint32 MOD_VAL;
	uint32 CxSC_VAL;
	uint8 FTM_ID;
} tPwmConfigType;
/*----------------------------------------------------------------------------*/
/*                 External declaration of global RAM-Variables               */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                 External declaration of global ROM-Variables               */
/*----------------------------------------------------------------------------*/
const tPwmConfigType PWM_moduleInit[NUMBER_OF_PWMS] =
{
{ 0x00000009, 50000, 0x38, 2, } /* Prescaler = 2, Assign BUS clock, count until 50000 to achieve 200Hz on FTM2 */
};
/*----------------------------------------------------------------------------*/
/*                  External declaration of global functions                  */
/*----------------------------------------------------------------------------*/

#endif /* PWM_PWM_CFG_H_ */