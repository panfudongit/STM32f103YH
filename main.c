
#include "stm32f10x.h"
#include "gpio_api.h"  
#include "gpio_reg.h"
#include "exti_api.h"
#include "systick_api.h"
#include "usart_api.h"
#include "rcc_api.h"

void Delay(__IO uint32_t nCount)
{
	 for(; nCount != 0; nCount--);
}
int main(void)
{
	LED_GPIO_Config();
	
	EXTI_Key_Config();
	
	USART_Config();

	printf("Start the main thread ...\n");
	while(1)
	{
		digitalToggle(GPIOB,GPIO_Pin_0);
		SysTick_Delay_Ms(1000);
	}
}
