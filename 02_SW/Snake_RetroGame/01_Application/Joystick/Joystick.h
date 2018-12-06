/*
 * JOYSTICK.h
 *
 *  Created on: 12 mai 2018
 *      Author: Alex
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "types.h"

typedef enum {
	JoyStick_Center=0,
	JoyStick_North,
	JoyStick_South,
	JoyStick_East,
	JoyStick_West
} Joystick_State;


void JoyStick_Init(uint8,uint8);
Joystick_State getJoystickState(void);

#endif /* JOYSTICK_H_ */
