/******************************************************************************

                  ��Ȩ���� (C), 2018-2028, White.

 ******************************************************************************
  �� �� ��   : bsp_tft.c
  �� �� ��   : ����
  ��    ��   : white
  ��������   : 2018��9��8�� 21:15:15
  ����޸�   :
  ��������   : ILI9341����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��9��8�� 21:15:15
    ��    ��   : white
    �޸�����   : �����ļ�

******************************************************************************/

#include "bsp.h"

//#define MADCTL_MY   0x80
//#define MADCTL_MX   0x40
//#define MADCTL_MV   0x20
//#define MADCTL_ML   0x10
//#define MADCTL_RGB 0x00
//#define MADCTL_BGR 0x08
//#define MADCTL_MH   0x04

//����LCD��Ҫ����
//Ĭ��Ϊ����
_lcd_dev lcddev;

//������ɫ,������ɫ
//u16 POINT_COLOR = BLACK, BACK_COLOR = WHITE;

/*LCDģ��GPIO��ʼ��*/
//BK PE4 A0(RS/DC) PE2 RES PE5 CS PE3
void lcd_gpio_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(bsp_GetRCCofGPIO(LCD_CS_PORT) | bsp_GetRCCofGPIO(LCD_A0_PORT) \
							| bsp_GetRCCofGPIO(LCD_RES_PORT), ENABLE);//ʹ��GPIOA,Cʱ��

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//��ͨ���ģʽ
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	
	GPIO_InitStructure.GPIO_Pin = LCD_CS_PIN;
	GPIO_Init(LCD_CS_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LCD_A0_PIN;
	GPIO_Init(LCD_A0_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LCD_RES_PIN;
	GPIO_Init(LCD_RES_PORT, &GPIO_InitStructure);

	LCD_CS_1();			//SPIƬѡȡ��

	bsp_Init_SPI(LCD_SPI);

	//SPI_SetSpeed(LCD_SPI, SPI_BaudRatePrescaler_4);

	//	LCD_SPI_Init();//���LCD���ص��޸�SPI������
}


//******************************************************************
//��������  bsp_lcd_light_Init
//���ߣ�    
//���ڣ�    
//���ܣ�    lcd������Ƴ�ʼ��
//���������0:����ֻ�ܿ��ƿ���. 1:����pwm��������
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void lcd_light_Init(void)
{
#ifdef TFT_Light_Ctl	
	bsp_SetTIMOutPWM(LCD_BK_PORT, LCD_BK_PIN, LCD_BK_TIM, 3, LCD_BK_PWMFREQ, 50);
	//TIM11_PWM_Init(500 - 1, 84 - 1);	//84M/84=1Mhz�ļ���Ƶ��,��װ��ֵ500������PWMƵ��Ϊ 1M/500=2Khz. 
#else

	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(bsp_GetRCCofGPIO(LCD_BK_PORT), ENABLE);//ʹ��GPIOBʱ��

	GPIO_InitStructure.GPIO_Pin = LCD_BK_PIN;   //PB9�������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//��ͨ���ģʽ
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
	//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//�ر���������
	GPIO_Init(LCD_BK_PORT, &GPIO_InitStructure);//��ʼ��PB9

#endif
}

//����LCD����
//������к�������תģʽ�л�
void lcd_param(void)
{
	lcddev.id = LCD_ID;
	lcddev.dir = 0;

	lcddev.move_width = LCD_MOVE_WIDTH;
	lcddev.move_height = LCD_MOVE_HEIGHT;
	lcddev.hide_width_l = LCD_HIDE_WIDTH_L;
	lcddev.hide_width_r = LCD_HIDE_WIDTH_R;
	lcddev.hide_height_u = LCD_HIDE_HEIGHT_U;
	lcddev.hide_height_d = LCD_HIDE_HEIGHT_D;
	lcddev.max_width = LCD_MAX_WIDTH - LCD_HIDE_WIDTH_L - LCD_HIDE_WIDTH_R;
	lcddev.max_height = LCD_MAX_HEIGHT - LCD_HIDE_HEIGHT_U - LCD_HIDE_HEIGHT_D;


	lcddev.wramcmd = LCD_WRAM;
	lcddev.setxcmd = LCD_SETX;
	lcddev.setycmd = LCD_SETY;

	lcddev.light = LCD_LIGHT;
}

/*************************************************
��������lcd_set_addr_window
���ܣ�����lcd��ʾ���ڣ��ڴ�����д�������Զ�����,�����С:w*h.
��ڲ�����x,y������ʼ����(���Ͻ�,0,0��ʼ);w,h���ڿ�Ⱥ͸߶�,�������0!!
����ֵ����
*************************************************/
void lcd_set_addr_window(u16 x, u16 y, u16 w, u16 h)
{
	x += lcddev.move_width + lcddev.hide_width_l;
	y += lcddev.move_height + lcddev.hide_height_u;
	w += lcddev.move_width;
	h += lcddev.move_height;

	lcd_wr_cmd(lcddev.setxcmd);
	lcd_wr_16bit(x);
	lcd_wr_16bit(w);

	lcd_wr_cmd(lcddev.setycmd);
	lcd_wr_16bit(y);
	lcd_wr_16bit(h);

	lcd_wr_cmd(lcddev.wramcmd);
}

void lcd_set_cursor(u16 Xpos, u16 Ypos)
{
	//lcd_set_window(Xpos,Ypos,Xpos,Ypos)
	lcd_set_addr_window(Xpos,Ypos,lcddev.max_width-1,lcddev.max_height-1);

	//Xpos += lcddev.move_width + lcddev.hide_width;
	//Ypos += lcddev.move_height + lcddev.hide_height;

	//lcd_wr_cmd(lcddev.setxcmd);
	//lcd_wr_16bit(Xpos);

	//lcd_wr_cmd(lcddev.setycmd);
	//lcd_wr_16bit(Ypos);

	//lcd_wr_cmd(lcddev.wramcmd);
}


void bsp_fillScreen(u16 color)
{
	u16 i, j;
	lcd_start_wr();
	lcd_set_addr_window(0, 0, lcddev.max_width + lcddev.hide_width_l -1, lcddev.max_height + lcddev.hide_height_u - 1);
	
	for (i = 0; i < lcddev.max_height; i++)
	{
		for (j = 0; j < lcddev.max_width; j++)
			lcd_wr_16bit(color);	//д������ 	
	}
	lcd_end_wr();
}

//void LCD_DrawPoint(u16 x, u16 y, u16 color)
//{
//	lcd_start_wr();
//	//lcd_set_addr_window(x,y,1,1);
//	//lcd_set_addr_window(x,y,x+1,y+1);
//	lcd_set_cursor(x, y);//���ù��λ�� 
//	lcd_wr_16bit(color);
//	lcd_end_wr();
//}



//��LCD����оƬд��һ���ֽڡ�
//data1:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
void lcd_wr(u8 cmd, u8 data1)
{
	LCD_CS_0();
	if (cmd)
	{
		LCD_A0_1();
	}
	else
	{
		LCD_A0_0();
	}
	bsp_SPI_Write_Byte(LCD_SPI, data1);
	LCD_CS_1();
}

void lcd_wr_cmd(u8 data1)
{
	LCD_A0_0();
	bsp_SPI_Write_Byte(LCD_SPI, data1);
	LCD_A0_1();
}

void lcd_wr_8bit(u8 data1)
{
	bsp_SPI_Write_Byte(LCD_SPI, data1);
}


void lcd_wr_16bit(u16 data1)
{
	bsp_SPI_Write_Byte(LCD_SPI, data1 >> 8);
	bsp_SPI_Write_Byte(LCD_SPI, data1);
}

void lcd_wr_32bit(u16 data1)
{
	bsp_SPI_Write_Byte(LCD_SPI, data1 >> 24);
	bsp_SPI_Write_Byte(LCD_SPI, data1 >> 16);
	bsp_SPI_Write_Byte(LCD_SPI, data1 >> 8);
	bsp_SPI_Write_Byte(LCD_SPI, data1);
}


//******************************************************************
//��������  lcd_wr_reg
//���ߣ�    
//���ڣ�    
//���ܣ�    д�Ĵ�������
//���������LCD_Reg:�Ĵ�����ַ
//			LCD_RegValue:Ҫд�������
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void lcd_wr_reg(u8 LCD_Reg, u8 LCD_RegValue)
{
	lcd_wr_cmd(LCD_Reg);
	lcd_wr_8bit(LCD_RegValue);
}

//******************************************************************
//��������  LCD_WR_GRAM
//���ߣ�    
//���ڣ�    
//���ܣ�    ��ʼдGRAM
//			�ڸ�Һ��������RGB����ǰ��Ӧ�÷���дGRAMָ��
//�����������
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void lcd_wr_gram(void)
{
	lcd_wr_cmd(lcddev.wramcmd);
}


//��ILI93xx����������ΪGBR��ʽ��������д���ʱ��ΪRGB��ʽ��
//ͨ���ú���ת��
//c:GBR��ʽ����ɫֵ
//����ֵ��RGB��ʽ����ɫֵ
u16 bsp_bgr2rgb(u16 c)
{
	u16  r,g,b,rgb;   
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);
} 

// Pass 8-bit (each) R,G,B, get back 16-bit packed color
uint16_t bsp_color565(uint8_t r, uint8_t g, uint8_t b) 
{
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3);
}

//******************************************************************
//��������  bsp_lcd_rst
//���ߣ�    
//���ڣ�    
//���ܣ�    LCD��λ������Һ����ʼ��ǰҪ���ô˺���
//�����������
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void lcd_rst(void)
{
	LCD_RES_1();
	bsp_DelayMS(100);
	LCD_RES_0();
	bsp_DelayMS(100);
	LCD_RES_1();
	bsp_DelayMS(100);
}

void bsp_Init_Lcd(void)
{
	lcd_gpio_Init();
	lcd_light_Init();

	lcd_rst();	//��λҺ��

	lcd_start_wr();

#ifdef TFT_ILI9341_2_X
    //lcd_wr_cmd(0xEF);
    //lcd_wr_8bit(0x03);
    //lcd_wr_8bit(0x80);
    //lcd_wr_8bit(0x02);
	
	lcd_wr_cmd(0xCB);
	lcd_wr_8bit(0x39);
	lcd_wr_8bit(0x2C);
	lcd_wr_8bit(0x00);
	lcd_wr_8bit(0x34);
	lcd_wr_8bit(0x02);

	lcd_wr_cmd(0xCF);
	lcd_wr_8bit(0x00);
	lcd_wr_8bit(0XC1);
	lcd_wr_8bit(0X30);

	lcd_wr_cmd(0xE8);
	lcd_wr_8bit(0x85);
	lcd_wr_8bit(0x00);
	lcd_wr_8bit(0x78);

	lcd_wr_cmd(0xEA);
	lcd_wr_8bit(0x00);
	lcd_wr_8bit(0x00);

	lcd_wr_cmd(0xED);
	lcd_wr_8bit(0x64);
	lcd_wr_8bit(0x03);
	lcd_wr_8bit(0X12);
	lcd_wr_8bit(0X81);

	lcd_wr_cmd(0xF7);
	lcd_wr_8bit(0x20);

	lcd_wr_cmd(TFT_PWCTR1);    //Power control 
	lcd_wr_8bit(0x23);	 //VRH[5:0] 

	lcd_wr_cmd(TFT_PWCTR2);    //Power control 
	lcd_wr_8bit(0x10);	 //SAP[2:0];BT[3:0] 

	lcd_wr_cmd(TFT_VMCTR1);    //VCM control 
	lcd_wr_8bit(0x3e); //�Աȶȵ���
	lcd_wr_8bit(0x28);

	lcd_wr_cmd(TFT_VMCTR2);    //VCM control2 
	lcd_wr_8bit(0x86);	//--

	lcd_wr_cmd(TFT_MADCTL);    // Memory Access Control 
	lcd_wr_8bit(0x48);

	//lcd_wr_cmd(TFT_VSCRSADD); 
	//LCD_WR_16Bit(0);

	lcd_wr_cmd(TFT_PIXFMT);
	lcd_wr_8bit(0x55);

	lcd_wr_cmd(TFT_FRMCTR1);
	lcd_wr_8bit(0x00);
	lcd_wr_8bit(0x18);

	lcd_wr_cmd(TFT_DFUNCTR);	// Display Function Control 
	lcd_wr_8bit(0x08);
	lcd_wr_8bit(0x82);
	lcd_wr_8bit(0x27);

	lcd_wr_cmd(0xF2);	 // 3Gamma Function Disable 
	lcd_wr_8bit(0x00);

	lcd_wr_cmd(TFT_GAMMASET);	 //Gamma curve selected 
	lcd_wr_8bit(0x01);

	lcd_wr_cmd(TFT_GMCTRP1);	//Set Gamma 
	lcd_wr_8bit(0x0F);
	lcd_wr_8bit(0x31);
	lcd_wr_8bit(0x2B);
	lcd_wr_8bit(0x0C);
	lcd_wr_8bit(0x0E);
	lcd_wr_8bit(0x08);
	lcd_wr_8bit(0x4E);
	lcd_wr_8bit(0xF1);
	lcd_wr_8bit(0x37);
	lcd_wr_8bit(0x07);
	lcd_wr_8bit(0x10);
	lcd_wr_cmd(0x03);
	lcd_wr_8bit(0x0E);
	lcd_wr_8bit(0x09);
	lcd_wr_8bit(0x00);

	lcd_wr_cmd(TFT_GMCTRN1);	//Set Gamma 
	lcd_wr_8bit(0x00);
	lcd_wr_8bit(0x0E);
	lcd_wr_8bit(0x14);
	lcd_wr_8bit(0x03);
	lcd_wr_8bit(0x11);
	lcd_wr_8bit(0x07);
	lcd_wr_8bit(0x31);
	lcd_wr_8bit(0xC1);
	lcd_wr_8bit(0x48);
	lcd_wr_8bit(0x08);
	lcd_wr_8bit(0x0F);
	lcd_wr_8bit(0x0C);
	lcd_wr_8bit(0x31);
	lcd_wr_8bit(0x36);
	lcd_wr_8bit(0x0F);

	lcd_wr_cmd(TFT_SLPOUT);    //Exit Sleep 
	bsp_DelayMS(120);

	lcd_wr_cmd(TFT_DISPON);    //Display on 
	bsp_DelayMS(120);

#endif

#ifdef TFT_ILI9163_1_8

	lcd_wr_cmd(0x11);	//�˳�˯��
	bsp_DelayMS(100);

	lcd_wr_cmd(0x3a);       		  	//ÿ�δ���16λ����(VIPF3-0=0101)��ÿ������16λ(IFPF2-0=101)
    lcd_wr_8bit(0x55);						
   
    lcd_wr_cmd(0x26);       		  	
    lcd_wr_8bit(0x04);
	
    lcd_wr_cmd(0xf2);              		//Driver Output Control(1)
    lcd_wr_8bit(0x01);
    
    lcd_wr_cmd(0xe0);              		//Driver Output Control(1)
    lcd_wr_8bit(0x3f);
    lcd_wr_8bit(0x25);
    lcd_wr_8bit(0x1c);
   	lcd_wr_8bit(0x1e);
    lcd_wr_8bit(0x20);
    lcd_wr_8bit(0x12);
    lcd_wr_8bit(0x2a);
    lcd_wr_8bit(0x90);
    lcd_wr_8bit(0x24);
    lcd_wr_8bit(0x11);
    lcd_wr_8bit(0x00);
    lcd_wr_8bit(0x00);
    lcd_wr_8bit(0x00);
    lcd_wr_8bit(0x00);
    lcd_wr_8bit(0x00);
     
    lcd_wr_cmd(0xe1);              //Driver Output Control(1)
    lcd_wr_8bit(0x20);
    lcd_wr_8bit(0x20);
    lcd_wr_8bit(0x20);
    lcd_wr_8bit(0x20);
    lcd_wr_8bit(0x05);
    lcd_wr_8bit(0x00);
    lcd_wr_8bit(0x15);
    lcd_wr_8bit(0xa7);
    lcd_wr_8bit(0x3d);
    lcd_wr_8bit(0x18);
    lcd_wr_8bit(0x25);
    lcd_wr_8bit(0x2a);
    lcd_wr_8bit(0x2b);
    lcd_wr_8bit(0x2b);  
    lcd_wr_8bit(0x3a);  
    
    lcd_wr_cmd(0xb1);              	//������Ļˢ��Ƶ��
    lcd_wr_8bit(0x08);				   	//DIVA=8
    lcd_wr_8bit(0x08);				   	//VPA =8��Լ90Hz
    				   
    lcd_wr_cmd(0xb4);              	//LCD Driveing control
    lcd_wr_8bit(0x07);				  	//NLA=1,NLB=1,NLC=1
   
   
    lcd_wr_cmd(0xc0);              //LCD Driveing control
    lcd_wr_8bit(0x0a);
    lcd_wr_8bit(0x02);
      
    lcd_wr_cmd(0xc1);              //LCD Driveing control
    lcd_wr_8bit(0x02);

    lcd_wr_cmd(0xc5);              //LCD Driveing control
    lcd_wr_8bit(0x4f);
   	lcd_wr_8bit(0x5a);

    lcd_wr_cmd(0xc7);              //LCD Driveing control
    lcd_wr_8bit(0x40);
    
    lcd_wr_cmd(0x2a);              	//����MCU�ɲ�����LCD�ڲ�RAM��������ʼ����������
    lcd_wr_8bit(0x00);				   	//��������ʼ��ַ0x0000
    lcd_wr_8bit(0x00);					
    lcd_wr_8bit(0x00);				   	//�����������ַ0x007f(127)
    lcd_wr_8bit(0x7f);
   
    lcd_wr_cmd(0x2b);              	//����MCU�ɲ�����LCD�ڲ�RAM��������ʼ��������
    lcd_wr_8bit(0x00);				   	//��������ʼ��ַ0x0000
    lcd_wr_8bit(0x00);
    lcd_wr_8bit(0x00);				  	//�����������ַ0x009f(159)
    lcd_wr_8bit(0x9f);

    lcd_wr_cmd(0x36);              	//����MPU��DDRAM��Ӧ��ϵ
    lcd_wr_8bit(0xc0);					//MX=1,MY=1

    lcd_wr_cmd(0xb7);              	//LCD Driveing control
    lcd_wr_8bit(0x00);				   	//CRL=0

	lcd_wr_cmd(TFT_DISPON);//Display on
	//lcd_wr_cmd(ILI9163_RAMWR);

#endif

#if defined (TFT_ST7735_1_44) || defined (TFT_ST7735_1_8)

	lcd_wr_cmd(0x11);	//�˳�˯��
	bsp_DelayMS(120);

	//ST7735R Frame Rate
    lcd_wr_cmd(TFT_FRMCTR1);		//Frame Rate Control ֡�ʿ���
	lcd_wr_8bit(0x01);
	lcd_wr_8bit(0x2C);
	lcd_wr_8bit(0x2D);

    lcd_wr_cmd(TFT_FRMCTR2);
	lcd_wr_8bit(0x01);
	lcd_wr_8bit(0x2C);
	lcd_wr_8bit(0x2D);

	lcd_wr_cmd(TFT_FRMCTR3);
	lcd_wr_8bit(0x01);
	lcd_wr_8bit(0x2C);
	lcd_wr_8bit(0x2D);
	lcd_wr_8bit(0x01);
	lcd_wr_8bit(0x2C);
	lcd_wr_8bit(0x2D);

	lcd_wr_cmd(TFT_INVCTR);		 //Display Inversion Control ��ʾ��ת����
	lcd_wr_8bit(0x07);

	//ST7735R Power Sequence
	lcd_wr_cmd(TFT_PWCTR1);
	lcd_wr_8bit(0xA2);
	lcd_wr_8bit(0X02);
	lcd_wr_8bit(0X84);

	lcd_wr_cmd(TFT_PWCTR2);
	lcd_wr_8bit(0xC5);

	lcd_wr_cmd(TFT_PWCTR3);
	lcd_wr_8bit(0x0A);
	lcd_wr_8bit(0x00);

	lcd_wr_cmd(TFT_PWCTR4);
	lcd_wr_8bit(0x8A);
	lcd_wr_8bit(0x2A);

	lcd_wr_cmd(TFT_PWCTR5);
	lcd_wr_8bit(0x8A);
	lcd_wr_8bit(0xEE);

	lcd_wr_cmd(TFT_VMCTR1);    //VCM control 
	lcd_wr_8bit(0x0e); //�Աȶȵ���


	lcd_wr_cmd(LCD_DIR_REG);    // //MX, MY, RGB mode 
	lcd_wr_8bit(0xC0 | LCD_RGB);

	//ST7735R Gamma Sequence
	lcd_wr_cmd(TFT_GMCTRP1);	//Gamma (��+��polarity) Correction Characteristics Setting
	lcd_wr_8bit(0x0f);
	lcd_wr_8bit(0x1a);
	lcd_wr_8bit(0x0f);
	lcd_wr_8bit(0x18);
	lcd_wr_8bit(0x2f);
	lcd_wr_8bit(0x28);
	lcd_wr_8bit(0x20);
	lcd_wr_8bit(0x22);
	lcd_wr_8bit(0x1f);
	lcd_wr_8bit(0x1b);
	lcd_wr_8bit(0x23);
	lcd_wr_8bit(0x37);
	lcd_wr_8bit(0x00);
	lcd_wr_8bit(0x07);
	lcd_wr_8bit(0x02);
	lcd_wr_8bit(0x10);

	lcd_wr_cmd(TFT_GMCTRN1); //Gamma (��-��polarity) Correction Characteristics Setting
	lcd_wr_8bit(0x0f);
	lcd_wr_8bit(0x1b);
	lcd_wr_8bit(0x0f);
	lcd_wr_8bit(0x17);
	lcd_wr_8bit(0x33);
	lcd_wr_8bit(0x2c);
	lcd_wr_8bit(0x29);
	lcd_wr_8bit(0x2e);
	lcd_wr_8bit(0x30);
	lcd_wr_8bit(0x30);
	lcd_wr_8bit(0x39);
	lcd_wr_8bit(0x3f);
	lcd_wr_8bit(0x00);
	lcd_wr_8bit(0x07);
	lcd_wr_8bit(0x03);
	lcd_wr_8bit(0x10);

	lcd_wr_cmd(TFT_CASET);	//Column Address Set
	lcd_wr_8bit(0x00);
	lcd_wr_8bit(0x00);
	lcd_wr_8bit(0x00);
	lcd_wr_8bit(0x7f);	//128*128 Ϊ0x7f 128*160 0x81

	lcd_wr_cmd(TFT_PASET);	//Row Address Set
	lcd_wr_8bit(0x00);
	lcd_wr_8bit(0x00);
	lcd_wr_8bit(0x00);
	lcd_wr_8bit(0x9f);	////128*128 Ϊ0x7f��128*160Ϊ0x9f Ĭ������Ϊ0x9f

	lcd_wr_cmd(0xF0); //Enable test command  
	lcd_wr_8bit(0x01);
	lcd_wr_cmd(0xF6); //Disable ram power save mode 
	lcd_wr_8bit(0x00);

	lcd_wr_cmd(TFT_PIXFMT); //65k mode Interface Pixel Format
	lcd_wr_8bit(0x05);

	lcd_wr_cmd(TFT_DISPON);//Display on
	//lcd_wr_cmd(TFT_RAMWR);

	//bsp_DelayMS(120);

#endif

	lcd_end_wr();
	
	lcd_param();		//����LCD����

	bsp_lcd_rotate(LCD_ROTATE);

	bsp_lcd_setlight(lcddev.light);
}

/*************************************************
��������LCD_Rotate
���ܣ���Ļ��ת
��ڲ���������
����ֵ����
*************************************************/
void bsp_lcd_rotate(u8 dir)
{
	lcd_start_wr();
	switch (dir)
	{
	case DLOOK:		//0�������ϣ�������
		lcddev.dir = 0;
		lcddev.move_width = LCD_MOVE_WIDTH;
		lcddev.move_height = LCD_MOVE_HEIGHT;
		lcddev.hide_width_l = LCD_HIDE_WIDTH_L;
		lcddev.hide_width_r = LCD_HIDE_WIDTH_R;
		lcddev.hide_height_u = LCD_HIDE_HEIGHT_U;
		lcddev.hide_height_d = LCD_HIDE_HEIGHT_D;
		lcddev.max_width = LCD_MAX_WIDTH - LCD_HIDE_WIDTH_L - LCD_HIDE_WIDTH_R;
		lcddev.max_height = LCD_MAX_HEIGHT - LCD_HIDE_HEIGHT_U - LCD_HIDE_HEIGHT_D;
		lcd_wr_reg(LCD_DIR_REG, DLOOK | LCD_RGB);
		break;
	case ULOOK:		//0�������£�������
		lcddev.dir = 0;
		lcddev.move_width = LCD_MOVE_WIDTH;
		lcddev.move_height = LCD_MOVE_HEIGHT;
		lcddev.hide_width_l = LCD_HIDE_WIDTH_R;
		lcddev.hide_width_r = LCD_HIDE_WIDTH_L;
		lcddev.hide_height_u = LCD_HIDE_HEIGHT_D;
		lcddev.hide_height_d = LCD_HIDE_HEIGHT_U;
		lcddev.max_width = LCD_MAX_WIDTH - LCD_HIDE_WIDTH_L - LCD_HIDE_WIDTH_R;
		lcddev.max_height = LCD_MAX_HEIGHT - LCD_HIDE_HEIGHT_U - LCD_HIDE_HEIGHT_D;
		lcd_wr_reg(LCD_DIR_REG, ULOOK | LCD_RGB);
		break;
	case LLOOK:		//0�������ϣ��󿴺���
		lcddev.dir = 1;
		lcddev.move_width = LCD_MOVE_HEIGHT;
		lcddev.move_height = LCD_MOVE_WIDTH;
		lcddev.hide_width_l = LCD_HIDE_HEIGHT_U;
		lcddev.hide_width_r = LCD_HIDE_HEIGHT_D;
		lcddev.hide_height_u = LCD_HIDE_WIDTH_R;
		lcddev.hide_height_d = LCD_HIDE_WIDTH_L;
		lcddev.max_width = LCD_MAX_HEIGHT - LCD_HIDE_HEIGHT_U - LCD_HIDE_HEIGHT_D;
		lcddev.max_height = LCD_MAX_WIDTH - LCD_HIDE_WIDTH_L - LCD_HIDE_WIDTH_R;
		lcd_wr_reg(LCD_DIR_REG, LLOOK | LCD_RGB);
		break;
	case RLOOK:		//0�������£��ҿ�����
		lcddev.dir = 1;
		lcddev.move_width = LCD_MOVE_HEIGHT;
		lcddev.move_height = LCD_MOVE_WIDTH;
		lcddev.hide_width_l = LCD_HIDE_HEIGHT_D;
		lcddev.hide_width_r = LCD_HIDE_HEIGHT_U;
		lcddev.hide_height_u = LCD_HIDE_WIDTH_L;
		lcddev.hide_height_d = LCD_HIDE_WIDTH_R;
		lcddev.max_width = LCD_MAX_HEIGHT - LCD_HIDE_HEIGHT_U - LCD_HIDE_HEIGHT_D;
		lcddev.max_height = LCD_MAX_WIDTH - LCD_HIDE_WIDTH_L - LCD_HIDE_WIDTH_R;
		lcd_wr_reg(LCD_DIR_REG, RLOOK | LCD_RGB);
		break;
	default:
		break;
	}
	lcd_end_wr();
}


//******************************************************************
//��������  bsp_lcd_setlight
//���ߣ�    
//���ڣ�    
//���ܣ�    lcd��������
//���������ctl �Ƿ��������ȵ��ڣ�light ���ȵȼ�0-10�����ñ������ȵ���ʱ��0Ϊ�أ�����Ϊ��
//����ֵ��  ��
//�޸ļ�¼����
//******************************************************************
void bsp_lcd_setlight(u8 light)
{
#if defined (TFT_Light_Ctl)	

	TIM_SetCompare3(TIM2, 25 * light);   //�޸ıȽ�ֵ���޸�ռ�ձȣ���Ϊ�õ�TIM11��CH1��������TIM_SetCompare1�������CH2������TIM_SetCompare2

#else

	if (light == 0)
	{
		LCD_BK_0();
	}
	else
	{
		LCD_BK_1();
	}

#endif
}


void bsp_lcd_display(boolean i) 
{
	lcd_start_wr();
	if ( i )
	{
	    lcd_wr_cmd(TFT_DISPON);
		bsp_lcd_setlight(lcddev.light);
	}
	else
	{
		lcd_wr_cmd(TFT_DISPOFF);
		bsp_lcd_setlight(0);
	}
	lcd_end_wr();
}

void bsp_lcd_invertDisplay(boolean i) 
{
    lcd_start_wr();
    lcd_wr_cmd(i ? TFT_INVON : TFT_INVOFF);
    lcd_end_wr();
}


void bsp_lcd_scrollTo(uint16_t y) 
{
	lcd_start_wr();
    lcd_wr_cmd(TFT_VSCRSADD);
    lcd_wr_16bit(y);
	lcd_end_wr();
}

void lcd_start_wr(void)
{
	LCD_CS_0();
}

void lcd_end_wr(void)
{
	LCD_CS_1();
}

void lcd_pushColor(uint16_t color) 
{
  lcd_start_wr();
  lcd_wr_16bit(color);
  lcd_end_wr();
}


void lcd_writePixel(int16_t x, int16_t y, uint16_t color) 
{
    if((x < 0) ||(x >= lcddev.max_width) || (y < 0) || (y >= lcddev.max_height)) return;
    lcd_set_addr_window(x,y,x,y);
	//lcd_set_cursor(x, y);
    lcd_wr_16bit(color);
}

void bsp_writePixel(int16_t x, int16_t y, uint16_t color) 
{
	lcd_writePixel(x, y, color);
}


void bsp_drawPixel(int16_t x, int16_t y, uint16_t color) 
{
	lcd_start_wr();
	lcd_writePixel(x, y, color);
	lcd_end_wr();
}

void bsp_writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    if((x >= lcddev.max_width) || (y >= lcddev.max_height)) return;
    int16_t x2 = x + w - 1, y2 = y + h - 1;
    if((x2 < 0) || (y2 < 0)) return;

    // Clip left/top
    if(x < 0)
    {
        x = 0;
        w = x2 + 1;
    }
    if(y < 0)
    {
        y = 0;
        h = y2 + 1;
    }

    // Clip right/bottom
    if(x2 >= lcddev.max_width)  w = lcddev.max_width  - x;
    if(y2 >= lcddev.max_height) h = lcddev.max_height - y;

	lcd_set_addr_window(x, y,x+w-1, y+h-1);

	for(y=h; y>0; y--) 
	{
		for(x=w; x>0; x--) 
		{
			lcd_wr_16bit(color);
		}
	}
    //int32_t len = (int32_t)w * h;
    //lcd_set_addr_window(x, y,x+w-1, y+h-1);
    //bsp_writeColor(color, len);
}

void bsp_writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
    bsp_writeFillRect(x, y, 1, h, color);
}

void bsp_writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
    bsp_writeFillRect(x, y, w, 1, color);
}

//void lcd_writePixels(uint16_t * colors, uint32_t len))
//{
//	for(uint32_t i=0; i<(len); i+=2)
//	{
//		lcd_wr_8bit(((uint8_t*)(colors))[i+1]); 
//		lcd_wr_8bit(((uint8_t*)(colors))[i]); 
//	}
//}

//void lcd_writeColor(uint16_t color, uint32_t len)
//{
//    //if(_sclk >= 0){
//    //    for (uint32_t t=0; t<len; t++){
//    //        lcd_writePixel(color);
//    //    }
//    //    return;
//    //}
//    static uint16_t temp[32];
//    uint16_t blen = (len > 32)?32:len;
//    uint16_t tlen = 0;

//    for (uint32_t t=0; t<blen; t++){
//        temp[t] = color;
//    }

//    while(len){
//        tlen = (len>blen)?blen:len;
//        lcd_writePixels(temp, tlen);
//        len -= tlen;
//    }
//}


//void lcd_writeFillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
//{
//    if((x >= lcddev.max_width) || (y >= lcddev.max_height)) return;
//    int16_t x2 = x + w - 1, y2 = y + h - 1;
//    if((x2 < 0) || (y2 < 0)) return;

//    // Clip left/top
//    if(x < 0) {
//        x = 0;
//        w = x2 + 1;
//    }
//    if(y < 0) {
//        y = 0;
//        h = y2 + 1;
//    }

//    // Clip right/bottom
//    if(x2 >= lcddev.max_width)  w = lcddev.max_width  - x;
//    if(y2 >= lcddev.max_height) h = lcddev.max_height - y;

//    int32_t len = (int32_t)w * h;
//    lcd_set_addr_window(x, y, w, h);
//    lcd_writeColor(color, len);
//}


//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void bsp_fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{          
	u16 i,j;
	u16 xlen=0;
//	u16 temp;
	xlen=ex-sx+1;	 

	lcd_start_wr();
	for(i=sy;i<=ey;i++)
	{
	 	lcd_set_cursor(sx,i);      				//���ù��λ��  
		for(j=0;j<xlen;j++)
			lcd_wr_16bit(color);	//��ʾ��ɫ 	    
	}	
	lcd_end_wr();
}  
//��ָ�����������ָ����ɫ��			 
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void bsp_fill_color(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 height,width;
	u16 i,j;
	width=ex-sx+1; 			//�õ����Ŀ��
	height=ey-sy+1;			//�߶�
	
	lcd_start_wr();
 	for(i=0;i<height;i++)
	{
 		lcd_set_cursor(sx,sy+i);   	//���ù��λ�� 
		for(j=0;j<width;j++)
			lcd_wr_16bit(color[i*width+j]);//д������ 
	}	
	lcd_end_wr();
} 

















