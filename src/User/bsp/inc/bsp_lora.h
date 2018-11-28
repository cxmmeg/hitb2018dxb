#ifndef __BSP_LORA_H__
#define __BSP_LORA_H__

#ifdef __cplusplus
 extern "C" {
#endif 

/* 定义GPIO端口 */
#define Lora_SPI  				SPI1H
#define Lora_SPI_SPEED			10000000	//最大10M，但地址-数据 数据-地址 数据-数据 需要加100ns间隔
													//不加延时的话，单字节发送最大9M，突发模式（连续模式）最大6.5M
													//所以加了等待,读MISO也就是GDO1脚状态
		
#define Lora_CSN_PORT  			GPIOA
#define Lora_CSN_PIN   			GPIO_Pin_8

#define Lora_RST_PORT  			GPIOA		
#define Lora_RST_PIN 			GPIO_Pin_12

#define Lora_DIO0_PORT 			GPIOA
#define Lora_DIO0_PIN  			GPIO_Pin_11
		
//#define Lora_DIO1_PORT  		GPIOD
//#define Lora_DIO1_PIN 			GPIO_Pin_2
		
		/* 引脚操作，采用寄存器的形式，加快操作速度 */
#define Lora_CSN_1()  			Lora_CSN_PORT->BSRR = Lora_CSN_PIN
#define Lora_CSN_0()    		Lora_CSN_PORT->BRR = Lora_CSN_PIN

#define Lora_RST_1()  			Lora_RST_PORT->BSRR = Lora_RST_PIN
#define Lora_RST_0()    		Lora_RST_PORT->BRR = Lora_RST_PIN

#define Lora_DIO0_1()     		Lora_DIO0_PORT->BSRR = Lora_DIO0_PIN
#define Lora_DIO0_0()     		Lora_DIO0_PORT->BRR = Lora_DIO0_PIN
		
#define Lora_DIO0_Read()	  	(Lora_DIO0_PORT->IDR & Lora_DIO0_PIN)
//#define Lora_DIO1_Read()	  	(Lora_DIO1_PORT->IDR & Lora_DIO1_PIN)

u8 bsp_Init_Lora(void);
int Lora_available(void);
int Lora_read(void);
void Lora_receive(int size);
u8 Lora_beginPacket(u8 implicitHeader);
void Lora_disableCRC(void);
void Lora_enableCRC(void);
u8 Lora_endPacket(void);
void Lora_explicitHeaderMode(void);
void Lora_idle(void);
void Lora_implicitHeaderMode(void);
int8_t Lora_packetRssi(void);
float Lora_packetSnr(void);
u8 Lora_parsePacket(int size);
uint8_t Lora_random(void);
uint8_t Lora_readReg(uint8_t reg);
void Lora_RegConfig(void);
void Lora_setCodingRate4(int denominator);
void Lora_setFrequency(uint64_t frequency);
void Lora_setPreambleLength(u16 length);
void Lora_setSignalBandwidth(long sbw);
void Lora_setSpreadingFactor(int sf);
void Lora_setSyncWord(int sw);
void Lora_setTxPowerMax(int level);
void Lora_sleep(void);
uint8_t Lora_writeReg(uint8_t reg, uint8_t value);
u8 Lora_writeByte(uint8_t byte);
u8 Lora_writeBuf(const uint8_t *buffer, u8 size);



#ifdef __cplusplus
		}
#endif /* __cplusplus */

#endif



