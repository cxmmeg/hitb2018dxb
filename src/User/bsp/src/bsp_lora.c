#include "bsp.h"

// registers
#define REG_FIFO                 		0x00
#define REG_OP_MODE              		0x01
#define REG_FRF_MSB              		0x06
#define REG_FRF_MID              		0x07
#define REG_FRF_LSB              		0x08
#define REG_PA_CONFIG            		0x09
#define REG_LR_OCP				 		0X0b
//#define REG_LNA                		  0x0c
#define REG_FIFO_ADDR_PTR        		0x0d
#define REG_FIFO_TX_BASE_ADDR    		0x0e
#define REG_FIFO_RX_BASE_ADDR    		0x0f
#define REG_FIFO_RX_CURRENT_ADDR 		0x10
#define REG_IRQ_FLAGS            		0x12
#define REG_RX_NB_BYTES          		0x13
#define REG_PKT_RSSI_VALUE       		0x1a
#define REG_PKT_SNR_VALUE        		0x1b
#define REG_MODEM_CONFIG_1       		0x1d
#define REG_MODEM_CONFIG_2       		0x1e
#define REG_PREAMBLE_MSB         		0x20
#define REG_PREAMBLE_LSB         		0x21
#define REG_PAYLOAD_LENGTH       		0x22
#define REG_MODEM_CONFIG_3       		0x26
#define REG_RSSI_WIDEBAND        		0x2c
#define REG_DETECTION_OPTIMIZE   		0x31
#define REG_DETECTION_THRESHOLD  		0x37
#define REG_SYNC_WORD            		0x39
#define REG_DIO_MAPPING_1        		0x40
#define REG_VERSION              		0x42
#define REG_PaDac				 		0x4d //add REG_PaDac
		
// modes		
#define MODE_LONG_RANGE_MODE     		0x80
#define MODE_SLEEP               		0x00
#define MODE_STDBY               		0x01
#define MODE_TX                  		0x03
#define MODE_RX_CONTINUOUS       		0x05
#define MODE_RX_SINGLE           		0x06
		
// PA config		
#define PA_BOOST                 		0x80
#define RFO                      		0x70
// IRQ masks
#define IRQ_TX_DONE_MASK           		0x08
#define IRQ_PAYLOAD_CRC_ERROR_MASK		0x20
#define IRQ_RX_DONE_MASK           		0x40

#define MAX_PKT_LENGTH           		255

static u8 _packetIndex = 0;
static u8 _implicitHeaderMode;
static u8 _frequency;


//如果需要重新初始化SPI口
#if 0
static void Lora_CfgSpiHard(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	
	/*
	STM32F4XX 时钟计算.
		HCLK = 168M
		PCLK1 = HCLK / 4 = 42M
		PCLK2 = HCLK / 2 = 84M

		SPI2、SPI3 在 PCLK1, 时钟42M
		SPI1       在 PCLK2, 时钟84M

		STM32F4 支持的最大SPI时钟为 37.5 Mbits/S, 因此需要分频。下面使用的是SPI1。
	*/
	/* 配置SPI硬件参数 */
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	/* 数据方向：2线全双工 */
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		/* STM32的SPI工作模式 ：主机模式 */
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;	/* 数据位长度 ： 8位 */
	/* SPI_CPOL和SPI_CPHA结合使用决定时钟和数据采样点的相位关系、
	   本例配置: 总线空闲是低电平,第1个边沿采样数据。
	*/
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;			/* 片选控制方式：软件控制 */

	/* 设置波特率预分频系数 84MHz / 16 = 5.25MHz，CC1101支持的最大SPI时钟为10MHz
	   这里选择SPI_BaudRatePrescaler_8容易出错。
	*/
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	/* 数据位传输次序：高位先传 */
	SPI_InitStructure.SPI_CRCPolynomial = 7;			/* CRC多项式寄存器，复位后为7。本例程不用 */
	SPI_Init(SPI3, &SPI_InitStructure);

	SPI_Cmd(SPI3, ENABLE);				/* 使能SPI  */
}
#endif


u8 bsp_Init_Lora(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*使能GPIO时钟 */
	RCC_APB2PeriphClockCmd(bsp_GetRCCofGPIO(Lora_RST_PORT) | bsp_GetRCCofGPIO(Lora_CSN_PORT) \
							| bsp_GetRCCofGPIO(Lora_DIO0_PORT), ENABLE);

	
	/* 配置CC1101的CSN引脚 */
	/* 配置为推挽输出模式 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	
	GPIO_InitStructure.GPIO_Pin = Lora_CSN_PIN;
	GPIO_Init(Lora_CSN_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = Lora_RST_PIN;
	GPIO_Init(Lora_RST_PORT, &GPIO_InitStructure);
	
	/* 配置CC1101的 GDO0 引脚 */
	/* 配置为输入带上拉 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 	

	GPIO_InitStructure.GPIO_Pin = Lora_DIO0_PIN;
	GPIO_Init(Lora_DIO0_PORT, &GPIO_InitStructure);

	Lora_RST_0();
	bsp_DelayUS(120);
	Lora_RST_1();
	bsp_DelayMS(5);
	
	Lora_CSN_1();		//SPI片选取消	

	bsp_Init_SPI(Lora_SPI);  
	//Lora_CfgSpiHard();
	
	bsp_DelayMS(5); //等待5ms比较稳妥

	// check version
	uint8_t version = Lora_readReg(REG_VERSION);
	if (version != 0x12) 
	{ 
		return 0; 
	}

	Lora_sleep();
	return 1;
}


/*
*********************************************************************************************************
*	函 数 名: Lora_writeReg
*	功能说明: 用于向Lora特定的寄存器写入数据
*	形    参: _ucRegAddr: Lora的命令+寄存器地址。
 		      _usValue:   将要向寄存器写入的数据
*	返 回 值: Lora的status寄存器的状态		        
*********************************************************************************************************
*/
uint8_t Lora_writeReg(uint8_t reg, uint8_t value)
{
	uint8_t status;

	
	/* 置低CSN，使能SPI传输 */
	Lora_CSN_0();
			
	/* 发送命令及寄存器号 */
	status = bsp_SPI_Write_Byte(Lora_SPI, (0x80 | reg));
		 
	 /* 向寄存器写入数据 */
	bsp_SPI_Write_Byte(Lora_SPI, value); 
	          
	/* CSN拉高，完成 */	   
	Lora_CSN_1();	
		
	/* 返回状态寄存器的值 */
	return status;
}

/*
*********************************************************************************************************
*	函 数 名: Lora_readReg
*	功能说明: 用于从Lora特定的寄存器读出数据
*	形    参: reg: Lora的命令+寄存器地址
*	返 回 值: 寄存器中的数据		        
*********************************************************************************************************
*/
uint8_t Lora_readReg(uint8_t reg)
{
 	uint8_t result;
	
	/* 置低CSN，使能SPI传输 */
 	Lora_CSN_0();
			
  	 /* 发送寄存器号 */
	bsp_SPI_Write_Byte(Lora_SPI, ( 0x7f & reg ) );

	 /* 读取寄存器的值 */
	result = bsp_SPI_Write_Byte(Lora_SPI, 0x00);
	            
   	/*CSN拉高，完成*/
	Lora_CSN_1();		
   	
	return result;
}	

void Lora_receive(int size)
{
	if (size > 0)
	{
		Lora_implicitHeaderMode();
		Lora_writeReg(REG_PAYLOAD_LENGTH, size & 0xff);
	} 
	else 
	{
		Lora_explicitHeaderMode();
	}
	Lora_writeReg(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_RX_CONTINUOUS);
}

void Lora_idle(void)
{
	Lora_writeReg(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_STDBY);
}

void Lora_sleep(void)
{
	Lora_writeReg(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_SLEEP);
}

//void Lora_setTxPower(int level, int outputPin)
//{
//    if (PA_OUTPUT_RFO_PIN == outputPin)
//    {
//        // RFO
//        if (level < -1)
//        {
//            level = -1;
//        }
//        else if (level > 14)
//        {
//            level = 14;
//        }
//        Lora_writeReg(REG_PaDac,0x84);
//        Lora_writeReg(REG_PA_CONFIG, RFO | (level + 1));
//        //spiWrite(RH_RF95_REG_09_PA_CONFIG, RH_RF95_MAX_POWER | (power + 1));
////  	Lora_writeReg(REG_PA_CONFIG, RFO | level);
//    }
//    else
//    {
//        // PA BOOST
//        if (level < 2)
//        {
//            level = 2;
//        }
//        else if (level > 17)
//        {
//            level = 17;
//        }
//        //Lora_writeReg(REG_LR_OCP,0x3f);
//        Lora_writeReg(REG_PaDac,0x84);
//        Lora_writeReg(REG_PA_CONFIG, PA_BOOST | (level - 2));//Lora_writeReg(REG_PA_CONFIG, PA_BOOST | (level - 2));

//    }
//}

void Lora_setTxPowerMax(int level)
{
    if (level < 5)
    {
        level = 5;
    }
    else if(level > 20)
    {
        level = 20;
    }
    Lora_writeReg(REG_LR_OCP,0x3f);
    Lora_writeReg(REG_PaDac,0x87);//Open PA_BOOST
    Lora_writeReg(REG_PA_CONFIG, PA_BOOST | (level - 5));
}

void Lora_setFrequency(uint64_t frequency)
{
    uint64_t frf = ((uint64_t)frequency << 19) / 32000000;
    Lora_writeReg(REG_FRF_MSB, (uint8_t)(frf >> 16));
    Lora_writeReg(REG_FRF_MID, (uint8_t)(frf >> 8));
    Lora_writeReg(REG_FRF_LSB, (uint8_t)(frf >> 0));
}

void Lora_setSpreadingFactor(int sf)
{
    if (sf < 6)
    {
        sf = 6;
    }
    else if (sf > 12)
    {
        sf = 12;
    }
    if (sf == 6)
    {
        Lora_writeReg(REG_DETECTION_OPTIMIZE, 0xc5);
        Lora_writeReg(REG_DETECTION_THRESHOLD, 0x0c);
    }
    else
    {
        Lora_writeReg(REG_DETECTION_OPTIMIZE, 0xc3);
        Lora_writeReg(REG_DETECTION_THRESHOLD, 0x0a);
    }
    Lora_writeReg(REG_MODEM_CONFIG_2, (Lora_readReg(REG_MODEM_CONFIG_2) & 0x0f) | ((sf << 4) & 0xf0));
}

void Lora_setSignalBandwidth(long sbw)
{
    int bw;

    if (sbw <= 7.8E3)
    {
        bw = 0;
    }
    else if (sbw <= 10.4E3)
    {
        bw = 1;
    }
    else if (sbw <= 15.6E3)
    {
        bw = 2;
    }
    else if (sbw <= 20.8E3)
    {
        bw = 3;
    }
    else if (sbw <= 31.25E3)
    {
        bw = 4;
    }
    else if (sbw <= 41.7E3)
    {
        bw = 5;
    }
    else if (sbw <= 62.5E3)
    {
        bw = 6;
    }
    else if (sbw <= 125E3)
    {
        bw = 7;
    }
    else if (sbw <= 250E3)
    {
        bw = 8;
    }
    else /*if (sbw <= 250E3)*/
    {
        bw = 9;
    }
    Lora_writeReg(REG_MODEM_CONFIG_1,(Lora_readReg(REG_MODEM_CONFIG_1) & 0x0f) | (bw << 4));
}

void Lora_setCodingRate4(int denominator)
{
    if (denominator < 5)
    {
        denominator = 5;
    }
    else if (denominator > 8)
    {
        denominator = 8;
    }
    int cr = denominator - 4;
    Lora_writeReg(REG_MODEM_CONFIG_1, (Lora_readReg(REG_MODEM_CONFIG_1) & 0xf1) | (cr << 1));
}

void Lora_setPreambleLength(u16 length)
{
    Lora_writeReg(REG_PREAMBLE_MSB, (uint8_t)(length >> 8));
    Lora_writeReg(REG_PREAMBLE_LSB, (uint8_t)(length >> 0));
}

void Lora_setSyncWord(int sw)
{
    Lora_writeReg(REG_SYNC_WORD, sw);
}

void Lora_enableCRC(void)
{
    Lora_writeReg(REG_MODEM_CONFIG_2, Lora_readReg(REG_MODEM_CONFIG_2) | 0x04);
}

void Lora_disableCRC(void)
{
    Lora_writeReg(REG_MODEM_CONFIG_2, Lora_readReg(REG_MODEM_CONFIG_2) & 0xfb);
}

uint8_t Lora_random(void)
{
    return Lora_readReg(REG_RSSI_WIDEBAND);
}

void Lora_RegConfig(void)
{
	// set frequency
	Lora_setFrequency(433000000);
	// set base addresses
	Lora_writeReg(REG_FIFO_TX_BASE_ADDR, 0);
	Lora_writeReg(REG_FIFO_RX_BASE_ADDR, 0);
	// set LNA boost
	Lora_writeReg(0x0C, Lora_readReg(0x0C) | 0x03);
	// set auto AGC
	Lora_writeReg(REG_MODEM_CONFIG_3, 0x04);
	// set output power to 12 dBm
	Lora_setTxPowerMax(20);	//PA_BOOST
	// set Spreading Factor to 7 (6~12)
	Lora_setSpreadingFactor(11);
	// put in standby mode
	Lora_setSignalBandwidth(125E3);
	//setCodingRate4(5);
	Lora_setSyncWord(0x34);
	Lora_enableCRC();
	Lora_idle();
}


u8 Lora_beginPacket(u8 implicitHeader)
{
    // put in standby mode
    Lora_idle();
    if (implicitHeader)
    {
        Lora_implicitHeaderMode();
    }
    else
    {
        Lora_explicitHeaderMode();
    }
    // reset FIFO address and paload length
    Lora_writeReg(REG_FIFO_ADDR_PTR, 0);
    Lora_writeReg(REG_PAYLOAD_LENGTH, 0);
    return 1;
}

u8 Lora_endPacket(void)
{
    // put in TX mode
    Lora_writeReg(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_TX);
    // wait for TX done
    while((Lora_readReg(REG_IRQ_FLAGS) & IRQ_TX_DONE_MASK) == 0);
    // clear IRQ's
    Lora_writeReg(REG_IRQ_FLAGS, IRQ_TX_DONE_MASK);
    return 1;
}

u8 Lora_parsePacket(int size)
{
    int packetLength = 0;
    int irqFlags = Lora_readReg(REG_IRQ_FLAGS);

    if (size > 0)
    {
        Lora_implicitHeaderMode();
        Lora_writeReg(REG_PAYLOAD_LENGTH, size & 0xff);
    }
    else
    {
        Lora_explicitHeaderMode();
    }

    // clear IRQ's
    Lora_writeReg(REG_IRQ_FLAGS, irqFlags);

    if ((irqFlags & IRQ_RX_DONE_MASK) && (irqFlags & IRQ_PAYLOAD_CRC_ERROR_MASK) == 0)
    {
        // received a packet
        _packetIndex = 0;
        // read packet length
        if (_implicitHeaderMode)
        {
            packetLength = Lora_readReg(REG_PAYLOAD_LENGTH);
        }
        else
        {
            packetLength = Lora_readReg(REG_RX_NB_BYTES);
        }
        // set FIFO address to current RX address
        Lora_writeReg(REG_FIFO_ADDR_PTR, Lora_readReg(REG_FIFO_RX_CURRENT_ADDR));
        // put in standby mode
        Lora_idle();
    }
    else if (Lora_readReg(REG_OP_MODE) != (MODE_LONG_RANGE_MODE | MODE_RX_SINGLE))
    {
        // not currently in RX mode
        // reset FIFO address
        Lora_writeReg(REG_FIFO_ADDR_PTR, 0);
        // put in single RX mode
        Lora_writeReg(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_RX_SINGLE);
    }
    return packetLength;
}

int8_t Lora_packetRssi(void)
{
    return (Lora_readReg(REG_PKT_RSSI_VALUE) - (_frequency < 868E6 ? 164 : 157));
}

float Lora_packetSnr(void)
{
    return ((int8_t)Lora_readReg(REG_PKT_SNR_VALUE)) * 0.25;
}

u8 Lora_writeByte(uint8_t byte)
{
	return Lora_writeBuf(&byte, sizeof(byte));
}

u8 Lora_writeBuf(const uint8_t *buffer, u8 size)
{
	u8 currentLength = Lora_readReg(REG_PAYLOAD_LENGTH);
	// check size
	if ((currentLength + size) > MAX_PKT_LENGTH) 
	{
		size = MAX_PKT_LENGTH - currentLength;
	}
	// write data
	for (u8 i = 0; i < size; i++) 
	{
		Lora_writeReg(REG_FIFO, buffer[i]);
	}
	// update length
	Lora_writeReg(REG_PAYLOAD_LENGTH, currentLength + size);
	return size;
}


void Lora_explicitHeaderMode(void)
{
	_implicitHeaderMode = 0;
	Lora_writeReg(REG_MODEM_CONFIG_1, Lora_readReg(REG_MODEM_CONFIG_1) & 0xfe);
}

void Lora_implicitHeaderMode(void)
{
	_implicitHeaderMode = 1;
	Lora_writeReg(REG_MODEM_CONFIG_1, Lora_readReg(REG_MODEM_CONFIG_1) | 0x01);
}


int Lora_available(void)
{
    return (Lora_readReg(REG_RX_NB_BYTES) - _packetIndex);
}

int Lora_read(void)
{
    if (!Lora_available())
    {
        return -1;
    }
    _packetIndex++;
    return Lora_readReg(REG_FIFO);
}

int Lora_peek(void)
{
    if (!Lora_available())
    {
        return -1;
    }
    // store current FIFO address
    int currentAddress = Lora_readReg(REG_FIFO_ADDR_PTR);
    // read
    uint8_t b = Lora_readReg(REG_FIFO);
    // restore FIFO address
    Lora_writeReg(REG_FIFO_ADDR_PTR, currentAddress);
    return b;
}

void Lora_flush(void)
{
}

//void Lora_onReceive(void(*callback)(int))
//{
//    _onReceive = callback;

//    if (callback)
//    {
//        Lora_writeReg(REG_DIO_MAPPING_1, 0x00);
//        attachInterrupt(digitalPinToInterrupt(_dio0), Lora_onDio0Rise, RISING);
////    attachInterrupt(digitalPinToInterrupt(_dio0), Lora_onDio0Rise, RISING);
//    }
//    else
//    {
//        detachInterrupt(digitalPinToInterrupt(_dio0));
//    }
//}

//void Lora_receive(int size)
//{
//    if (size > 0)
//    {
//        implicitHeaderMode();
//        Lora_writeReg(REG_PAYLOAD_LENGTH, size & 0xff);
//    }
//    else
//    {
//        explicitHeaderMode();
//    }

//    Lora_writeReg(REG_OP_MODE, MODE_LONG_RANGE_MODE | MODE_RX_CONTINUOUS);
//}

