
#ifndef __USART_API_H
#define __USART_API_H
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include <stdio.h>
#define  USART1_BAUDRATE           115200

void USART1_SendByte(USART_TypeDef* USARTx, uint8_t ch);
void USART_Config(void);
void TEST_DMA1_C4_Usart1(void);
#endif /*__USART_API_H*/
