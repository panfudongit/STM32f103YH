
#ifndef __GPIO_REG_H
#define	__GPIO_REG_H


#include "stm32f10x.h"

// Green PB0

#define GPIOB_BASE_R (0x40010c00)
#define GPIOB_R_CRL *(unsigned int *)(GPIOB_BASE_R + 0x00)
#define GPIOB_R_CRH *(unsigned int *)(GPIOB_BASE_R + 0x04)
#define GPIOB_R_IDR *(unsigned int *)(GPIOB_BASE_R + 0x08)
#define GPIOB_R_ODR *(unsigned int *)(GPIOB_BASE_R + 0x0c)
#define GPIOB_R_BSRR *(unsigned int *)(GPIOB_BASE_R + 0x10)

void GRE_LED(void);
#endif /* __GPIO_REG_H */
