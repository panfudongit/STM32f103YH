
#include "stm32f10x.h"
#include "exti_api.h"

void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/*设定中断优先级的分组1：0-1， 0-7*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	/*对应GPIOx0, x=A,B,C,D,E,F*/
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn; 
	/*主优先级*/
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	/*子优先级*/
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	/*使能EXTI0_IRQn 这一通道*/
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}
void EXTI_Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	
	/*开启GPIOA和AFIO的时钟*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);

	NVIC_Configuration();

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	/*配置为浮空输入*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}
