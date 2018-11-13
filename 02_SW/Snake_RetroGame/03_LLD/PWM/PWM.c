/*
 * PWM.c
 *
 *  Created on: Nov 12, 2018
 *      Author: Alex
 */

/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include "PWM.h"
/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/
#define FTM_SC_BASE_ADR 			(0x40038000u)
#define FTM_SC_OFFSET	    	    (0x1000u)

#define FTM_CxV_BASE_ADR 		 	(0x40038010u)
#define FTM_CxV_OFFSET  		 	(0x1000u)
#define FTM_CxV_CHANNELS_OFFSET  	(0x8u)

#define FTM_OFFSET_IN_SCGC			(0x5u)

#define FTM_SC_MOD_OFFSET (0x2u) /* offset between SC register and MOD register */
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
void PWM_vInit()
{
	uint8 index;
	uint32 * FTM_Pointer;
	for (index = 0; index < NUMBER_OF_PWMS; index++)
	{
		/* Enable clock for FTM module */
		SIM_SCGC |= (1 << (FTM_OFFSET_IN_SCGC + PWM_moduleInit[index].FTM_ID));
		/* FTM2 CH0 mapped on PTH0 */
		SIM_PINSEL1 |= 0x1u;
		/* Calculating address of the SC register */
		FTM_Pointer = (uint32) FTM_SC_BASE_ADR
				+ ((uint32) PWM_moduleInit[index].FTM_ID * FTM_SC_OFFSET);
		/* Storing data at the address where pointing */
		*FTM_Pointer = PWM_moduleInit[index].SC_VAL;
		/* Pointing to the MOD register */
		FTM_Pointer += FTM_SC_MOD_OFFSET;
		/* Storing data to MOD register */
		*FTM_Pointer = PWM_moduleInit[index].MOD_VAL;
		/* Pointing to C0SC register */
		FTM_Pointer++;
		/* Storing data */
		*FTM_Pointer = PWM_moduleInit[index].CxSC_VAL; /* Edge-Aligned PWM High-true pulses (clear Output on match) */
	}
}

tOperationResultType PWM_vSetDutyCycle(uint8 ModuleAndChannel, uint8 Percent)
{
	uint8 index;
	uint32 * FTM_CxV;
	uint32 aux;
	tOperationResultType returnValue = OPERATION_SUCCESS;
	/* if percentage is not valid, return error */
	if ((Percent < 0) || (Percent > 100))
	{
		returnValue = OPERATION_ERROR;
	}
	else
	{
		/* Calculate adress of CxV for the selected module */
		FTM_CxV = FTM_CxV_BASE_ADR
				+ (FTM_CxV_OFFSET * UINT8_MS_HALF(ModuleAndChannel))
				+ (UINT8_LS_HALF(ModuleAndChannel) * FTM_CxV_CHANNELS_OFFSET);
		for (index = 0; index < NUMBER_OF_PWMS; index++)
		{
			/* Find index of configuration to get MOD_VAL from it */
			if (UINT8_MS_HALF(ModuleAndChannel)
					== PWM_moduleInit[index].FTM_ID)
			{
				/* Set CxV to the given percentage */
				*FTM_CxV = ((Percent * PWM_moduleInit[index].MOD_VAL) / 100);
			}
		}
	}
	return returnValue;
}
/*----------------------------------------------------------------------------*/
/*                     Implementation of local functions                      */
/*----------------------------------------------------------------------------*/

