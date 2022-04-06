/*
 * dht11.h
 *
 *  Created on: Apr 4, 2022
 *      Author: Umur Edip Dincer
 */

#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#include"main.h"

#define INPUT	0
#define OUTPUT	1
#define milisec 0
#define microsec 1

typedef struct{

	GPIO_TypeDef* GPIOx; // configure GPIO port. e.g. GPIOD
	uint16_t Sensor_Pin; //	configure Pin
	float temperature;
	float humidity;

}DHT11_HandleTypeDef;


void DHT11_Init(DHT11_HandleTypeDef *dht11);
void set_DHT11_input_output(DHT11_HandleTypeDef *dht11 , uint8_t In_Out);
uint8_t read_DHT11(DHT11_HandleTypeDef *dht11);
void delay_ms_us(uint8_t milisec_or_microsec, uint16_t duration);

#endif /* INC_DHT11_H_ */
