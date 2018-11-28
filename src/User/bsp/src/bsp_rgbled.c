/******************************************************************************

                  版权所有 (C), 2018-2028, White.

 ******************************************************************************
  文 件 名   : bsp_rgb.c
  版 本 号   : 初稿
  作    者   : white
  生成日期   : 2018年9月12日 21:52:44
  最近修改   :
  功能描述   : RGB LED
  函数列表   :
              blue
              bsp_RGBLED_Init
              bsp_RGBLED_Init2
              bsp_RGBLED_OFF
              bsp_RGBLED_Send
              bsp_RGBW_Color
              bsp_RGBW_pulseWhite
              bsp_RGBW_rainbowFade2White
              bsp_RGB_Color
              bsp_RGB_colorWipe
              bsp_RGB_fullWhite
              bsp_RGB_getBrightness
              bsp_RGB_numPixels
              bsp_RGB_rainbow
              bsp_RGB_rainbowCycle
              bsp_RGB_setBrightness
              bsp_RGB_setPixelColor
              bsp_RGB_setPixelColor2
              bsp_RGB_Show
              bsp_RGB_theaterChase
              bsp_RGB_theaterChaseRainbow
              bsp_RGB_Wheel
              bsp_RGB_whiteOverRainbow
              green
              red
              RGB_clear
              RGB_DMASend
              RGB_SPI_Init
              RGB_updateLength
  修改历史   :
  1.日    期   : 2018年9月12日 21:52:44
    作    者   : white
    修改内容   : 创建文件

******************************************************************************/

#include "bsp.h"

/* Buffer that holds one complete DMA transmission
 * 
 * Ensure that this buffer is big enough to hold
 * all data bytes that need to be sent
 * 
 * The buffer size can be calculated as follows:
 * number of LEDs * 24 bytes + 42 bytes
 * 
 * This leaves us with a maximum string length of
 * (2^16 bytes per DMA stream - 42 bytes)/24 bytes per LED = 2728 LEDs
 */

uint16_t
  numLEDs,		 // Number of RGB LEDs in strip
  numBytes; 	 // Size of 'pixels' buffer
  
uint8_t
  brightness;

#ifdef RGB_TIM_DMA

#ifdef SK6812

#define TIMING_ONE  55
#define TIMING_ZERO 35
#define RGB_FREQ 800000

#endif /* SK6812 */

uint16_t
 *pixels;		 // Holds the current LED color values, which the external API calls interact with 9 bytes per pixel + start + end empty bytes


/*****************************************************************************
 函 数 名  : RGB_updateLength
 功能描述  : 初始化分配内存作为缓冲区，并将缓冲区数据初始为关灯码
 			TIM需要缓冲太大，使用单buf
 输入参数  : uint16_t n  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年9月12日 21:15:15
    作    者   : white
    修改内容   : 新生成函数

*****************************************************************************/
#ifdef malloc_used

uint16_t  *doubleBuffer;   // Holds the start of the double buffer (1 buffer for async DMA transfer and one for the API interaction.

void RGB_updateLength(uint16_t n)
{
	if(doubleBuffer) 
	{
		free(doubleBuffer); 
	}

	numBytes = 48*n; // 48个字节，一个灯需要24*2个字节
	doubleBuffer = (uint16_t *)malloc(numBytes);
	if(doubleBuffer)
	{
		numLEDs = n;	 
		pixels = doubleBuffer;
		// Only need to init the part of the double buffer which will be interacted with by the API e.g. setPixelColor
		*pixels=0;//clear the preamble byte
		*(pixels+numBytes-1)=0;// clear the post send cleardown byte.
		RGB_clear();// Set the encoded data to all encoded zeros 
	} 
	else 
	{
		numLEDs = numBytes = 0;
	}
}

#else

uint16_t LED_BYTE_Buffer[RGBLED_NUM*48];	//64*(24+12)+42

void RGB_updateLength(uint16_t n)
{
	pixels = LED_BYTE_Buffer;
	numLEDs = RGBLED_NUM;
	numBytes = RGBLED_NUM*48;
	RGB_clear();
}

#endif /* malloc_used */


/*****************************************************************************
 函 数 名  : RGB_clear
 功能描述  : 缓冲区写0码，关闭所有RGB LED
 输入参数  : void  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年9月12日 21:20:14
    作    者   : white
    修改内容   : 新生成函数

*****************************************************************************/
void RGB_clear(void) 
{
	uint16_t * bptr= pixels;// Note first byte in the buffer is a preable and is always zero. hence the +1

	for(u16 i=0;i< numLEDs;i++)
	{
		for (u8 j = 0 ; j < 8*3; j++ )
		{
	   	   *bptr++ = TIMING_ZERO;
		   *bptr++ = 0;	
		}
	}
}

void bsp_Init_RgbLed(void)
{
	RGB_updateLength(RGBLED_NUM);
	RGB_TIM_Init();
	bsp_RGB_Show();
	bsp_DelayMS(1);	//需要，否则会两个灯数据连续
}

void RGB_TIM_Init(void)
{
	uint16_t usPeriod;
	uint32_t uiTIMxCLK;

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	DMA_InitTypeDef DMA_InitStructure;

	bsp_ConfigTimGpio(RGB_OCPWM_GPIO_PORT, RGB_OCPWM_PIN, RGB_TIM, RGB_TIM_CH);	/* 使能GPIO和TIM时钟，并连接TIM通道到GPIO */

	if ((RGB_TIM == TIM1) || (RGB_TIM == TIM8) || (RGB_TIM == TIM9) || (RGB_TIM == TIM10) || (RGB_TIM == TIM11))
	{
		/* APB2 定时器 */
		uiTIMxCLK = SystemCoreClock;
	}
	else	/* APB1 定时器 */
	{
		uiTIMxCLK = SystemCoreClock / 2;
	}

	usPeriod = uiTIMxCLK / RGB_FREQ - 1;	/* 自动重装的值 */


	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = usPeriod;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;		/* TIM1 和 TIM8 必须设置 */

	TIM_TimeBaseInit(RGB_TIM, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	//选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR,设置占空比。反转模式时候无效
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;		//输出极性:TIM输出比较极性高

	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;	/* only for TIM1 and TIM8. */
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;			/* only for TIM1 and TIM8. */
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;		/* only for TIM1 and TIM8. */
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;		/* only for TIM1 and TIM8. */

	if (RGB_TIM_CH == 1)
	{
		TIM_OC1Init(RGB_TIM, &TIM_OCInitStructure);
		//TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
	}
	else if (RGB_TIM_CH == 2)
	{
		TIM_OC2Init(RGB_TIM, &TIM_OCInitStructure);
		//TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
	}
	else if (RGB_TIM_CH == 3)
	{
		TIM_OC3Init(RGB_TIM, &TIM_OCInitStructure);
		//TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
	}
	else if (RGB_TIM_CH == 4)
	{
		TIM_OC4Init(RGB_TIM, &TIM_OCInitStructure);
		//TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
	}

	TIM_ARRPreloadConfig(RGB_TIM, ENABLE);
	
	/* configure DMA */
	/* DMA clock enable */
	RCC_AHB1PeriphClockCmd(TIM_DMA_CLK, ENABLE);

	DMA_DeInit(TIM_DMA_STREAM);
	/* 确保DMA数据流复位完成 */
	while (DMA_GetCmdStatus(TIM_DMA_STREAM) != DISABLE)  {
	}

	DMA_InitStructure.DMA_Channel = TIM_DMA_CHANNEL;  
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)TIM_DMA_ADDRESS;	// physical address of Timer 3 CCR1
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)pixels;		// this is the buffer memory 
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;						// data shifted from memory to peripheral
	DMA_InitStructure.DMA_BufferSize = TIM_DMA_BUFSIZE;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;					// automatically increase buffer index
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;							// stop DMA feed after buffer size is reached
	DMA_InitStructure.DMA_Priority = DMA_Priority_Low;		//DMA中断优先级
	//DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStructure.DMA_FIFOMode            = DMA_FIFOMode_Disable;          /* FIFO模式/直接模式 */
	DMA_InitStructure.DMA_FIFOThreshold       = DMA_FIFOThreshold_Full; /* FIFO大小 */
	DMA_InitStructure.DMA_MemoryBurst         = DMA_MemoryBurst_Single;       /* 单次传输 */
	DMA_InitStructure.DMA_PeripheralBurst     = DMA_PeripheralBurst_Single;

	DMA_Init(TIM_DMA_STREAM, &DMA_InitStructure);	

	/* TIM3 CC1 DMA Request enable */
	TIM_DMACmd(RGB_TIM, TIM_DMA_SOURCE, ENABLE);
}

//void RGB_clear(void) 
//{
//	u8 i;
//	u16 j;
//	for(j = 0; j < RGBLED_NUM; j++)
//	{
//	   for(i = 0; i < 8 * 3; i++) // GREEN data
//	   {
//		   LED_BYTE_Buffer[48*j+2*i] = TIMING_ZERO;
//		   LED_BYTE_Buffer[48*j+2*i+1] = 0;
//	   }
//	}
//}

//void bsp_RGB_setPixelColor(u16 n, uint8_t (*color)[3])
//{
//	uint8_t i;
//	uint16_t memaddr;
//	memaddr = 48*n;				// reset buffer memory index

//	for(i=0; i<8; i++) // GREEN data
//	{
//		LED_BYTE_Buffer[memaddr] = ((color[0][1]<<i) & 0x0080) ? TIMING_ONE:TIMING_ZERO;
//		memaddr+=2;
//	}
//	for(i=0; i<8; i++) // RED
//	{
//		LED_BYTE_Buffer[memaddr] = ((color[0][0]<<i) & 0x0080) ? TIMING_ONE:TIMING_ZERO;
//		memaddr+=2;
//	}
//	for(i=0; i<8; i++) // BLUE
//	{
//		LED_BYTE_Buffer[memaddr] = ((color[0][2]<<i) & 0x0080) ? TIMING_ONE:TIMING_ZERO;
//		memaddr+=2;
//	}
//}

void bsp_RGB_setPixelColor(uint16_t n, uint32_t c)
  {
     uint8_t r,g,b;
	 uint8_t i;
   
    if(brightness) 
	{ 
      r = ((int)((uint8_t)(c >> 16)) * (int)brightness) >> 8;
      g = ((int)((uint8_t)(c >>  8)) * (int)brightness) >> 8;
      b = ((int)((uint8_t)c) * (int)brightness) >> 8;
	}
	else
	{
      r = (uint8_t)(c >> 16),
      g = (uint8_t)(c >>  8),
	  b = (uint8_t)c;		
	}
	
   uint16_t *bptr = pixels + 48*n;
   
   for(i=0; i<8; i++) // GREEN data
   {
	   *bptr++ = ((g<<i) & 0x80) ? TIMING_ONE:TIMING_ZERO;
	   *bptr++ = 0;
   }
   for(i=0; i<8; i++) // GREEN data
   {
	   *bptr++ = ((r<<i) & 0x80) ? TIMING_ONE:TIMING_ZERO;
	   *bptr++ = 0;
   }
   for(i=0; i<8; i++) // GREEN data
   {
	   *bptr++ = ((b<<i) & 0x80) ? TIMING_ONE:TIMING_ZERO;
	   *bptr++ = 0;
   }

}


void bsp_RGB_setPixelColor2(uint16_t n, uint8_t r, uint8_t g, uint8_t b)
{
	uint8_t i;
	uint16_t *bptr = pixels + 48*n;


	for(i=0; i<8; i++) // GREEN data
	{
		*bptr++ = ((g<<i) & 0x80) ? TIMING_ONE:TIMING_ZERO;
		*bptr++ = 0;
	}
	for(i=0; i<8; i++) // GREEN data
	{
		*bptr++ = ((r<<i) & 0x80) ? TIMING_ONE:TIMING_ZERO;
		*bptr++ = 0;
	}
	for(i=0; i<8; i++) // GREEN data
	{
		*bptr++ = ((b<<i) & 0x80) ? TIMING_ONE:TIMING_ZERO;
		*bptr++ = 0;
	}
}


void bsp_RGB_Show(void)
{
	RGB_DMASend(numBytes);
	
#ifdef malloc_used
	
	//pixels = doubleBuffer;

	//if (pixels==doubleBuffer)
	//{
	//  // pixels was using the first buffer
	//  pixels  = doubleBuffer+numBytes;	// set pixels to second buffer
	//  memcpy(pixels,doubleBuffer,numBytes);// copy first buffer to second buffer
	//}
	//else
	//{
	//  // pixels was using the second buffer 	
	//  pixels  = doubleBuffer;  // set pixels to first buffer
	//  memcpy(pixels,doubleBuffer+numBytes,numBytes);   // copy second buffer to first buffer 
	//} 
#endif
}

// Adjust output brightness; 0=darkest (off), 255=brightest.  This does
// NOT immediately affect what's currently displayed on the LEDs.  The
// next call to show() will refresh the LEDs at this level.  However,
// this process is potentially "lossy," especially when increasing
// brightness.  The tight timing in the WS2811/WS2812 code means there
// aren't enough free cycles to perform this scaling on the fly as data
// is issued.  So we make a pass through the existing color data in RAM
// and scale it (subsequent graphics commands also work at this
// brightness level).  If there's a significant step up in brightness,
// the limited number of steps (quantization) in the old data will be
// quite visible in the re-scaled version.  For a non-destructive
// change, you'll need to re-render the full strip data.  C'est la vie.
void bsp_RGB_setBrightness(uint8_t b) {
  // Stored brightness value is different than what's passed.
  // This simplifies the actual scaling math later, allowing a fast
  // 8x8-bit multiply and taking the MSB.  'brightness' is a uint8_t,
  // adding 1 here may (intentionally) roll over...so 0 = max brightness
  // (color values are interpreted literally; no scaling), 1 = min
  // brightness (off), 255 = just below max brightness.
  uint8_t newBrightness = b + 1;
  if(newBrightness != brightness) { // Compare against prior value
    // Brightness has changed -- re-scale existing data in RAM
    uint16_t  c,
            *ptr           = pixels;
    uint8_t       oldBrightness = brightness - 1; // De-wrap old brightness value
    uint16_t scale;
    if(oldBrightness == 0) scale = 0; // Avoid /0
    else if(b == 255) scale = 65535 / oldBrightness;
    else scale = (((uint16_t)newBrightness << 8) - 1) / oldBrightness;
    for(uint16_t i=0; i<numBytes; i++) 
	{
      c      = *ptr;
      *ptr++ = (c * scale) >> 8;
    }
    brightness = newBrightness;
  }
}



void RGB_DMASend(uint32_t length)
{
	DMA_SetCurrDataCounter(TIM_DMA_STREAM, length); 	// load number of bytes to be transferred
	DMA_Cmd(TIM_DMA_STREAM, ENABLE); 			// enable DMA channel 6
	TIM_Cmd(RGB_TIM, ENABLE); 						// enable Timer 3
	while(!DMA_GetFlagStatus(TIM_DMA_STREAM, TIM_DMA_FLAG)) ; 	// wait until transfer complete
	TIM_Cmd(RGB_TIM, DISABLE); 	// disable Timer 3
	DMA_Cmd(TIM_DMA_STREAM, DISABLE); 			// disable DMA channel 6
	DMA_ClearFlag(TIM_DMA_STREAM,TIM_DMA_FLAG); 				// clear DMA1 Channel 6 transfer complete flag

	//TIM_Cmd(RGB_TIM, DISABLE); 	// disable Timer 3
	//DMA_Cmd(TIM_DMA_STREAM, DISABLE); 			// disable DMA channel 6
	//DMA_ClearFlag(TIM_DMA_STREAM,TIM_DMA_FLAG); 				// clear DMA1 Channel 6 transfer complete flag
	//DMA_SetCurrDataCounter(TIM_DMA_STREAM, length); 	// load number of bytes to be transferred
	//DMA_Cmd(TIM_DMA_STREAM, ENABLE); 			// enable DMA channel 6
	//TIM_Cmd(RGB_TIM, ENABLE); 						// enable Timer 3
}

#endif /* TIM_DMA */


#ifdef RGB_SPI_DMA

uint8_t
 *pixels,		 // Holds the current LED color values, which the external API calls interact with 9 bytes per pixel + start + end empty bytes
 *doubleBuffer;   // Holds the start of the double buffer (1 buffer for async DMA transfer and one for the API interaction.

 
// New version uses one large LUT as its faster index into sequential bytes for the GRB pattern
const uint8_t encoderLookup[256*3]={	0x92,0x49,0x24,0x92,0x49,0x26,0x92,0x49,0x34,0x92,0x49,0x36,0x92,0x49,0xA4,0x92,0x49,0xA6,0x92,0x49,0xB4,0x92,0x49,0xB6,0x92,0x4D,0x24,0x92,0x4D,0x26,0x92,0x4D,0x34,0x92,0x4D,0x36,0x92,0x4D,0xA4,0x92,0x4D,0xA6,0x92,0x4D,0xB4,0x92,0x4D,0xB6,0x92,0x69,0x24,0x92,0x69,0x26,0x92,0x69,0x34,0x92,0x69,0x36,0x92,0x69,0xA4,0x92,0x69,0xA6,0x92,0x69,0xB4,0x92,0x69,0xB6,0x92,0x6D,0x24,0x92,0x6D,0x26,0x92,0x6D,0x34,0x92,0x6D,0x36,0x92,0x6D,0xA4,0x92,0x6D,0xA6,0x92,0x6D,0xB4,0x92,0x6D,0xB6,0x93,0x49,0x24,0x93,0x49,0x26,0x93,0x49,0x34,0x93,0x49,0x36,0x93,0x49,0xA4,0x93,0x49,0xA6,0x93,0x49,0xB4,0x93,0x49,0xB6,0x93,0x4D,0x24,0x93,0x4D,0x26,0x93,0x4D,0x34,0x93,0x4D,0x36,0x93,0x4D,0xA4,0x93,0x4D,0xA6,0x93,0x4D,0xB4,0x93,0x4D,0xB6,0x93,0x69,0x24,0x93,0x69,0x26,0x93,0x69,0x34,0x93,0x69,0x36,0x93,0x69,0xA4,0x93,0x69,0xA6,0x93,0x69,0xB4,0x93,0x69,0xB6,0x93,0x6D,0x24,0x93,0x6D,0x26,0x93,0x6D,0x34,0x93,0x6D,0x36,0x93,0x6D,0xA4,0x93,0x6D,0xA6,0x93,0x6D,0xB4,0x93,0x6D,0xB6,0x9A,0x49,0x24,0x9A,0x49,0x26,0x9A,0x49,0x34,0x9A,0x49,0x36,0x9A,0x49,0xA4,0x9A,0x49,0xA6,0x9A,0x49,0xB4,0x9A,0x49,0xB6,0x9A,0x4D,0x24,0x9A,0x4D,0x26,0x9A,0x4D,0x34,0x9A,0x4D,0x36,0x9A,0x4D,0xA4,0x9A,0x4D,0xA6,0x9A,0x4D,0xB4,0x9A,0x4D,0xB6,0x9A,0x69,0x24,0x9A,0x69,0x26,0x9A,0x69,0x34,0x9A,0x69,0x36,0x9A,0x69,0xA4,0x9A,0x69,\
											0xA6,0x9A,0x69,0xB4,0x9A,0x69,0xB6,0x9A,0x6D,0x24,0x9A,0x6D,0x26,0x9A,0x6D,0x34,0x9A,0x6D,0x36,0x9A,0x6D,0xA4,0x9A,0x6D,0xA6,0x9A,0x6D,0xB4,0x9A,0x6D,0xB6,0x9B,0x49,0x24,0x9B,0x49,0x26,0x9B,0x49,0x34,0x9B,0x49,0x36,0x9B,0x49,0xA4,0x9B,0x49,0xA6,0x9B,0x49,0xB4,0x9B,0x49,0xB6,0x9B,0x4D,0x24,0x9B,0x4D,0x26,0x9B,0x4D,0x34,0x9B,0x4D,0x36,0x9B,0x4D,0xA4,0x9B,0x4D,0xA6,0x9B,0x4D,0xB4,0x9B,0x4D,0xB6,0x9B,0x69,0x24,0x9B,0x69,0x26,0x9B,0x69,0x34,0x9B,0x69,0x36,0x9B,0x69,0xA4,0x9B,0x69,0xA6,0x9B,0x69,0xB4,0x9B,0x69,0xB6,0x9B,0x6D,0x24,0x9B,0x6D,0x26,0x9B,0x6D,0x34,0x9B,0x6D,0x36,0x9B,0x6D,0xA4,0x9B,0x6D,0xA6,0x9B,0x6D,0xB4,0x9B,0x6D,0xB6,0xD2,0x49,0x24,0xD2,0x49,0x26,0xD2,0x49,0x34,0xD2,0x49,0x36,0xD2,0x49,0xA4,0xD2,0x49,0xA6,0xD2,0x49,0xB4,0xD2,0x49,0xB6,0xD2,0x4D,0x24,0xD2,0x4D,0x26,0xD2,0x4D,0x34,0xD2,0x4D,0x36,0xD2,0x4D,0xA4,0xD2,0x4D,0xA6,0xD2,0x4D,0xB4,0xD2,0x4D,0xB6,0xD2,0x69,0x24,0xD2,0x69,0x26,0xD2,0x69,0x34,0xD2,0x69,0x36,0xD2,0x69,0xA4,0xD2,0x69,0xA6,0xD2,0x69,0xB4,0xD2,0x69,0xB6,0xD2,0x6D,0x24,0xD2,0x6D,0x26,0xD2,0x6D,0x34,0xD2,0x6D,0x36,0xD2,0x6D,0xA4,0xD2,0x6D,0xA6,0xD2,0x6D,0xB4,0xD2,0x6D,0xB6,0xD3,0x49,0x24,0xD3,0x49,0x26,0xD3,0x49,0x34,0xD3,0x49,0x36,0xD3,0x49,0xA4,0xD3,0x49,0xA6,0xD3,0x49,0xB4,0xD3,0x49,0xB6,0xD3,0x4D,0x24,0xD3,0x4D,0x26,0xD3,0x4D,0x34,0xD3,\
											0x4D,0x36,0xD3,0x4D,0xA4,0xD3,0x4D,0xA6,0xD3,0x4D,0xB4,0xD3,0x4D,0xB6,0xD3,0x69,0x24,0xD3,0x69,0x26,0xD3,0x69,0x34,0xD3,0x69,0x36,0xD3,0x69,0xA4,0xD3,0x69,0xA6,0xD3,0x69,0xB4,0xD3,0x69,0xB6,0xD3,0x6D,0x24,0xD3,0x6D,0x26,0xD3,0x6D,0x34,0xD3,0x6D,0x36,0xD3,0x6D,0xA4,0xD3,0x6D,0xA6,0xD3,0x6D,0xB4,0xD3,0x6D,0xB6,0xDA,0x49,0x24,0xDA,0x49,0x26,0xDA,0x49,0x34,0xDA,0x49,0x36,0xDA,0x49,0xA4,0xDA,0x49,0xA6,0xDA,0x49,0xB4,0xDA,0x49,0xB6,0xDA,0x4D,0x24,0xDA,0x4D,0x26,0xDA,0x4D,0x34,0xDA,0x4D,0x36,0xDA,0x4D,0xA4,0xDA,0x4D,0xA6,0xDA,0x4D,0xB4,0xDA,0x4D,0xB6,0xDA,0x69,0x24,0xDA,0x69,0x26,0xDA,0x69,0x34,0xDA,0x69,0x36,0xDA,0x69,0xA4,0xDA,0x69,0xA6,0xDA,0x69,0xB4,0xDA,0x69,0xB6,0xDA,0x6D,0x24,0xDA,0x6D,0x26,0xDA,0x6D,0x34,0xDA,0x6D,0x36,0xDA,0x6D,0xA4,0xDA,0x6D,0xA6,0xDA,0x6D,0xB4,0xDA,0x6D,0xB6,0xDB,0x49,0x24,0xDB,0x49,0x26,0xDB,0x49,0x34,0xDB,0x49,0x36,0xDB,0x49,0xA4,0xDB,0x49,0xA6,0xDB,0x49,0xB4,0xDB,0x49,0xB6,0xDB,0x4D,0x24,0xDB,0x4D,0x26,0xDB,0x4D,0x34,0xDB,0x4D,0x36,0xDB,0x4D,0xA4,0xDB,0x4D,0xA6,0xDB,0x4D,0xB4,0xDB,0x4D,0xB6,0xDB,0x69,0x24,0xDB,0x69,0x26,0xDB,0x69,0x34,0xDB,0x69,0x36,0xDB,0x69,0xA4,0xDB,0x69,0xA6,0xDB,0x69,0xB4,0xDB,0x69,0xB6,0xDB,0x6D,0x24,0xDB,0x6D,0x26,0xDB,0x6D,0x34,0xDB,0x6D,0x36,0xDB,0x6D,0xA4,0xDB,0x6D,0xA6,0xDB,0x6D,0xB4,0xDB,0x6D,0xB6};

#ifdef RGBW

const uint8_t LEDGamma[] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
	1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
	2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
	5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

#endif

/*****************************************************************************
 函 数 名  : bsp_RGBLED_Init2
 功能描述  : 初始化并关闭所有灯
 输入参数  : void  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年9月12日 21:21:35
    作    者   : white
    修改内容   : 新生成函数

*****************************************************************************/
void bsp_Init_RgbLed(void)
{
	RGB_updateLength(RGBLED_NUM);
	RGB_SPI_Init();
	bsp_RGB_Show();
}

/*****************************************************************************
 函 数 名  : RGB_clear
 功能描述  : 缓冲区写0码，关闭所有RGB LED
 输入参数  : void  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年9月12日 21:20:14
    作    者   : white
    修改内容   : 新生成函数

*****************************************************************************/
void RGB_clear(void) 
{
	uint8_t * bptr= pixels+1;// Note first byte in the buffer is a preable and is always zero. hence the +1
	uint8_t *tPtr;

	for(int i=0;i< (numLEDs *3);i++)
	{
	   tPtr = (uint8_t *)encoderLookup;
   	   *bptr++ = *tPtr++;
	   *bptr++ = *tPtr++;
	   *bptr++ = *tPtr++;	
	}
}


//void LED_SPI_WriteByte(uint16_t Data)
//{
//    /* Wait until the transmit buffer is empty */
//    /*
//    while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
//    {
//    }
//    */

//    PixelBuffer[PixelPointer] = Data;
//    PixelPointer++;

//    /* Send the byte */
//    /* SPI_I2S_SendData16(SPI2, Data); */
//}

//void LED_SPI_SendBits(uint8_t bits)
//{
//    int zero = 0x7000;  //11100000000000
//    int one = 0x7F00;  //111111100000000
//    int i = 0x00;

//    for (i = 0x80; i >= 0x01; i >>= 1)
//    {
//        LED_SPI_WriteByte((bits & i) ? one : zero);
//    }
//}

//void LED_SPI_SendPixel(uint32_t color)
//{
//    /*
//     r7,r6,r5,r4,r3,r2,r1,r0,g7,g6,g5,g4,g3,g2,g1,g0,b7,b6,b5,b4,b3,b2,b1,b0
//     \_____________________________________________________________________/
//                               |      _________________...
//                               |     /   __________________...
//                               |    /   /   ___________________...
//                               |   /   /   /
//                              RGB,RGB,RGB,RGB,...,STOP
//    */

//    /*
//    	BUG Fix : Actual is GRB,datasheet is something wrong.
//    */
//	  uint8_t Red, Green, Blue;  // 三原色
//		// 绿 红 蓝 三原色分解
//	  Red   = color>>8;
//	  Green = color>>16;
//	  Blue  = color;
//    LED_SPI_SendBits(Green);
//    LED_SPI_SendBits(Red);
//    LED_SPI_SendBits(Blue);
//}

//void LED_SPI_Update(uint32_t buffer[], uint32_t length)
//{
//    uint8_t i = 0;
//    uint8_t m = 0;
//    if(DMA_GetCurrDataCounter(DMA1_Channel5) == 0)
//    {

//        for (i = 0; i < length; i++)
//        {
//            LED_SPI_SendPixel(buffer[i]);
//        }

//        if(length < 6)
//        {
//            for(i = 6 - length; i < length; i++)
//            {
//                for(m = 0; m < 3; m++)
//                {
//                    LED_SPI_SendBits(0x00);
//                }
//            }
//        }

//        for (i = 0; i < 20; i++)   
//        {
//            LED_SPI_WriteByte(0x00);
//        }

//        PixelPointer = 0;

//        DMA_Cmd(DMA1_Channel5, DISABLE);
//        DMA_ClearFlag(DMA1_FLAG_TC5);
//        DMA_SetCurrDataCounter(DMA1_Channel5, 24*length+20);
//        DMA_Cmd(DMA1_Channel5, ENABLE);
//    }
//}


/*****************************************************************************
 函 数 名  : RGB_updateLength
 功能描述  : 初始化分配内存作为缓冲区，并将缓冲区数据初始为关灯码
 输入参数  : uint16_t n  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年9月12日 21:15:15
    作    者   : white
    修改内容   : 新生成函数

*****************************************************************************/
void RGB_updateLength(uint16_t n)
{
	if(doubleBuffer) 
	{
		free(doubleBuffer); 
	}

	numBytes = (n<<3) + n + 2; // 9 encoded bytes per pixel. 1 byte empty peamble to fix issue with SPI MOSI and on byte at the end to clear down MOSI 
							// Note. (n<<3) +n is a fast way of doing n*9
	doubleBuffer = (uint8_t *)malloc(numBytes*2);
	if(doubleBuffer)
	{
		numLEDs = n;	 
		pixels = doubleBuffer;
		// Only need to init the part of the double buffer which will be interacted with by the API e.g. setPixelColor
		*pixels=0;//clear the preamble byte
		*(pixels+numBytes-1)=0;// clear the post send cleardown byte.
		RGB_clear();// Set the encoded data to all encoded zeros 
	} 
	else 
	{
		numLEDs = numBytes = 0;
	}
}

/*****************************************************************************
 函 数 名  : RGB_SPI_Init
 功能描述  : 初始化SPI+DMA，单线MOSI驱动
 输入参数  : void  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年9月12日 21:16:39
    作    者   : white
    修改内容   : 新生成函数

*****************************************************************************/
void RGB_SPI_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    SPI_InitTypeDef   SPI_InitStructure;
    DMA_InitTypeDef   DMA_InitStructure;

	//RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
 //   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
 //   RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

 //   DMA_DeInit(DMA1_Channel5);
 //   DMA_InitStructure.DMA_BufferSize = 0;
 //   DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (SPI2->DR);
 //   DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)pixels;
 //   DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
 //   DMA_InitStructure.DMA_Priority = DMA_Priority_Low;			//如果有问题 可能是因为被打断 提高优先级DMA_Priority_Medium
 //   DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
 //   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
 //   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
 //   DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
 //   DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	//DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
 //   DMA_Init(DMA1_Channel5, &DMA_InitStructure); /* DMA1 CH3 = MEM -> DR */

 //   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; 
 //   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
 //   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 //   GPIO_Init(GPIOB, &GPIO_InitStructure);

	////GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 
 ////   GPIO_Init(GPIOB, &GPIO_InitStructure);

 //   SPI_I2S_DeInit(SPI2);

 //   SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
 //   SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
 //   SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
 //   SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
 //   SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
 //   SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
 //   SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16; /* 48MHz / 8 = 6MHz */
 //   SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
 //   SPI_InitStructure.SPI_CRCPolynomial = 7;
 //   SPI_Init(SPI2, &SPI_InitStructure);

 //   SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);

 //   SPI_Cmd(SPI2, ENABLE);

    RCC_AHBPeriphClockCmd(RGB_SPI_DMA_CLK, ENABLE);
    RCC_APB2PeriphClockCmd(RGB_SPI_GPIO_CLK, ENABLE);

	/* 使能SPI时钟 */
	if (RGB_SPI == SPI1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	}
	else if (RGB_SPI == SPI2)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	}
	else if (RGB_SPI == SPI3)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
	}

    DMA_DeInit(RBG_SPI_DMA_CHANNEL);

	//while (DMA_GetCmdStatus(RBG_SPI_DMA_STREAM) != DISABLE)  {
	//}
		
	//DMA_InitStructure.DMA_Channel = RBG_SPI_DMA_CHANNEL;  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (RGB_SPI->DR);
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)pixels;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = 0;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	//DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
 //   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Low;

	//DMA_InitStructure.DMA_FIFOMode            = DMA_FIFOMode_Disable;          /* FIFO模式/直接模式 */
	//DMA_InitStructure.DMA_FIFOThreshold       = DMA_FIFOThreshold_Full; /* FIFO大小 */
	//DMA_InitStructure.DMA_MemoryBurst         = DMA_MemoryBurst_Single;       /* 单次传输 */
	//DMA_InitStructure.DMA_PeripheralBurst     = DMA_PeripheralBurst_Single;

    DMA_Init(RBG_SPI_DMA_CHANNEL, &DMA_InitStructure); /* DMA1 CH3 = MEM -> DR */

    GPIO_InitStructure.GPIO_Pin = RGB_SPI_PIN; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(RGB_SPI_GPIO_PORT, &GPIO_InitStructure);

    SPI_I2S_DeInit(RGB_SPI);

    SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	//SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;

	/* 使能SPI时钟 */
	if ((RGB_SPI == SPI2) || (RGB_SPI == SPI3))
	{
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16; /* 48MHz / 8 = 6MHz */
	}
	else
	{
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32; /* 168MHz / 32 = 5.25MHz */
	}

    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(RGB_SPI, &SPI_InitStructure);

    SPI_I2S_DMACmd(RGB_SPI, SPI_I2S_DMAReq_Tx, ENABLE);

    SPI_Cmd(RGB_SPI, ENABLE);
}

/*****************************************************************************
 函 数 名  : RGB_DMASend
 功能描述  : RGB数据通过DMA发送
 输入参数  : uint32_t length  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年9月12日 21:17:34
    作    者   : white
    修改内容   : 新生成函数

*****************************************************************************/
void RGB_DMASend(uint32_t length)
{
	DMA_Cmd(DMA1_Channel5, DISABLE);
    DMA_ClearFlag(DMA1_FLAG_TC5);
    DMA_SetCurrDataCounter(DMA1_Channel5, length);
    DMA_Cmd(DMA1_Channel5, ENABLE);
}

/*****************************************************************************
 函 数 名  : bsp_RGB_Show
 功能描述  : RGB灯显示，将缓冲区中的灯数据通过DMA发送，同时更新缓冲区
 输入参数  : void  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年9月12日 21:18:01
    作    者   : white
    修改内容   : 新生成函数

*****************************************************************************/
void bsp_RGB_Show(void)
{
	RGB_DMASend(numBytes);

	if (pixels==doubleBuffer)
	{
	  // pixels was using the first buffer
	  pixels  = doubleBuffer+numBytes;	// set pixels to second buffer
	  memcpy(pixels,doubleBuffer,numBytes);// copy first buffer to second buffer
	}
	else
	{
	  // pixels was using the second buffer 	
	  pixels  = doubleBuffer;  // set pixels to first buffer
	  memcpy(pixels,doubleBuffer+numBytes,numBytes);   // copy second buffer to first buffer 
	} 
}

/*Sets a specific pixel to a specific r,g,b colour 
* Because the pixels buffer contains the encoded bitstream, which is in triplets
* the lookup table need to be used to find the correct pattern for each byte in the 3 byte sequence.
*/
void bsp_RGB_setPixelColor(uint16_t n, uint32_t c)
  {
     uint8_t r,g,b;
   
    if(brightness) 
	{ 
      r = ((int)((uint8_t)(c >> 16)) * (int)brightness) >> 8;
      g = ((int)((uint8_t)(c >>  8)) * (int)brightness) >> 8;
      b = ((int)((uint8_t)c) * (int)brightness) >> 8;
	}
	else
	{
      r = (uint8_t)(c >> 16),
      g = (uint8_t)(c >>  8),
	  b = (uint8_t)c;		
	}
	
   uint8_t *bptr = pixels + (n<<3) + n +1;
   uint8_t *tPtr = (uint8_t *)encoderLookup + g*2 + g;// need to index 3 x g into the lookup
   
   *bptr++ = *tPtr++;
   *bptr++ = *tPtr++;
   *bptr++ = *tPtr++;

   tPtr = (uint8_t *)encoderLookup + r*2 + r;
   *bptr++ = *tPtr++;
   *bptr++ = *tPtr++;
   *bptr++ = *tPtr++;   
   
   tPtr = (uint8_t *)encoderLookup + b*2 + b;
   *bptr++ = *tPtr++;
   *bptr++ = *tPtr++;
   *bptr++ = *tPtr++;
}


void bsp_RGB_setPixelColor2(uint16_t n, uint8_t r, uint8_t g, uint8_t b)
 {
   uint8_t *bptr = pixels + (n<<3) + n +1;
   uint8_t *tPtr = (uint8_t *)encoderLookup + g*2 + g;// need to index 3 x g into the lookup
   
   *bptr++ = *tPtr++;
   *bptr++ = *tPtr++;
   *bptr++ = *tPtr++;

   tPtr = (uint8_t *)encoderLookup + r*2 + r;
   *bptr++ = *tPtr++;
   *bptr++ = *tPtr++;
   *bptr++ = *tPtr++;   
   
   tPtr = (uint8_t *)encoderLookup + b*2 + b;
   *bptr++ = *tPtr++;
   *bptr++ = *tPtr++;
   *bptr++ = *tPtr++;
 }


// Adjust output brightness; 0=darkest (off), 255=brightest.  This does
// NOT immediately affect what's currently displayed on the LEDs.  The
// next call to show() will refresh the LEDs at this level.  However,
// this process is potentially "lossy," especially when increasing
// brightness.  The tight timing in the WS2811/WS2812 code means there
// aren't enough free cycles to perform this scaling on the fly as data
// is issued.  So we make a pass through the existing color data in RAM
// and scale it (subsequent graphics commands also work at this
// brightness level).  If there's a significant step up in brightness,
// the limited number of steps (quantization) in the old data will be
// quite visible in the re-scaled version.  For a non-destructive
// change, you'll need to re-render the full strip data.  C'est la vie.
void bsp_RGB_setBrightness(uint8_t b) {
  // Stored brightness value is different than what's passed.
  // This simplifies the actual scaling math later, allowing a fast
  // 8x8-bit multiply and taking the MSB.  'brightness' is a uint8_t,
  // adding 1 here may (intentionally) roll over...so 0 = max brightness
  // (color values are interpreted literally; no scaling), 1 = min
  // brightness (off), 255 = just below max brightness.
  uint8_t newBrightness = b + 1;
  if(newBrightness != brightness) { // Compare against prior value
    // Brightness has changed -- re-scale existing data in RAM
    uint8_t  c,
            *ptr           = pixels,
             oldBrightness = brightness - 1; // De-wrap old brightness value
    uint16_t scale;
    if(oldBrightness == 0) scale = 0; // Avoid /0
    else if(b == 255) scale = 65535 / oldBrightness;
    else scale = (((uint16_t)newBrightness << 8) - 1) / oldBrightness;
    for(uint16_t i=0; i<numBytes; i++) 
	{
      c      = *ptr;
      *ptr++ = (c * scale) >> 8;
    }
    brightness = newBrightness;
  }
}

#if 0
//低效率SPI+DMA驱动方式 能用，不再花费时间优化

uint16_t PixelBuffer[256] = {0};
uint16_t PixelPointer = 0;
uint8_t brightness = 0;
uint32_t cleartemp[3] = {0x000000,0x000000,0x000000};
uint32_t ws2812_temp[6] = {0x110011,0x0C000C,0x030003,
                          0x000000,0x000000,0x000000};

void LED_SPI_LowLevel_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    SPI_InitTypeDef   SPI_InitStructure;
    DMA_InitTypeDef   DMA_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);

    DMA_DeInit(DMA1_Stream7);

	while (DMA_GetCmdStatus(DMA1_Stream7) != DISABLE)  {
	}
		
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & (SPI3->DR);
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)PixelBuffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = 0;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Low;

	DMA_InitStructure.DMA_FIFOMode            = DMA_FIFOMode_Disable;          /* FIFO模式/直接模式 */
	DMA_InitStructure.DMA_FIFOThreshold       = DMA_FIFOThreshold_Full; /* FIFO大小 */
	DMA_InitStructure.DMA_MemoryBurst         = DMA_MemoryBurst_Single;       /* 单次传输 */
	DMA_InitStructure.DMA_PeripheralBurst     = DMA_PeripheralBurst_Single;

    DMA_Init(DMA1_Stream7, &DMA_InitStructure); /* DMA1 CH3 = MEM -> DR */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI3);

    SPI_I2S_DeInit(SPI3);

    SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16; /* 48MHz / 8 = 6MHz */
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI3, &SPI_InitStructure);

    SPI_I2S_DMACmd(SPI3, SPI_I2S_DMAReq_Tx, ENABLE);

    SPI_Cmd(SPI3, ENABLE);
	
    PixelPointer = 0;
	//brightness = 0;
	//numLEDs = 6;
//	ws2812_clear();
}

void LED_SPI_WriteByte(uint16_t Data)
{
    /* Wait until the transmit buffer is empty */
    /*
    while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
    {
    }
    */

    PixelBuffer[PixelPointer] = Data;
    PixelPointer++;

    /* Send the byte */
    /* SPI_I2S_SendData16(SPI2, Data); */
}

void LED_SPI_SendBits(uint8_t bits)
{
    int zero = 0x7800;  //1111110000000000
    int one = 0x7f80;  //111111110000000
    int i = 0x00;

    for (i = 0x80; i >= 0x01; i >>= 1)
    {
        LED_SPI_WriteByte((bits & i) ? one : zero);
    }
}

void LED_SPI_SendPixel(uint32_t color)
{
    /*
     r7,r6,r5,r4,r3,r2,r1,r0,g7,g6,g5,g4,g3,g2,g1,g0,b7,b6,b5,b4,b3,b2,b1,b0
     \_____________________________________________________________________/
                               |      _________________...
                               |     /   __________________...
                               |    /   /   ___________________...
                               |   /   /   /
                              RGB,RGB,RGB,RGB,...,STOP
    */

    /*
    	BUG Fix : Actual is GRB,datasheet is something wrong.
    */
	  uint8_t Red, Green, Blue;  // 三原色
		// 绿 红 蓝 三原色分解
	  Red   = color>>16;
	  Green = color>>8;
	  Blue  = color;
    LED_SPI_SendBits(Green);
    LED_SPI_SendBits(Red);
    LED_SPI_SendBits(Blue);
}

void LED_SPI_Update(uint32_t buffer[], uint32_t length)
{
    uint8_t i = 0;
    uint8_t m = 0;
    if(DMA_GetCurrDataCounter(DMA1_Stream7) == 0)
    {

        for (i = 0; i < length; i++)
        {
            LED_SPI_SendPixel(buffer[i]);
        }

        if(length < RGBLED_NUM)
        {
            for(i = RGBLED_NUM - length; i < length; i++)
            {
                for(m = 0; m < 3; m++)
                {
                    LED_SPI_SendBits(0x00);
                }
            }
        }

        for (i = 0; i < 20; i++)   
        {
            LED_SPI_WriteByte(0x00);
        }

        PixelPointer = 0;

        DMA_Cmd((DMA1_Stream7), DISABLE);
        DMA_ClearFlag((DMA1_Stream7),DMA_FLAG_TCIF7);
        DMA_SetCurrDataCounter((DMA1_Stream7), 24*length+20);
        DMA_Cmd((DMA1_Stream7), ENABLE);
    }
}

void ws2812_clear(void)
{
	//u8 i = 0;
	//for (i = 0; i < 6; i++)
	//{
	//	ws2812_temp[i] = 0x000000;
	//}
	LED_SPI_Update(cleartemp, RGBLED_NUM);
}

void ws2812_colorWipe(uint32_t c, uint16_t wait)
{
	u8 i = 0;
	for (i = 0; i < 6; i++)
	{
		ws2812_setPixelColor(i, c);
		LED_SPI_Update(ws2812_temp, 6);
		bsp_DelayMS(wait);
	}
}

void ws2812_setPixelColor_RGB(u8 i, uint8_t r, uint8_t g, uint8_t b)
{
	ws2812_temp[i] = ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

#endif

#endif /* SPI_DMA */

// Convert separate R,G,B into packed 32-bit RGB color.
// Packed format is always RGB, regardless of LED strand color order.
uint32_t bsp_RGB_Color(uint8_t r, uint8_t g, uint8_t b) 
{
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

uint16_t bsp_RGB_numPixels(void) 
{
  return numLEDs;
}

//Return the brightness value
uint8_t bsp_RGB_getBrightness(void) 
{
  return brightness - 1;
}

void bsp_RGB_ledoff(void)
{
	for ( u16 i = 0 ; i < numLEDs ; i++ )
	{
	    bsp_RGB_setPixelColor2(i,0,0,0);
	}
	bsp_RGB_Show();
}

// Fill the dots one after the other with a color
void bsp_RGB_colorWipe(uint32_t c, uint8_t wait) 
{
	for(uint16_t i=0; i<bsp_RGB_numPixels(); i++) 
	{
	  bsp_RGB_setPixelColor(i, c);
	  bsp_RGB_Show();
	  bsp_DelayMS(wait);
	}
}

void  bsp_RGB_rainbow(uint8_t wait) 
{
	uint16_t i, j;

	for(j=0; j<256; j++) 
	{
		for(i=0; i< bsp_RGB_numPixels(); i++) 
		{
			bsp_RGB_setPixelColor(i, bsp_RGB_Wheel((i+j) & 255));
		}
		bsp_RGB_Show();
		bsp_DelayMS(wait);
	}
}

// Slightly different, this makes the rainbow equally distributed throughout
void bsp_RGB_rainbowCycle(uint8_t wait) 
{
uint16_t i, j;

	for(j=0; j<256*5; j++) 
	{ // 5 cycles of all colors on wheel
		for(i=0; i<bsp_RGB_numPixels(); i++) 
		{
			bsp_RGB_setPixelColor(i, bsp_RGB_Wheel(((i * 256 / bsp_RGB_numPixels()) + j) & 255));
		}
		bsp_RGB_Show();
		bsp_DelayMS(wait);
	}
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t bsp_RGB_Wheel(uint8_t WheelPos) 
{
	if(WheelPos < 85) 
	{
		return bsp_RGB_Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	} 
	else 
	{
		if(WheelPos < 170) 
		{
			WheelPos -= 85;
			return bsp_RGB_Color(255 - WheelPos * 3, 0, WheelPos * 3);
		} 
		else 
		{
			WheelPos -= 170;
			return bsp_RGB_Color(0, WheelPos * 3, 255 - WheelPos * 3);
		}
	}
}


//Theatre-style crawling lights.
void bsp_RGB_theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < bsp_RGB_numPixels(); i=i+3) {
        bsp_RGB_setPixelColor(i+q, c);    //turn every third pixel on
      }
      bsp_RGB_Show();

      bsp_DelayMS(wait);

      for (uint16_t i=0; i < bsp_RGB_numPixels(); i=i+3) {
        bsp_RGB_setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void bsp_RGB_theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < bsp_RGB_numPixels(); i=i+3) {
        bsp_RGB_setPixelColor(i+q, bsp_RGB_Wheel( (i+j) % 255));    //turn every third pixel on
      }
      bsp_RGB_Show();

      bsp_DelayMS(wait);

      for (uint16_t i=0; i < bsp_RGB_numPixels(); i=i+3) {
        bsp_RGB_setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}


#ifdef RGBW

// Convert separate R,G,B,W into packed 32-bit WRGB color.
// Packed format is always WRGB, regardless of LED strand color order.
uint32_t bsp_RGBW_Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{
	return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

void bsp_RGBW_pulseWhite(uint8_t wait) {
  for(int j = 0; j < 256 ; j++){
      for(uint16_t i=0; i<bsp_RGB_numPixels(); i++) {
          bsp_RGB_setPixelColor(i, bsp_RGBW_Color(0,0,0, LEDGamma[j] ) );
        }
        bsp_DelayMS(wait);
        bsp_RGB_Show();
      }

  for(int j = 255; j >= 0 ; j--){
      for(uint16_t i=0; i<bsp_RGB_numPixels(); i++) {
          bsp_RGB_setPixelColor(i, bsp_RGBW_Color(0,0,0, LEDGamma[j] ) );
        }
        bsp_DelayMS(wait);
        bsp_RGB_Show();
      }
}

void bsp_RGB_fullWhite() {
  
    for(uint16_t i=0; i<bsp_RGB_numPixels(); i++) {
        bsp_RGB_setPixelColor(i, bsp_RGBW_Color(0,0,0, 255 ) );
    }
     bsp_RGB_Show();
}

void bsp_RGBW_rainbowFade2White(uint8_t wait, int rainbowLoops, int whiteLoops) {
  float fadeMax = 100.0;
  int fadeVal = 0;
  uint32_t wheelVal;
  int redVal, greenVal, blueVal;

  for(int k = 0 ; k < rainbowLoops ; k ++){
    
    for(int j=0; j<256; j++) { // 5 cycles of all colors on wheel

      for(int i=0; i< bsp_RGB_numPixels(); i++) {

        wheelVal = bsp_RGB_Wheel(((i * 256 / bsp_RGB_numPixels()) + j) & 255);

        redVal = red(wheelVal) * float(fadeVal/fadeMax);
        greenVal = green(wheelVal) * float(fadeVal/fadeMax);
        blueVal = blue(wheelVal) * float(fadeVal/fadeMax);

        bsp_RGB_setPixelColor( i, bsp_RGB_Color( redVal, greenVal, blueVal ) );

      }

      //First loop, fade in!
      if(k == 0 && fadeVal < fadeMax-1) {
          fadeVal++;
      }

      //Last loop, fade out!
      else if(k == rainbowLoops - 1 && j > 255 - fadeMax ){
          fadeVal--;
      }

        bsp_RGB_Show();
        bsp_DelayMS(wait);
    }
  
  }

  bsp_DelayMS(500);

  for(int k = 0 ; k < whiteLoops ; k ++){

    for(int j = 0; j < 256 ; j++){

        for(uint16_t i=0; i < bsp_RGB_numPixels(); i++) {
            bsp_RGB_setPixelColor(i, bsp_RGBW_Color(0,0,0, LEDGamma[j] ) );
          }
          bsp_RGB_Show();
        }

        bsp_DelayMS(2000);
    for(int j = 255; j >= 0 ; j--){

        for(uint16_t i=0; i < bsp_RGB_numPixels(); i++) {
            bsp_RGB_setPixelColor(i, bsp_RGBW_Color(0,0,0, LEDGamma[j] ) );
          }
          bsp_RGB_Show();
        }
  }
  bsp_DelayMS(500);
}

void bsp_RGBW_whiteOverRainbow(uint8_t wait, uint8_t whiteSpeed, uint8_t whiteLength ) {
  
  if(whiteLength >= bsp_RGB_numPixels()) whiteLength = bsp_RGB_numPixels() - 1;

  int head = whiteLength - 1;
  int tail = 0;

  int loops = 3;
  int loopNum = 0;

  static unsigned long lastTime = 0;


  while(true){
    for(int j=0; j<256; j++) {
      for(uint16_t i=0; i<bsp_RGB_numPixels(); i++) {
        if((i >= tail && i <= head) || (tail > head && i >= tail) || (tail > head && i <= head) ){
          bsp_RGB_setPixelColor(i, bsp_RGBW_Color(0,0,0, 255 ) );
        }
        else{
          bsp_RGB_setPixelColor(i, bsp_RGB_Wheel(((i * 256 / bsp_RGB_numPixels()) + j) & 255));
        }
        
      }

      if(millis() - lastTime > whiteSpeed) {
        head++;
        tail++;
        if(head == bsp_RGB_numPixels()){
          loopNum++;
        }
        lastTime = millis();
      }

      if(loopNum == loops) return;
    
      head%=bsp_RGB_numPixels();
      tail%=bsp_RGB_numPixels();
        bsp_RGB_Show();
        bsp_DelayMS(wait);
    }
  }
  
}


uint8_t red(uint32_t c) {
  return (c >> 16);
}
uint8_t green(uint32_t c) {
  return (c >> 8);
}
uint8_t blue(uint32_t c) {
  return (c);
}

#endif

#if 0
void bsp_RGB_test(void)
{
	bsp_RGBLED_Init();
	bsp_RGB_setBrightness(10);
	while ( 1 )
	{
		for ( u8 i = 0 ; i <RGBLED_NUM ; i++ )
		{
			bsp_RGB_setPixelColor(i,bsp_RGB_Color(255,0,0));
			bsp_RGB_Show();
			bsp_DelayMS(50);
		}
		for ( u8 i = 0 ; i <RGBLED_NUM ; i++ )
		{
			bsp_RGB_setPixelColor(i,bsp_RGB_Color(0,0,0));
			bsp_RGB_Show();
			bsp_DelayMS(50);
		}
		bsp_RGB_colorWipe(bsp_RGB_Color(10,0,0),10);
		bsp_RGB_colorWipe(bsp_RGB_Color(0,10,0),10);
		bsp_RGB_colorWipe(bsp_RGB_Color(0,0,10),10);
		bsp_RGB_rainbow(20);
		bsp_RGB_rainbowCycle(20);
		bsp_RGB_theaterChase(bsp_RGB_Color(255,0,0),20);
		bsp_RGB_theaterChase(bsp_RGB_Color(0,255,0),20);
		bsp_RGB_theaterChase(bsp_RGB_Color(0,0,255),20);
		bsp_RGB_theaterChaseRainbow(10);
	}
}
#endif



