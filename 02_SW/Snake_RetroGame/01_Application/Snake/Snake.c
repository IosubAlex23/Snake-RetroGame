/*
 * Snake.c
 *
 *  Created on: Dec 13, 2018
 *      Author: Alex
 */

/*----------------------------------------------------------------------------*/
/*                                 Includes                                   */
/*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Snake.h"
#include "stdlib.h"
#include "LCD.h"
#include "Joystick.h"
/*----------------------------------------------------------------------------*/
/*                               Local defines                                */
/*----------------------------------------------------------------------------*/
#define SNAKE_INITIAL_BODY_PARTS		(3u)
#define SNAKE_HEAD_INITIAL_LOCATION_X	(5u)
#define SNAKE_HEAD_INITIAL_LOCATION_Y	(1u)
#define SNAKE_NO_OF_BODY_PARTS			(9u)
#define SNAKE_HEAD_INDEX				(0u)
#define SNAKE_TOP_ROW					(1u)
#define SNAKE_BOTTOM_ROW				(5u)
#define SNAKE_EASTERN_ROW				(13u)
#define SNAKE_WESTERN_ROW				(0u)
#define SNAKE_INITIAL_FRUIT_TIMER_LIMIT	(30u)

#define ACTUAL_SCORE_LOCATION_X			(11u)
#define ACTUAL_SCORE_LOCATION_Y			(0u)

/*----------------------------------------------------------------------------*/
/*                              Local data types                              */
/*----------------------------------------------------------------------------*/
typedef enum
{
	HEAD_NORTH = 0x22u,
	HEAD_EAST,
	HEAD_SOUTH,
	HEAD_WEST,
	BODY,
	TAIL_NORTH,
	TAIL_EAST,
	TAIL_SOUTH,
	TAIL_WEST
} Snake_bodyParts;

typedef struct
{
	uint8 xPos;
	uint8 yPos;
	Snake_bodyParts orientation;
} SnakeStruct;

typedef enum
{
	GameState_StartMenu = 0u, GameState_Playing, GameState_GameOver
} Snake_GameState;

typedef struct
{
	uint8 xPos;
	uint8 yPos;
} SnakeFruit;

/*----------------------------------------------------------------------------*/
/*                             Global data at RAM                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Global data at ROM                             */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                             Local data at RAM                              */
/*----------------------------------------------------------------------------*/
SnakeStruct * Snake_body;
uint8 Number_of_body_parts;
uint16 actual_score;
Snake_GameState stateOfTheGame;
Joystick_State prevState, currentState;
uint8 Joystick_mean;
uint8 FruitTimer;
uint8 FruitTimerLimit;
SnakeFruit SnakeMainFruit;
Snake_Direction actualDirection;
/*----------------------------------------------------------------------------*/
/*                             Local data at ROM                              */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*                       Declaration of local functions                       */
/*----------------------------------------------------------------------------*/
void Snake_vGrow(void);
void Snake_vUpdateDisplayAS(void);
void Snake_vUpdateInfoText(void);
void Snake_vGenerateFruit(void);
/*----------------------------------------------------------------------------*/
/*                     Implementation of global functions                     */
/*----------------------------------------------------------------------------*/
void Snake_vInit(void)
{
	Joystick_mean = 0;
	actualDirection = DIRECTION_EAST;
	stateOfTheGame = GameState_Playing;
	actual_score = 0;
	FruitTimerLimit = SNAKE_INITIAL_FRUIT_TIMER_LIMIT;
	Snake_body = (SnakeStruct*) malloc(
			(SNAKE_INITIAL_BODY_PARTS * sizeof(SnakeStruct)));
	Number_of_body_parts = SNAKE_INITIAL_BODY_PARTS;
	uint8 index = 0;
	Snake_vGenerateFruit();
	for (index = 0; index < SNAKE_INITIAL_BODY_PARTS; index++)
	{
		Snake_body[index].yPos = (SNAKE_HEAD_INITIAL_LOCATION_Y);
		Snake_body[index].xPos = (SNAKE_HEAD_INITIAL_LOCATION_X - index);
		switch (index)
		{
		case 0:
			Snake_body[index].orientation = HEAD_EAST;
			break;
		case (SNAKE_INITIAL_BODY_PARTS - 1):
			Snake_body[index].orientation = TAIL_WEST;
			break;
		default:
			Snake_body[index].orientation = BODY;
			break;
		}
		LCD_vUpdateDataOnDisplay(Snake_body[index].xPos, Snake_body[index].yPos,
				Snake_body[index].orientation);
	}
}

void Snake_vMainFunction(void)
{
	if (GameState_Playing == stateOfTheGame)
	{

		prevState = currentState;
		currentState = getJoystickState();

		if (JoyStick_Center == prevState)
		{
			if (JoyStick_South == currentState)
			{
				actualDirection = DIRECTION_SOUTH;
				/*rm*/
			}
			else if (JoyStick_North == currentState)
			{
				actualDirection = DIRECTION_NORTH;
				/*Snake_vMove(DIRECTION_NORTH);*/
			}
			else if (JoyStick_East == currentState)
			{
				actualDirection = DIRECTION_EAST;
				/*Snake_vMove(DIRECTION_EAST);*/
			}
			else if (JoyStick_West == currentState)
			{
				actualDirection = DIRECTION_WEST;
				/*Snake_vMove(DIRECTION_WEST);*/
			}

		}
		if((FruitTimer % 3) == 0)
		{
			Snake_vMove(actualDirection);
		}
		Snake_vUpdateDisplayAS();
		if (FruitTimer > FruitTimerLimit)
		{
			Snake_vGenerateFruit();
		}
		else
		{
			FruitTimer++;
		}
	}
	Snake_vUpdateInfoText();

}
/*----------------------------------------------------------------------------*/
/*                     Implementation of local functions                      */
/*----------------------------------------------------------------------------*/
void Snake_vGrow(void)
{
	Snake_body = realloc(Snake_body,
			((Number_of_body_parts + 1) * sizeof(SnakeStruct)));

	Snake_body[Number_of_body_parts].orientation =
			Snake_body[Number_of_body_parts - 1].orientation;
	Snake_body[Number_of_body_parts - 1].orientation = BODY;
	Number_of_body_parts++;
}

void Snake_vUpdateHighestScore(void)
{

}

void Snake_vUpdateDisplayAS(void)
{
	LCD_vUpdateDataOnDisplay(ACTUAL_SCORE_LOCATION_X, ACTUAL_SCORE_LOCATION_Y,
			(actual_score / 100) + 0x30); // sute
	LCD_vUpdateDataOnDisplay(ACTUAL_SCORE_LOCATION_X + 1,
	ACTUAL_SCORE_LOCATION_Y, ((actual_score / 10) % 10) + 0x30); // zeci
	LCD_vUpdateDataOnDisplay(ACTUAL_SCORE_LOCATION_X + 2,
	ACTUAL_SCORE_LOCATION_Y, (actual_score % 10) + 0x30); // cifre
	if (actual_score >= 150)
	{
		FruitTimerLimit = 20;
	}
	else if (actual_score >= 110)
	{
		FruitTimerLimit = 22;
	}
	else if (actual_score >= 75)
	{
		FruitTimerLimit = 25;
	}
}

void Snake_vUpdateInfoText(void)
{
	if (GameState_GameOver == stateOfTheGame)
	{
		uint8 index;
		uint8 * text = "Looser!";
		for (index = 0; index < 7; index++)
		{
			LCD_vUpdateDataOnDisplay(index, 0, text[index]);
		}
	}
}

void Snake_vMove(Snake_Direction direction)
{
	uint8 index;
	LCD_vUpdateDataOnDisplay(Snake_body[Number_of_body_parts - 1].xPos,
			Snake_body[Number_of_body_parts - 1].yPos, LCD_BLANK); /* This clears the last position */

	/* This is used to draw body parts new positions */
	for (index = Number_of_body_parts - 1; index > 0; index--)
	{
		if ((Snake_body[index].orientation == TAIL_EAST)
				|| (Snake_body[index].orientation == TAIL_WEST))
		{
			if (Snake_body[index - 2].yPos > Snake_body[index].yPos)
			{
				Snake_body[index].orientation = TAIL_NORTH;
			}
			else if (Snake_body[index - 2].yPos < Snake_body[index].yPos)
			{
				Snake_body[index].orientation = TAIL_SOUTH;
			}
		}
		else if ((Snake_body[index].orientation == TAIL_NORTH)
				|| (Snake_body[index].orientation == TAIL_SOUTH))
		{
			if (Snake_body[index - 2].xPos > Snake_body[index].xPos)
			{
				Snake_body[index].orientation = TAIL_WEST;
			}
			else if (Snake_body[index - 2].xPos < Snake_body[index].xPos)
			{
				Snake_body[index].orientation = TAIL_EAST;
			}
		}
		Snake_body[index].xPos = Snake_body[index - 1].xPos;
		Snake_body[index].yPos = Snake_body[index - 1].yPos;
		LCD_vUpdateDataOnDisplay(Snake_body[index].xPos, Snake_body[index].yPos,
				Snake_body[index].orientation);
	}
	/* This is used to draw head's new position */
	switch (direction)
	{
	case DIRECTION_NORTH:
		if (Snake_body[SNAKE_HEAD_INDEX].yPos > SNAKE_TOP_ROW)
		{
			Snake_body[SNAKE_HEAD_INDEX].yPos--;
		}
		else
		{
			Snake_body[SNAKE_HEAD_INDEX].yPos = SNAKE_BOTTOM_ROW;
		}
		Snake_body[SNAKE_HEAD_INDEX].orientation = HEAD_NORTH;
		break;
	case DIRECTION_EAST:
		if (Snake_body[SNAKE_HEAD_INDEX].xPos < SNAKE_EASTERN_ROW)
		{
			Snake_body[SNAKE_HEAD_INDEX].xPos++;
		}
		else
		{
			Snake_body[SNAKE_HEAD_INDEX].xPos = SNAKE_WESTERN_ROW;
		}
		Snake_body[SNAKE_HEAD_INDEX].orientation = HEAD_EAST;
		break;
	case DIRECTION_WEST:
		if (Snake_body[SNAKE_HEAD_INDEX].xPos > SNAKE_WESTERN_ROW)
		{
			Snake_body[SNAKE_HEAD_INDEX].xPos--;
		}
		else
		{
			Snake_body[SNAKE_HEAD_INDEX].xPos = SNAKE_EASTERN_ROW;
		}
		Snake_body[SNAKE_HEAD_INDEX].orientation = HEAD_WEST;
		break;
	case DIRECTION_SOUTH:
		if (Snake_body[SNAKE_HEAD_INDEX].yPos < SNAKE_BOTTOM_ROW)
		{
			Snake_body[SNAKE_HEAD_INDEX].yPos++;
		}
		else
		{
			Snake_body[SNAKE_HEAD_INDEX].yPos = SNAKE_TOP_ROW;
		}
		Snake_body[SNAKE_HEAD_INDEX].orientation = HEAD_SOUTH;
		break;
	}
	/* If snake's body was touched */
	if (0u
			== LCD_IsPositionFree(Snake_body[SNAKE_HEAD_INDEX].xPos,
					Snake_body[SNAKE_HEAD_INDEX].yPos))
	{
		stateOfTheGame = GameState_GameOver;
	}
	/* If fruit was touched */
	else if (1u
			== LCD_IsPositionAFruit(Snake_body[SNAKE_HEAD_INDEX].xPos,
					Snake_body[SNAKE_HEAD_INDEX].yPos))
	{
		Snake_vGrow();
		actual_score += FruitTimerLimit - FruitTimer;
		Snake_vGenerateFruit();
	}
	LCD_vUpdateDataOnDisplay(Snake_body[SNAKE_HEAD_INDEX].xPos,
			Snake_body[SNAKE_HEAD_INDEX].yPos,
			Snake_body[SNAKE_HEAD_INDEX].orientation);
}

void Snake_vGenerateFruit(void)
{
	uint8 xRandom;
	uint8 yRandom;
	FruitTimer = 0;
	do
	{
		srand(PWM_uiReadCntValue(2));
		xRandom = (rand() % (SNAKE_EASTERN_ROW - SNAKE_WESTERN_ROW))
				+ SNAKE_WESTERN_ROW;
		srand(PWM_uiReadCntValue(2));
		yRandom = (rand() % (SNAKE_BOTTOM_ROW - SNAKE_TOP_ROW))
				+ SNAKE_TOP_ROW;
	} while (0u == LCD_IsPositionFree(xRandom, yRandom));
	/* Clears the fruit that was not eaten */
	LCD_vUpdateDataOnDisplay(SnakeMainFruit.xPos, SnakeMainFruit.yPos,
			LCD_BLANK);
	SnakeMainFruit.xPos = xRandom;
	SnakeMainFruit.yPos = yRandom;
	LCD_vUpdateDataOnDisplay(xRandom, yRandom, SNAKE_FRUIT);
}
