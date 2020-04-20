
#include "rcc_api.h"

/*
 * 配置HSE做为SYSCLK的时钟源，pullmul是位频
 * SYSCLK 最大建议设定为72MHZ,pullmul为RCC_PLLMul_9 (9)
 * 调用示例  HES_SetSysClock(RCC_PLLMul_9);
 */
void HES_SetSysClock(uint32_t pullmul)
{
	__IO uint32_t ForHSEStartUpCounter = 0 , ForHSEStartUpStatus = 0;
	// 把RCC外设初始化到复位状态，这是必须
	// 因为之前system_stm32f10x那里已经设置了
	RCC_DeInit();

	// 使能HSE时钟
	RCC_HSEConfig(RCC_HSE_ON);

	ForHSEStartUpStatus = RCC_WaitForHSEStartUp();

	if(ForHSEStartUpStatus == SUCCESS)
	{
		// 使能FLASH 预存储缓存区
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

		// SYSCLK 周期与闪存访问时间的比例设置，一般是设置2
		// 0: 0 < SYSCLK <= 24M
		// 1: 24< SYSCLK <= 48M
		// 2: 48< SYSCLK <= 72M
		FLASH_SetLatency(FLASH_Latency_2);

		// HCLK = SYSCLK
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		// PCLK2 = SYSCLK
		RCC_PCLK2Config(RCC_HCLK_Div1);
		// PCLK1 = SYSCLK/2
		RCC_PCLK1Config(RCC_HCLK_Div2);

		// 选择PLL的时钟源HSE,不分频， PLL=HSE*pullmul
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, pullmul);
		// 使能PLL
		RCC_PLLCmd(ENABLE);

		// 等PLL稳定
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET ) {
			;
		}

		// 当PLL稳定后选择PLL做为SYSCLK
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		// 等时钟切换稳定
		while(RCC_GetSYSCLKSource() != 0x08) {
			;
		}
	} else {
	}
}

/*
 * 配置HSI做为SYSCLK的时钟源，pullmul是位频
 * SYSCLK 最大建议设定为64MHZ,pullmul为RCC_PLLMul_16 (16)
 * 因为HSI做为PLL的源要做2分频
 * 调用示例  HES_SetSysClock(RCC_PLLMul_16);
 */
void HSI_SetSysClock(uint32_t pullmul)
{
	__IO uint32_t ForHSIStartUpCounter = 0 , ForHSIStartUpStatus = 0;
	// 把RCC外设初始化到复位状态，这是必须
	// 因为之前system_stm32f10x那里已经设置了
	RCC_DeInit();

	// 使能HSE时钟
	RCC_HSICmd(ENABLE);

	ForHSIStartUpStatus = RCC->CR & RCC_CR_HSIRDY;

	if(ForHSIStartUpStatus == RCC_CR_HSIRDY)
	{
		// 使能FLASH 预存储缓存区
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

		// SYSCLK 周期与闪存访问时间的比例设置，一般是设置2
		// 0: 0 < SYSCLK <= 24M
		// 1: 24< SYSCLK <= 48M
		// 2: 48< SYSCLK <= 72M
		FLASH_SetLatency(FLASH_Latency_2);

		// HCLK = SYSCLK
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		// PCLK2 = SYSCLK
		RCC_PCLK2Config(RCC_HCLK_Div1);
		// PCLK1 = SYSCLK/2
		RCC_PCLK1Config(RCC_HCLK_Div2);

		// 选择PLL的时钟源HSE,不分频， PLL=HSE*pullmul
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2, pullmul);
		// 使能PLL
		RCC_PLLCmd(ENABLE);

		// 等PLL稳定
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET ) {
			;
		}

		// 当PLL稳定后选择PLL做为SYSCLK
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		// 等时钟切换稳定
		while(RCC_GetSYSCLKSource() != 0x08) {
			;
		}
	} else {
	}
}

/*
 * 初始化MCO引脚PA8
 * 在F03系列中，MCO只有一个引脚，即PA8
 */
void MCO_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// 开启GPIOA的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	// 设置为复用功能推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	// 初始化GPIOA8
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// 选择MCO的时钟源
	//RCC_MCOConfig(RCC_MCO_SYSCLK);
}
