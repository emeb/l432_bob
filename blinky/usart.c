/*
 * usart.c - usart support for stbone L4
 * 03-30-2017 E. Brombaugh
 */

#include "usart.h"
#include "led.h"

USART_HandleTypeDef UsartHandle;

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED1 on */
  while(1)
  {
    /* Error if LED is blinking fast */
    LEDToggle(); 
    HAL_Delay(50); 
  }
}

/* USART setup */
void setup_usart(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Setup USART GPIO */
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/* Configure USART Tx as alternate function push-pull */
	GPIO_InitStructure.Pin = GPIO_PIN_6;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Configure USART Rx as alternate function push-pull */
	GPIO_InitStructure.Pin = GPIO_PIN_7;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	GPIO_InitStructure.Alternate = GPIO_AF7_USART1;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* Setup USART */
	__HAL_RCC_USART1_CLK_ENABLE();

	/* USART = 115k-8-N-1 */
	UsartHandle.Instance        = USART1;
	UsartHandle.Init.BaudRate   = 115200;
	UsartHandle.Init.WordLength = USART_WORDLENGTH_8B;
	UsartHandle.Init.StopBits   = USART_STOPBITS_1;
	UsartHandle.Init.Parity     = USART_PARITY_NONE;
	UsartHandle.Init.Mode       = USART_MODE_TX_RX;
	if(HAL_USART_DeInit(&UsartHandle) != HAL_OK)
	{
		Error_Handler();
	}  
	if(HAL_USART_Init(&UsartHandle) != HAL_OK)
	{
		Error_Handler();
	}
}

/*
 * output for tiny printf
 */
void usart_putc(void* p, char c)
{
	while(__HAL_USART_GET_FLAG(&UsartHandle, USART_FLAG_TC) == RESET)
	{
	}
	USART1->TDR = c;
}
