/*
 * LCD.c
 *
 *  Created on: Oct 30, 2018
 *      Author: Alex
 */

/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include "LCD.h"
#include "delay.h"
#include "LCD_Characters.h"
#include "GPIO.h"
#include "Snake.h"
/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/

/*
 #define DC_HIGH() 	(GPIOB_PSOR |= (1 << DC_PIN))
 #define DC_LOW() 	(GPIOB_PCOR |= (1 << DC_PIN))

 #define RST_HIGH()	(GPIOB_PSOR |= (1 << RST_PIN))
 #define RST_LOW()	(GPIOB_PCOR |= (1 << RST_PIN))
 */

#define PIN_LCD_DC		(0x25) /* 001 = GPIOB; 1 << 5 = PTE5 */
#define PIN_LCD_RST 	(0x24) /* 001 = GPIOB; 1 << 4 = PTE4 */
#define LCD_X_CHARS		(14u)
#define LCD_Y_CHARS		(6u)
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
static uint8 LCD_DISPLAY[LCD_Y_CHARS][LCD_X_CHARS] =
{
{ LCD_BLANK, 'H', 'S', ':', LCD_BLANK, LCD_BLANK, LCD_BLANK,
LCD_BLANK, 'A', 'S', ':', LCD_BLANK, LCD_BLANK,
LCD_BLANK },

{ LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK,
LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK,
LCD_BLANK, },

{ LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK,
LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK,
LCD_BLANK, },

{ LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK,
LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK,
LCD_BLANK, },

{ LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK,
LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK,
LCD_BLANK, },

{ LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK,
LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK, LCD_BLANK,
LCD_BLANK, } };
/*----------------------------------------------------------------------------*/
/*                             Local data at ROM                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                       Declaration of local functions                       */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/
void LCD_vInit()
{
	GPIO_vSetPinDirection(PIN_LCD_DC, PIN_OUTPUT);
	GPIO_vSetPinDirection(PIN_LCD_RST, PIN_OUTPUT);

	LCD_vReset();

	LCD_vSendCommand(0x21); /*command set in addition mode*/

	LCD_vSendCommand(0xC0); /*set the voltage by sending C0 means VOP = 5V*/

	LCD_vSendCommand(0x07); /*set the temp. coefficient to 3*/

	LCD_vSendCommand(0x13); /*set value of Voltage Bias System*/

	LCD_vSendCommand(0x20); /*command set in basic mode*/

	LCD_vSendCommand(0x0C); /*display result in normal mode*/

	LCD_vClear();
}

void LCD_vMainFunction(void)
{
	uint8 yIndex;
	LCD_vSendString(&LCD_DISPLAY, 14, 1); // Sending first line
	for (yIndex = 1; yIndex < LCD_Y_CHARS; yIndex++)
	{
		LCD_vSendString(&LCD_DISPLAY[yIndex], 14, 0); // Painting rest of the display
	}
}

void LCD_vReset()
{
	GPIO_vSetPinLevel(PIN_LCD_RST, STD_LOW);
	delay_ms(100);
	GPIO_vSetPinLevel(PIN_LCD_RST, STD_HIGH);
}

void LCD_vClear()
{
	uint16 index;
	LCD_vSetXY(0, 0);
	for (index = 0; index < 502; index++)
	{
		LCD_vSendData(0x00);
	}
}

void LCD_vSendCommand(uint8 commandToBeSent)
{
	GPIO_vSetPinLevel(PIN_LCD_DC, STD_LOW); /* make DC pin to logic zero for command operation */
	/* enable SS pin to slave selection */
	SPI_vSendData(commandToBeSent); /* send data on data register */
	GPIO_vSetPinLevel(PIN_LCD_DC, STD_HIGH); /* make DC pin to logic high for data operation */

}

void LCD_vSendData(uint8 dataToBeSent)
{
	GPIO_vSetPinLevel(PIN_LCD_DC, STD_HIGH); /* make DC pin to logic high for command operation */
	/* enable SS pin to slave selection */
	SPI_vSendData(dataToBeSent); /* send data on data register */

}

void LCD_vSetXY(uint8 x, uint8 y)
{
	LCD_vSendCommand((0x80 + x));
	LCD_vSendCommand((0x40 + y));
}

void LCD_vSendString(uint8 *DATA, uint8 lenan, bool inverted)
{
	uint8 index;
	uint8 g;
	GPIO_vSetPinLevel(PIN_LCD_DC, STD_HIGH); /* make DC pin to logic high for data operation */
	/* enable SS pin to slave selection */
	for (g = 0; g < lenan; g++)
	{
		if (1 == inverted)
		{
			LCD_vSendData(~0x00);
		}
		else
		{
			LCD_vSendData(0x00);
		}
		for (index = 0; index < 5; index++)
		{
			if (1 == inverted)
			{
				LCD_vSendData(~(ASCII[DATA[g] - 0x20][index])); /* send the data on data register */
			}
			else
			{
				LCD_vSendData(ASCII[DATA[g] - 0x20][index]);
			}
		}

	}

}

void LCD_vUpdateDataOnDisplay(uint8 x, uint8 y, uint8 character)
{
	LCD_DISPLAY[y][x] = character;
}

bool LCD_IsPositionFree(uint8 x, uint8 y)
{
	bool returnValue = 1u;
	if((LCD_DISPLAY[y][x] >= 0x22) && (LCD_DISPLAY[y][x] <= 0x2a))
	{
		returnValue = 0u;
	}
	return returnValue;
}

bool LCD_IsPositionAFruit(uint8 x, uint8 y)
{
	bool returnValue = 0u;
	if((LCD_DISPLAY[y][x] == SNAKE_FRUIT))
	{
		returnValue = 1u;
	}
	return returnValue;
}
/*----------------------------------------------------------------------------*/
/*                     Implementation of local functions                      */
/*----------------------------------------------------------------------------*/

