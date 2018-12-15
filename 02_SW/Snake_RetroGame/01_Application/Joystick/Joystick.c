/*
 * Joystick.c
 *
 *  Created on: 13 mai 2018
 *      Author: Alex
 */

#include "Joystick.h"
#include "Delay.h"
#include "types.h"
#include "ADC.h"

#define UP_ADC_VALUE 900
#define DOWN_ADC_VALUE 100

uint8 rxAdcCh, ryAdcCh;
uint8 sampling_counter = 0;
static Joystick_State Joystick_Position;

Joystick_State getJoystickState(void) {
	uint16_t rxAdcResult = 0, ryAdcResult = 0;

	//X Axis
	Adc_StartSingleConversion(rxAdcCh); // start conversion on channel rx
	/*while (Adc_IsConversionComplete() == 0)
	 ;*//* +TIMEOUT */
	delay_us(2); /* ADICLK 00 ADLSMP 0 => 23adck CYCLES + 5 BUS CLOCK CYCLES => 1.4 uS; Details on page 342 */
	if (Adc_IsConversionComplete())
		Adc_GetSingleResult(&rxAdcResult);
	else
		return;

	// Y Axis
	Adc_StartSingleConversion(ryAdcCh); // start conversion on channel ry
	/*while (Adc_IsConversionComplete() == 0)
	 ;*/
	delay_us(2);
	if (Adc_IsConversionComplete())
		Adc_GetSingleResult(&ryAdcResult);
	else
		return;
	if (rxAdcResult > UP_ADC_VALUE) {
		Joystick_Position = JoyStick_East;
	} else if (rxAdcResult < DOWN_ADC_VALUE) {
		Joystick_Position = JoyStick_West;
	} else if (ryAdcResult > UP_ADC_VALUE) {
		Joystick_Position = JoyStick_South;
	} else if (ryAdcResult < DOWN_ADC_VALUE) { // 5V pt South
		Joystick_Position = JoyStick_North;
	} else {
		Joystick_Position = JoyStick_Center;
	}
	return Joystick_Position;
}

// use only for GPIOA pins
void JoyStick_Init(uint8 rxAdc, uint8 ryAdc) {
	rxAdcCh = rxAdc;
	ryAdcCh = ryAdc;

	init_IRQs();	// init for ddelay
	init_delay();

	Adc_Init();
	tAdcCfg * myCfg = Adc_GetCfgHandle();
	myCfg->AdcOpMode = ADC_OPMODE_SINGLESHOT;
	myCfg->AdcResolution = ADC_RES_10_BIT;

	Adc_ConfigAcquisition(myCfg);
	getJoystickState();
}

