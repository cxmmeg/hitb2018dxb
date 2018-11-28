/*
*********************************************************************************************************
*
*	模块名称 : SPI总线驱动
*	文件名称 : bsp_spi_bus.h
*	版    本 : V1.0
*	说    明 : 头文件
*
*	Copyright (C), 2014-2015, 
*
*********************************************************************************************************
*/

#ifndef __BSP_SPI_BUS_H__
#define __BSP_SPI_BUS_H__

#ifdef __cplusplus
 extern "C" {
#endif 

#define SPI1_HARD_EN		1
#define SPI2_HARD_EN		1
#define SPI3_HARD_EN		0
#define SPI4_SOFT_EN		0
#define SPI5_SOFT_EN		0
#define SPI6_SOFT_EN		0
#define SPI7_SOFT_EN		0
#define SPI8_SOFT_EN		0

/*硬件SPI接口定义:
SPI1	SCK			PA5		PB3
		MISO		PA6		PB4
		MOSI		PA7		PB5
		
SPI2	SCK			PB13	PB10	PI1
		MISO		PB14	PC2		PI2
		MOSI		PB15	PC3		PI3
		
SPI3	SCK			PC10	PB3
		MISO		PC11	PB4
		MOSI		PC12	PB5
*/

/*
STM32F4XX 时钟计算.
	HCLK = 168M
	PCLK1 = HCLK / 4 = 42M
	PCLK2 = HCLK / 2 = 84M

	SPI2、SPI3 在 PCLK1, 时钟42M
	SPI1	   在 PCLK2, 时钟84M

	STM32F4 支持的最大SPI时钟为 37.5 Mbits/S, 因此需要分频。
	SPI2/3是SPI1速度一半，所以按照分频系数除2才是SPI2/3速度
*/
#define SPI_SPEED_42M		SPI_BaudRatePrescaler_2
#define SPI_SPEED_21M		SPI_BaudRatePrescaler_4
#define SPI_SPEED_10_5M		SPI_BaudRatePrescaler_8
#define SPI_SPEED_5_2M		SPI_BaudRatePrescaler_16
#define SPI_SPEED_2_6M		SPI_BaudRatePrescaler_32
#define SPI_SPEED_1_3M		SPI_BaudRatePrescaler_64
#define SPI_SPEED_0_6M		SPI_BaudRatePrescaler_128
#define SPI_SPEED_0_3M		SPI_BaudRatePrescaler_256


#if SPI1_HARD_EN == 1
	#define SPI1_PORT			SPI1			//SPI口
	#define SPI1_SPEED			SPI_SPEED_10_5M	//SPI速度 SPI_Speed_Fast SPI_Speed_Normal
	
	#define SPI1_SCK_PORT		GPIOA		//SCK GPIO口
	#define SPI1_SCK_PIN		GPIO_Pin_5		//SCK Pin脚位
	#define SPI1_MISO_PORT		GPIOA			//MISO GPIO口
	#define SPI1_MISO_PIN		GPIO_Pin_6		//MISO Pin脚位
	#define SPI1_MOSI_PORT		GPIOA			//MOSI GPIO口
	#define SPI1_MOSI_PIN		GPIO_Pin_7		//MOSI Pin脚位
	
	#define SPI1_Direction		SPI_Direction_2Lines_FullDuplex
	#define SPI1_DataSize		SPI_DataSize_8b
	#define SPI1_CPOL			SPI_CPOL_High
	#define SPI1_CPHA			SPI_CPHA_2Edge
	#define SPI1_FirstBit		SPI_FirstBit_MSB
	#define SPI1_MASTER			SPI_Mode_Master			//是主机还是从机
	#define	SPI1_WADDR_DELAY	0
	#define SPI1_BUSY			FALSE
#endif

#if SPI2_HARD_EN == 1
	#define SPI2_PORT			SPI2			//SPI口
	#define SPI2_SPEED			SPI_SPEED_42M	//SPI速度 spi2速度要除以2，SPI_Speed_Fast SPI_Speed_Normal
	
	#define SPI2_SCK_PORT		GPIOB			//SCK GPIO口
	#define SPI2_SCK_PIN		GPIO_Pin_13		//SCK Pin脚位
	#define SPI2_MISO_PORT		GPIOB			//MISO GPIO口
	#define SPI2_MISO_PIN		GPIO_Pin_14		//MISO Pin脚位
	#define SPI2_MOSI_PORT		GPIOB			//MOSI GPIO口
	#define SPI2_MOSI_PIN		GPIO_Pin_15		//MOSI Pin脚位
	
	#define SPI2_Direction		SPI_Direction_2Lines_FullDuplex
	#define SPI2_DataSize		SPI_DataSize_8b
	#define SPI2_CPOL			SPI_CPOL_High
	#define SPI2_CPHA			SPI_CPHA_2Edge
	#define SPI2_FirstBit		SPI_FirstBit_MSB
	#define SPI2_MASTER			SPI_Mode_Master			//是主机还是从机
	#define	SPI2_WADDR_DELAY	0
	#define SPI2_BUSY			FALSE
#endif

#if SPI3_HARD_EN == 1
	#define SPI3_PORT			SPI3			//SPI口
	#define SPI3_SPEED			SPI_SPEED_21M	//SPI速度 spi3速度要除以2，SPI_Speed_Fast SPI_Speed_Normal
	
	#define SPI3_SCK_PORT		GPIOC			//SCK GPIO口
	#define SPI3_SCK_PIN		GPIO_Pin_10		//SCK Pin脚位
	#define SPI3_MISO_PORT		GPIOC			//MISO GPIO口
	#define SPI3_MISO_PIN		GPIO_Pin_11		//MISO Pin脚位
	#define SPI3_MOSI_PORT		GPIOC			//MOSI GPIO口
	#define SPI3_MOSI_PIN		GPIO_Pin_12		//MOSI Pin脚位
	
	#define SPI3_Direction		SPI_Direction_2Lines_FullDuplex
	#define SPI3_DataSize		SPI_DataSize_8b
	#define SPI3_CPOL			SPI_CPOL_Low
	#define SPI3_CPHA			SPI_CPHA_1Edge
	#define SPI3_FirstBit		SPI_FirstBit_MSB
	#define SPI3_MASTER			SPI_Mode_Master			//是主机还是从机
	#define	SPI3_WADDR_DELAY	0
	#define SPI3_BUSY			FALSE
#endif

#if SPI4_SOFT_EN == 1
	#define SPI4_PORT			SPI4S			//SPI口
	#define SPI4_SPEED			SPI_SPEED_21M	//SPI速度 SPI_Speed_Fast SPI_Speed_Normal
		
	#define SPI4_SCK_PORT		GPIOB			//SCK GPIO口
	#define SPI4_SCK_PIN		GPIO_Pin_13		//SCK Pin脚位
	#define SPI4_MISO_PORT		GPIOB			//MISO GPIO口
	#define SPI4_MISO_PIN		GPIO_Pin_14		//MISO Pin脚位
	#define SPI4_MOSI_PORT		GPIOB			//MOSI GPIO口
	#define SPI4_MOSI_PIN		GPIO_Pin_15		//MOSI Pin脚位
	
	#define SPI4_Direction		SPI_Direction_2Lines_FullDuplex
	#define SPI4_DataSize		SPI_DataSize_8b
	#define SPI4_CPOL			SPI_CPOL_Low
	#define SPI4_CPHA			SPI_CPHA_1Edge
	#define SPI4_FirstBit		SPI_FirstBit_MSB
	#define SPI4_MASTER			SPI_Mode_Master			//是主机还是从机
	#define	SPI4_WADDR_DELAY	0
	#define SPI4_BUSY			FALSE
#endif

#if SPI5_SOFT_EN == 1
	#define SPI5_PORT			SPI5S			//SPI口
	#define SPI5_SPEED			SPI_SPEED_21M	//SPI速度 SPI_Speed_Fast SPI_Speed_Normal
	
	#define SPI5_SCK_PORT		GPIOB			//SCK GPIO口
	#define SPI5_SCK_PIN		GPIO_Pin_7		//SCK Pin脚位
	#define SPI5_MISO_PORT		GPIOB			//MISO GPIO口
	#define SPI5_MISO_PIN		GPIO_Pin_7		//MISO Pin脚位
	#define SPI5_MOSI_PORT		GPIOB			//MOSI GPIO口
	#define SPI5_MOSI_PIN		GPIO_Pin_6		//MOSI Pin脚位
	
	#define SPI5_Direction		SPI_Direction_2Lines_FullDuplex
	#define SPI5_DataSize		SPI_DataSize_8b
	#define SPI5_CPOL			SPI_CPOL_High
	#define SPI5_CPHA			SPI_CPHA_2Edge
	#define SPI5_FirstBit		SPI_FirstBit_MSB
	#define SPI5_MASTER			SPI_Mode_Master			//是主机还是从机
	#define	SPI5_WADDR_DELAY	0
	#define SPI5_BUSY			FALSE
#endif

#if SPI6_SOFT_EN == 1
	#define SPI6_PORT			SPI6S			//SPI口
	#define SPI6_SPEED			SPI_SPEED_21M	//SPI速度 SPI_Speed_Fast SPI_Speed_Normal
	
	#define SPI6_SCK_PORT		GPIOB			//SCK GPIO口
	#define SPI6_SCK_PIN		GPIO_Pin_7		//SCK Pin脚位
	#define SPI6_MISO_PORT		GPIOB			//MISO GPIO口
	#define SPI6_MISO_PIN		GPIO_Pin_7		//MISO Pin脚位
	#define SPI6_MOSI_PORT		GPIOB			//MOSI GPIO口
	#define SPI6_MOSI_PIN		GPIO_Pin_6		//MOSI Pin脚位
	
	#define SPI6_Direction		SPI_Direction_2Lines_FullDuplex
	#define SPI6_DataSize		SPI_DataSize_8b
	#define SPI6_CPOL			SPI_CPOL_High
	#define SPI6_CPHA			SPI_CPHA_2Edge
	#define SPI6_FirstBit		SPI_FirstBit_MSB
	#define SPI6_MASTER			SPI_Mode_Master			//是主机还是从机
	#define	SPI6_WADDR_DELAY	0
	#define SPI6_BUSY			FALSE
#endif

#if SPI7_SOFT_EN == 1
	#define SPI7_PORT			SPI7S			//SPI口
	#define SPI7_SPEED			SPI_SPEED_21M	//SPI速度 SPI_Speed_Fast SPI_Speed_Normal
	
	#define SPI7_SCK_PORT		GPIOB			//SCK GPIO口
	#define SPI7_SCK_PIN		GPIO_Pin_7		//SCK Pin脚位
	#define SPI7_MISO_PORT		GPIOB			//MISO GPIO口
	#define SPI7_MISO_PIN		GPIO_Pin_7		//MISO Pin脚位
	#define SPI7_MOSI_PORT		GPIOB			//MOSI GPIO口
	#define SPI7_MOSI_PIN		GPIO_Pin_6		//MOSI Pin脚位
	
	#define SPI7_Direction		SPI_Direction_2Lines_FullDuplex
	#define SPI7_DataSize		SPI_DataSize_8b
	#define SPI7_CPOL			SPI_CPOL_High
	#define SPI7_CPHA			SPI_CPHA_2Edge
	#define SPI7_FirstBit		SPI_FirstBit_MSB
	#define SPI7_MASTER			SPI_Mode_Master			//是主机还是从机
	#define	SPI7_WADDR_DELAY	0
	#define SPI7_BUSY			FALSE
#endif

#if SPI8_SOFT_EN == 1
	#define SPI8_PORT			SPI8S			//SPI口
	#define SPI8_SPEED			SPI_SPEED_21M	//SPI速度 SPI_Speed_Fast SPI_Speed_Normal
	
	#define SPI8_SCK_PORT		GPIOB			//SCK GPIO口
	#define SPI8_SCK_PIN		GPIO_Pin_7		//SCK Pin脚位
	#define SPI8_MISO_PORT		GPIOB			//MISO GPIO口
	#define SPI8_MISO_PIN		GPIO_Pin_7		//MISO Pin脚位
	#define SPI8_MOSI_PORT		GPIOB			//MOSI GPIO口
	#define SPI8_MOSI_PIN		GPIO_Pin_6		//MOSI Pin脚位
	
	#define SPI8_Direction		SPI_Direction_2Lines_FullDuplex
	#define SPI8_DataSize		SPI_DataSize_8b
	#define SPI8_CPOL			SPI_CPOL_High
	#define SPI8_CPHA			SPI_CPHA_2Edge
	#define SPI8_FirstBit		SPI_FirstBit_MSB
	#define SPI8_MASTER			SPI_Mode_Master			//是主机还是从机
	#define	SPI8_WADDR_DELAY	0
	#define SPI8_BUSY			FALSE
#endif


#define SPI1H		1
#define SPI2H		2
#define SPI3H		3
#define SPI4S		4
#define SPI5S		5
#define SPI6S		6
#define SPI7S		7
#define SPI8S		8


typedef struct 
{
	uint8_t 		SEL;				//SPI口
	SPI_TypeDef* 	SPIx;			//SPI接口
	uint16_t 		SPEED;				//如果是硬件SPI，就是EEPROM 速率
	
	GPIO_TypeDef* 	SCK_PORT;		
	uint16_t 		SCK_PIN;
	GPIO_TypeDef* 	MISO_PORT;		
	uint16_t 		MISO_PIN;
	GPIO_TypeDef* 	MOSI_PORT;		
	uint16_t 		MOSI_PIN;
	
	uint16_t		Direction;
	uint16_t		DataSize;
	uint16_t		CPOL;
	uint16_t		CPHA;
	uint16_t		FirstBit;
	uint16_t 		Master;       			//主从选择控制:FALSE-从机，TRUE-主机
	uint16_t		WAddr_Delay;
	bool			BUSY;
}SPI_CONFIG;


//#define SOFT_SPI		/* 定义此行表示使用GPIO模拟SPI接口 */
#define HARD_SPI		/* 定义此行表示使用CPU的硬件SPI接口 */

/*等待超时时间*/
#define SPIT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define SPIT_LONG_TIMEOUT         ((uint32_t)(10 * SPIT_FLAG_TIMEOUT))

/*信息输出*/
#define SPI_DEBUG_ON         1

#define SPI_INFO(fmt,arg...)           printf("<<-SPI-INFO->> "fmt"\n",##arg)
#define SPI_ERROR(fmt,arg...)          printf("<<-SPI-ERROR->> "fmt"\n",##arg)
#define SPI_DEBUG(fmt,arg...)          do{\
                                          if(SPI_DEBUG_ON)\
                                          printf("<<-SPI-DEBUG->> [%d]"fmt"\n",__LINE__, ##arg);\
                                          }while(0)

void bsp_Init_SPI(uint8_t SPI_SEL);
void bsp_Init_SPI_Quick(SPI_TypeDef* SPIx, uint16_t _cr1);
void bsp_SpiBusEnter(uint8_t SPI_SEL);
void bsp_SpiBusExit(uint8_t SPI_SEL);
bool bsp_SpiBusBusy(uint8_t SPI_SEL);
void bsp_SpiBusBusyCheck(uint8_t SPI_SEL, u8 chkcmd, u8 stacmd, u8 flag);
void bsp_SetSpiSck(uint8_t SPI_SEL, uint8_t _data);
void bsp_SPI_SetSpeed(uint8_t SPI_SEL, u8 SPI_BaudRatePrescaler);
uint8_t bsp_SPI_Read_Byte(uint8_t SPI_SEL, u8 TxData);
uint8_t bsp_SPI_Write_Byte(uint8_t SPI_SEL, u8 TxData);
uint16_t bsp_SPI_Write_HalfWord(uint8_t SPI_SEL, u16 HalfWord);
void bsp_SPI_Write_16(uint8_t SPI_SEL, u16 TxData);
void bsp_SPI_Write_32(uint8_t SPI_SEL, u32 TxData);
uint32_t bsp_GetRCCofSPI(SPI_TypeDef* SPIx);
//uint8_t bsp_GetAFofSPI(SPI_TypeDef* SPIx);


#ifdef __cplusplus
	}
#endif /* __cplusplus */

#endif

/***************************** (END OF FILE) *********************************/
