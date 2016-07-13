#ifndef _LED_H_
#define	_LED_H_

#include "stm32f4xx.h"

#define  LED0_ON	  	GPIO_SetBits(GPIOB,GPIO_Pin_9)
#define	 LED0_OFF	    GPIO_ResetBits(GPIOB,GPIO_Pin_9)

//#define LED1_OFF         ANO_GPIO_LED->BSRRL = ANO_Pin_LED1   //H
//#define LED1_ON          ANO_GPIO_LED->BSRRH = ANO_Pin_LED1		//L

/***************LED GPIO∂®“Â******************/
//#define ANO_RCC_LED			RCC_AHB1Periph_GPIOE
//#define ANO_GPIO_LED		GPIOE
//#define ANO_Pin_LED1		GPIO_Pin_3
/*********************************************/

void LED_Init(void);
void LED_Duty(void);

void LED_MPU_Err(void);
void LED_Mag_Err(void);

#endif

