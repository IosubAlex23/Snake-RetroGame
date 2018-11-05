/*
 * delay.h
 *
 *  Created on: 9 mai 2018
 *      Author: Alex
 */

#ifndef DELAY_H_
#define DELAY_H_

#include "derivative.h"

void init_delay(void);
void init_IRQs (void);
void delay_ns(unsigned int ns);
void delay_us(unsigned int us);
void delay_ms(unsigned int ms);

#endif /* DELAY_H_ */
