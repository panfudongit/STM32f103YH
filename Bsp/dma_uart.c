/**
 ******************************************************************************
 * @测试DMA的例程，把内存的数据通过DMA传到UART的DATA寄存器然后通过UART输出
 * @测试入口函数， TEST_DMA1_C4_Usart1
 *
 * @DMA1_CHANEL4,  USART1
 *
 ******************************************************************************
 * 
 * 
 * 
 * 
 *
 ******************************************************************************
 */

#include "dma_api.h"
#include "usart_api.h"

uint8_t SRC_Buffer[BUFFER_SIZE] = { 0 };

void DMA1_C4_Config_Uart1(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	// 开启DMA的时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	// 内存地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)SRC_Buffer;
	// 内存数据单位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	// 传输数据大小
	DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE;
	// 内存地址自增
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	// 传输方向内存到外设
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	// 外设地址，这里是串口数据存在器地址
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->DR);
	// 外设数据单位
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	// 内存到外设，所以禁止内存到内存传输
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	// 外设是寄存器地址不增
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	// 传输模式，一次或循环
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	// 优先级，中
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	
	// 配置DMA
	DMA_Init(DMA1_Channel4, &DMA_InitStructure);
	// 使能DMA
	DMA_Cmd(DMA1_Channel4, ENABLE);
}

void TEST_DMA1_C4_Usart1(void)
{
	uint8_t i = 0;
	
	USART_Config();
	
	DMA1_C4_Config_Uart1();
	
	for( ; i < BUFFER_SIZE; i++)
	{
		SRC_Buffer[i] = 'A';
	}
	
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
}
