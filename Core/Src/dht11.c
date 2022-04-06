/*
 * dht11.c
 *
 *  Created on: Apr 4, 2022
 *      Author: ASUS
 */

#include"dht11.h"

GPIO_InitTypeDef gpio_dht11;
TIM_HandleTypeDef tim2;
extern DHT11_HandleTypeDef dht11;

void delay_ms_us(uint8_t milisec_or_microsec, uint16_t duration)
{

	if(milisec_or_microsec == microsec){
		__HAL_TIM_SET_COUNTER(&tim2, 0);
		while(__HAL_TIM_GET_COUNTER(&tim2) <  duration);
	}
	else if(milisec_or_microsec == milisec){
		for(uint16_t i = 0; i < duration; i++){
			__HAL_TIM_SET_COUNTER(&tim2, 0);
			while(__HAL_TIM_GET_COUNTER(&tim2) < 1000);
		}
	}
}




void DHT11_Init(DHT11_HandleTypeDef *dht11)
{
	__HAL_RCC_GPIOD_CLK_ENABLE();
	gpio_dht11.Pin = dht11->Sensor_Pin;
	gpio_dht11.Pull = GPIO_NOPULL;
	gpio_dht11.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(dht11->GPIOx, &gpio_dht11);

	__HAL_RCC_TIM2_CLK_ENABLE();
	tim2.Instance = TIM2;
	tim2.Init.Prescaler = 84 - 1; // 1us
	tim2.Init.Period = 0xffff - 1; //1us each tick
	tim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	tim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	tim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	if(HAL_TIM_Base_Init(&tim2) != HAL_OK){
		Error_Handler();
	}

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

uint8_t read_DHT11(DHT11_HandleTypeDef* dht11)
{
	uint8_t data[5] = {0x00, 0x00, 0x00, 0x00, 0x00}; //integ_rh, dec_rh, integ_temp, dec_temp, check_sum
	uint8_t i, j, check_time;
	HAL_TIM_Base_Start(&tim2);
	//Generate start condition
	set_DHT11_input_output(dht11, OUTPUT);
	HAL_GPIO_WritePin(dht11->GPIOx, dht11->Sensor_Pin, RESET);

	delay_ms_us(milisec, 20); // should wait at least 18ms

	HAL_GPIO_WritePin(dht11->GPIOx, dht11->Sensor_Pin, SET);
	delay_ms_us(microsec, 40); // should wait 20-40 us for DHT's response
	//End start condition

	set_DHT11_input_output(dht11, INPUT); // config input mode to take data

	__HAL_TIM_SET_COUNTER(&tim2, 0);
	while(!HAL_GPIO_ReadPin(dht11->GPIOx, dht11->Sensor_Pin)){	// send out a low-voltage-level response signal, which lasts min 80us
		if(__HAL_TIM_GET_COUNTER(&tim2) > 80)
			return 1;
	}
	__HAL_TIM_SET_COUNTER(&tim2, 0);
	while(HAL_GPIO_ReadPin(dht11->GPIOx, dht11->Sensor_Pin)){ //voltage level from low to high and keeps it for min 80us
		if(__HAL_TIM_GET_COUNTER(&tim2) > 100)
				return 1;
		}


	for(i = 0; i < 5; ++i){
		for(j = 0; j < 8; ++j){

			//every bit of data begins with the 50us low-voltage-level
			while(!HAL_GPIO_ReadPin(dht11->GPIOx, dht11->Sensor_Pin));

			// if HIGH for 26-28us means 0 and 70us means 1
			__HAL_TIM_SET_COUNTER(&tim2, 0);

			while(HAL_GPIO_ReadPin(dht11->GPIOx, dht11->Sensor_Pin));

			check_time = __HAL_TIM_GET_COUNTER(&tim2);

			data[i] = data[i] << 1;

			if(check_time > 30){
				data[i] = data[i] + 1;
			}
		}
	}

	//check sum
	if(data[4] != data[0] + data[1] + data[2] + data[3])
		return 1;

	dht11->humidity = data[0];
	dht11->temperature = data[2];
	HAL_TIM_Base_Stop(&tim2);
	return SUCCESS;


}
