/*
 * gpio.h
 *
 *  Created on: 21-Aug-2026
 *      Author: manoj_kumar
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "stm32f446re.h"
#include <stdint.h>

typedef struct {
	uint8_t portName;
	uint8_t pinNumber;
	uint8_t pinMode;
	uint8_t oputSpeed;
	uint8_t oputMode;
	uint8_t pupdMode;
	uint8_t AltfuncMode;

}GPIO_CNFG;

typedef struct {
	GPIO_RegDef *pGPIOx; //Holds the baseaddress of port to which the pin belongs
	GPIO_CNFG GPIO_pincfg; //Holds <pin config> settings

}GPIO_HANDLE;


void GPIO_PeriCLKEN(GPIO_RegDef* pGPIOx , uint8_t EnorDi );
void GPIO_Init(GPIO_HANDLE* pGPIOx);
void GPIO_DeInit(GPIO_RegDef* pGPIOx);

uint8_t GPIO_Readfrompin(GPIO_RegDef* pGPIOx , uint8_t pinNumber);
uint16_t GPIO_Readfromport(GPIO_RegDef* pGPIOx);
void GPIO_Writetopin(GPIO_RegDef* pGPIOx , uint8_t pinNumber , uint8_t Value);
void GPIO_Writetoport(GPIO_RegDef* pGPIOx , uint16_t Value);
void GPIO_Togglepin(GPIO_RegDef* pGPIOx , uint8_t pinNumber);

void GPIO_IRQcfg(uint8_t IRQpinNumber, uint8_t IRQpriority ,uint8_t EnorDi);
void GPIO_IRQhandling(uint8_t IRQpinNumber);



#endif /* INC_GPIO_H_ */
