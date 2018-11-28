/******************************************************************************

                  ��Ȩ���� (C), 2018-2028, White.

 ******************************************************************************
  �� �� ��   : bsp_rgb.h
  �� �� ��   : ����
  ��    ��   : white
  ��������   : 2018��9��10�� 18:50:26
  ����޸�   :
  ��������   : bsp_rgb.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��9��10�� 18:50:26
    ��    ��   : white
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __BSP_RGBLED_H__
#define __BSP_RGBLED_H__

#ifdef __cplusplus
 extern "C" {
#endif 

#define SK6812

#define RGBLED_NUM	 18

//��ʱ��������Ϊ��ض�ʱ���ٴ򿪣����Ի�Ӱ��ԭ���Ķ�ʱ�������Ƽ�ʹ�ã��е���·�����࣬���Ժܶ�·��һ����
//��ʱ������������Ч�ʵͣ�24���ֽ�һ�����ټ�12�ֽڲ�0��ĩβ42��0�ֽ�����reset����������Ҫ36*lednum+42
//#define RGB_TIM_DMA

//��ʱ�������Ƿ�����malloc����ΪԤ�ȷ���48*2*lednum��Ҫ̫����ڴ棬��Ҫ���������ļ���Heap Configuration��С
//#define malloc_used

//ʹ��SPI MOSI�ڣ���ռ��һ��SPI��
//SPI������Ч�ʸ��ߣ�9���ֽ�һ���ƣ�3���ֽ�1����ɫ���ټ���1���ֽ�ǰ����1���ֽڽ�����1���ֽ�ĩβ���ͣ�����11���ֽڣ�˫����Ҳ��22���ֽ�
//����ͬ����Ҫע�⣬��Ҫ11*2*lednum���ڴ棬�����������Ҫ���������ļ���Heap Configuration��С
#define RGB_SPI_DMA

//#define RGBW

#ifdef RGB_TIM_DMA

/* ��ʱ�� */
#define RGB_TIM						TIM3
#define RGB_TIM_CH					3
#define RGB_TIM_CLK					RCC_APB1Periph_TIM3
	
/* TIM3ͨ��3������� */
#define RGB_OCPWM_GPIO_PORT			GPIOB                      
#define RGB_OCPWM_PIN				GPIO_Pin_0 


//TIM ��ʱ�� CCRƫ�Ƶ�ַ
#define TIM_CCR1_Address			0x34
#define TIM_CCR2_Address 			0x38
#define TIM_CCR3_Address			0x3C
#define TIM_CCR4_Address			0x40

/* DMA	*/
//DMAͨ������������Ӧ��ϵ����datasheet DMAӳ���ϵ
#define TIM_DMA_ADDRESS				TIM3_BASE+TIM_CCR3_Address
#define TIM_DMA_BUFSIZE				42
#define TIM_DMA_CLK					RCC_AHB1Periph_DMA1
#define TIM_DMA_CHANNEL				DMA_Channel_5
#define TIM_DMA_SOURCE				TIM_DMA_CC3
#define TIM_DMA_STREAM				DMA1_Stream7
#define TIM_DMA_FLAG				DMA_FLAG_TCIF7

	
void RGB_TIM_Init(void);

#endif /* RGB_TIM_DMA */

#ifdef RGB_SPI_DMA

/*
SPI1_MOSI	PA7 PB5 		DMA2 ch3-s3-s5
SPI2_MOSI	PB15 PC3 PI3	DMA1 ch0-s4
SPI3_MOSI	PB5 PC12		DMA1 ch0-s5-s7
*/

#define RGB_SPI						SPI2   
#define RGB_SPI_GPIO_PORT			GPIOB  
#define RGB_SPI_GPIO_CLK			RCC_APB2Periph_GPIOB
#define RGB_SPI_PIN					GPIO_Pin_15   
#define RGB_SPI_PINSOURCE			GPIO_PinSource15

#define RGB_SPI_DMA_CLK				RCC_AHBPeriph_DMA1
#define RBG_SPI_DMA_CHANNEL			DMA1_Channel5
//#define RBG_SPI_DMA_STREAM			DMA1_Stream5
#define RGB_SPI_DMA_FLAG			DMA1_FLAG_TC5

void RGB_SPI_Init(void);

#endif /* RBG_SPI_DMA */


void bsp_Init_RgbLed(void);
void RGB_updateLength(uint16_t n);
void bsp_RGB_setPixelColor2(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
void bsp_RGB_setPixelColor(uint16_t n, uint32_t c);
void RGB_clear(void);
void bsp_RGB_Show(void);
void RGB_DMASend(uint32_t length);
uint32_t bsp_RGB_Color(uint8_t r, uint8_t g, uint8_t b);
uint16_t bsp_RGB_numPixels(void);
uint8_t bsp_RGB_getBrightness(void);
void bsp_RGB_setBrightness(uint8_t b);
void bsp_RGB_ledoff(void);
void bsp_RGB_colorWipe(uint32_t c, uint8_t wait);
void  bsp_RGB_rainbow(uint8_t wait);
void bsp_RGB_rainbowCycle(uint8_t wait);
uint32_t bsp_RGB_Wheel(uint8_t WheelPos);
void bsp_RGB_theaterChase(uint32_t c, uint8_t wait);
void bsp_RGB_theaterChaseRainbow(uint8_t wait);


#ifdef RGBW

/* ���ⲿ���õĺ������� */
struct Pixel {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};
uint32_t bsp_RGBW_Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
void bsp_RGBW_pulseWhite(uint8_t wait);
void bsp_RGBW_rainbowFade2White(uint8_t wait, int rainbowLoops, int whiteLoops);
void bsp_RGBW_whiteOverRainbow(uint8_t wait, uint8_t whiteSpeed, uint8_t whiteLength );
void bsp_RGB_fullWhite();
uint8_t green(uint32_t c);
uint8_t red(uint32_t c);
uint8_t blue(uint32_t c);

#endif /* RGBW */

#ifdef __cplusplus
	}
#endif /* __cplusplus */

#endif /* __BSP_RGBLED_H__ */
