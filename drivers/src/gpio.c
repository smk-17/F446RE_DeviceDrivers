/*
 * gpio.c
 *
 *  Created on: 21-Aug-2026
 *      Author: manoj_kumar
 */

#include "gpio.h"
#include "stm32f446re.h"
/* ----------------------------------------------------
 * @fn - GPIO_PeriCLKEN()
 *
 * @brief  To EnableOrDisable Clk fro specific GPIO Port using Macros
 *
 * @Parameters -
 * @p1 - GPIO_RegDef *pGPIOx (Base address of Reg)
 * @p2 - Enable or Disable Macros
 *
 * @return - none
 *
 * @NeedOfApi- Enable or Disable Clk of a specific GPIO port in need
 *
--------------------------------------------*/

void GPIO_PeriCLKEN(GPIO_RegDef* pGPIOx , uint8_t EnorDi ){

if (EnorDi == ENABLE){

	if (pGPIOx == GPIOA){
		GPIOA_CLKEN();
	}
	else if (pGPIOx == GPIOB){
		GPIOB_CLKEN();
	}
	else if (pGPIOx == GPIOC){
			GPIOC_CLKEN();
		}
	else if (pGPIOx == GPIOD){
			GPIOD_CLKEN();
		}
	else if (pGPIOx == GPIOE){
			GPIOE_CLKEN();
		}
	else if (pGPIOx == GPIOF){
			GPIOF_CLKEN();
		}
	else if (pGPIOx == GPIOG){
			GPIOG_CLKEN();
		}
	else if (pGPIOx == GPIOH){
			GPIOH_CLKEN();
		}
}

 else if (EnorDi == DISABLE){

	if (pGPIOx == GPIOA){
		GPIOA_CLKD();
	}
	else if (pGPIOx == GPIOB){
		GPIOB_CLKD();
	}
	else if (pGPIOx == GPIOC){
			GPIOC_CLKD();
		}
	else if (pGPIOx == GPIOD){
			GPIOD_CLKD();
		}
	else if (pGPIOx == GPIOE){
			GPIOE_CLKD();
		}
	else if (pGPIOx == GPIOF){
			GPIOF_CLKD();
		}
	else if (pGPIOx == GPIOG){
			GPIOG_CLKD();
		}
	else if (pGPIOx == GPIOH){
			GPIOH_CLKD();
		}
}
}


/* ----------------------------------------------------
 * @fn - GPIO_Init()
 *
 * @brief - Initialise the Specific GPIO port and the Gpio reg with Default values
 *
 * @Parameters -
 * @p1 - GPIO_RegDef *pGPIOx (Base address of Reg)
 * @p2 - none
 *
 * @return - none
 *
 * @NeedOfApi-
 *
 *
 *
--------------------------------------------*/

void GPIO_Init(GPIO_HANDLE* pGPIOxHandle){

//Configuring the Mode
	uint32_t temp =0;
	if (pGPIOxHandle->GPIO_pincfg.pinMode <= GPIO_AMODE){

		//Non Interrupt mode
		temp = (pGPIOxHandle->GPIO_pincfg.pinMode << (2*pGPIOxHandle->GPIO_pincfg.pinNumber));

		pGPIOxHandle->pGPIOx->GPIO_MODER &= ~(0x03 << 2*pGPIOxHandle->GPIO_pincfg.pinNumber);
		pGPIOxHandle->pGPIOx->GPIO_MODER |= temp;
	}

	else {

		//interrupt Mode
		if (pGPIOxHandle->GPIO_pincfg.pinMode == GPIO_IT_FT){

			//Enable the Corresponding EXTI line according to No of Gpio
			EXTI->FTSR |= (1 << pGPIOxHandle->GPIO_pincfg.pinNumber);
			EXTI->RTSR &= ~(1<< pGPIOxHandle->GPIO_pincfg.pinNumber);

		}
		else if(pGPIOxHandle->GPIO_pincfg.pinMode == GPIO_IT_RT){

			EXTI->RTSR |= (1 << pGPIOxHandle->GPIO_pincfg.pinNumber);
		    EXTI->FTSR &= ~(1<< pGPIOxHandle->GPIO_pincfg.pinNumber);

		}
		else if(pGPIOxHandle->GPIO_pincfg.pinMode == GPIO_IT_RFT){

			EXTI->FTSR |= (1 << pGPIOxHandle->GPIO_pincfg.pinNumber);
			EXTI->RTSR |= (1<< pGPIOxHandle->GPIO_pincfg.pinNumber);

		}


		//Config SYSCFG_EXTI CTR REG
        SYSCFG_Peri_CLKEN();
        uint8_t temp1,temp2;

        temp1 = pGPIOxHandle->GPIO_pincfg.pinNumber / 4;
        temp2 = pGPIOxHandle->GPIO_pincfg.pinNumber % 4;
        uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOxHandle->pGPIOx);

        SYSCFG->SYSCFG_EXTICR[temp1] = portcode << (temp2 * 4);


		//Enable the IRQ
		EXTI->IMR |= (1<< pGPIOxHandle->GPIO_pincfg.pinNumber);
	}

//Configure Speed

	temp =0;
	temp = pGPIOxHandle->GPIO_pincfg.oputSpeed << (2*(pGPIOxHandle->GPIO_pincfg.pinNumber));

	pGPIOxHandle->pGPIOx->GPIO_OSPEEDR &= ~(0x03 << 2* pGPIOxHandle->GPIO_pincfg.pinNumber);
	pGPIOxHandle->pGPIOx->GPIO_OSPEEDR |= temp;

// Configure Output type

	   temp =0;
	   temp = pGPIOxHandle->GPIO_pincfg.oputMode << (pGPIOxHandle->GPIO_pincfg.pinNumber);

	   pGPIOxHandle->pGPIOx->GPIO_OTYPER &= ~(0x01 << pGPIOxHandle->GPIO_pincfg.pinNumber);
	   pGPIOxHandle->pGPIOx->GPIO_OTYPER |= temp;

// Congiguring the PushpullType

	   temp =0;
	   temp = pGPIOxHandle->GPIO_pincfg.pupdMode << (2*(pGPIOxHandle->GPIO_pincfg.pinNumber));

	   pGPIOxHandle->pGPIOx->GPIO_PUPDR &= ~(0x03 << 2*pGPIOxHandle->GPIO_pincfg.pinNumber);
       pGPIOxHandle->pGPIOx->GPIO_PUPDR |= temp;

// Confguring the AltFunction Reg


       if (pGPIOxHandle->GPIO_pincfg.pinMode == GPIO_ALTMODE){

    	   uint8_t temp1 ,temp2;

    	   temp =0;
    	   temp1 = pGPIOxHandle->GPIO_pincfg.pinNumber / 8;
    	   temp2 = pGPIOxHandle->GPIO_pincfg.pinNumber % 8;

    	   pGPIOxHandle->pGPIOx->GPIO_AFR[temp1] &= ~(0x0F << (4*temp2));
		   pGPIOxHandle->pGPIOx->GPIO_AFR[temp1] |= (pGPIOxHandle->GPIO_pincfg.AltfuncMode << 4*temp2);

}
}



/* ----------------------------------------------------
 * @fn - GPIO_DeInit()
 *
 * @brief -
 *
 * @Parameters -
 * @p1 - GPIO_RegDef *pGPIOx (Base address of Reg)
 * @p2 - Enable or Disable Macros
 *
 * @return - none
 *
 * @NeedOfApi-
 *
 *
 *
--------------------------------------------*/

void GPIO_DeInit(GPIO_RegDef* pGPIOx){

	if (pGPIOx == GPIOA){
			GPIOA_Reset();
		}
		else if (pGPIOx == GPIOB){
			GPIOB_Reset();
		}
		else if (pGPIOx == GPIOC){
				GPIOC_Reset();
			}
		else if (pGPIOx == GPIOD){
				GPIOD_Reset();
			}
		else if (pGPIOx == GPIOE){
				GPIOE_Reset();
			}
		else if (pGPIOx == GPIOF){
				GPIOF_Reset();
			}
		else if (pGPIOx == GPIOG){
				GPIOG_Reset();
			}
		else if (pGPIOx == GPIOH){
				GPIOH_Reset();
			}

}
/* ----------------------------------------------------
 * @fn - GPIO_PeriCLKEN()
 *
 * @brief -
 *
 * @Parameters -
 * @p1 - GPIO_RegDef *pGPIOx (Base address of Reg)
 * @p2 - Enable or Disable Macros
 *
 * @return - none
 *
 * @NeedOfApi-
 *
 *
 *
--------------------------------------------*/

uint8_t GPIO_Readfrompin(GPIO_RegDef* pGPIOx , uint8_t pinNumber){

	uint8_t value=0;
	value = (uint8_t)(( pGPIOx->GPIO_IDR >> pinNumber)  & 0x00000001);
	return value;
}

/* ----------------------------------------------------
 * @fn - GPIO_PeriCLKEN()
 *
 * @brief -
 *
 * @Parameters -
 * @p1 - GPIO_RegDef *pGPIOx (Base address of Reg)
 * @p2 - Enable or Disable Macros
 *
 * @return - none
 *
 * @NeedOfApi-
 *
 *
 *
--------------------------------------------*/

uint16_t GPIO_Readfromport(GPIO_RegDef* pGPIOx){

	    uint16_t value=0;
		value = (uint16_t)( pGPIOx->GPIO_IDR);
		return value;

}

/* ----------------------------------------------------
 * @fn - GPIO_PeriCLKEN()
 *
 * @brief -
 *
 * @Parameters -
 * @p1 - GPIO_RegDef *pGPIOx (Base address of Reg)
 * @p2 - Enable or Disable Macros
 *
 * @return - none
 *
 * @NeedOfApi-
 *
 *
 *
--------------------------------------------*/

void GPIO_Writetopin(GPIO_RegDef* pGPIOx , uint8_t pinNumber , uint8_t Value){

	if (Value == GPIO_PIN_SET){
		pGPIOx->GPIO_ODR |= (1<< pinNumber);
	}

	else {
		pGPIOx->GPIO_ODR &= ~(1<< pinNumber);
	}
}

/* ----------------------------------------------------
 * @fn - GPIO_PeriCLKEN()
 *
 * @brief -
 *
 * @Parameters -
 * @p1 - GPIO_RegDef *pGPIOx (Base address of Reg)
 * @p2 - Enable or Disable Macros
 *
 * @return - none
 *
 * @NeedOfApi-
 *
 *
 *
--------------------------------------------*/

void GPIO_Writetoport(GPIO_RegDef* pGPIOx , uint16_t Value){

   pGPIOx->GPIO_ODR = Value;
}

/* ----------------------------------------------------
 * @fn - GPIO_PeriCLKEN()
 *
 * @brief -
 *
 * @Parameters -
 * @p1 - GPIO_RegDef *pGPIOx (Base address of Reg)
 * @p2 - Enable or Disable Macros
 *
 * @return - none
 *
 * @NeedOfApi-
 *
 *
 *
--------------------------------------------*/

void GPIO_Togglepin(GPIO_RegDef* pGPIOx , uint8_t pinNumber){

	pGPIOx->GPIO_ODR ^= (1<< pinNumber);

}

/* ----------------------------------------------------
 * @fn - GPIO_PeriCLKEN()
 *
 * @brief -
 *
 * @Parameters -
 * @p1 - GPIO_RegDef *pGPIOx (Base address of Reg)
 * @p2 - Enable or Disable Macros
 *
 * @return - none
 *
 * @NeedOfApi-
 *
 *
 *
--------------------------------------------*/

void GPIO_IRQcfg(uint8_t IRQpinNumber, uint8_t IRQpriority ,uint8_t EnorDi){

if (EnorDi == ENABLE){

	if (IRQpinNumber <= 31){

		*(NVIC_ISER0) |= (1 << IRQpinNumber);

	}
	if (IRQpinNumber > 31 && IRQpinNumber <= 63){

		*(NVIC_ISER1) |= (1 << (IRQpinNumber %32));

	}
	if (IRQpinNumber > 64 && IRQpinNumber <= 95 ){

		*(NVIC_ISER2) |= (1 << (IRQpinNumber %64));


	}
}

else {

	if (IRQpinNumber <= 31){

		*(NVIC_ICER0) &= ~(1 << IRQpinNumber);
		}
		if (IRQpinNumber > 31 && IRQpinNumber < 63){

		*(NVIC_ICER1) &= ~(1 << (IRQpinNumber % 32));
		}
		if (IRQpinNumber > 64 && IRQpinNumber <95 ){

		*(NVIC_ICER2) &= ~(1 << (IRQpinNumber % 64));
		}

}

}

/* ----------------------------------------------------
 * @fn - GPIO_PeriCLKEN()
 *
 * @brief -
 *
 * @Parameters -
 * @p1 - GPIO_RegDef *pGPIOx (Base address of Reg)
 * @p2 - Enable or Disable Macros
 *
 * @return - none
 *
 * @NeedOfApi-
 *
 *
 *
--------------------------------------------*/

void GPIO_IRQhandling(uint8_t IRQpinNumber){



}




