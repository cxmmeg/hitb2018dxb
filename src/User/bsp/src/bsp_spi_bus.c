/*
*********************************************************************************************************
*
*	ģ������ : SPI��������
*	�ļ����� : bsp_spi_bus.h
*	��    �� : V1.2
*	˵    �� : SPI���ߵײ��������ṩSPI���á��շ����ݡ����豸����SPI֧�֡�
*	�޸ļ�¼ :
*		�汾��  ����        ����    ˵��
*       v1.0    2014-10-24 white  �װ档������FLASH��TSC2046��VS1053��AD7705��ADS1256��SPI�豸������
*									���շ����ݵĺ������л��ܷ��ࡣ�������ͬ�ٶȵ��豸��Ĺ������⡣
*		V1.1	2015-02-25 white  Ӳ��SPIʱ��û�п���GPIOBʱ�ӣ��ѽ����
*		V1.2	2015-07-23 white  �޸� bsp_SPI_Init() ���������ӿ���SPIʱ�ӵ���䡣�淶Ӳ��SPI�����SPI�ĺ궨��.
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


/* ����ÿ��SPI�ڽṹ����� */
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
*	�� �� ��: SELToSPI
*	����˵��: ��SELת��ΪSPIָ��
*	��    ��: SEL: SPI��(SPI1H-SPI3H SPI4S-SPI8S)
*	�� �� ֵ: SPIָ��
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
		/* �����κδ��� */
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

		SPI_Cmd(p_SPI->SPIx, DISABLE);	//����SPI����
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//100MHz

		RCC_APB2PeriphClockCmd(bsp_GetRCCofGPIO(p_SPI->SCK_PORT) | bsp_GetRCCofGPIO(p_SPI->MISO_PORT)				\
								| bsp_GetRCCofGPIO(p_SPI->MOSI_PORT), ENABLE);//ʹ��SCKʱ��
		
		if ( p_SPI->SPIx == SPI1 )
		{
		    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
		}
		else
		{
		    RCC_APB1PeriphClockCmd(bsp_GetRCCofSPI(p_SPI->SPIx), ENABLE);//ʹ��SPI1ʱ��
		}

		GPIO_InitStructure.GPIO_Pin = p_SPI->SCK_PIN;
		GPIO_Init(p_SPI->SCK_PORT, &GPIO_InitStructure);//��ʼ��
		
		GPIO_InitStructure.GPIO_Pin = p_SPI->MISO_PIN;
		GPIO_Init(p_SPI->MISO_PORT, &GPIO_InitStructure);//��ʼ��
		
		GPIO_InitStructure.GPIO_Pin = p_SPI->MOSI_PIN;
		GPIO_Init(p_SPI->MOSI_PORT, &GPIO_InitStructure);//��ʼ��


		//GPIO_PinAFConfig(p_SPI->SCK_PORT, bsp_GetPinSource(p_SPI->SCK_PIN), bsp_GetAFofSPI(p_SPI->SPIx)); //PB6����Ϊ SPI1
		//GPIO_PinAFConfig(p_SPI->MISO_PORT, bsp_GetPinSource(p_SPI->MISO_PIN), bsp_GetAFofSPI(p_SPI->SPIx)); //PB7����Ϊ SPI1
		//GPIO_PinAFConfig(p_SPI->MOSI_PORT, bsp_GetPinSource(p_SPI->MOSI_PIN), bsp_GetAFofSPI(p_SPI->SPIx)); //PB7����Ϊ SPI1

		//����ֻ���SPI�ڳ�ʼ��
		if ( p_SPI->SPIx == SPI1 )
		{
		    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE);//��λSPI1
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, DISABLE);//ֹͣ��λSPI1
		}
		else
		{
		    RCC_APB1PeriphResetCmd(bsp_GetRCCofSPI(p_SPI->SPIx), ENABLE);//��λSPI1
			RCC_APB1PeriphResetCmd(bsp_GetRCCofSPI(p_SPI->SPIx), DISABLE);//ֹͣ��λSPI1
		}
		
		SPI_InitStructure.SPI_Direction = p_SPI->Direction;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
		SPI_InitStructure.SPI_Mode = p_SPI->Master;		//����SPI����ģʽ:����Ϊ��SPI
		SPI_InitStructure.SPI_DataSize = p_SPI->DataSize;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
		SPI_InitStructure.SPI_CPOL = p_SPI->CPOL;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
		SPI_InitStructure.SPI_CPHA = p_SPI->CPHA;	//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
		SPI_InitStructure.SPI_BaudRatePrescaler = p_SPI->SPEED;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵSPI_BaudRatePrescaler
		SPI_InitStructure.SPI_FirstBit = p_SPI->FirstBit;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
		SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
		SPI_Init(p_SPI->SPIx, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
		
		SPI_Cmd(p_SPI->SPIx, ENABLE);	//ʹ��SPI����

		bsp_SPI_Write_Byte(SPI_SEL, 0xff);//�������䣬����8��ʱ�Ӹ����豸��ʹMOSIһֱά�ָߵ�ƽ����ȻҲ����ά�ֵ͵�ƽ��д0X00�Ϳ��ԣ�����ͨ����������ά�ָߵ�ƽ

	}
	else
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//���ù���
		//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	//�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//100MHz
		//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//����������

		RCC_APB1PeriphClockCmd(bsp_GetRCCofGPIO(p_SPI->SCK_PORT), ENABLE);//ʹ��SCKʱ��
		RCC_APB1PeriphClockCmd(bsp_GetRCCofGPIO(p_SPI->MISO_PORT), ENABLE);//ʹ��MISOʱ��
		RCC_APB1PeriphClockCmd(bsp_GetRCCofGPIO(p_SPI->MOSI_PORT), ENABLE);//ʹ��MOSIʱ��

		GPIO_InitStructure.GPIO_Pin = p_SPI->SCK_PIN;
		GPIO_Init(p_SPI->SCK_PORT, &GPIO_InitStructure);//��ʼ��
		
		GPIO_InitStructure.GPIO_Pin = p_SPI->MOSI_PIN;
		GPIO_Init(p_SPI->MOSI_PORT, &GPIO_InitStructure);//��ʼ��

		/* ����GPIOΪ��������ģʽ(ʵ����CPU��λ���������״̬) */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		/* ��Ϊ����� */
		//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		/* ��Ϊ����ģʽ */
		//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	/* �������������� */
		//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	/* IO������ٶ� */

		GPIO_InitStructure.GPIO_Pin = p_SPI->MISO_PIN;
		GPIO_Init(p_SPI->MISO_PORT, &GPIO_InitStructure);//��ʼ��
	}
	//free(p_SPI);
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_SpiDelay
*	����˵��: ʱ���ӳ�
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_spiDelay(void)
{
#if 0
	uint32_t i;

	/*
		�ӳ�5ʱ�� F407 (168MHz��Ƶ�� GPIOģ�⣬ʵ�� SCK ���� = 480ns (��Լ2M)
	*/
	for (i = 0; i < 5; i++);
#else
	/*
		������ӳ���䣬 F407 (168MHz��Ƶ�� GPIOģ�⣬ʵ�� SCK ���� = 200ns (��Լ5M)
	*/
#endif
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_SPI_Read_Byte
*	����˵��: ��SPI���߶�ȡ1���ֽڹ�8��bit���ݡ�  SCK�����زɼ�����, SCK_FREE����SCK����ʱΪ��/�͵�ƽ
*	��    ��: SPIx ʹ���ĸ�SPI�ӿ� ����ʱ��TxData����NOP��0xff����0��
*	�� �� ֵ: ��ȡ�����ֽ�
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
		while (SPI_I2S_GetFlagStatus(p_SPI->SPIx, SPI_I2S_FLAG_TXE) == RESET);	//�ȴ���������  
		SPI_I2S_SendData(p_SPI->SPIx, TxData); //ͨ������SPIx����һ��byte NOP������оƬ�ĵ�����0����0xff
		while (SPI_I2S_GetFlagStatus(p_SPI->SPIx, SPI_I2S_FLAG_RXNE) == RESET);	//�ȴ�������һ��byte  
		return SPI_I2S_ReceiveData(p_SPI->SPIx); //����ͨ��SPIx������յ�����	
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
*	�� �� ��: bsp_SPI_Write_Byte
*	����˵��: ��SPI���߷���1���ֽڹ�8��bit���ݡ�  SCK�����زɼ�����, SCK_FREE����SCK����ʱΪ��/�͵�ƽ
*	��    ��: SPIx ʹ���ĸ�SPI�ӿڣ�TxData ���͵�����
*	�� �� ֵ: ��
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
		while (SPI_I2S_GetFlagStatus(p_SPI->SPIx, SPI_I2S_FLAG_TXE) == RESET)	//�ȴ���������  
		{
			if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(0);
		}
		SPI_I2S_SendData(p_SPI->SPIx, TxData); //��������
		while (SPI_I2S_GetFlagStatus(p_SPI->SPIx, SPI_I2S_FLAG_RXNE) == RESET)	//�ȴ�������һ��byte
		{
			if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(1);
		}
		return SPI_I2S_ReceiveData(p_SPI->SPIx); //��ȡͨ��SPIx������յ�����
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
				p_SPI->SCK_PORT->BSRR = p_SPI->SCK_PIN;		//SCK_1				/* SCK�����زɼ�����, SCK����ʱΪ�ߵ�ƽ */
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
				p_SPI->SCK_PORT->BSRR = p_SPI->SCK_PIN;		//SCK_1				/* SCK�����زɼ�����, SCK����ʱΪ�ߵ�ƽ */
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
*	�� �� ��: bsp_SPI_Init
*	����˵��: ����STM32�ڲ�SPIӲ���Ĺ���ģʽ�� �򻯿⺯�������ִ��Ч�ʡ� ������SPI�ӿڼ��л���
*	��    ��: _cr1 �Ĵ���ֵ
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_Init_SPI_Quick(SPI_TypeDef* SPIx, uint16_t _cr1)
{
	SPIx->CR1 = ((SPIx->CR1 & CR1_CLEAR_Mask) | _cr1);
	  
	//SPI_Cmd(SPIx, DISABLE);			/* �Ƚ�ֹSPI  */	    
    SPIx->CR1 &= CR1_SPE_Reset;	/* Disable the selected SPI peripheral */

	//SPI_Cmd(SPIx, ENABLE);			/* ʹ��SPI  */		    
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
*	�� �� ��: bsp_SpiBusEnter
*	����˵��: ռ��SPI����
*	��    ��: ��
*	�� �� ֵ: 0 ��ʾ��æ  1��ʾæ
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
*	�� �� ��: bsp_SpiBusExit
*	����˵��: �ͷ�ռ�õ�SPI����
*	��    ��: ��
*	�� �� ֵ: 0 ��ʾ��æ  1��ʾæ
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
*	�� �� ��: bsp_SpiBusBusy
*	����˵��: �ж�SPI����æ�������Ǽ������SPIоƬ��Ƭѡ�ź��Ƿ�Ϊ1
*	��    ��: ��
*	�� �� ֵ: 0 ��ʾ��æ  1��ʾæ
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
	
	/* ���� ��״̬�Ĵ��� ���� */
	bsp_SPI_Write_Byte(SPI_SEL, chkcmd);
	
	SPITimeout = SPIT_FLAG_TIMEOUT;
	/* ��FLASHæµ����ȴ� */
	do
	{
	  /* ��ȡFLASHоƬ��״̬�Ĵ��� */
	  FLASH_Status = bsp_SPI_Read_Byte(SPI_SEL, stacmd);   
	
	  {
		if((SPITimeout--) == 0) 
		{
		  SPI_TIMEOUT_UserCallback(4);
		  return;
		}
	  } 
	}
	while ((FLASH_Status & flag) == SET); /* ����д���־ */
}

/*
*********************************************************************************************************
*	�� �� ��: bsp_SetSpiSck
*	����˵��: �������ģʽ������SCK GPIO��״̬���ں���CS=0֮ǰ�����ã����ڲ�ͬ�����SPI�豸���л���
*	��    ��: ��
*	�� �� ֵ: ��
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

//SPI�ٶ����ú���
//SPI�ٶ�=fAPB2/��Ƶϵ��
//@ref SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256  
//fAPB2ʱ��һ��Ϊ84Mhz��
void bsp_SPI_SetSpeed(uint8_t SPI_SEL, u8 SPI_BaudRatePrescaler)
{
	SPI_CONFIG *p_SPI;
	
	p_SPI = SELToSPI(SPI_SEL);

	if(SPI_SEL < SPI4S)
	{
		SPI_Cmd(p_SPI->SPIx, DISABLE); //ʹ��SPIx
		assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//�ж���Ч��
		p_SPI->SPIx->CR1 &= 0XFFC7;//λ3-5���㣬�������ò�����
		p_SPI->SPIx->CR1 |= SPI_BaudRatePrescaler;	//����SPIx�ٶ� 
		SPI_Cmd(p_SPI->SPIx, ENABLE); //ʹ��SPIx
	}
}

/**
  * @brief  �ȴ���ʱ�ص�����
  * @param  None.
  * @retval None.
  */
static  uint16_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
  /* �ȴ���ʱ��Ĵ���,���������Ϣ */
  SPI_ERROR("SPI �ȴ���ʱ!errorCode = %d",errorCode);
  return 0;
}


/*
*********************************************************************************************************
*	�� �� ��: bsp_GetRCCofTIM
*	����˵��: ����TIM �õ�RCC�Ĵ���
*	��    �Σ���
*	�� �� ֵ: TIM����ʱ����
*********************************************************************************************************
*/
uint32_t bsp_GetRCCofSPI(SPI_TypeDef* SPIx)
{
	uint32_t rcc = 0;

	/*
	SPI1-3����APB1 
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
*	�� �� ��: bsp_GetAFofTIM
*	����˵��: ����TIM �õ�AF�Ĵ�������
*	��    ��: ��
*	�� �� ֵ: AF�Ĵ�������
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
