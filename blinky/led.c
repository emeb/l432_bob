/*
 * led.c - L432 BOB LED setup
 */

#include "led.h"

/*
 * Initialize the breakout board LED
 */
void LEDInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable GPIO A Clock */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	
	/* Enable PB2 for output */
	GPIO_InitStructure.Pin =  GPIO_PIN_2;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL ;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*
 * Turn on LED
 */
void LEDOn(void)
{
	GPIOA->BSRR = (1<<2);
}

/*
 * Turn off LED
 */
void LEDOff(void)
{
	GPIOA->BSRR = (1<<(2+16));
}

/*
 * Toggle LED
 */
void LEDToggle(void)
{
	GPIOA->ODR ^= (1<<2);
}

