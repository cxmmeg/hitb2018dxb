/******************************************************************************

                  版权所有 (C), 2018-2028, White.

 ******************************************************************************
  文 件 名   : bsp_gfx.c
  版 本 号   : 初稿
  作    者   : white
  生成日期   : 2018年9月8日 21:25:16
  最近修改   :
  功能描述   : 
  函数列表   :
  修改历史   :
              bsp_drawCircle
              bsp_drawCircleHelper
              bsp_drawFastHLine
              bsp_drawFastVLine
              bsp_drawLine
              bsp_drawRect
              bsp_drawRoundRect
              bsp_drawTriangle
              bsp_fillCircle
              bsp_fillCircleHelper
              bsp_fillRect
              bsp_fillRoundRect
              bsp_fillScreen
              bsp_fillTriangle
              bsp_writeFastHLine
              bsp_writeFastVLine
              bsp_writeFillRect
              bsp_writeLine
              bsp_writePixel
  1.日    期   : 2018年9月8日 21:25:16
    作    者   : white
    修改内容   : 创建文件

******************************************************************************/

#include "bsp.h"

extern unsigned char const font_5x7[];
u16 cursor_x, cursor_y, textcolor, textbgcolor;
u8 textsize, wrap;

//int16_t
//  _width,		  ///< Display width as modified by current rotation
//  _height,		  ///< Display height as modified by current rotation
//  cursor_x, 	  ///< x location to start print()ing text
//  cursor_y; 	  ///< y location to start print()ing text
//uint16_t
//  textcolor,	  ///< 16-bit background color for print()
//  textbgcolor;	  ///< 16-bit text color for print()
//uint8_t
//  textsize, 	  ///< Desired magnification of text to print()
//  rotation; 	  ///< Display rotation (0 thru 3)
//boolean
//  wrap, 		  ///< If set, 'wrap' text at right edge of display
//  _cp437;		  ///< If set, use correct CP437 charset (default is off)
////GFXfont
////  *gfxFont; 	  ///< Pointer to special font


///**************************************************************************/
///*!
//   @brief    Instatiate a GFX context for graphics! Can only be done by a superclass
//   @param    w   Display width, in pixels
//   @param    h   Display height, in pixels
//*/
///**************************************************************************/
//void bsp_Initgfx(void)
//{
//    //_width    = w;
//    //_height   = h;
//    //rotation  = 0;
//    cursor_y  = cursor_x    = 0;
//    textsize  = 1;
//    textcolor = textbgcolor = 0xFFFF;
//    wrap      = true;
//    //_cp437    = false;
//    //gfxFont   = NULL;
//}

/**************************************************************************/
/*!
   @brief    Write a line.  Bresenham's algorithm - thx wikpedia
    @param    x0  Start point x coordinate
    @param    y0  Start point y coordinate
    @param    x1  End point x coordinate
    @param    y1  End point y coordinate
    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void bsp_writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) 
{
    int16_t steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        _swap_int16_t(x0, y0);
        _swap_int16_t(x1, y1);
    }

    if (x0 > x1) {
        _swap_int16_t(x0, x1);
        _swap_int16_t(y0, y1);
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0<=x1; x0++) {
        if (steep) {
            bsp_writePixel(y0, x0, color);
        } else {
            bsp_writePixel(x0, y0, color);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}

/*
//画线2
//x1,y1:起点坐标
//x2,y2:终点坐标  
void bsp_writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, u16 color)
{
	int16_t t; 
	int16 xerr=0,yerr=0,delta_x,delta_y,distance; 
	int16 incx,incy,uRow,uCol; 
	delta_x=x1-x0; //计算坐标增量 
	delta_y=y1-y0; 
	uRow=x0; 
	uCol=y0; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	lcd_start_wr();
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		lcd_writePixel(uRow, uCol, color);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}
	lcd_end_wr();
} 

*/


///**************************************************************************/
///*!
//   @brief    Write a perfectly vertical line, overwrite in subclasses if startWrite is defined!
//    @param    x   Top-most x coordinate
//    @param    y   Top-most y coordinate
//    @param    h   Height in pixels
//   @param    color 16-bit 5-6-5 Color to fill with
//*/
///**************************************************************************/
//void bsp_writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) 
//{
//    // Overwrite in subclasses if startWrite is defined!
//    // Can be just writeLine(x, y, x, y+h-1, color);
//    // or writeFillRect(x, y, 1, h, color);
//    bsp_writeLine(x, y, x, y+h-1, color);
//}

///**************************************************************************/
///*!
//   @brief    Write a perfectly horizontal line, overwrite in subclasses if startWrite is defined!
//    @param    x   Left-most x coordinate
//    @param    y   Left-most y coordinate
//    @param    w   Width in pixels
//   @param    color 16-bit 5-6-5 Color to fill with
//*/
///**************************************************************************/
//void bsp_writeFastHLine(int16_t x, int16_t y,          int16_t w, uint16_t color) 
//{
//    // Overwrite in subclasses if startWrite is defined!
//    // Example: writeLine(x, y, x+w-1, y, color);
//    // or writeFillRect(x, y, w, 1, color);
//    bsp_writeLine(x, y, x+w-1, y, color);	
//}


/**************************************************************************/
/*!
   @brief    Draw a perfectly vertical line (this is often optimized in a subclass!)
    @param    x   Top-most x coordinate
    @param    y   Top-most y coordinate
    @param    h   Height in pixels
   @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void bsp_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) 
{
	lcd_start_wr();
    bsp_writeFastVLine(x, y, h, color);
	lcd_end_wr();
}

/**************************************************************************/
/*!
   @brief    Draw a perfectly horizontal line (this is often optimized in a subclass!)
    @param    x   Left-most x coordinate
    @param    y   Left-most y coordinate
    @param    w   Width in pixels
   @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void bsp_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{	
	lcd_start_wr();
    bsp_writeFastHLine(x, y, w, color);	
	lcd_end_wr();
}

/**************************************************************************/
/*!
   @brief    Fill a rectangle completely with one color. Update in subclasses if desired!
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    w   Width in pixels
    @param    h   Height in pixels
   @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void bsp_fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) 
{
	lcd_start_wr();
    bsp_writeFillRect(x,y,w,h,color);
	lcd_end_wr();
	//bsp_fill(x,y,x+w-1,y+h-1,color);
} 

void bsp_fillRect2(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) 
{
	lcd_start_wr();
    bsp_writeFillRect(x0,y0,x1-x0+1,y1-y0+1,color);
	lcd_end_wr();
	//bsp_fill(x,y,x+w-1,y+h-1,color);
} 


//void bsp_writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) 
//{
//    for (int16_t i=x; i<x+w; i++) 
//	{
//        bsp_writeFastVLine(i, y, h, color);
//    }
//} 



/**************************************************************************/
/*!
   @brief    Fill the screen completely with one color. Update in subclasses if desired!
    @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
//void bsp_fillScreen(uint16_t color) 
//{
//    bsp_fillRect(0, 0, lcddev.max_width, lcddev.max_height, color);
//}

/**************************************************************************/
/*!
   @brief    Draw a line
    @param    x0  Start point x coordinate
    @param    y0  Start point y coordinate
    @param    x1  End point x coordinate
    @param    y1  End point y coordinate
    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void bsp_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) 
{
    // Update in subclasses if desired!
    if(x0 == x1){
        if(y0 > y1) _swap_int16_t(y0, y1);
        bsp_drawFastVLine(x0, y0, y1 - y0 + 1, color);
    } else if(y0 == y1){
        if(x0 > x1) _swap_int16_t(x0, x1);
        bsp_drawFastHLine(x0, y0, x1 - x0 + 1, color);
    } else {
    	lcd_start_wr();
        bsp_writeLine(x0, y0, x1, y1, color);
		lcd_end_wr();
    }
}

/**************************************************************************/
/*!
   @brief    Draw a circle outline
    @param    x0   Center-point x coordinate
    @param    y0   Center-point y coordinate
    @param    r   Radius of circle
    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void bsp_drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) 
{
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

	lcd_start_wr();
    bsp_writePixel(x0  , y0+r, color);
    bsp_writePixel(x0  , y0-r, color);
    bsp_writePixel(x0+r, y0  , color);
    bsp_writePixel(x0-r, y0  , color);

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        bsp_writePixel(x0 + x, y0 + y, color);
        bsp_writePixel(x0 - x, y0 + y, color);
        bsp_writePixel(x0 + x, y0 - y, color);
        bsp_writePixel(x0 - x, y0 - y, color);
        bsp_writePixel(x0 + y, y0 + x, color);
        bsp_writePixel(x0 - y, y0 + x, color);
        bsp_writePixel(x0 + y, y0 - x, color);
        bsp_writePixel(x0 - y, y0 - x, color);
    }
	lcd_end_wr();
}

/**************************************************************************/
/*!
   @brief    Quarter-circle drawer, used to do circles and roundrects
    @param    x0   Center-point x coordinate
    @param    y0   Center-point y coordinate
    @param    r   Radius of circle
    @param    cornername  Mask bit #1 or bit #2 to indicate which quarters of the circle we're doing
    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void bsp_drawCircleHelper( int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color) 
{
    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;
        if (cornername & 0x4) {
            bsp_writePixel(x0 + x, y0 + y, color);
            bsp_writePixel(x0 + y, y0 + x, color);
        }
        if (cornername & 0x2) {
            bsp_writePixel(x0 + x, y0 - y, color);
            bsp_writePixel(x0 + y, y0 - x, color);
        }
        if (cornername & 0x8) {
            bsp_writePixel(x0 - y, y0 + x, color);
            bsp_writePixel(x0 - x, y0 + y, color);
        }
        if (cornername & 0x1) {
            bsp_writePixel(x0 - y, y0 - x, color);
            bsp_writePixel(x0 - x, y0 - y, color);
        }
    }
}

/**************************************************************************/
/*!
   @brief    Draw a circle with filled color
    @param    x0   Center-point x coordinate
    @param    y0   Center-point y coordinate
    @param    r   Radius of circle
    @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void bsp_fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) 
{
	lcd_start_wr();
    bsp_writeFastVLine(x0, y0-r, 2*r+1, color);
    bsp_fillCircleHelper(x0, y0, r, 3, 0, color);
	lcd_end_wr();
}


/**************************************************************************/
/*!
   @brief    Quarter-circle drawer with fill, used to do circles and roundrects
    @param    x0   Center-point x coordinate
    @param    y0   Center-point y coordinate
    @param    r   Radius of circle
    @param    cornername  Mask bit #1 or bit #2 to indicate which quarters of the circle we're doing
    @param    delta  Offset from center-point, used for round-rects
    @param    color 16-bit 5-6-5 Color to fill with
*/
/**************************************************************************/
void bsp_fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color) 
{

    int16_t f     = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x     = 0;
    int16_t y     = r;

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f     += ddF_y;
        }
        x++;
        ddF_x += 2;
        f     += ddF_x;

        if (cornername & 0x1) {
            bsp_writeFastVLine(x0+x, y0-y, 2*y+1+delta, color);
            bsp_writeFastVLine(x0+y, y0-x, 2*x+1+delta, color);
        }
        if (cornername & 0x2) {
            bsp_writeFastVLine(x0-x, y0-y, 2*y+1+delta, color);
            bsp_writeFastVLine(x0-y, y0-x, 2*x+1+delta, color);
        }
    }
}

/**************************************************************************/
/*!
   @brief   Draw a rectangle with no fill color
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    w   Width in pixels
    @param    h   Height in pixels
    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void bsp_drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) 
{
	lcd_start_wr();
    bsp_writeFastHLine(x, y, w, color);
    bsp_writeFastHLine(x, y+h-1, w, color);
    bsp_writeFastVLine(x, y, h, color);
    bsp_writeFastVLine(x+w-1, y, h, color);
	lcd_end_wr();
}

void bsp_drawRect2(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) 
{
	lcd_start_wr();
    bsp_writeFastHLine(x0, y0, x1-x0+1, color);
    bsp_writeFastHLine(x0, y1, x1-x0+1, color);
    bsp_writeFastVLine(x0, y0, y1-y0+1, color);
    bsp_writeFastVLine(x1, y0, y1-y0+1, color);
	lcd_end_wr();
}


/**************************************************************************/
/*!
   @brief   Draw a rounded rectangle with no fill color
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    w   Width in pixels
    @param    h   Height in pixels
    @param    r   Radius of corner rounding
    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void bsp_drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) 
{
	lcd_start_wr();

    // smarter version
    bsp_writeFastHLine(x+r  , y    , w-2*r, color); // Top
    bsp_writeFastHLine(x+r  , y+h-1, w-2*r, color); // Bottom
    bsp_writeFastVLine(x    , y+r  , h-2*r, color); // Left
    bsp_writeFastVLine(x+w-1, y+r  , h-2*r, color); // Right
    // draw four corners
    bsp_drawCircleHelper(x+r    , y+r    , r, 1, color);
    bsp_drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
    bsp_drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
    bsp_drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
	lcd_end_wr();
}

/**************************************************************************/
/*!
   @brief   Draw a rounded rectangle with fill color
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    w   Width in pixels
    @param    h   Height in pixels
    @param    r   Radius of corner rounding
    @param    color 16-bit 5-6-5 Color to draw/fill with
*/
/**************************************************************************/
void bsp_fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) 
{
	
	lcd_start_wr();
	
    // smarter version
    bsp_writeFillRect(x+r, y, w-2*r, h, color);

    // draw four corners
    bsp_fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
    bsp_fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
	lcd_end_wr();
}

/**************************************************************************/
/*!
   @brief   Draw a triangle with no fill color
    @param    x0  Vertex #0 x coordinate
    @param    y0  Vertex #0 y coordinate
    @param    x1  Vertex #1 x coordinate
    @param    y1  Vertex #1 y coordinate
    @param    x2  Vertex #2 x coordinate
    @param    y2  Vertex #2 y coordinate
    @param    color 16-bit 5-6-5 Color to draw with
*/
/**************************************************************************/
void bsp_drawTriangle(int16_t x0, int16_t y0,         int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) 
{
	lcd_start_wr();

    bsp_writeLine(x0, y0, x1, y1, color);
    bsp_writeLine(x1, y1, x2, y2, color);
    bsp_writeLine(x2, y2, x0, y0, color);
	lcd_end_wr();
}

/**************************************************************************/
/*!
   @brief     Draw a triangle with color-fill
    @param    x0  Vertex #0 x coordinate
    @param    y0  Vertex #0 y coordinate
    @param    x1  Vertex #1 x coordinate
    @param    y1  Vertex #1 y coordinate
    @param    x2  Vertex #2 x coordinate
    @param    y2  Vertex #2 y coordinate
    @param    color 16-bit 5-6-5 Color to fill/draw with
*/
/**************************************************************************/
void bsp_fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) 
{

    int16_t a, b, y, last;

    // Sort coordinates by Y order (y2 >= y1 >= y0)
    if (y0 > y1) {
        _swap_int16_t(y0, y1); _swap_int16_t(x0, x1);
    }
    if (y1 > y2) {
        _swap_int16_t(y2, y1); _swap_int16_t(x2, x1);
    }
    if (y0 > y1) {
        _swap_int16_t(y0, y1); _swap_int16_t(x0, x1);
    }

	lcd_start_wr();
    if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
        a = b = x0;
        if(x1 < a)      a = x1;
        else if(x1 > b) b = x1;
        if(x2 < a)      a = x2;
        else if(x2 > b) b = x2;
        bsp_writeFastHLine(a, y0, b-a+1, color);
        return;
    }

    int16_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1;
    int32_t
    sa   = 0,
    sb   = 0;

    // For upper part of triangle, find scanline crossings for segments
    // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
    // is included here (and second loop will be skipped, avoiding a /0
    // error there), otherwise scanline y1 is skipped here and handled
    // in the second loop...which also avoids a /0 error here if y0=y1
    // (flat-topped triangle).
    if(y1 == y2) last = y1;   // Include y1 scanline
    else         last = y1-1; // Skip it

    for(y=y0; y<=last; y++) {
        a   = x0 + sa / dy01;
        b   = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        /* longhand:
        a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
        b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
        */
        if(a > b) _swap_int16_t(a,b);
        bsp_writeFastHLine(a, y, b-a+1, color);
    }
    // For lower part of triangle, find scanline crossings for segments
    // 0-2 and 1-2.  This loop is skipped if y1=y2.
    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for(; y<=y2; y++) {
        a   = x1 + sa / dy12;
        b   = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        /* longhand:
        a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
        b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
        */
        if(a > b) _swap_int16_t(a,b);
        bsp_writeFastHLine(a, y, b-a+1, color);
    }
	lcd_end_wr();
}

/**************************************************************************/
/*!
   @brief      Draw a RAM-resident 1-bit image at the specified (x,y) position, using the specified foreground (for set bits) and background (unset bits) colors.
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    bitmap  byte array with monochrome bitmap
    @param    w   Width of bitmap in pixels
    @param    h   Hieght of bitmap in pixels
    @param    color 16-bit 5-6-5 Color to draw pixels with
    @param    bg 16-bit 5-6-5 Color to draw background with
*/
/**************************************************************************/
void bsp_drawBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg) 
{

    int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t byte = 0;

    lcd_start_wr();
    for(int16_t j=0; j<h; j++, y++) {
        for(int16_t i=0; i<w; i++ ) {
            if(i & 7) byte <<= 1;
            else      byte   = bitmap[j * byteWidth + i / 8];
			if ( bg != color )
            {
            	bsp_writePixel(x+i, y, (byte & 0x80) ? color : bg);
			}
			else
			{
				if(byte & 0x80) bsp_writePixel(x+i, y, color);
			}
        }
    }
    lcd_end_wr();
}


/**************************************************************************/
/*!
   @brief      Draw PROGMEM-resident XBitMap Files (*.xbm), exported from GIMP. 
   Usage: Export from GIMP to *.xbm, rename *.xbm to *.c and open in editor.
   C Array can be directly used with this function.
   There is no RAM-resident version of this function; if generating bitmaps
   in RAM, use the format defined by drawBitmap() and call that instead.
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    bitmap  byte array with monochrome bitmap
    @param    w   Width of bitmap in pixels
    @param    h   Hieght of bitmap in pixels
    @param    color 16-bit 5-6-5 Color to draw pixels with
*/
/**************************************************************************/
void bsp_drawXBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bg) 
{

    int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t byte = 0;

    lcd_start_wr();
    for(int16_t j=0; j<h; j++, y++) {
        for(int16_t i=0; i<w; i++ ) {
            if(i & 7) byte >>= 1;
            //else      byte   = pgm_read_byte(&bitmap[j * byteWidth + i / 8]);
			else      byte   = bitmap[j * byteWidth + i / 8];
            // Nearly identical to drawBitmap(), only the bit order
            // is reversed here (left-to-right = LSB to MSB):
            //if(byte & 0x01) bsp_writePixel(x+i, y, color);
            if ( bg != color )
            {
                bsp_writePixel(x+i, y, (byte & 0x01) ? color : bg);
            }
			else
			{
				if(byte & 0x01) bsp_writePixel(x+i, y, color);
			}
        }
    }
    lcd_end_wr();
}


///**************************************************************************/
///*!
//   @brief   Draw a PROGMEM-resident 8-bit image (grayscale) at the specified (x,y) pos.  
//   Specifically for 8-bit display devices such as IS31FL3731; no color reduction/expansion is performed.
//    @param    x   Top left corner x coordinate
//    @param    y   Top left corner y coordinate
//    @param    bitmap  byte array with grayscale bitmap
//    @param    w   Width of bitmap in pixels
//    @param    h   Hieght of bitmap in pixels
//*/
///**************************************************************************/
//void bsp_drawGrayscaleBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h) 
//{
//    lcd_start_wr();
//    for(int16_t j=0; j<h; j++, y++) {
//        for(int16_t i=0; i<w; i++ ) {
//            bsp_writePixel(x+i, y, (uint8_t)pgm_read_byte(&bitmap[j * w + i]));
//        }
//    }
//    lcd_end_wr();
//}

/**************************************************************************/
/*!
   @brief   Draw a PROGMEM-resident 16-bit image (RGB 5/6/5) at the specified (x,y) position.  
   For 16-bit display devices; no color reduction performed.
    @param    x   Top left corner x coordinate
    @param    y   Top left corner y coordinate
    @param    bitmap  byte array with 16-bit color bitmap
    @param    w   Width of bitmap in pixels
    @param    h   Height of bitmap in pixels
*/
/**************************************************************************/
void bsp_drawRGBBitmap(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h) 
{
    lcd_start_wr();
    for(int16_t j=0; j<h; j++, y++) {
        for(int16_t i=0; i<w; i++ ) {
			bsp_writePixel(x+i, y, bitmap[j * w + i]);
            //bsp_writePixel(x+i, y, pgm_read_word(&bitmap[j * w + i]));
        }
    }
    lcd_end_wr();
}

/*****************************************************************************
 函 数 名  : bsp_drawImage
 功能描述  : 显示图片，image2lcd，水平扫描，16位真彩，RGB565，左边不勾选任何
 输入参数  : int16_t x        
             int16_t y        
             uint8_t *bitmap  
             int16_t w        
             int16_t h        
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年9月9日 21:08:37
    作    者   : white
    修改内容   : 新生成函数

*****************************************************************************/
void bsp_drawImage(int16_t x, int16_t y, uint8_t *bitmap, int16_t w, int16_t h) 
{
    lcd_start_wr();
    for(int16_t j=0; j<h; j++, y++) {
        for(int16_t i=0; i<w; i++ ) {
			bsp_writePixel(x+i, y, bitmap[(j * w + i) * 2 + 1] << 8 | bitmap[(j * w + i) * 2]);
        }
    }
    lcd_end_wr();
}


/*****************************************************************************
 函 数 名  : bsp_drawQRcode
 功能描述  : 显示二维码
 输入参数  : u16 x_offset      
             u16 y_offset      
             const char *data  
             u8 size           
             u16 color         
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年9月10日 0:09:08
    作    者   : white
    修改内容   : 新生成函数

*****************************************************************************/
void bsp_drawQRcode(u16 x_offset, u16 y_offset, const char *data, u8 size, u16 color)
{
	QRCode qrcode;
	uint8_t qrcodeData[qrcode_getBufferSize(3)];

	qrcode_initText(&qrcode, qrcodeData, 3, ECC_HIGH, data);

	lcd_start_wr();

	bsp_writeFillRect(x_offset, y_offset, qrcode.size*size, qrcode.size*size, WHITE);
	for (uint8_t y = 0; y < qrcode.size; y++)
	{
		for (uint8_t x = 0; x < qrcode.size; x++) 
		{
			if (qrcode_getModule(&qrcode, x, y)) 
			{
				//bsp_writePixel(x_offset + (x * 2), y_offset + (y * 2), BLACK);
				//bsp_writePixel(x_offset + (x * 2) + 1, y_offset + (y * 2), BLACK);
				//bsp_writePixel(x_offset + (x * 2) + 1, y_offset + (y * 2) + 1, BLACK);
				//bsp_writePixel(x_offset + (x * 2), y_offset + (y * 2) + 1, BLACK);
				bsp_writeFillRect(x_offset + x * size, y_offset + y * size, size, size, color);
			}
		}
	}
	lcd_end_wr();
}

// TEXT- AND CHARACTER-HANDLING FUNCTIONS ----------------------------------

// Draw a character
/**************************************************************************/
/*!
   @brief   Draw a single character
    @param    x   Bottom left corner x coordinate
    @param    y   Bottom left corner y coordinate
    @param    c   The 8-bit font-indexed character (likely ascii)
    @param    color 16-bit 5-6-5 Color to draw chraracter with
    @param    bg 16-bit 5-6-5 Color to fill background with (if same as color, no background)
    @param    size  Font magnification level, 1 is 'original' size
*/
/**************************************************************************/
void bsp_drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size) 
{
        if((x >= lcddev.max_width)   || // Clip right
           (y >= lcddev.max_height)  || // Clip bottom
           ((x + 6 * size - 1) < 0) || // Clip left
           ((y + 8 * size - 1) < 0))   // Clip top
            return;

        //if(!_cp437 && (c >= 176)) c++; // Handle 'classic' charset behavior

        lcd_start_wr();
        for(int8_t i=0; i<5; i++ ) 
		{ // Char bitmap = 5 columns
            uint8_t line = pgm_read_byte(&font_5x7[c * 5 + i]);
            for(int8_t j=0; j<8; j++, line >>= 1) 
			{
                if(line & 1) 
				{
                    if(size == 1)
                        bsp_writePixel(x+i, y+j, color);
                    else
                        bsp_writeFillRect(x+i*size, y+j*size, size, size, color);
                } 
				else if(bg != color) 
                {
                    if(size == 1)
                        bsp_writePixel(x+i, y+j, bg);
                    else
                        bsp_writeFillRect(x+i*size, y+j*size, size, size, bg);
                }
            }
        }
        if(bg != color) 
		{ // If opaque, draw vertical line for last column
            if(size == 1) bsp_writeFastVLine(x+5, y, 8, bg);
            else          bsp_writeFillRect(x+5*size, y, size, 8*size, bg);
        }
        lcd_end_wr();
}

void bsp_writeChar(uint8_t c) 
{
	if(c == '\n') {                        // Newline?
	    cursor_x  = 0;                     // Reset x to zero,
	    cursor_y += textsize * 8;          // advance y one line
	} else if(c != '\r') {                 // Ignore carriage returns
	    if(wrap && ((cursor_x + textsize * 6) > lcddev.max_width)) { // Off right?
	        cursor_x  = 0;                 // Reset x to zero,
	        cursor_y += textsize * 8;      // advance y one line
	    }
	    bsp_drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
	    cursor_x += textsize * 6;          // Advance x one char
	}
}


/**************************************************************************/
/*!
    @brief  Set text cursor location
    @param  x    X coordinate in pixels
    @param  y    Y coordinate in pixels
*/
/**************************************************************************/
void bsp_lcd_setCursor(int16_t x, int16_t y) 
{
    cursor_x = x;
    cursor_y = y;
}

/**************************************************************************/
/*!
    @brief  Get text cursor X location
    @returns    X coordinate in pixels
*/
/**************************************************************************/
int16_t bsp_getCursorX(void)
{
    return cursor_x;
}

/**************************************************************************/
/*!
    @brief      Get text cursor Y location
    @returns    Y coordinate in pixels
*/
/**************************************************************************/
int16_t bsp_getCursorY(void)
{
    return cursor_y;
}

/**************************************************************************/
/*!
    @brief   Set text 'magnification' size. Each increase in s makes 1 pixel that much bigger.
    @param  s  Desired text size. 1 is default 6x8, 2 is 12x16, 3 is 18x24, etc
*/
/**************************************************************************/
void bsp_setTextSize(uint8_t s) 
{
    textsize = (s > 0) ? s : 1;
}

/**************************************************************************/
/*!
    @brief   Set text font color with transparant background
    @param   c   16-bit 5-6-5 Color to draw text with
*/
/**************************************************************************/
void bsp_setTextColor(uint16_t c) 
{
    // For 'transparent' background, we'll set the bg
    // to the same as fg instead of using a flag
    textcolor = textbgcolor = c;
}

/**************************************************************************/
/*!
    @brief   Set text font color with custom background color
    @param   c   16-bit 5-6-5 Color to draw text with
    @param   b   16-bit 5-6-5 Color to draw background/fill with
*/
/**************************************************************************/
void bsp_setTextColor2(uint16_t c, uint16_t b) 
{
    textcolor   = c;
    textbgcolor = b;
}

/**************************************************************************/
/*!
    @brief      Whether text that is too long should 'wrap' around to the next line.
    @param  w Set true for wrapping, false for clipping
*/
/**************************************************************************/
void bsp_setTextWrap(boolean w) 
{
    wrap = w;
}

void bsp_drawText(int16_t x, int16_t y, const char * text)
{
	bsp_setTextWrap(FALSE);
	bsp_lcd_setCursor(x,y);
	while ( *text )
	{
	    bsp_writeChar(*text++);
	}
}

void bsp_drawColorText(int16_t x, int16_t y, const char * text, uint16_t c, uint16_t b)
{
	bsp_setTextColor2(c, b);
	bsp_drawText(x, y, text);
}


void bsp_drawTextWrap(int16_t x, int16_t y, const char * text)
{
	bsp_setTextWrap(TRUE);
	bsp_lcd_setCursor(x,y);
	while ( *text )
	{
	    bsp_writeChar(*text++);
	}
}

void bsp_lcd_print(const char * text)
{
	bsp_drawText(cursor_x,cursor_y,text);
}

void bsp_lcd_println(const char * text)
{
	bsp_drawTextWrap(cursor_x,cursor_y,text);
}

void bsp_lcd_printf(const char* fmt, ...)
{
	static char sz[1024] = { 0, };
	/* 组合使用可变参数以及vsprintf，实现printf */
	va_list ap;
	
	va_start(ap, fmt);
	vsprintf(sz, fmt, ap); 
	bsp_lcd_print(sz);
	va_end(ap);
}

//范围0-4294967295
void bsp_drawNum(int16_t x, int16_t y, u32 num)
{
	char tem[10];
	sprintf(tem, "%u", num);
	bsp_drawText(x, y, tem);
}

//格式化数字为字符串,format格式要加""比如"%08X"
void bsp_drawNum_Format(u16 x, u16 y, u32 num, char * format)
{
	char tem[10];
	sprintf(tem, format, num);
	bsp_drawText(x, y, tem);
}

void bsp_display_qrcode(u16 x_offset, u16 y_offset, const char *data, u8 size, u16 bg)
{
	QRCode qrcode;
	uint8_t qrcodeData[qrcode_getBufferSize(3)];

	qrcode_initText(&qrcode, qrcodeData, 3, ECC_HIGH, data);

	bsp_fillRect(x_offset, y_offset, qrcode.size*size, qrcode.size*size, WHITE);
	for (uint8_t y = 0; y < qrcode.size; y++)
	{
		for (uint8_t x = 0; x < qrcode.size; x++) 
		{
			if (qrcode_getModule(&qrcode, x, y)) 
			{
				//tft.drawPixel(x_offset + x, y_offset + y, ST7735_BLACK);
				//LCD_DrawPixel(x_offset + (x * 2), y_offset + (y * 2), BLACK);
				//LCD_DrawPixel(x_offset + (x * 2) + 1, y_offset + (y * 2), BLACK);
				//LCD_DrawPixel(x_offset + (x * 2) + 1, y_offset + (y * 2) + 1, BLACK);
				//LCD_DrawPixel(x_offset + (x * 2), y_offset + (y * 2) + 1, BLACK);
				bsp_fillRect(x_offset + x * size, y_offset + y * size, size, size, bg);
			}
		}
	}
}


uint32_t testFillScreen(void) 
{
	uint32_t start = bsp_GetRunTimeUS();
	bsp_fillScreen(BLACK);
	bsp_fillScreen(RED);
	bsp_fillScreen(GREEN);
	bsp_fillScreen(BLUE);
	bsp_fillScreen(YELLOW);
	bsp_fillScreen(WHITE);
	bsp_fillScreen(BLACK);
	return bsp_GetRunTimeUS() - start;
}
uint32_t testText(void) 
{
	bsp_fillScreen(BLACK);
	uint32_t start = micros();
	bsp_lcd_setCursor(0, 0);
	bsp_setTextColor(WHITE);	bsp_setTextSize(1);
	bsp_lcd_println("Hello World!\r\n");
	bsp_setTextColor(YELLOW); bsp_setTextSize(2);
	bsp_lcd_println("1234.56\r\n");
	bsp_setTextColor(RED);	bsp_setTextSize(3);
	bsp_lcd_println("0xABCDEF\r\n\r\n");
	bsp_setTextColor(GREEN);
	bsp_setTextSize(5);
	bsp_lcd_println("TEST\r\n");
	bsp_setTextSize(2);
	bsp_lcd_println("1234567890\r\n");
	bsp_setTextSize(1);
	bsp_lcd_println("1234567890\r\n");
	return micros() - start;
}

uint32_t testLines(uint16_t color)
{
    uint32_t start, t;
    int           x1, y1, x2, y2,
      w = lcddev.max_width,
      h = lcddev.max_height;

    bsp_fillScreen(BLACK);

    x1 = y1 = 0;
    y2    = h - 1;
    start = bsp_GetRunTimeUS();
    for(x2=0; x2<w; x2+=6) bsp_drawLine(x1, y1, x2, y2, color);
    x2    = w - 1;
    for(y2=0; y2<h; y2+=6) bsp_drawLine(x1, y1, x2, y2, color);
    t     = bsp_GetRunTimeUS() - start; // fillScreen doesn't count against timing

    bsp_fillScreen(BLACK);

    x1    = w - 1;
    y1    = 0;
    y2    = h - 1;
    start = bsp_GetRunTimeUS();
    for(x2=0; x2<w; x2+=6) bsp_drawLine(x1, y1, x2, y2, color);
    x2    = 0;
    for(y2=0; y2<h; y2+=6) bsp_drawLine(x1, y1, x2, y2, color);
    t    += bsp_GetRunTimeUS() - start;

    bsp_fillScreen(BLACK);

    x1    = 0;
    y1    = h - 1;
    y2    = 0;
    start = bsp_GetRunTimeUS();
    for(x2=0; x2<w; x2+=6) bsp_drawLine(x1, y1, x2, y2, color);
    x2    = w - 1;
    for(y2=0; y2<h; y2+=6) bsp_drawLine(x1, y1, x2, y2, color);
    t    += bsp_GetRunTimeUS() - start;

    bsp_fillScreen(BLACK);

    x1    = w - 1;
    y1    = h - 1;
    y2    = 0;
    start = bsp_GetRunTimeUS();
    for(x2=0; x2<w; x2+=6) bsp_drawLine(x1, y1, x2, y2, color);
    x2    = 0;
    for(y2=0; y2<h; y2+=6) bsp_drawLine(x1, y1, x2, y2, color);

    return bsp_GetRunTimeUS() - start;
}

uint32_t testFastLines(uint16_t color1, uint16_t color2)
{
    uint32_t start;
    int           x, y, w = lcddev.max_width, h = lcddev.max_height;

    bsp_fillScreen(BLACK);
    start = bsp_GetRunTimeUS();
    for(y=0; y<h; y+=5) bsp_drawFastHLine(0, y, w, color1);
    for(x=0; x<w; x+=5) bsp_drawFastVLine(x, 0, h, color2);

    return bsp_GetRunTimeUS() - start;
}

uint32_t testRects(uint16_t color)
{
    uint32_t start;
    int           n, i, i2,
      cx = lcddev.max_width  / 2,
      cy = lcddev.max_height / 2;

    bsp_fillScreen(BLACK);
    n     = min(lcddev.max_width, lcddev.max_height);
    start = bsp_GetRunTimeUS();
    for(i=2; i<n; i+=6)
    {
        i2 = i / 2;
        bsp_drawRect(cx-i2, cy-i2, i, i, color);
    }

    return bsp_GetRunTimeUS() - start;
}

uint32_t testFilledRects(uint16_t color1, uint16_t color2)
{
    uint32_t start, t = 0;
    int           n, i, i2,
      cx = lcddev.max_width  / 2,
      cy = lcddev.max_height / 2;

    bsp_fillScreen(BLACK);
    n = min(lcddev.max_width, lcddev.max_height);
    for(i=n; i>0; i-=6)
    {
        i2    = i / 2;
        start = bsp_GetRunTimeUS();
        bsp_fillRect(cx-i2, cy-i2, i, i, color1);
        t    += bsp_GetRunTimeUS() - start;
        // Outlines are not included in timing results
        bsp_drawRect(cx-i2, cy-i2, i, i, color2);
    }

    return t;
}

uint32_t testFilledCircles(uint8_t radius, uint16_t color)
{
    uint32_t start;
    int x, y, w = lcddev.max_width, h = lcddev.max_height, r2 = radius * 2;

    bsp_fillScreen(BLACK);
    start = bsp_GetRunTimeUS();
    for(x=radius; x<w; x+=r2)
    {
        for(y=radius; y<h; y+=r2)
        {
            bsp_fillCircle(x, y, radius, color);
        }
    }

    return bsp_GetRunTimeUS() - start;
}

uint32_t testCircles(uint8_t radius, uint16_t color)
{
    uint32_t start;
    int           x, y, r2 = radius * 2,
                        w = lcddev.max_width  + radius,
                        h = lcddev.max_height + radius;

    // Screen is not cleared for this one -- this is
    // intentional and does not affect the reported time.
    start = bsp_GetRunTimeUS();
    for(x=0; x<w; x+=r2)
    {
        for(y=0; y<h; y+=r2)
        {
            bsp_drawCircle(x, y, radius, color);
        }
    }

    return bsp_GetRunTimeUS() - start;
}

uint32_t testTriangles()
{
    uint32_t start;
    int           n, i, cx = lcddev.max_width  / 2,
                        cy = lcddev.max_height / 2;

    bsp_fillScreen(BLACK);
    n     = min(cx, cy);
    start = bsp_GetRunTimeUS();
    for(i=0; i<n; i+=5)
    {
        bsp_drawTriangle(
            cx    , cy - i, // peak
            cx - i, cy + i, // bottom left
            cx + i, cy + i, // bottom right
            bsp_color565(i, i, i));
    }

    return bsp_GetRunTimeUS() - start;
}

uint32_t testFilledTriangles()
{
    uint32_t start, t = 0;
    int           i, cx = lcddev.max_width  / 2,
                     cy = lcddev.max_height / 2;

    bsp_fillScreen(BLACK);
    start = bsp_GetRunTimeUS();
    for(i=min(cx,cy); i>10; i-=5)
    {
        start = bsp_GetRunTimeUS();
        bsp_fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
                         bsp_color565(0, i*10, i*10));
        t += bsp_GetRunTimeUS() - start;
        bsp_drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
                         bsp_color565(i*10, i*10, 0));
    }

    return t;
}

uint32_t testRoundRects()
{
    uint32_t start;
    int           w, i, i2,
      cx = lcddev.max_width  / 2,
      cy = lcddev.max_height / 2;

    bsp_fillScreen(BLACK);
    w     = min(lcddev.max_width, lcddev.max_height);
    start = bsp_GetRunTimeUS();
    for(i=0; i<w; i+=6)
    {
        i2 = i / 2;
        bsp_drawRoundRect(cx-i2, cy-i2, i, i, i/8, bsp_color565(i, 0, 0));
    }

    return bsp_GetRunTimeUS() - start;
}

uint32_t testFilledRoundRects()
{
    uint32_t start;
    int           i, i2,
      cx = lcddev.max_width  / 2,
      cy = lcddev.max_height / 2;

    bsp_fillScreen(BLACK);
    start = bsp_GetRunTimeUS();
    for(i=min(lcddev.max_width, lcddev.max_height); i>20; i-=6)
    {
        i2 = i / 2;
        bsp_fillRoundRect(cx-i2, cy-i2, i, i, i/8, bsp_color565(0, i, 0));
    }

    return bsp_GetRunTimeUS() - start;
}

void bsp_TFT_TEST(void)
{
	printf("Benchmark                Time (microseconds)\r\n");
	
    printf("Screen fill              %d\r\n",testFillScreen());
    bsp_DelayMS(500);
    printf("Text                     %d\r\n",testText());
    bsp_DelayMS(2000);
    printf("Lines                    %d\r\n",testLines(CYAN));
    bsp_DelayMS(500);
    printf("Horiz/Vert Lines         %d\r\n",testFastLines(RED, BLUE));
    bsp_DelayMS(500);
    printf("Rectangles (outline)     %d\r\n",testRects(GREEN));
    bsp_DelayMS(500);
    printf("Rectangles (filled)      %d\r\n",testFilledRects(YELLOW, MAGENTA));
    bsp_DelayMS(500);
    printf("Circles (filled)         %d\r\n",testFilledCircles(10, MAGENTA));
    printf("Circles (outline)        %d\r\n",testCircles(10, WHITE));
    bsp_DelayMS(500);
    printf("Triangles (outline)      %d\r\n",testTriangles());
    bsp_DelayMS(500);
    printf("Triangles (filled)       %d\r\n",testFilledTriangles());
    bsp_DelayMS(500);
    printf("Rounded rects (outline)  %d\r\n",testRoundRects());
    bsp_DelayMS(500);
    printf("Rounded rects (filled)   %d\r\n",testFilledRoundRects());
    bsp_DelayMS(500);

	printf("Done!\r\n");

	while(1)
	{
		bsp_lcd_rotate(DLOOK);
		testText();
		bsp_DelayMS(1000);
		bsp_lcd_rotate(LLOOK);
		testText();
		bsp_DelayMS(1000);
		bsp_lcd_rotate(ULOOK);
		testText();
		bsp_DelayMS(1000);
		bsp_lcd_rotate(RLOOK);
		testText();
		bsp_DelayMS(1000);
	}
}

#if 0
void bsp_LCD_test(void)
{
	bsp_fillScreen(BLACK);

	for ( u8 i = 1 ; i < 10 ; i++ )
	{
	bsp_fillScreen(RED);
	bsp_drawChar(10,10,'a',WHITE,BLACK,i);
	bsp_DelayMS(1000);

	}

	bsp_drawImage(0,0,(u8 *)gImage_d1);
	bsp_drawBitmap(0,0,(u8 *)hacknown,240,220,BLACK,WHITE);
	bsp_drawXBitmap(0,0,hk_20logo_22_bits,240,220,BLACK,WHITE);
	bsp_drawImage(0,0,(u8 *)gImage_d1,240,220);

	for (u16 i = 0 ; i < 51 ; i++ )
	{
		bsp_fillRect(20,20,100,100,GREEN);
	    bsp_fillRoundRect(20,20,100,100,i,WHITE);
		bsp_DelayMS(200);
	}
	for(u16 i=0; i<119; i+=5) 
	{
	    bsp_drawTriangle(
	      119    , 159 - i, // peak
	      119 - i, 159 + i, // bottom left
	      119 + i, 159 + i, // bottom right
	      WHITE);
		bsp_DelayMS(200);
	}
	bsp_fillRect(20,20,100,100,WHITE);
	bsp_drawCircleHelper(100,100,50,1,WHITE);
	bsp_drawCircleHelper(100,100,50,2,WHITE);
	bsp_drawCircleHelper(100,100,50,4,WHITE);
	bsp_drawCircleHelper(100,100,50,8,WHITE);

	LCD_DrawPoint(8,8,WHITE);
	LCD_DrawPoint(10,10,WHITE);
	LCD_DrawPoint(12,12,WHITE);
}

#endif


