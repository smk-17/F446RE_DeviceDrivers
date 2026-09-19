/*
 * stm32f446re.h
 *
 *  Created on: 19-Aug-2026
 *      Author: manoj_kumar
 */

#ifndef INC_STM32F446RE_H_
#define INC_STM32F446RE_H_
#include <stdint.h>

//Processor Specific Macros For EXTI lines To nvic

// NVIC reg macros

#define NVIC_ISER_BASE  (volatile uint32_t*)(0xE000E100)
#define NVIC_ICER_BASE  (volatile uint32_t*)(0XE000E180)

#define NVIC_ISER0  (NVIC_ICER_BASE + 0x00) //(0-31)
#define NVIC_ISER1	(NVIC_ICER_BASE + 0x04)
#define NVIC_ISER2	(NVIC_ICER_BASE + 0x08)
#define NVIC_ISER3	(NVIC_ICER_BASE + 0x0C)

#define NVIC_ICER0  (NVIC_ICER_BASE + 0x00) //(0-31)
#define NVIC_ICER1	(NVIC_ICER_BASE + 0x04)
#define NVIC_ICER2	(NVIC_ICER_BASE + 0x08)
#define NVIC_ICER3	(NVIC_ICER_BASE + 0x0C)

#define EXTI_LINE0      (0U)
#define EXTI_LINE1      (1U)
#define EXTI_LINE2      (2U)
#define EXTI_LINE3      (3U)
#define EXTI_LINE4      (4U)

#define EXTI_LINE5      (5U)
#define EXTI_LINE6      (6U)
#define EXTI_LINE7      (7U)
#define EXTI_LINE8      (8U)
#define EXTI_LINE9      (9U)

#define EXTI_LINE10     (10U)
#define EXTI_LINE11     (11U)
#define EXTI_LINE12     (12U)
#define EXTI_LINE13     (13U)
#define EXTI_LINE14     (14U)
#define EXTI_LINE15     (15U)

/*Base address of flash and SRAM and ROM */

#define FLASH_BASEADDR         0x08000000U //or (uint32_t) 0x08000000
#define SRAM1_BASEADDR         0x20000000U
#define SRAM2_BASEADDR         0x2001C000U
#define SRAM SRAM1_BASEADDR
#define ROM                    0x1FFF0000U

/* base address of AHB AND APB peripherals */

#define PERIPHERAL_BASE    0x40000000U
#define AHB1_BASEADDR      0x40020000U
#define AHB2_BASEADDR      0x50000000U
#define AHB3_BASEADDR      0xA0001000U
#define APB1_BASEADDR      PERIPHERAL_BASE  //Address of peripheral starts from APB1 only
#define APB2_BASEADDR      0x40010000U

/* Base address of all the AHB1 pheripheral*/

#define RCC_BASEADDR     (AHB1_BASEADDR +0x3800)
#define DMA1_BASEADDR    (AHB1_BASEADDR +0x6000)
#define DMA2_BASEADDR    (AHB1_BASEADDR +0x6400)

/* base address of APB1 */

#define TIM2_BASEADDR    (APB1_BASEADDR+0x0000)
#define I2C1_BASEADDR    (APB1_BASEADDR+0x5400)
#define UART4_BASEADDR   (APB1_BASEADDR+0x4C00)
#define USART2_BASEADDR  (APB1_BASEADDR+0x4400)
#define CAN1_BASEADDR    (APB1_BASEADDR+0x6400)
#define DAC_BASEADDR     (APB1_BASEADDR+0x7400)
#define IDWG_BASEADDR    (APB1_BASEADDR+0x3000)
#define WWDG_BASEADDR    (APB1_BASEADDR+0x2C00)
#define RTC_BASEADDR     (APB1_BASEADDR+0x2800)

/* base address of APB2 */
#define SPI1_BASEADDR     (APB2_BASEADDR+0x3000)
#define ADC1_BASEADDR     (APB2_BASEADDR+0x2000)
#define EXTI_BASEADDR     (APB2_BASEADDR+0x3C00)
#define SYSCFG_BASEADDR   (APB2_BASEADDR+0x3800)


/* GPIOx struct*/

typedef struct {
	volatile uint32_t GPIO_MODER;   //00-ip 01-op 11-analog 10-Alternate fnc
	volatile uint32_t GPIO_OTYPER;  //0-push-pull //1-open drain
	volatile uint32_t GPIO_OSPEEDR; //00-low 10-High 01-very high 11-reserved (Slew rate i.e Rise and fall time)
	volatile uint32_t GPIO_PUPDR;   //00-nothing 10-pull down 01-pullup 11-reserved
	volatile uint32_t GPIO_IDR;     //input read by hardware
	volatile uint32_t GPIO_ODR;     // output to be driven
	volatile uint32_t GPIO_BSSR;    //set and reset the bit of a Reg
	volatile uint32_t GPIO_LCKR;    //prevents accidental config during runtime
	volatile uint32_t GPIO_AFR[2];	//AFR[0]:Alternate func reg for Pin 0-7 and AFR[1]:pin 8-15

}GPIO_RegDef;

/* Base addresses of ports  Every GPIO lies on AHB1 bus and every port has 16 pins and consume 40 bytes
    (4bytes per reg * 10 reg) per port remaining goes in padding and stuff */
#define GPIOA_BASEADDR     (AHB1_BASEADDR + 0x0000U)
#define GPIOB_BASEADDR     (AHB1_BASEADDR + 0x0400U)
#define GPIOC_BASEADDR     (AHB1_BASEADDR + 0x0800U)
#define GPIOD_BASEADDR     (AHB1_BASEADDR + 0x0C00U)
#define GPIOE_BASEADDR     (AHB1_BASEADDR + 0x1000U)
#define GPIOF_BASEADDR     (AHB1_BASEADDR + 0x1400U)
#define GPIOG_BASEADDR     (AHB1_BASEADDR + 0x1800U)
#define GPIOH_BASEADDR     (AHB1_BASEADDR + 0x1C00U)

/* Peripheral Base Addresses cast directly to Struct Pointers */
#define GPIOA              ((GPIO_RegDef *)GPIOA_BASEADDR)
#define GPIOB              ((GPIO_RegDef *)GPIOB_BASEADDR)
#define GPIOC              ((GPIO_RegDef *)GPIOC_BASEADDR)
#define GPIOD              ((GPIO_RegDef *)GPIOD_BASEADDR)
#define GPIOE              ((GPIO_RegDef *)GPIOE_BASEADDR)
#define GPIOF              ((GPIO_RegDef *)GPIOF_BASEADDR)
#define GPIOG              ((GPIO_RegDef *)GPIOG_BASEADDR)
#define GPIOH              ((GPIO_RegDef *)GPIOH_BASEADDR)

typedef struct {
    volatile uint32_t CR;         /* 0x00: RCC clock control register */
    volatile uint32_t PLLCFGR;    /* 0x04: RCC PLL configuration register */
    volatile uint32_t CFGR;       /* 0x08: RCC clock configuration register */
    volatile uint32_t CIR;        /* 0x0C: RCC clock interrupt register */
    volatile uint32_t AHB1RSTR;   /* 0x10: RCC AHB1 peripheral reset register */
    volatile uint32_t AHB2RSTR;   /* 0x14: RCC AHB2 peripheral reset register */
    volatile uint32_t AHB3RSTR;   /* 0x18: RCC AHB3 peripheral reset register */
    uint32_t RESERVED0;           /* 0x1C: Reserved padding */
    volatile uint32_t APB1RSTR;   /* 0x20: RCC APB1 peripheral reset register */
    volatile uint32_t APB2RSTR;   /* 0x24: RCC APB2 peripheral reset register */
    uint32_t RESERVED1[2];        /* 0x28 - 0x2C: Reserved padding */
    volatile uint32_t AHB1ENR;    /* 0x30: RCC AHB1 peripheral clock enable register */
    volatile uint32_t AHB2ENR;    /* 0x34: RCC AHB2 peripheral clock enable register */
    volatile uint32_t AHB3ENR;    /* 0x38: RCC AHB3 peripheral clock enable register */
    uint32_t RESERVED2;           /* 0x3C: Reserved padding */
    volatile uint32_t APB1ENR;    /* 0x40: RCC APB1 peripheral clock enable register */
    volatile uint32_t APB2ENR;    /* 0x44: RCC APB2 peripheral clock enable register */
    uint32_t RESERVED3[2];        /* 0x48 - 0x4C: Reserved padding */
    volatile uint32_t AHB1LPENR;  /* 0x50: RCC AHB1 peripheral clock enable in low power mode register */
    volatile uint32_t AHB2LPENR;  /* 0x54: RCC AHB2 peripheral clock enable in low power mode register */
    volatile uint32_t AHB3LPENR;  /* 0x58: RCC AHB3 peripheral clock enable in low power mode register */
    uint32_t RESERVED4;           /* 0x5C: Reserved padding */
    volatile uint32_t APB1LPENR;  /* 0x60: RCC APB1 peripheral clock enable in low power mode register */
    volatile uint32_t APB2LPENR;  /* 0x66: RCC APB2 peripheral clock enable in low power mode register */
    uint32_t RESERVED5[2];        /* 0x68 - 0x6C: Reserved padding */
    volatile uint32_t BDCR;       /* 0x70: RCC Backup domain control register */
    volatile uint32_t CSR;        /* 0x74: RCC clock control & status register */
    uint32_t RESERVED6[2];        /* 0x78 - 0x7C: Reserved padding */
    volatile uint32_t SSCGR;      /* 0x80: RCC spread spectrum clock generation register */
    volatile uint32_t PLLI2SCFGR;  /* 0x84: RCC PLLI2S configuration register */
    volatile uint32_t PLLSAICFGR;  /* 0x88: RCC PLLSAI configuration register */
    volatile uint32_t DCKCFGR;    /* 0x8C: RCC Dedicated Clocks Configuration Register */
} RCC_TypeDef;

#define RCC                ((RCC_TypeDef *)RCC_BASEADDR)


#define GPIOA_CLKEN()   RCC->AHB1ENR |= (1<<0)
#define GPIOB_CLKEN()   RCC->AHB1ENR |= (1<<1)
#define GPIOC_CLKEN()   RCC->AHB1ENR |= (1<<2)
#define GPIOD_CLKEN()   RCC->AHB1ENR |= (1<<3)
#define GPIOE_CLKEN()   RCC->AHB1ENR |= (1<<4)
#define GPIOF_CLKEN()   RCC->AHB1ENR |= (1<<5)
#define GPIOG_CLKEN()   RCC->AHB1ENR |= (1<<6)
#define GPIOH_CLKEN()   RCC->AHB1ENR |= (1<<7)


#define I2C1_CLKEN()    RCC->APB1ENR |= (1<<21)
#define SPI1_CLKEN()    RCC->APB2ENR |= (1<<12)
#define USART1_CLKEN()  RCC->APB2ENR |= (1<<4)
#define UART4_CLKEN()   RCC->APB1ENR |= (1<<19)

#define GPIOA_CLKD()   RCC->AHB1ENR &= ~(1<<0)
#define GPIOB_CLKD()   RCC->AHB1ENR &= ~(1<<1)
#define GPIOC_CLKD()   RCC->AHB1ENR &= ~(1<<2)
#define GPIOD_CLKD()   RCC->AHB1ENR &= ~(1<<3)
#define GPIOE_CLKD()   RCC->AHB1ENR &= ~(1<<4)
#define GPIOF_CLKD()   RCC->AHB1ENR &= ~(1<<5)
#define GPIOG_CLKD()   RCC->AHB1ENR &= ~(1<<6)
#define GPIOH_CLKD()   RCC->AHB1ENR &= ~(1<<7)


#define I2C1_CLKD()    RCC->APB1ENR &= ~(1<<21)
#define SPI1_CLKD()    RCC->APB2ENR &= ~(1<<12)
#define USART1_CLKD()  RCC->APB2ENR &= ~(1<<4)
#define UART4_CLKD()   RCC->APB1ENR &= ~(1<<19)

#define SYSCLKCFG()   RCC->APB2ENR |= (1<<14)
#define SYSCLKCFGD()  RCC->APB2ENR &= ~(1<<14)


/* GenricMacros*/

#define ENABLE  1
#define DISABLE 0

#define SET   ENABLE
#define RESET DISABLE

#define GPIO_PIN_SET    SET
#define GPIO_PIN_RESET  RESET

#define GPIO_IMODE   0
#define GPIO_OMODE   1
#define GPIO_ALTMODE 2
#define GPIO_AMODE   3

#define GPIO_IT_RT      4
#define GPIO_IT_FT      5
#define GPIO_IT_RFT     6

#define GPIO_OUTTYP_PP   0
#define GPIO_OUTTYP_OD   1

#define GPIO_OSPEED_LOW     0
#define GPIO_OSPEED_MEDIUM  1
#define GPIO_OSPEED_FAST    2
#define GPIO_OSPEED_HIGH    3

#define GPIO_NO_PHPL   0
#define GPIO_PIN_PULLUP    1
#define GPIO_PIN_PULLDOWN  2

#define GPIO_PIN_NO_0   0
#define GPIO_PIN_NO_1   1
#define GPIO_PIN_NO_2   2
#define GPIO_PIN_NO_3   3
#define GPIO_PIN_NO_4   4
#define GPIO_PIN_NO_5   5
#define GPIO_PIN_NO_6   6
#define GPIO_PIN_NO_7   7
#define GPIO_PIN_NO_8   8
#define GPIO_PIN_NO_9   9
#define GPIO_PIN_NO_10  10
#define GPIO_PIN_NO_11  11
#define GPIO_PIN_NO_12  12
#define GPIO_PIN_NO_13  13
#define GPIO_PIN_NO_14  14
#define GPIO_PIN_NO_15  15

//GPIO port Reset

#define GPIOA_Reset()   do {RCC->AHB1RSTR |= (1<<0); RCC->AHB1RSTR &= ~(1<<0);} while(0)
#define GPIOB_Reset()   do {RCC->AHB1RSTR |= (1<<1); RCC->AHB1RSTR &= ~(1<<1);} while(0)
#define GPIOC_Reset()	do {RCC->AHB1RSTR |= (1<<2); RCC->AHB1RSTR &= ~(1<<2);} while(0)
#define GPIOD_Reset()   do {RCC->AHB1RSTR |= (1<<3); RCC->AHB1RSTR &= ~(1<<3);} while(0)
#define GPIOE_Reset()   do {RCC->AHB1RSTR |= (1<<4); RCC->AHB1RSTR &= ~(1<<4);} while(0)
#define GPIOF_Reset()   do {RCC->AHB1RSTR |= (1<<5); RCC->AHB1RSTR &= ~(1<<5);} while(0)
#define GPIOG_Reset()   do {RCC->AHB1RSTR |= (1<<6); RCC->AHB1RSTR &= ~(1<<6);} while(0)
#define GPIOH_Reset()   do {RCC->AHB1RSTR |= (1<<7); RCC->AHB1RSTR &= ~(1<<7);} while(0)

//EXTI PORT LEVELS


typedef struct{

	volatile uint32_t IMR;  //Offset - 0x00
	volatile uint32_t FMR;  //04
	volatile uint32_t RTSR;   //08
	volatile uint32_t FTSR;   //0c
	volatile uint32_t SWIER;   //10
	volatile uint32_t PR;    //14

}EXTI_RegDef;

#define EXTI ((EXTI_RegDef*)EXTI_BASEADDR)

//SYScFG Peripherals

#define SYSCFG_Peri_CLKEN()   RCC->APB2ENR |= (1<< 14)

typedef struct {

	volatile uint32_t SYSCFG_MEMRMP;
	volatile uint32_t SYSCFG_PMC;
	volatile uint32_t SYSCFG_EXTICR[4];
	uint32_t RESERVED1[2];
	volatile uint32_t SYSCFG_CMPCR;
	uint32_t RESERVED2[2];
	volatile uint32_t SYSCFG_CFGR;

}SYSCFG_RegDef;

#define SYSCFG   ((SYSCFG_RegDef*)SYSCFG_BASEADDR)

#define  GPIO_BASEADDR_TO_CODE(x)                   (x==GPIOA)?0 :\
			                                        (x==GPIOB)?1 :\
			                                        (x==GPIOC)?2 :\
			                                        (x==GPIOD)?3 :\
			                                        (x==GPIOE)?4 :\
			                                        (x==GPIOF)?5 :\
							                    	(x==GPIOG)?6 :\
							                    	(x==GPIOH)?7 :0

#endif /* INC_STM32F446RE_H_ */

