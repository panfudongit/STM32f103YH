/**
 ******************************************************************************
 * @测试DMA的例程，一次传输，检测状态位判断传输完成。
 * @测试入口函数：DMA_Memory_t_Sram
 *
 * @LED: PB1, PB5, 低电平亮灯
 *
 ******************************************************************************
 * 功能：使用DMA，把FLASH的数据传输到SRAM, 判断SRAM数据与FLASH是否相同，通过LED
 * 来表明这个结果。
 * 流程：定义常量数组(const保存在FLASH), 定义变量数组(保存在SRAM)
 *       配置DMA结构体， 初始化DMA， 清除DMA发送完成状态位，使能DMA
 *       通过读取状态位检测数据传输完成，比较数据。
 ******************************************************************************
 */
#include "dma_api.h"
#include "gpio_api.h"

const uint32_t aSRC_Const_Buffer[BUFFER_SIZE]= {
                                    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
                                    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
                                    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
                                    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
                                    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
                                    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
                                    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
                                    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80};
uint32_t aDST_Buffer[BUFFER_SIZE];
void DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	// 开启DMA时钟，时钟在AHB总线上
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	// 源数据地址
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)aSRC_Const_Buffer;
	// 目标地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)aDST_Buffer;
	// 方向：外设到存储器（这里的外设是内部的FLASH）
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	// 传输大小
	DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE;
	// 内存数据单位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	// 外设数据单位
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	// 内存地址递增
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	// 外设（这里是FLASH）地址递增
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
	// 使能内存到内存的传输
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
	// 设定优先级
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	// DMA模式，一次或循环， 这里用一次
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	// 配置DMA通道
	DMA_Init(DMA1_Channel6, &DMA_InitStructure);
	// 清除DMA数据传输完成标志位，防止干扰
	DMA_ClearFlag(DMA1_FLAG_TC6);
	// 使能DMA
	DMA_Cmd(DMA1_Channel6, ENABLE);
}

uint8_t Buffercmp_32b(const uint32_t *pBuffer, uint32_t *pBuffer1, uint16_t BufferLength)
{

	while(BufferLength--)
	{
		if(*pBuffer != *pBuffer1)
			return 0;
		
		pBuffer++;
		pBuffer1++;
	}
	
	return 1;
}
void DMA_Memory_t_Sram(void)
{
	uint8_t BufferFlag;
	
	DMA_Config();
	
	while(DMA_GetFlagStatus(DMA1_FLAG_TC6) == RESET)
		;
	
	BufferFlag = Buffercmp_32b(aSRC_Const_Buffer, aDST_Buffer, BUFFER_SIZE);
	
	if(BufferFlag)
	{
		digitalLo(GPIOB, GPIO_Pin_5);
	}
	else
	{
		digitalLo(GPIOB, GPIO_Pin_1);
	}
}
