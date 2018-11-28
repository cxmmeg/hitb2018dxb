/******************************************************************************

                  版权所有 (C), 2018-2028, White.

 ******************************************************************************
  文 件 名   : bsp_rgb.h
  版 本 号   : 初稿
  作    者   : white
  生成日期   : 2018年9月10日 18:50:26
  最近修改   :
  功能描述   : bsp_rgb.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2018年9月10日 18:50:26
    作    者   : white
    修改内容   : 创建文件

******************************************************************************/

#ifndef __BSP_RGBLED_H__
#define __BSP_RGBLED_H__

#ifdef __cplusplus
 extern "C" {
#endif 

#define SK6812

#define RGBLED_NUM	 18

//定时器方法因为会关定时器再打开，所以会影响原本的定时器，不推荐使用，有点是路数够多，可以很多路灯一起用
//定时器方法缓冲区效率低，24个字节一个灯再加12字节补0和末尾42个0字节用于reset，单缓冲需要36*lednum+42
//#define RGB_TIM_DMA

//定时器方法是否启用malloc，因为预先分配48*2*lednum需要太多的内存，需要调整启动文件中Heap Configuration大小
//#define malloc_used

//使用SPI MOSI口，会占用一个SPI口
//SPI缓冲区效率更高，9个字节一个灯，3个字节1个颜色，再加上1个字节前导码1个字节结束码1个字节末尾拉低，共计11个字节，双缓冲也才22个字节
//不过同样需要注意，需要11*2*lednum的内存，如果不够，需要调整启动文件中Heap Configuration大小
#define RGB_SPI_DMA

//#define RGBW

#ifdef RGB_TIM_DMA

/* 定时器 */
#define RGB_TIM						TIM3
#define RGB_TIM_CH					3
#define RGB_TIM_CLK					RCC_APB1Periph_TIM3
	
/* TIM3通道3输出引脚 */
#define RGB_OCPWM_GPIO_PORT			GPIOB                      
#define RGB_OCPWM_PIN				GPIO_Pin_0 


//TIM 定时器 CCR偏移地址
#define TIM_CCR1_Address			0x34
#define TIM_CCR2_Address 			0x38
#define TIM_CCR3_Address			0x3C
#define TIM_CCR4_Address			0x40

/* DMA	*/
//DMA通道、数据流对应关系，看datasheet DMA映射关系
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

/* 供外部调用的函数声明 */
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
