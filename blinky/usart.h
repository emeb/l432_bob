/*
 * usart.h -usart support for stbone L4
 * 03-30-2017 E. Brombaugh
 */

#ifndef __usart__
#define __usart__

#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"

void setup_usart(void);
void usart_putc(void* p, char c);

#endif
