/*
 * dht11.c
 *
 *  Created on: Apr 4, 2022
 *      Author: ASUS
 */

#include"dht11.h"

GPIO_InitTypeDef gpio_dht11;

void DHT11_Init(DHT11_HandleTypeDef *dht11)
{
	gpio_dht11.Pin = dht11->Sensor_Pin;
	gpio_dht11.Pull = GPIO_NOPULL;
	gpio_dht11.Speed = GPIO_SPEED_FAST;

	HAL_GPIO_Init(dht11->GPIOx, &gpio_dht11);
}

void set_DHT11_input_output(DHT11_HandleTypeDef *dht11 , uint8_t In_Out)
{
	if(In_Out == INPUT){
		gpio_dht11.Mode = GPIO_MODE_INPUT;
		HAL_GPIO_Init(dht11->GPIOx, &gpio_dht11);
	}
	else if(In_Out == OUTPUT){
		gpio_dht11.Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(dht11->GPIOx, &gpio_dht11);
	}


}
