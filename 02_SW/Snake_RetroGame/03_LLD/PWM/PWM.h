/*
 * PWM.h
 *
 *  Created on: Nov 12, 2018
 *      Author: Alex
 */

#ifndef PWM_PWM_H_
#define PWM_PWM_H_

/*----------------------------------------------------------------------------*/
/*                                  Includes                                  */
/*----------------------------------------------------------------------------*/
#include "PWM_Cfg.h"
#include "types.h"

/*----------------------------------------------------------------------------*/
/*                             Defines and macros                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                                 Data types                                 */
/*----------------------------------------------------------------------------*/

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
 * \brief     This function initializes PWM module according to the PWM_moduleInit[NUMBER_OF_PWMS] array from PWM_Cfg.h
 * \param     none
 * \return    none
 */
void PWM_vInit();

/**
 * \brief     This function is used to set duty cycle on a channel
 * \param     ModuleAndCHannel - the most significant 4 bits represents the Module
 * 							   - the least significant 4 bits represent the channel of the module
 * 			  Percent - PWM percent to be set.
 * \return    tOperationResultType: OPERATION_SUCCESS or OPERATION_ERROR
 */
tOperationResultType PWM_tSetDutyCycle(uint8 ModuleAndChannel, uint8 Percent);
/*
 * \brief     This function is used to get the value of the CNT register
 * \param     Module - ID of the PWM module
 * \return    uint16: Value of the counter;
 *  */
uint16 PWM_uiReadCntValue(uint8 Module);

#endif /* PWM_PWM_H_ */
