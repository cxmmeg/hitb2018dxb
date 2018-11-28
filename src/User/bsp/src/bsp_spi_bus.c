/*
*********************************************************************************************************
*
*	模块名称 : SPI总线驱动
*	文件名称 : bsp_spi_bus.h
*	版    本 : V1.2
*	说    明 : SPI总线底层驱动。提供SPI配置、收发数据、多设备共享SPI支持。
*	修改记录 :
*		版本号  日期        作者    说明
*       v1.0    2014-10-24 white  首版。将串行FLASH、TSC2046、VS1053、AD7705、ADS1256等SPI设备的配置
*									和收发数据的函数进行汇总分类。并解决不同速度的设备间的共享问题。
*		V1.1	2015-02-25 white  硬件SPI时，没有开启GPIOB时钟，已解决。
*		V1.2	2015-07-23 white  修改 bsp_SPI_Init() 函数，增加开关SPI时钟的语句。规范硬件SPI和软件SPI的宏定义.
*
*	Copyright (C), 2015-2016, 
*
*********************************************************************************************************
*/

#include "bsp.h"


/* SPI or I2S mode selection masks */
#define SPI_Mode_Select      ((uint16_t)0xF7FF)
#define I2S_Mode_Select      ((uint16_t)0x0800) 

/* SPI registers Masks */
#define CR1_CLEAR_Mask       ((uint16_t)0x3040)
#define I2SCFGR_CLEAR_Mask   ((uint16_t)0xF040)

/* SPI SPE mask */
#define CR1_SPE_Set          ((uint16_t)0x0040)
#define CR1_SPE_Reset        ((uint16_t)0xFFBF)


static __IO uint32_t  SPITimeout = SPIT_LONG_TIMEOUT;   

static uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);


void SPI_Init_Var(u8 SEL);
SPI_CONFIG *SELToSPI(u8 SEL);


/* 定义每个SPI口结构体变量 */
#if SPI1_HARD_EN == 1
	static SPI_CONFIG g_SPI1, *p_SPI1 = &g_SPI1;
#endif

#if SPI2_HARD_EN == 1
	static SPI_CONFIG g_SPI2, *p_SPI2 = &g_SPI2;
#endif

#if SPI3_HARD_EN == 1
	static SPI_CONFIG g_SPI3, *p_SPI3 = &g_SPI3;
#endif

#if SPI4_SOFT_EN == 1
	static SPI_CONFIG g_SPI4, *p_SPI4 = &g_SPI4;
#endif

#if SPI5_SOFT_EN == 1
	static SPI_CONFIG g_SPI5, *p_SPI5 = &g_SPI5;
#endif

#if SPI6_SOFT_EN == 1
	static SPI_CONFIG g_SPI6, *p_SPI6 = &g_SPI6;
#endif

#if SPI7_SOFT_EN == 1
	static SPI_CONFIG g_SPI7, *p_SPI7 = &g_SPI7;
#endif

#if SPI8_SOFT_EN == 1
	static SPI_CONFIG g_SPI8, *p_SPI8 = &g_SPI8;
#endif

void SPI_Init_Var(u8 SEL)
{
#if SPI1_HARD_EN == 1
	if(SEL == SPI1H)
	{
		p_SPI1->SEL = SPI1H;
		p_SPI1->SPIx = SPI1_PORT;
		p_SPI1->SPEED = SPI1_SPEED;
		p_SPI1->MOSI_PORT = SPI1_MOSI_PORT;
		p_SPI1->MOSI_PIN = SPI1_MOSI_PIN;
		p_SPI1->MISO_PORT = SPI1_MISO_PORT;
		p_SPI1->MISO_PIN = SPI1_MISO_PIN;
		p_SPI1->SCK_PORT = SPI1_SCK_PORT;
		p_SPI1->SCK_PIN = SPI1_SCK_PIN;
		p_SPI1->Direction = SPI1_Direction;
		p_SPI1->DataSize = SPI1_DataSize;
		p_SPI1->CPOL = SPI1_CPOL;
		p_SPI1->CPHA = SPI1_CPHA;
		p_SPI1->FirstBit = SPI1_FirstBit;
		p_SPI1->Master = SPI1_MASTER;
		p_SPI1->WAddr_Delay = SPI1_WADDR_DELAY;
		p_SPI1->BUSY = SPI1_BUSY;
	}
#endif
	
#if SPI2_HARD_EN == 1
	if(SEL == SPI2H)
	{
		p_SPI2->SEL = SPI2H;
		p_SPI2->SPIx = SPI2_PORT;
		p_SPI2->SPEED = SPI2_SPEED;
		p_SPI2->MOSI_PORT = SPI2_MOSI_PORT;
		p_SPI2->MOSI_PIN = SPI2_MOSI_PIN;
		p_SPI2->MISO_PORT = SPI2_MISO_PORT;
		p_SPI2->MISO_PIN = SPI2_MISO_PIN;
		p_SPI2->SCK_PORT = SPI2_SCK_PORT;
		p_SPI2->SCK_PIN = SPI2_SCK_PIN;
		p_SPI2->Direction = SPI2_Direction;
		p_SPI2->DataSize = SPI2_DataSize;
		p_SPI2->CPOL = SPI2_CPOL;
		p_SPI2->CPHA = SPI2_CPHA;
		p_SPI2->FirstBit = SPI2_FirstBit;
		p_SPI2->Master = SPI2_MASTER;
		p_SPI2->WAddr_Delay = SPI2_WADDR_DELAY;
		p_SPI2->BUSY = SPI2_BUSY;
	}
#endif
	
#if SPI3_HARD_EN == 1
	if(SEL == SPI3H)
	{
		p_SPI3->SEL = SPI3H;
		p_SPI3->SPIx = SPI3_PORT;
		p_SPI3->SPEED = SPI3_SPEED;
		p_SPI3->MOSI_PORT = SPI3_MOSI_PORT;
		p_SPI3->MOSI_PIN = SPI3_MOSI_PIN;
		p_SPI3->MISO_PORT = SPI3_MISO_PORT;
		p_SPI3->MISO_PIN = SPI3_MISO_PIN;
		p_SPI3->SCK_PORT = SPI3_SCK_PORT;
		p_SPI3->SCK_PIN = SPI3_SCK_PIN;
		p_SPI3->Direction = SPI3_Direction;
		p_SPI3->DataSize = SPI3_DataSize;
		p_SPI3->CPOL = SPI3_CPOL;
		p_SPI3->CPHA = SPI3_CPHA;
		p_SPI3->FirstBit = SPI3_FirstBit;
		p_SPI3->Master = SPI3_MASTER;
		p_SPI3->WAddr_Delay = SPI3_WADDR_DELAY;
		p_SPI3->BUSY = SPI3_BUSY;
	}
#endif
	
#if SPI4_SOFT_EN == 1
	if(SEL == SPI4S)
	{
		p_SPI4->SEL = SPI4S;
		p_SPI4->SPEED = SPI4_SPEED;
		p_SPI4->MOSI_PORT = SPI4_MOSI_PORT;
		p_SPI4->MOSI_PIN = SPI4_MOSI_PIN;
		p_SPI4->MISO_PORT = SPI4_MISO_PORT;
		p_SPI4->MISO_PIN = SPI4_MISO_PIN;
		p_SPI4->SCK_PORT = SPI4_SCK_PORT;
		p_SPI4->SCK_PIN = SPI4_SCK_PIN;
		p_SPI4->Direction = SPI4_Direction;
		p_SPI4->DataSize = SPI4_DataSize;
		p_SPI4->CPOL = SPI4_CPOL;
		p_SPI4->CPHA = SPI4_CPHA;
		p_SPI4->FirstBit = SPI4_FirstBit;
		p_SPI4->Master = SPI4_MASTER;
		p_SPI4->WAddr_Delay = SPI4_WADDR_DELAY;
		p_SPI4->BUSY = SPI4_BUSY;
	}
#endif
	
#if SPI5_SOFT_EN == 1
	if(SEL == SPI5S)
	{
		p_SPI5->SEL = SPI5S;
		p_SPI5->SPEED = SPI5_SPEED;
		p_SPI5->MOSI_PORT = SPI5_MOSI_PORT;
		p_SPI5->MOSI_PIN = SPI5_MOSI_PIN;
		p_SPI5->MISO_PORT = SPI5_MISO_PORT;
		p_SPI5->MISO_PIN = SPI5_MISO_PIN;
		p_SPI5->SCK_PORT = SPI5_SCK_PORT;
		p_SPI5->SCK_PIN = SPI5_SCK_PIN;
		p_SPI5->Direction = SPI5_Direction;
		p_SPI5->DataSize = SPI5_DataSize;
		p_SPI5->CPOL = SPI5_CPOL;
		p_SPI5->CPHA = SPI5_CPHA;
		p_SPI5->FirstBit = SPI5_FirstBit;
		p_SPI5->Master = SPI5_MASTER;
		p_SPI5->WAddr_Delay = SPI5_WADDR_DELAY;
		p_SPI5->BUSY = SPI5_BUSY;
	}
#endif
	
#if SPI6_SOFT_EN == 1
	if(SEL == SPI6S)
	{
		p_SPI6->SEL = SPI6S;
		p_SPI6->SPEED = SPI6_SPEED;
		p_SPI6->MOSI_PORT = SPI6_MOSI_PORT;
		p_SPI6->MOSI_PIN = SPI6_MOSI_PIN;
		p_SPI6->MISO_PORT = SPI6_MISO_PORT;
		p_SPI6->MISO_PIN = SPI6_MISO_PIN;
		p_SPI6->SCK_PORT = SPI6_SCK_PORT;
		p_SPI6->SCK_PIN = SPI6_SCK_PIN;
		p_SPI6->Direction = SPI6_Direction;
		p_SPI6->DataSize = SPI6_DataSize;
		p_SPI6->CPOL = SPI6_CPOL;
		p_SPI6->CPHA = SPI6_CPHA;
		p_SPI6->FirstBit = SPI6_FirstBit;
		p_SPI6->Master = SPI6_MASTER;
		p_SPI6->WAddr_Delay = SPI6_WADDR_DELAY;
		p_SPI6->BUSY = SPI6_BUSY;
	}
#endif
	
#if SPI7_SOFT_EN == 1
	if(SEL == SPI7S)
	{
		p_SPI7->SEL = SPI7S;
		p_SPI7->SPEED = SPI7_SPEED;
		p_SPI7->MOSI_PORT = SPI7_MOSI_PORT;
		p_SPI7->MOSI_PIN = SPI7_MOSI_PIN;
		p_SPI7->MISO_PORT = SPI7_MISO_PORT;
		p_SPI7->MISO_PIN = SPI7_MISO_PIN;
		p_SPI7->SCK_PORT = SPI7_SCK_PORT;
		p_SPI7->SCK_PIN = SPI7_SCK_PIN;
		p_SPI7->Direction = SPI7_Direction;
		p_SPI7->DataSize = SPI7_DataSize;
		p_SPI7->CPOL = SPI7_CPOL;
		p_SPI7->CPHA = SPI7_CPHA;
		p_SPI7->FirstBit = SPI7_FirstBit;
		p_SPI7->Master = SPI7_MASTER;
		p_SPI7->WAddr_Delay = SPI7_WADDR_DELAY;
		p_SPI7->BUSY = SPI7_BUSY;
	}
#endif
	
#if SPI8_SOFT_EN == 1
	if(SEL == SPI8S)
	{
		p_SPI8->SEL = SPI8S;
		p_SPI8->SPEED = SPI8_SPEED;
		p_SPI8->MOSI_PORT = SPI8_MOSI_PORT;
		p_SPI8->MOSI_PIN = SPI8_MOSI_PIN;
		p_SPI8->MISO_PORT = SPI8_MISO_PORT;
		p_SPI8->MISO_PIN = SPI8_MISO_PIN;
		p_SPI8->SCK_PORT = SPI8_SCK_PORT;
		p_SPI8->SCK_PIN = SPI8_SCK_PIN;
		p_SPI8->Direction = SPI8_Direction;
		p_SPI8->DataSize = SPI8_DataSize;
		p_SPI8->CPOL = SPI8_CPOL;
		p_SPI8->CPHA = SPI8_CPHA;
		p_SPI8->FirstBit = SPI8_FirstBit;
		p_SPI8->Master = SPI8_MASTER;
		p_SPI8->WAddr_Delay = SPI8_WADDR_DELAY;
		p_SPI8->BUSY = SPI8_BUSY;
	}
#endif
}

/*
*********************************************************************************************************
*	函 数 名: SELToSPI
*	功能说明: 将SEL转换为SPI指针
*	形    参: SEL: SPI号(SPI1H-SPI3H SPI4S-SPI8S)
*	返 回 值: SPI指针
*********************************************************************************************************
*/
SPI_CONFIG *SELToSPI(u8 SEL)
{
	if (SEL == SPI1H)
	{
		#if SPI1_HARD_EN == 1
			return &g_SPI1;
		#else
			return 0;
		#endif
	}
	else if (SEL == SPI2H)
	{
		#if SPI2_HARD_EN == 1
			return &g_SPI2;
		#else
			return 0;
		#endif
	}
	else if (SEL == SPI3H)
	{
		#if SPI3_HARD_EN == 1
			return &g_SPI3;
		#else
			return 0;
		#endif
	}
	else if (SEL == SPI4S)
	{
		#if SPI4_SOFT_EN == 1
			return &g_SPI4;
		#else
			return 0;
		#endif
	}
	else if (SEL == SPI5S)
	{
		#if SPI5_SOFT_EN == 1
			return &g_SPI5;
		#else
			return 0;
		#endif
	}
	else if (SEL == SPI6S)
	{
		#if SPI6_SOFT_EN == 1
			return &g_SPI6;
		#else
			return 0;
		#endif
	}
	else if (SEL == SPI7S)
	{
		#if SPI7_SOFT_EN == 1
			return &g_SPI7;
		#else
			return 0;
		#endif
	}
	else if (SEL == SPI8S)
	{
		#if SPI8_SOFT_EN == 1
			return &g_SPI8;
		#else
			return 0;
		#endif
	}
	else
	{
		/* 不做任何处理 */
		return 0;
	}
}


void bsp_Init_SPI(u8 SPI_SEL)
{
	SPI_CONFIG *p_SPI;
	
	SPI_Init_Var(SPI_SEL);
	
	p_SPI = SELToSPI(SPI_SEL);

	GPIO_InitTypeDef  GPIO_InitStructure;

	if(SPI_SEL < SPI4S)
	{
		SPI_InitTypeDef  SPI_InitStructure;

		SPI_Cmd(p_SPI->SPIx, DISABLE);	//禁用SPI外设
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用功能
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//100MHz

		RCC_APB2PeriphClockCmd(bsp_GetRCCofGPIO(p_SPI->SCK_PORT) | bsp_GetRCCofGPIO(p_SPI->MISO_PORT)				\
								| bsp_GetRCCofGPIO(p_SPI->MOSI_PORT), ENABLE);//使能SCK时钟
		
		if ( p_SPI->SPIx == SPI1 )
		{
		    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
		}
		else
		{
		    RCC_APB1PeriphClockCmd(bsp_GetRCCofSPI(p_SPI->SPIx), ENABLE);//使能SPI1时钟
		}

		GPIO_InitStructure.GPIO_Pin = p_SPI->SCK_PIN;
		GPIO_Init(p_SPI->SCK_PORT, &GPIO_InitStructure);//初始化
		
		GPIO_InitStructure.GPIO_Pin = p_SPI->MISO_PIN;
		GPIO_Init(p_SPI->MISO_PORT, &GPIO_InitStructure);//初始化
		
		GPIO_InitStructure.GPIO_Pin = p_SPI->MOSI_PIN;
		GPIO_Init(p_SPI->MOSI_PORT, &GPIO_InitStructure);//初始化


		//GPIO_PinAFConfig(p_SPI->SCK_PORT, bsp_GetPinSource(p_SPI->SCK_PIN), bsp_GetAFofSPI(p_SPI->SPIx)); //PB6复用为 SPI1
		//GPIO_PinAFConfig(p_SPI->MISO_PORT, bsp_GetPinSource(p_SPI->MISO_PIN), bsp_GetAFofSPI(p_SPI->SPIx)); //PB7复用为 SPI1
		//GPIO_PinAFConfig(p_SPI->MOSI_PORT, bsp_GetPinSource(p_SPI->MOSI_PIN), bsp_GetAFofSPI(p_SPI->SPIx)); //PB7复用为 SPI1

		//这里只针对SPI口初始化
		if ( p_SPI->SPIx == SPI1 )
		{
		    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE);//复位SPI1
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, DISABLE);//停止复位SPI1
		}
		else
		{
		    RCC_APB1PeriphResetCmd(bsp_GetRCCofSPI(p_SPI->SPIx), ENABLE);//复位SPI1
			RCC_APB1PeriphResetCmd(bsp_GetRCCofSPI(p_SPI->SPIx), DISABLE);//停止复位SPI1
		}
		
		SPI_InitStructure.SPI_Direction = p_SPI->Direction;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
		SPI_InitStructure.SPI_Mode = p_SPI->Master;		//设置SPI工作模式:设置为主SPI
		SPI_InitStructure.SPI_DataSize = p_SPI->DataSize;		//设置SPI的数据大小:SPI发送接收8位帧结构
		SPI_InitStructure.SPI_CPOL = p_SPI->CPOL;		//串行同步时钟的空闲状态为高电平
		SPI_InitStructure.SPI_CPHA = p_SPI->CPHA;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
		SPI_InitStructure.SPI_BaudRatePrescaler = p_SPI->SPEED;		//定义波特率预分频的值:波特率预分频值SPI_BaudRatePrescaler
		SPI_InitStructure.SPI_FirstBit = p_SPI->FirstBit;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
		SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
		SPI_Init(p_SPI->SPIx, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
		
		SPI_Cmd(p_SPI->SPIx, ENABLE);	//使能SPI外设

		bsp_SPI_Write_Byte(SPI_SEL, 0xff);//启动传输，发送8个时钟给从设备，使MOSI一直维持高电平，当然也可以维持低电平，写0X00就可以，不过通常的做法是维持高电平

	}
	else
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//复用功能
		//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	//推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//100MHz
		//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//不上拉下拉

		RCC_APB1PeriphClockCmd(bsp_GetRCCofGPIO(p_SPI->SCK_PORT), ENABLE);//使能SCK时钟
		RCC_APB1PeriphClockCmd(bsp_GetRCCofGPIO(p_SPI->MISO_PORT), ENABLE);//使能MISO时钟
		RCC_APB1PeriphClockCmd(bsp_GetRCCofGPIO(p_SPI->MOSI_PORT), ENABLE);//使能MOSI时钟

		GPIO_InitStructure.GPIO_Pin = p_SPI->SCK_PIN;
		GPIO_Init(p_SPI->SCK_PORT, &GPIO_InitStructure);//初始化
		
		GPIO_InitStructure.GPIO_Pin = p_SPI->MOSI_PIN;
		GPIO_Init(p_SPI->MOSI_PORT, &GPIO_InitStructure);//初始化

		/* 配置GPIO为浮动输入模式(实际上CPU复位后就是输入状态) */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		/* 设为输入口 */
		//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		/* 设为推挽模式 */
		//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	/* 无需上下拉电阻 */
		//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	/* IO口最大速度 */

		GPIO_InitStructure.GPIO_Pin = p_SPI->MISO_PIN;
		GPIO_Init(p_SPI->MISO_PORT, &GPIO_InitStructure);//初始化
	}
	//free(p_SPI);
}

/*
*********************************************************************************************************
*	函 数 名: bsp_SpiDelay
*	功能说明: 时序延迟
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_spiDelay(void)
{
#if 0
	uint32_t i;

	/*
		延迟5时， F407 (168MHz主频） GPIO模拟，实测 SCK 周期 = 480ns (大约2M)
	*/
	for (i = 0; i < 5; i++);
#else
	/*
		不添加延迟语句， F407 (168MHz主频） GPIO模拟，实测 SCK 周期 = 200ns (大约5M)
	*/
#endif
}

/*
*********************************************************************************************************
*	函 数 名: bsp_SPI_Read_Byte
*	功能说明: 从SPI总线读取1个字节共8个bit数据。  SCK上升沿采集数据, SCK_FREE决定SCK空闲时为高/低电平
*	形    参: SPIx 使用哪个SPI接口 读的时候TxData发送NOP（0xff或者0）
*	返 回 值: 读取到的字节
*********************************************************************************************************
*/
uint8_t bsp_SPI_Read_Byte(uint8_t SPI_SEL, u8 TxData)
{
	uint8_t i;
	uint8_t read = 0;

	SPI_CONFIG *p_SPI;

	p_SPI = SELToSPI(SPI_SEL);

	if(SPI_SEL < SPI4S)
	{
		while (SPI_I2S_GetFlagStatus(p_SPI->SPIx, SPI_I2S_FLAG_TXE) == RESET);	//等待发送区空  
		SPI_I2S_SendData(p_SPI->SPIx, TxData); //通过外设SPIx发送一个byte NOP，按照芯片文档发送0或者0xff
		while (SPI_I2S_GetFlagStatus(p_SPI->SPIx, SPI_I2S_FLAG_RXNE) == RESET);	//等待接收完一个byte  
		return SPI_I2S_ReceiveData(p_SPI->SPIx); //返回通过SPIx最近接收的数据	
	}
	else
	{
		if (p_SPI->CPOL == SPI_CPOL_High)
		{
			for (i = 0; i < 8; i++)
			{
				p_SPI->SCK_PORT->BRR = p_SPI->SCK_PIN;		//SCK_0
				bsp_spiDelay();
				read = read << 1;
				if ((p_SPI->MISO_PORT->IDR & p_SPI->MISO_PIN) != 0)		//MISO == 1?
				{
					read++;
				}
				p_SPI->SCK_PORT->BSRR = p_SPI->SCK_PIN;		//SCK_1
				bsp_spiDelay();
			}
		}
		else
		{
			for (i = 0; i < 8; i++)
			{
				read = read<<1;

				if ((p_SPI->MISO_PORT->IDR & p_SPI->MISO_PIN) != 0)		//MISO == 1?
				{
					read++;
				}
				p_SPI->SCK_PORT->BSRR = p_SPI->SCK_PIN;		//SCK_1
				bsp_spiDelay();
				p_SPI->SCK_PORT->BRR = p_SPI->SCK_PIN;		//SCK_0
				bsp_spiDelay();
			}
		}
		return read;
	}
}

/*
*********************************************************************************************************
*	函 数 名: bsp_SPI_Write_Byte
*	功能说明: 从SPI总线发送1个字节共8个bit数据。  SCK上升沿采集数据, SCK_FREE决定SCK空闲时为高/低电平
*	形    参: SPIx 使用哪个SPI接口，TxData 发送的数据
*	返 回 值: 无
*********************************************************************************************************
*/
uint8_t bsp_SPI_Write_Byte(uint8_t SPI_SEL, u8 TxData)
{
	uint8_t i;

	SPI_CONFIG *p_SPI;

	p_SPI = SELToSPI(SPI_SEL);

	if(SPI_SEL < SPI4S)
	{
		SPITimeout = SPIT_FLAG_TIMEOUT;
		while (SPI_I2S_GetFlagStatus(p_SPI->SPIx, SPI_I2S_FLAG_TXE) == RESET)	//等待发送区空  
		{
			if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(0);
		}
		SPI_I2S_SendData(p_SPI->SPIx, TxData); //发送数据
		while (SPI_I2S_GetFlagStatus(p_SPI->SPIx, SPI_I2S_FLAG_RXNE) == RESET)	//等待接收完一个byte
		{
			if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(1);
		}
		return SPI_I2S_ReceiveData(p_SPI->SPIx); //读取通过SPIx最近接收的数据
	}
	else
	{
		if (p_SPI->CPOL == SPI_CPOL_High)
		{
			for (i = 0; i < 8; i++)
			{
				if (TxData & 0x80)
				{
					p_SPI->MOSI_PORT->BSRR = p_SPI->MOSI_PIN;		//MOSI_1
				}
				else
				{
					p_SPI->MOSI_PORT->BRR = p_SPI->MOSI_PIN;		//MOSI_0
				}
				p_SPI->SCK_PORT->BRR = p_SPI->SCK_PIN;		//SCK_0
				TxData <<= 1;
				bsp_spiDelay();
				p_SPI->SCK_PORT->BSRR = p_SPI->SCK_PIN;		//SCK_1				/* SCK上升沿采集数据, SCK空闲时为高电平 */
				bsp_spiDelay();
			}
		}
		else
		{
			for(i = 0; i < 8; i++)
			{
				if (TxData & 0x80)
				{
					p_SPI->MOSI_PORT->BSRR = p_SPI->MOSI_PIN;		//MOSI_1
				}
				else
				{
					p_SPI->MOSI_PORT->BRR = p_SPI->MOSI_PIN;		//MOSI_0
				}
				bsp_spiDelay();
				p_SPI->SCK_PORT->BSRR = p_SPI->SCK_PIN;		//SCK_1
				TxData <<= 1;
				bsp_spiDelay();
				p_SPI->SCK_PORT->BRR = p_SPI->SCK_PIN;		//SCK_0
			}
			bsp_spiDelay();
		}
		return 1;
	}
}

/*******************************************************************************
* Function Name  : SPI_FLASH_SendHalfWord
* Description    : Sends a Half Word through the SPI interface and return the
*                  Half Word received from the SPI bus.
* Input          : Half Word : Half Word to send.
* Output         : None
* Return         : The value of the received Half Word.
*******************************************************************************/
uint16_t bsp_SPI_Write_HalfWord(uint8_t SPI_SEL, u16 HalfWord)
{
	SPI_CONFIG *p_SPI;

	p_SPI = SELToSPI(SPI_SEL);

	if(SPI_SEL < SPI4S)
	{
		SPITimeout = SPIT_FLAG_TIMEOUT;

		/* Loop while DR register in not emplty */
		while (SPI_I2S_GetFlagStatus(p_SPI->SPIx, SPI_I2S_FLAG_TXE) == RESET)
		{
			if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(2);
		}

		/* Send Half Word through the FLASH_SPI peripheral */
		SPI_I2S_SendData(p_SPI->SPIx, HalfWord);

		SPITimeout = SPIT_FLAG_TIMEOUT;

		/* Wait to receive a Half Word */
		while (SPI_I2S_GetFlagStatus(p_SPI->SPIx, SPI_I2S_FLAG_RXNE) == RESET)
		{
			if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(3);
		}
		/* Return the Half Word read from the SPI bus */
		return SPI_I2S_ReceiveData(p_SPI->SPIx);
	}
	else
	{
		uint8_t i;
	
		if (p_SPI->CPOL == SPI_CPOL_High)
		{
			for (i = 0; i < 16; i++)
			{
				if (HalfWord & 0x8000)
				{
					p_SPI->MOSI_PORT->BSRR = p_SPI->MOSI_PIN;		//MOSI_1
				}
				else
				{
					p_SPI->MOSI_PORT->BRR = p_SPI->MOSI_PIN;		//MOSI_0
				}
				p_SPI->SCK_PORT->BRR = p_SPI->SCK_PIN;		//SCK_0
				HalfWord <<= 1;
				bsp_spiDelay();
				p_SPI->SCK_PORT->BSRR = p_SPI->SCK_PIN;		//SCK_1				/* SCK上升沿采集数据, SCK空闲时为高电平 */
				bsp_spiDelay();
			}
		}
		else
		{
			for(i = 0; i < 16; i++)
			{
				if (HalfWord & 0x8000)
				{
					p_SPI->MOSI_PORT->BSRR = p_SPI->MOSI_PIN;		//MOSI_1
				}
				else
				{
					p_SPI->MOSI_PORT->BRR = p_SPI->MOSI_PIN;		//MOSI_0
				}
				bsp_spiDelay();
				p_SPI->SCK_PORT->BSRR = p_SPI->SCK_PIN;		//SCK_1	
				HalfWord <<= 1;
				bsp_spiDelay();
				p_SPI->SCK_PORT->BRR = p_SPI->SCK_PIN;		//SCK_0;
			}
			bsp_spiDelay();
		}
		return 1;
	}
}

/*
*********************************************************************************************************
*	函 数 名: bsp_SPI_Init
*	功能说明: 配置STM32内部SPI硬件的工作模式。 简化库函数，提高执行效率。 仅用于SPI接口间切换。
*	形    参: _cr1 寄存器值
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_Init_SPI_Quick(SPI_TypeDef* SPIx, uint16_t _cr1)
{
	SPIx->CR1 = ((SPIx->CR1 & CR1_CLEAR_Mask) | _cr1);
	  
	//SPI_Cmd(SPIx, DISABLE);			/* 先禁止SPI  */	    
    SPIx->CR1 &= CR1_SPE_Reset;	/* Disable the selected SPI peripheral */

	//SPI_Cmd(SPIx, ENABLE);			/* 使能SPI  */		    
    SPIx->CR1 |= CR1_SPE_Set;	  /* Enable the selected SPI peripheral */
}



void bsp_SPI_Write_16(uint8_t SPI_SEL, u16 TxData)
{
	bsp_SPI_Write_Byte(SPI_SEL, TxData >> 8);
	bsp_SPI_Write_Byte(SPI_SEL, TxData  );
}

void bsp_SPI_Write_32(uint8_t SPI_SEL, u32 TxData)
{
	bsp_SPI_Write_Byte(SPI_SEL, TxData >> 24);
	bsp_SPI_Write_Byte(SPI_SEL, TxData >> 16);
	bsp_SPI_Write_Byte(SPI_SEL, TxData >> 8);
	bsp_SPI_Write_Byte(SPI_SEL, TxData  );
}

/*
*********************************************************************************************************
*	函 数 名: bsp_SpiBusEnter
*	功能说明: 占用SPI总线
*	形    参: 无
*	返 回 值: 0 表示不忙  1表示忙
*********************************************************************************************************
*/
void bsp_SpiBusEnter(uint8_t SPI_SEL)
{
	 SPI_CONFIG *p_SPI;
	 
	 p_SPI = SELToSPI(SPI_SEL);

	 p_SPI->BUSY = TRUE;
}

/*
*********************************************************************************************************
*	函 数 名: bsp_SpiBusExit
*	功能说明: 释放占用的SPI总线
*	形    参: 无
*	返 回 值: 0 表示不忙  1表示忙
*********************************************************************************************************
*/
void bsp_SpiBusExit(uint8_t SPI_SEL)
{
	SPI_CONFIG *p_SPI;
	
	p_SPI = SELToSPI(SPI_SEL);
	
	p_SPI->BUSY = FALSE;
}

/*
*********************************************************************************************************
*	函 数 名: bsp_SpiBusBusy
*	功能说明: 判断SPI总线忙。方法是检测其他SPI芯片的片选信号是否为1
*	形    参: 无
*	返 回 值: 0 表示不忙  1表示忙
*********************************************************************************************************
*/
bool bsp_SpiBusBusy(uint8_t SPI_SEL)
{
	SPI_CONFIG *p_SPI;
	
	p_SPI = SELToSPI(SPI_SEL);
	
	return p_SPI->BUSY;
}

void bsp_SpiBusBusyCheck(uint8_t SPI_SEL, u8 chkcmd, u8 stacmd, u8 flag)
{
	u8 FLASH_Status = 0;
	
	/* 发送 读状态寄存器 命令 */
	bsp_SPI_Write_Byte(SPI_SEL, chkcmd);
	
	SPITimeout = SPIT_FLAG_TIMEOUT;
	/* 若FLASH忙碌，则等待 */
	do
	{
	  /* 读取FLASH芯片的状态寄存器 */
	  FLASH_Status = bsp_SPI_Read_Byte(SPI_SEL, stacmd);   
	
	  {
		if((SPITimeout--) == 0) 
		{
		  SPI_TIMEOUT_UserCallback(4);
		  return;
		}
	  } 
	}
	while ((FLASH_Status & flag) == SET); /* 正在写入标志 */
}

/*
*********************************************************************************************************
*	函 数 名: bsp_SetSpiSck
*	功能说明: 用于软件模式。设置SCK GPIO的状态。在函数CS=0之前被调用，用于不同相序的SPI设备间切换。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_SetSpiSck(uint8_t SPI_SEL, uint8_t _data)
{
	SPI_CONFIG *p_SPI;
	
	p_SPI = SELToSPI(SPI_SEL);
	
	if (_data == 0)
	{
		p_SPI->SCK_PORT->BRR = p_SPI->SCK_PIN;		//SCK_0
	}
	else
	{
		p_SPI->SCK_PORT->BSRR = p_SPI->SCK_PIN;		//SCK_1	
	}
}

//SPI速度设置函数
//SPI速度=fAPB2/分频系数
//@ref SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256  
//fAPB2时钟一般为84Mhz：
void bsp_SPI_SetSpeed(uint8_t SPI_SEL, u8 SPI_BaudRatePrescaler)
{
	SPI_CONFIG *p_SPI;
	
	p_SPI = SELToSPI(SPI_SEL);

	if(SPI_SEL < SPI4S)
	{
		SPI_Cmd(p_SPI->SPIx, DISABLE); //使能SPIx
		assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
		p_SPI->SPIx->CR1 &= 0XFFC7;//位3-5清零，用来设置波特率
		p_SPI->SPIx->CR1 |= SPI_BaudRatePrescaler;	//设置SPIx速度 
		SPI_Cmd(p_SPI->SPIx, ENABLE); //使能SPIx
	}
}

/**
  * @brief  等待超时回调函数
  * @param  None.
  * @retval None.
  */
static  uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
  /* 等待超时后的处理,输出错误信息 */
  SPI_ERROR("SPI 等待超时!errorCode = %d",errorCode);
  return 0;
}


/*
*********************************************************************************************************
*	函 数 名: bsp_GetRCCofTIM
*	功能说明: 根据TIM 得到RCC寄存器
*	形    参：无
*	返 回 值: TIM外设时钟名
*********************************************************************************************************
*/
uint32_t bsp_GetRCCofSPI(SPI_TypeDef* SPIx)
{
	uint32_t rcc = 0;

	/*
	SPI1-3都在APB1 
	*/
	if (SPIx == SPI1)
	{
		rcc = RCC_APB2Periph_SPI1;
	}
	else if (SPIx == SPI2)
	{
		rcc = RCC_APB1Periph_SPI2;
	}
	else if (SPIx == SPI3)
	{
		rcc = RCC_APB1Periph_SPI3;
	}

	return rcc;
}

/*
*********************************************************************************************************
*	函 数 名: bsp_GetAFofTIM
*	功能说明: 根据TIM 得到AF寄存器配置
*	形    参: 无
*	返 回 值: AF寄存器配置
*********************************************************************************************************
*/
//uint8_t bsp_GetAFofSPI(SPI_TypeDef* SPIx)
//{
//	uint8_t ret = 0;

//	if (SPIx == SPI1)
//	{
//		ret = GPIO_AF_SPI1;
//	}
//	else if (SPIx == SPI2)
//	{
//		ret = GPIO_AF_SPI2;
//	}
//	else if (SPIx == SPI3)
//	{
//		ret = GPIO_AF_SPI3;
//	}
//	return ret;
//}



/***************************** (END OF FILE) *********************************/
