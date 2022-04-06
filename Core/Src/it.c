/*
 * it.c
 *
 *  Created on: Apr 4, 2022
 *      Author: Umur Edip Dincer
 */

#include "it.h"

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void EXTI0_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}
