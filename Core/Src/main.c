/*
 * main.c
 *
 *  Created on: Apr 4, 2022
 *      Author: ASUS
 */

#include"main.h"


void Error_Handler(void);
void SystemClockConfig(void);
void GPIO_Config(void);
void USART_Config(void);


int main()
{
	HAL_Init();


	while(1);

}


void GPIO_Config(void)
{
	GPIO_InitTypeDef button;

	button.Mode = GPIO_MODE_IT_FALLING;
	button.Pin = GPIO_PIN_0;
	button.Pull = GPIO_NOPULL;
	button.Speed = GPIO_SPEED_FAST;

	HAL_GPIO_Init(GPIOA, &button);

	HAL_NVIC_SetPriority(EXTI0_IRQn, 15, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}


void USART_Config(void)
{
	UART_HandleTypeDef uart2;

	uart2.Instance = USART2;
	uart2.Init.BaudRate = 9600;
	uart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart2.Init.Mode = UART_MODE_TX_RX;
	uart2.Init.WordLength = UART_WORDLENGTH_8B;
	uart2.Init.Parity = UART_PARITY_NONE;
	uart2.Init.StopBits = UART_STOPBITS_1;

	if(HAL_UART_Init(&uart2) != HAL_OK){
		Error_Handler();
	}
}

void SystemClockConfig(void)
{
	RCC_OscInitTypeDef osc;
	RCC_ClkInitTypeDef clk;

	osc.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc.HSEState = RCC_HSE_ON;
	osc.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	osc.PLL.PLLState = RCC_PLL_ON;
	osc.PLL.PLLM = 8; 		//
	osc.PLL.PLLN = 336;		// for max clock = 168MHz, APB1 Clk = 42MhHz, APB2 Clk = 84MHz
	osc.PLL.PLLP = 2;		//

	if(HAL_RCC_OscConfig(&osc) != HAL_OK){
		Error_Handler();
	}

	clk.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK ;
	clk.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK \
					| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clk.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clk.APB1CLKDivider = RCC_HCLK_DIV4;
	clk.APB2CLKDivider = RCC_HCLK_DIV2;

	if(HAL_RCC_ClockConfig(&clk, FLASH_ACR_LATENCY_5WS) != HAL_OK){	// 5 WS (6 CPU cycles) 150 < HCLK ≤ 168
		Error_Handler();
	}
}

void Error_Handler(void)
{
	while(1);
}
