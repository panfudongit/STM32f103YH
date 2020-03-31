/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2020-xx-xx
	* @brief   Conselo the gpio throught to write the reg 
  ******************************************************************************
  */
	
#include "gpio_reg.h"
	
void GRE_LED(void)
{	
	volatile int i = 2048573;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIOB_R_CRL &= ~(0xf << 0);
	GPIOB_R_CRL |= (0x1<< 0);

	GPIOB_R_ODR &= ~(0x1 << 0);
	
//	GPIOB_R_ODR |= (0x1 << 0);
	GPIOB_R_BSRR &= ~(0x1 << 16);
	GPIOB_R_BSRR |= (0x1 << 0);
	for(; i != 0; i--)
		;
	GPIOB_R_BSRR &= ~(0x1 << 0);
	GPIOB_R_BSRR |= (0x1 << 16);	
//	GPIOB_R_ODR &= ~(0x1 << 0);
}
