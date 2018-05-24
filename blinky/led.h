/*
 * led.h - L432 BOB LED setup
 */

#ifndef __led__
#define __led__

#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"

void LEDInit(void);
void LEDOn(void);
void LEDOff(void);
void LEDToggle(void);

#endif
