/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include <stdlib.h>
#include "derivative.h" /* include peripheral declarations SSKEAZ128M4 */
#include "types.h"
#include "SPI.h"
#include "LCD.h"
#include "clocks.h"
#include "delay.h"
#include "GPIO.h"
#include "Button.h"
#include "ADC.h"
#include "Joystick.h"
#include "Snake.h"

#define PTE7 (0x27)	/* 001 = GPIOB; 1 << 7 = PTE7 */
#define PTE6 (0x26) /* 001 = GPIOB; 1 << 6 = PTE6 */
#define PTE3 (0x23) /* 001 = GPIOB; 1 << 3 = PTE3 */
#define PTH0 (0x38) /* 001 = GPIOB; 1 << 24 = PTH0 */
#define PTH1 (0x39) /* 001 = GPIOB; 1 << 25 = PTH1 */
/* For details see page 678 on KEA128RM.pdf datasheet */

void App_vInit()
{
	init_clks_FEE_40MHz();
	init_IRQs();
	init_delay();
	SPI_vInit();
	LCD_vInit();
	PWM_vInit();
	Button_vInit();
	Adc_Init();
	JoyStick_Init(12, 13); /* PTF4-5 */
	Snake_vInit();
}

int main(void)
{
	App_vInit();
	/* Pull up for joystick button, no time for drivers :D :( */
	PORT_PUE1 |= (1 << JOYSTICK_BTN_PIN);
	while (1)
	{
		Button_vMainFunction();
		Snake_vMainFunction();
		LCD_vMainFunction();

	}

	/*uint8 * a = (uint8*)malloc(2 * sizeof(uint8));
	 a[0] = 1;
	 a[1] = 3;
	 PORT_PUE1 |= PORT_PUE1_PTHPE2_MASK;
	 GPIO_vSetPinDirection(PTE7, PIN_OUTPUT);
	 GPIO_vSetPinDirection(PTH0, PIN_INPUT);
	 GPIO_vSetPinDirection(PTH1, PIN_INPUT);
	 GPIO_vSetPinLevel(PTH0, STD_HIGH);
	 GPIO_vSetPinLevel(PTH1, STD_HIGH);
	 uint8 state = STD_HIGH;
	 uint8 flag = 0u;
	 while (1)
	 {
	 Button_vMainFunction();

	 if ((JoyStick_South == getJoystickState()) && (flag == 0))
	 {

	 state = ~state;
	 state &= 0x1;
	 GPIO_vSetPinLevel(PTE7, state);
	 flag = 0x1;
	 a = realloc(a, 3 * sizeof(uint8));
	 a[3] = 4;
	 }
	 else if((JoyStick_North == getJoystickState()) && (flag == 1))
	 {
	 flag = 0x0;
	 a = realloc(a, 4 * sizeof(uint8));
	 a[4] = 8;
	 }
	 }*/

	return 0;
}
