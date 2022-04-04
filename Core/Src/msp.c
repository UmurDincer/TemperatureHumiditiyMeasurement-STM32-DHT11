/*
 * msp.c
 *
 *  Created on: Apr 4, 2022
 *      Author: ASUS
 */

#include"main.h"


void HAL_MspInit(void)
{
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  SCB->SHCSR |= (0x7 << 16); // 0x7 = 111 so 16. 17. and 18. bits are enabled
  // which are MEMFAULTENA, BUSFAULTENA, ,USGFAULTENA

  HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
  HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
  HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  __HAL_RCC_TIM2_CLK_ENABLE(); // enable timer2 clock
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
     GPIO_InitTypeDef gpio_uart2;

     __HAL_RCC_GPIOA_CLK_ENABLE();
     __HAL_RCC_USART2_CLK_ENABLE();

     gpio_uart2.Alternate = GPIO_AF7_USART2;
     gpio_uart2.Mode = GPIO_MODE_AF_PP;
     gpio_uart2.Pull = GPIO_PULLUP;
     gpio_uart2.Pin = GPIO_PIN_2; // Tx

     HAL_GPIO_Init(GPIOA, &gpio_uart2);
}
