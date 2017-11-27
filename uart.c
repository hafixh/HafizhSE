/*
 * uart.c
 *
 *  Created on: Nov 11, 2017
 *      Author: lenovo
 */
#include "uart.h"
#include "stm32f1xx_hal.h"
UART_HandleTypeDef huart1;
void MX_USART1_UART_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
		__HAL_RCC_USART1_CLK_ENABLE();
		/**USART2 GPIO Configuration
		    PA2     ------> USART2_TX
		    PA3     ------> USART2_RX
		 */
		GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		//GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
}
void print_UART1(uint8_t string[], uint8_t length){
    HAL_UART_Transmit(&huart1, (uint8_t*)string, length, 5);
}

