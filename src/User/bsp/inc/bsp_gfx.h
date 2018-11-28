/******************************************************************************

                  版权所有 (C), 2018-2028, White.

 ******************************************************************************
  文 件 名   : bsp_gfx.h
  版 本 号   : 初稿
  作    者   : white
  生成日期   : 2018年9月8日 21:25:16
  最近修改   :
  功能描述   : bsp_gfx.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2018年9月8日 21:25:16
    作    者   : white
    修改内容   : 创建文件

******************************************************************************/

#ifndef __BSP_GFX_H__
#define __BSP_GFX_H__

#ifdef __cplusplus
 extern "C" {
#endif 


extern void bsp_drawPixel(int16_t x, int16_t y, uint16_t color);


//void bsp_Initgfx(void);
void bsp_writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color); 
void bsp_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) ;
//void bsp_writePixel(int16_t x, int16_t y, uint16_t color);
//void bsp_writeFastVLine(int16_t x, int16_t y,         int16_t h, uint16_t color);
//void bsp_writeFastHLine(int16_t x, int16_t y,        int16_t w, uint16_t color);
//void bsp_writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);


void bsp_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
void bsp_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
void bsp_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void bsp_fillRect2(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color); 
//void bsp_fillScreen(uint16_t color);
void bsp_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
void bsp_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void bsp_drawRect2(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
void bsp_drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void bsp_drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,uint16_t color);
void bsp_fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void bsp_fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,int16_t delta, uint16_t color);
void bsp_drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t color);
void bsp_fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t color);
void bsp_drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,int16_t radius, uint16_t color);
void bsp_fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,int16_t radius, uint16_t color);
//void bsp_drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[],int16_t w, int16_t h, uint16_t color);
//void bsp_drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[],int16_t w, int16_t h, uint16_t color, uint16_t bg);
//void bsp_drawBitmap(int16_t x, int16_t y, uint8_t *bitmap,int16_t w, int16_t h, uint16_t color); 
void bsp_drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg);
void bsp_drawXBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg);


//void bsp_drawGrayscaleBitmap(int16_t x, int16_t y, const uint8_t bitmap[],int16_t w, int16_t h);
//void bsp_drawGrayscaleBitmap(int16_t x, int16_t y, uint8_t *bitmap,int16_t w, int16_t h);
//void bsp_drawGrayscaleBitmap(int16_t x, int16_t y,const uint8_t bitmap[], const uint8_t mask[],int16_t w, int16_t h);
//void bsp_drawGrayscaleBitmap(int16_t x, int16_t y, uint8_t *bitmap, uint8_t *mask, int16_t w, int16_t h);
void bsp_drawRGBBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h);

void bsp_drawImage(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h);


//void bsp_drawRGBBitmap(int16_t x, int16_t y, int16_t *bitmap, int16_t w, int16_t h);
//void bsp_drawRGBBitmap(int16_t x, int16_t y, const int16_t bitmap[], const uint8_t mask[], int16_t w, int16_t h);
//void bsp_drawRGBBitmap(int16_t x, int16_t y, int16_t *bitmap, uint8_t *mask, int16_t w, int16_t h);
//void bsp_drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);
//void bsp_lcd_setCursor(int16_t x, int16_t y);
//void bsp_setTextColor(uint16_t c);
//void bsp_cp437(boolean x=true);
//void bsp_setFont(const GFXfont *f = NULL);
//void bsp_getTextBounds(const char *string, int16_t x, int16_t y, int16_t *x1, int16_t *y1, int16_t *w, int16_t *h);
//void bsp_getTextBounds(const __FlashStringHelper *s, int16_t x, int16_t y, int16_t *x1, int16_t *y1, int16_t *w, int16_t *h);
//void bsp_getTextBounds(const String &str, int16_t x, int16_t y, int16_t *x1, int16_t *y1, int16_t *w, int16_t *h);
void bsp_drawQRcode(u16 x_offset, u16 y_offset, const char *data, u8 size, u16 color);
void bsp_drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size); 
void bsp_writeChar(uint8_t c);
void bsp_lcd_setCursor(int16_t x, int16_t y);
int16_t bsp_getCursorX(void);
int16_t bsp_getCursorY(void);
void bsp_setTextSize(uint8_t s);
void bsp_setTextColor(uint16_t c);
void bsp_setTextColor2(uint16_t c, uint16_t b);
void bsp_setTextWrap(boolean w);
void bsp_drawText(int16_t x, int16_t y, const char * text);
void bsp_drawTextWrap(int16_t x, int16_t y, const char * text);
void bsp_drawColorText(int16_t x, int16_t y, const char * text, uint16_t c, uint16_t b);
void bsp_lcd_print(const char * text);
void bsp_lcd_println(const char * text);
void bsp_lcd_printf(const char* fmt, ...);
void bsp_drawNum(int16_t x, int16_t y, u32 num);
void bsp_drawNum_Format(u16 x, u16 y, u32 num, char * format);
void bsp_display_qrcode(u16 x_offset, u16 y_offset, const char *data, u8 size, u16 bg);

void bsp_TFT_TEST(void);




#ifdef __cplusplus
	}
#endif /* __cplusplus */


#endif /* __BSP_GFX_H__ */
