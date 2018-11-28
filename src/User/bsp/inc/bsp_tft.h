/******************************************************************************

                  版权所有 (C), 2018-2028, White.

 ******************************************************************************
  文 件 名   : bsp_tft.h
  版 本 号   : 初稿
  作    者   : white
  生成日期   : 2018年9月8日 21:15:15
  最近修改   :
  功能描述   : bsp_tft.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2018年9月8日 21:15:15
    作    者   : white
    修改内容   : 创建文件

******************************************************************************/

#ifndef __BSP_TFT_H__
#define __BSP_TFT_H__

#ifdef __cplusplus
 extern "C" {
#endif 

//------------------------- 预定义 --------------------------------------//

#define TFT_ST7735_1_44		//ST7735S_STD	36h寄存器写C8是RGB
//#define TFT_ST7735_1_8		//ST7735B_ALT	36h寄存器写C0是RGB
//#define TFT_ILI9163_1_8		//ILI9163B
//#define TFT_ILI9341_2_X			//ILI9341B

#define TFT_Light_Ctl           //使能背光亮度调节
//#define TFT_Light_SaveAddr		0x100	//TFT背光保存在EEPROM的位置


//------------------------- LCD接线和命令 --------------------------------------//

#define LCD_SPI					SPI1H
#define LCD_SPI_SPEED			SPI_SPEED_21M

#define LCD_CS_PORT				GPIOB			//LCD_CS GPIO口
#define LCD_CS_PIN				GPIO_Pin_0		//LCD_CS Pin脚位
#define LCD_A0_PORT				GPIOA			//LCD_A0 GPIO口
#define LCD_A0_PIN				GPIO_Pin_4		//LCD_A0 Pin脚位
#define LCD_RES_PORT			GPIOA			//LCD_RES GPIO口
#define LCD_RES_PIN				GPIO_Pin_3		//LCD_RES Pin脚位
#define LCD_BK_PORT				GPIOA			//LCD_BK GPIO口
#define LCD_BK_PIN				GPIO_Pin_2		//LCD_BK Pin脚位
#define LCD_BK_TIM				TIM2			//LCD_BK 对应定时器
#define LCD_BK_PWMFREQ			2000			//LCD_BK PWM频率位2k

#define LCD_CS_0()				LCD_CS_PORT->BRR = LCD_CS_PIN
#define LCD_CS_1()				LCD_CS_PORT->BSRR = LCD_CS_PIN
#define LCD_A0_0()				LCD_A0_PORT->BRR = LCD_A0_PIN
#define LCD_A0_1()				LCD_A0_PORT->BSRR = LCD_A0_PIN
#define LCD_RES_0()				LCD_RES_PORT->BRR = LCD_RES_PIN
#define LCD_RES_1()				LCD_RES_PORT->BSRR = LCD_RES_PIN
#define LCD_BK_0()				LCD_BK_PORT->BRR = LCD_BK_PIN
#define LCD_BK_1()				LCD_BK_PORT->BSRR = LCD_BK_PIN

#define LCD_LIGHT				8
#define LCD_ROTATE				DLOOK		//默认方向 正竖屏，零点左上
	
//------------------------- 	屏幕物理像素设置 --------------------------------------//
	
#ifdef TFT_ILI9341_2_X	
	
#define LCD_ID					0x9341
#define LCD_MOVE_WIDTH			0		//宽度偏移
#define LCD_MOVE_HEIGHT			0		//高度偏移
#define LCD_MAX_WIDTH			240
#define LCD_MAX_HEIGHT			320
#define LCD_HIDE_WIDTH_L		0		//不可视宽度，屏幕左面有遮挡看不到
#define LCD_HIDE_WIDTH_R		0		//不可视宽度，屏幕右面有遮挡看不到
#define LCD_HIDE_HEIGHT_U		0		//不可视高度，屏幕上面有遮挡看不到
#define LCD_HIDE_HEIGHT_D		0		//不可视高度，屏幕下面有遮挡看不到
	
		
#define LCD_WRAM				0x2C
#define LCD_SETX				0x2A
#define LCD_SETY				0x2B
		
#define LCD_DIR_REG				0x36
#define LCD_RGB					0x08
	
#define LCD_CMD					0	//写命令
#define LCD_DATA				1	//写数据
	
	
#define DLOOK					0x40	//0点在左上，正竖屏
#define ULOOK					0x80	//0点在右下，倒竖屏
#define LLOOK					0x20	//0点在右上，左看横屏
#define RLOOK					0xe0	//0点在左下，右看横屏
	
#define ILI9341_TFTWIDTH    	240
#define ILI9341_TFTHEIGHT   	320
	
#endif	
	
#ifdef TFT_ILI9163_1_8	
	
#define LCD_ID					0x9163
#define LCD_MOVE_WIDTH			0		//宽度偏移
#define LCD_MOVE_HEIGHT			0		//高度偏移
#define LCD_MAX_WIDTH			128
#define LCD_MAX_HEIGHT			160
#define LCD_HIDE_WIDTH_L		0		//不可视宽度，屏幕左面有遮挡看不到
#define LCD_HIDE_WIDTH_R		0		//不可视宽度，屏幕右面有遮挡看不到
#define LCD_HIDE_HEIGHT_U		0		//不可视高度，屏幕上面有遮挡看不到
#define LCD_HIDE_HEIGHT_D		0		//不可视高度，屏幕下面有遮挡看不到
	
		
#define LCD_WRAM				0x2C
#define LCD_SETX				0x2A
#define LCD_SETY				0x2B
		
#define LCD_DIR_REG				0x36
#define LCD_RGB					0x00
	
#define LCD_CMD					0	//写命令
#define LCD_DATA				1	//写数据
	
#define DLOOK					0xC0	//0点在左上，正竖屏
#define ULOOK					0x00	//0点在右下，倒竖屏
#define LLOOK					0xA0	//0点在右上，左看横屏
#define RLOOK					0x60	//0点在左下，右看横屏
	
#define ILI9163_TFTWIDTH    	128
#define ILI9163_TFTHEIGHT   	160
	
#endif	
	
#ifdef TFT_ST7735_1_8	
	
#define LCD_ID					0x7735
#define LCD_MOVE_WIDTH			2		//宽度偏移
#define LCD_MOVE_HEIGHT			1		//高度偏移
#define LCD_MAX_WIDTH			128
#define LCD_MAX_HEIGHT			160
#define LCD_HIDE_WIDTH_L		0		//不可视宽度，屏幕左面有遮挡看不到
#define LCD_HIDE_WIDTH_R		0		//不可视宽度，屏幕右面有遮挡看不到
#define LCD_HIDE_HEIGHT_U		0		//不可视高度，屏幕上面有遮挡看不到
#define LCD_HIDE_HEIGHT_D		0		//不可视高度，屏幕下面有遮挡看不到
	
#define LCD_WRAM				0x2C
#define LCD_SETX				0x2A
#define LCD_SETY				0x2B
		
#define LCD_DIR_REG				0x36
#define LCD_RGB					0x00
	
#define LCD_CMD					0	//写命令
#define LCD_DATA				1	//写数据
	
	
#define DLOOK					0xC0	//0点在左上，正竖屏
#define ULOOK					0x00	//0点在右下，倒竖屏
#define LLOOK					0xA0	//0点在右上，左看横屏
#define RLOOK					0x60	//0点在左下，右看横屏
	
#endif	
	
#ifdef TFT_ST7735_1_44		//蓝色1.44
	
#define LCD_ID					0x7735
#define LCD_MOVE_WIDTH			2		//宽度偏移
#define LCD_MOVE_HEIGHT			3		//高度偏移
#define LCD_MAX_WIDTH			128
#define LCD_MAX_HEIGHT			128
#define LCD_HIDE_WIDTH_L		0		//不可视宽度，屏幕左面有遮挡看不到
#define LCD_HIDE_WIDTH_R		0		//不可视宽度，屏幕右面有遮挡看不到
#define LCD_HIDE_HEIGHT_U		0		//不可视高度，屏幕上面有遮挡看不到
#define LCD_HIDE_HEIGHT_D		0		//不可视高度，屏幕下面有遮挡看不到
		
#define LCD_WRAM				0x2C
#define LCD_SETX				0x2A
#define LCD_SETY				0x2B
		
#define LCD_DIR_REG				0x36
#define LCD_RGB					0x08
	
#define LCD_CMD					0	//写命令
#define LCD_DATA				1	//写数据
	
#define DLOOK					0xC0	//0点在左上，正竖屏
#define ULOOK					0x00	//0点在右下，倒竖屏
#define LLOOK					0xA0	//0点在右上，左看横屏
#define RLOOK					0x60	//0点在左下，右看横屏

#endif

//------------------------- 屏幕寄存器 --------------------------------------//

#define TFT_NOP       			0x00
#define TFT_SWRESET   			0x01
#define TFT_RDDID     			0x04
#define TFT_RDDST     			0x09
				
#define TFT_SLPIN     			0x10
#define TFT_SLPOUT    			0x11
#define TFT_PTLON     			0x12
#define TFT_NORON     			0x13
				
#define TFT_RDMODE    			0x0A			//Display Power Mode
#define TFT_RDMADCTL  			0x0B			//MADCTL Mode
#define TFT_RDPIXFMT  			0x0C			//Pixel Format
#define TFT_RDIMGFMT  			0x0D			//Image Format
#define TFT_RDSELFDIAG			0x0F			//Self Diagnostic
				
#define TFT_INVOFF    			0x20
#define TFT_INVON     			0x21
#define TFT_GAMMASET  			0x26
#define TFT_DISPOFF   			0x28
#define TFT_DISPON    			0x29
				
#define TFT_CASET     			0x2A
#define TFT_PASET     			0x2B
#define TFT_RAMWR     			0x2C
#define TFT_RAMRD     			0x2E
				
#define TFT_PTLAR     			0x30
#define TFT_MADCTL    			0x36
#define TFT_VSCRSADD  			0x37
#define TFT_PIXFMT    			0x3A
				
#define TFT_FRMCTR1   			0xB1
#define TFT_FRMCTR2   			0xB2
#define TFT_FRMCTR3   			0xB3
#define TFT_INVCTR    			0xB4
#define TFT_DFUNCTR   			0xB6
				
#define TFT_PWCTR1    			0xC0
#define TFT_PWCTR2    			0xC1
#define TFT_PWCTR3    			0xC2
#define TFT_PWCTR4    			0xC3
#define TFT_PWCTR5    			0xC4
#define TFT_VMCTR1    			0xC5
#define TFT_VMCTR2    			0xC7
				
#define TFT_RDID1     			0xDA
#define TFT_RDID2     			0xDB
#define TFT_RDID3     			0xDC
#define TFT_RDID4     			0xDD
				
#define TFT_GMCTRP1   			0xE0
#define TFT_GMCTRN1   			0xE1

//------------------------- 颜色设置 --------------------------------------//


//画笔颜色 RGB565
#define BLACK       			0x0000      /*   0,   0,   0 */
#define NAVY        			0x000F      /*   0,   0, 128 */
#define DARKGREEN   			0x03E0      /*   0, 128,   0 */
#define DARKCYAN    			0x03EF      /*   0, 128, 128 */
#define MAROON      			0x7800      /* 128,   0,   0 */
#define PURPLE      			0x780F      /* 128,   0, 128 */
#define OLIVE       			0x7BE0      /* 128, 128,   0 */
#define LIGHTGREY   			0xC618      /* 192, 192, 192 */	 //浅灰色(PANNEL),窗体背景色
#define DARKGREY    			0x7BEF      /* 128, 128, 128 */
#define BLUE        			0x001F      /*   0,   0, 255 */
#define GREEN       			0x07E0      /*   0, 255,   0 */
#define CYAN        			0x07FF      /*   0, 255, 255 */
#define RED         			0xF800      /* 255,   0,   0 */
#define MAGENTA     			0xF81F      /* 255,   0, 255 */
#define YELLOW      			0xFFE0      /* 255, 255,   0 */
#define WHITE       			0xFFFF      /* 255, 255, 255 */
#define ORANGE      			0xFD20      /* 255, 165,   0 */
#define GREENYELLOW 			0xAFE5      /* 173, 255,  47 */
#define PINK        			0xF81F
		
#define BROWN					0XBC40 //棕色
#define BRRED					0XFC07 //棕红色
#define GRAY					0X8430 //灰色

//GUI颜色 RGB565

#define DARKBLUE      	 		0X01CF	//深蓝色
#define LIGHTBLUE      	 		0X7D7C	//浅蓝色  
#define GRAYBLUE       	 		0X5458 //灰蓝色
		
//以上三色为PANEL的颜色 RGB565
		
#define LIGHTGREEN     	 		0X841F //浅绿色
//#define LIGHTGRAY 				 0XC618 //浅灰色(PANNEL),窗体背景色
		
#define LGRAYBLUE        		0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           		0X2B12 //浅棕蓝色(选择条目的反色)

//------------------------- 参数、函数预定义 --------------------------------------//

//LCD重要参数集
typedef struct
{
	u16 id; 			//LCD ID
	u8	dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。 

	u16 move_width; 	//LCD 宽度偏移
	u16 move_height;	//LCD 宽度偏移
	//u16 width;			//LCD 使用宽度
	//u16 height;			//LCD 使用高度
	u16 max_width;		//LCD 全屏宽度
	u16 max_height; 	//LCD 全屏高度

	u16 hide_width_l; 	//不可视宽度
	u16 hide_width_r; 	//不可视宽度
	u16 hide_height_u;	//不可视高度
	u16 hide_height_d;	//不可视高度

	u16 wramcmd;		//开始写gram指令
	u16 setxcmd;		//设置x坐标指令
	u16 setycmd;		//设置y坐标指令 
	u8 light;
}_lcd_dev;
	
//LCD地址结构体
//typedef struct
//{
//	vu16 LCD_REG;
//	vu16 LCD_RAM;
//} LCD_TypeDef;

//#define LCD			  ((LCD_TypeDef *) LCD_BASE)

//LCD参数
extern _lcd_dev lcddev; //管理LCD重要参数
//LCD的画笔颜色和背景色
//extern u16	POINT_COLOR;//默认红色	  
//extern u16	BACK_COLOR; //背景颜色.默认为白色

uint16_t bsp_color565(uint8_t r, uint8_t g, uint8_t b);
void bsp_drawPixel(int16_t x, int16_t y, uint16_t color);
void bsp_writePixel(int16_t x, int16_t y, uint16_t color);

u16 bsp_bgr2rgb(u16 c);
void bsp_Init_Lcd(void);
void bsp_lcd_display(boolean i);
void bsp_lcd_invertDisplay(boolean i);
void bsp_lcd_rotate(u8 dir);
void bsp_lcd_scrollTo(uint16_t y);
void bsp_lcd_setlight(u8 light);
void lcd_end_wr(void);
void lcd_gpio_Init(void);
void lcd_light_Init(void);
void lcd_param(void);
void lcd_pushColor(uint16_t color);
void lcd_rst(void);
void lcd_set_addr_window(u16 x, u16 y, u16 w, u16 h);
void lcd_start_wr(void);
void lcd_wr(u8 cmd, u8 data1);
void lcd_writePixel(int16_t x, int16_t y, uint16_t color);
void lcd_wr_16bit(u16 data1);
void lcd_wr_32bit(u16 data1);
void lcd_wr_8bit(u8 data1);
void lcd_wr_cmd(u8 data1);
void lcd_wr_gram(void);
void lcd_wr_reg(u8 LCD_Reg, u8 LCD_RegValue);

void bsp_fillScreen(u16 color);
void lcd_set_cursor(u16 Xpos, u16 Ypos);
//void LCD_DrawPoint(u16 x, u16 y, u16 color);
void bsp_fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);
void bsp_fill_color(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);
void bsp_writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
void bsp_writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
void bsp_writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);



#ifdef __cplusplus
	}
#endif /* __cplusplus */


#endif /* __BSP_TFT_ILI9341_H__ */
