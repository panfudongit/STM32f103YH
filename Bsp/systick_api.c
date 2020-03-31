

#include "systick_api.h"

#define SYSCLK (72000000)
void SysTick_Delay_Us(__IO uint32_t us)
{
	uint32_t i;
	SysTick_Config(SYSCLK / 1000000);
	for(i = 0; i < us; i++)
	{
		while(!((SysTick->CTRL) & (0x1 << 16)));
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Delay_Ms(__IO uint32_t ms)
{
	uint32_t i;
	SysTick_Config(SYSCLK / 1000);
	for(i = 0; i < ms; i++)
	{
		while(!((SysTick->CTRL) & (0x1 << 16)));
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

