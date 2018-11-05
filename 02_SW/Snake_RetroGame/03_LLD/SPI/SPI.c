/**
 * \file       SPI.c
 * \author     Iosub Mihai Alexandru
 * \brief      Short description for this source file
 */

/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/

#include "SPI.h"

/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/
/*
 SPIE = 0; Interrupts from SPRF and MODF are inhibited—use polling;
 SPE = 1; SPI System Enable
 SPTIE = 0; 0 Interrupts from SPTEF inhibited (use polling)
 MSTR = 1; SPI module configured as a master SPI device
 CPOL = 0; 0 Active-high SPI clock (idles low)
 CPHA = 1; First edge on SPSCK at start of first data transfer cycle
 SSOE = 1; Determines SS pin function when mode fault enabled
 LSBFE = 0; 0 SPI serial data transfers start with the most significant bit.
 */
#define SPI1_C1_VAL	(0x56u)
/* SPMIE = 0; Interrupts from SPMF inhibited (use polling)
 * [6:5] = reserved;
 * MODFEN = 1; Enable mode fault function;
 * BIDIROE = 0; (no effect if SPC0 is 0 (SPC0 = 1 => one wire))
 * [2] = reserved;
 * SPISWAI = 0; SPI clocks continue to operate in Wait mode.
 * SPC0 = 0; SPI uses separate pins for data input and data output (pin mode is normal).
 *
 *
 * */
#define SPI1_C2_VAL	(0x10u)
/*
 * [7] = reserved;
 * [6:4] SPPR[2:0] = 100; Baud rate prescaler divisor is 5. (20MHz / 5 = 4MHz)
 * [3:0] SPR[3:0] = 0010; Baud rate divisor is 8. (4Mhz / 8 = 500kHz);
 *
 *
 */
#define SPI1_BR_VAL	(0x78u) /* 0x42 is the calculated value, 0x78 is used when testing on myDaq*/

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
void SPI_vInit()
{
	SIM_SCGC |= SIM_SCGC_SPI1_MASK; /* Clock enable for SPI1*/
	SPI1_C1 = SPI1_C1_VAL; /* Registers settings, more info can be found at definition of SPI1_C1_VAL, SPI1_C2_VAL and SPI1_BR_VAL */
	SPI1_C2 = SPI1_C2_VAL;
	SPI1_BR = SPI1_BR_VAL;
}

tOperationResultType SPI_vSendData(uint8 dataToBeSent)
{
	while ((SPI1_S & SPI_S_SPTEF_MASK) == 0)
		/* TIMEOUT will be implemented here */
		; /*Wait for transmit buffer to be empty*/
	(void) SPI1_S; /* Clear buffer empty flag */
	SPI1_D = dataToBeSent; /* Write data */

	return OPERATION_SUCCESS;
}

tOperationResultType SPI_vReadData(uint8 * dataLocation)
{
	while ((SPI1_S & SPI_S_SPRF_MASK) == 0)
		/* TIMEOUT will be implemented here */
		; /* Wait for receive buffer to be full */
	(void) SPI1_S; /* Clear buffer full flag */
	*dataLocation = SPI1_D; /* Return received data */
	return OPERATION_SUCCESS;
}

/*----------------------------------------------------------------------------*/
/*                     Implementation of local functions                      */
/*----------------------------------------------------------------------------*/
