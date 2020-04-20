
#ifndef __RCC_API_H

#include "stm32f10x_rcc.h"
#include "stm32f10x_flash.h"
#include "stm32f10x.h"

void HES_SetSysClock(uint32_t pullmul);
void HSI_SetSysClock(uint32_t pullmul);
void MCO_GPIO_Config(void);
#endif
