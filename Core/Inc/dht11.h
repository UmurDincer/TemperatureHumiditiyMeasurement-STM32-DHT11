/*
 * dht11.h
 *
 *  Created on: Apr 4, 2022
 *      Author: ASUS
 */

#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#include"main.h"

#define INPUT	0
#define OUTPUT	1

typedef struct{

	GPIO_TypeDef* GPIOx; // configure GPIO port. e.g. GPIOD
	uint16_t Sensor_Pin; //	configure Pin
	uint8_t temperature;
	uint8_t humidity;

}DHT11_HandleTypeDef;


void DHT11_Init(DHT11_HandleTypeDef *dht11);
void set_DHT11_input_output(DHT11_HandleTypeDef *dht11 , uint8_t In_Out);
uint8_t read_DHT11(DHT11_HandleTypeDef*);


#endif /* INC_DHT11_H_ */
