/*
 * LCD.h
 *
 *  Created on: Oct 30, 2018
 *      Author: Alex
 */

#ifndef LCD_LCD_H_
#define LCD_LCD_H_

/**
 * \file       LCD.h
 * \author     Iosub Mihai Alexandru
 * \brief      This is the driver for the Nokia5110 LCD HXE 70x48 pixels; 14x6 letters of 5x8 pixels;
 */


/*----------------------------------------------------------------------------*/
/*                                  Includes                                  */
/*----------------------------------------------------------------------------*/
#include "types.h"
#include "SPI.h"
/*----------------------------------------------------------------------------*/
/*                             Defines and macros                             */
/*----------------------------------------------------------------------------*/
#define LCD_BLANK		(0x20)
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

void LCD_vInit();

void LCD_vReset();

void LCD_vSendCommand(uint8 commandToBeSent);

void LCD_vSendData(uint8 dataToBeSent);

void LCD_vSetXY(uint8 x, uint8 y);

void LCD_vClear();

void LCD_vSendString(uint8 *DATA, uint8 lenan, bool inverted);

void LCD_vUpdateDataOnDisplay(uint8 x, uint8 y, uint8 character);

void LCD_vMainFunction(void);

bool LCD_IsPositionFree(uint8 x, uint8 y);

bool LCD_IsPositionAFruit(uint8 x, uint8 y);
#endif /* LCD_LCD_H_ */
