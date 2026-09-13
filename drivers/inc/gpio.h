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

void GPIO_PeriCLKEN(void);
void GPIO_Init(void);
void GPIO_Deinit(void);
void GPIO_Readfrompin(void);
void GPIO_Readfromport(void);
void GPIO_Writetopin(void);
void GPIO_Writetoport(void);
void GPIO_Togglepin(void);

void GPIO_IRQcfg(void);
void GPIO_IRQhandling(void);

typedef struct {
	uint8_t portname;
	uint8_t pinnumber;
	uint8_t pinmode;
	uint8_t oputspeed;
	uint8_t oputmode;
	uint8_t pupdmode;
	uint8_t Altfunc;

}GPIO_CNFG;

typedef struct {
	GPIO_Regdef *pGPIOx; //Holds the baseaddress of port to which the pin belongs
	GPIO_CNFG   pGPIO_pincfg; //Holds <pin config> settings

}GPIO_HANDLE;

#endif /* INC_GPIO_H_ */
