
#include "rcc_reg.h"

void HSE_SetSysCLK(uint32_t pullmul)
{
	__IO uint32_t StartUpCounter = 0, HSEStatus = 0;
	//-----------------------------------------------------------
	// 恢复RCC到初始状态
	/* Set HSION bit */
	RCC->CR |= (uint32_t)0x00000001;
	/* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */

	RCC->CFGR &= (uint32_t)0xF0FF0000;
	/* Reset HSEON, CSSON and PLLON bits */
	RCC->CR &= (uint32_t)0xFEF6FFFF;

	/* Reset HSEBYP bit */
	RCC->CR &= (uint32_t)0xFFFBFFFF;

	/* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
	RCC->CFGR &= (uint32_t)0xFF80FFFF;

	/* Disable all interrupts and clear pending bits  */
	RCC->CIR = 0x009F0000;
	//------------------------------------------------------------

	// 使能HSE
	RCC->CR |= (0x01 << 16);

	// 等待HSE稳定
	do
	{
		HSEStatus = (RCC->CR & (0x01 << 17));
		StartUpCounter++;
	} while( (HSEStatus == 0) && (StartUpCounter != 20) );

	if( (RCC->CR & (0x01 << 17)) != 0 )
	{
		HSEStatus = (uint32_t)0x01;
	} else {
		HSEStatus = (uint32_t)0x00;
	}

	if( HSEStatus == (uint32_t)0x01)
	{
		/* Enable Prefetch Buffer */
		FLASH->ACR |= FLASH_ACR_PRFTBE;

		/* Flash 2 wait state */
		FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
		FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;

		// HCLK = SYSCLK
		RCC->CFGR |= (uint32_t)(0x00 << 4);

		// PCLK1 = HCLK/2
		RCC->CFGR |= (uint32_t)(0x4 << 8);

		// PCLK2 = HCLK
		RCC->CFGR |= (uint32_t)(0x00 << 11);

		// HSE不会频
		RCC->CFGR &= (uint32_t)~(uint32_t)((0x01 << 17) | (0x01 << 16)
												              |(0x0f << 18));
		// 选择HSE做PLL源，PLL倍频输入HSE * 9
		RCC->CFGR |= (uint32_t)( (0x01 << 16) | (0x09 << 18) );

		// 使能PLL
		RCC->CR |= (uint32_t)(0x01 << 24);

		// 等待PLL稳定
		while( (RCC->CR & (uint32_t)(0x01 << 25)) == 0)
			;

		// 选择PLL做系统时钟
		RCC->CFGR &= ~(uint32_t)(0x03 << 0);
		RCC->CFGR |= (uint32_t)(0x02 << 0);

		while( (RCC->CFGR & (uint32_t)(0x02 << 2)) != (uint32_t)0x08)
		;

	} else {
		;
	}
}
