/*
*********************************************************************************************************
*
*	模块名称 : 主程序入口
*	文件名称 : main.c
*	版    本 : V1.0
*	说    明 : 串口通信例子，和PC机超级终端软件进行交互
*	修改记录 :
*		版本号  日期       作者    说明
*		V1.0    2015-08-30 armfly  首发
*
*	Copyright (C), 2015-2016, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#include "bsp.h"				/* 底层硬件驱动 */
#include "bsp_bitmap.h"

int8_t Heartbeat_RSSI = 0;
uint8_t Heartbeat_flag = 0;
extern uint8_t get_key[12];
extern uint8_t getkey_flag;
extern int8_t getkey_rssi;
extern uint8_t snake_flag;
/*
*********************************************************************************************************
*	函 数 名: main
*	功能说明: c程序入口
*	形    参：无
*	返 回 值: 错误代码(无需处理)
*********************************************************************************************************
*/
int main(void)
{
	//uint8_t ucKeyCode;	
	uint8_t s_ucTempBuff[64]; /* 数据接收或者发送缓冲 */
	int8_t s_ucTempRSSI;
	uint8_t Heartbeat[3] = {0x55,0x33,0x66};
	uint8_t HITB_KEY[13] = {"#HITB2018DXB"}; 
	uint8_t temp_key[3] = {0x22,0x60,0x00};
	uint8_t i,len;
	static uint8_t count = 0;
	static uint8_t tt;
	uint8_t super_flag = 0;
	//uint16_t i,j;

	/*
		ST固件库中的启动文件已经执行了 SystemInit() 函数，该函数在 system_stm32f4xx.c 文件，主要功能是
	配置CPU系统的时钟，内部Flash访问时序，配置FSMC用于外部SRAM
	*/
	
	bsp_Init();		/* 硬件初始化 */
	
//	PrintfID();	/* 打印例程名称和版本等信息 */
	//bsp_DelayMS(5000);

	bsp_fillScreen(BLACK);
	bsp_drawBitmap(8,0,(u8 *)gImage_hitb_logo_2,111,128,WHITE,BLACK);

	bsp_StartAutoTimer(0,300);	/* 启动1个1000ms的自动重装的定时器 */
	bsp_StartAutoTimer(1,200);	/* 启动1个1000ms的自动重装的定时器 */
#if	 DXB_Super > 0
	bsp_StartAutoTimer(2,50);	/* 启动1个1000ms的自动重装的定时器 */
#endif
//******************************* Menu *********************************//

	/* 主程序大循环 */
	while (1)
	{
		bsp_Idle();		/* CPU空闲时执行的函数，在 bsp.c */
		Menu_Loop();
#if	 DXB_Super > 0
		if (bsp_CheckTimer(2))	/* 判断定时器超时时间 */
		{
			if ( super_flag == (DXB_Super+2))
			{
			    temp_key[1] = 0x60+(DXB_Super%12);
				temp_key[2] = HITB_KEY[DXB_Super%12];
				Lora_beginPacket(FALSE);
				Lora_writeBuf(temp_key, 3);
				Lora_endPacket();
				super_flag = 0;
			}
			if ( super_flag   > 0 )
			{
			    super_flag++;
			}
		}
#endif
		if (bsp_CheckTimer(1))	/* 判断定时器超时时间 */
		{
			hitb_dxb_led(count++);
			if ( count == 12 )
			{
				Menu_DrawFrame();
				Menu_Init();
			    bsp_StopTimer(1);
			}
		}
		if (bsp_CheckTimer(0))	/* 判断定时器超时时间 */
		{
			tt++;
#if DXB_Attendee == 1
			if ( tt == 24 )
			{
			    Heartbeat_flag = 0;
				if ( snake_flag == 0 )
				{
					bsp_setTextSize(1);
					bsp_setTextColor2(RED,BLACK);
					bsp_lcd_setCursor(88, 4+113);
					bsp_lcd_print("NOSIG!");
				}		
				tt = 0;
			}
#endif

#if DXB_Supreme == 1
			if ( tt == 10 )
			{
			    Lora_beginPacket(FALSE);
				Lora_writeBuf(Heartbeat, 3);
				Lora_endPacket();
				tt = 0;
			}
#endif			

			//hitb_dxb_led(i++);
			//if ( i == 11 )
			//{
			//    i = 0;
			//}
				//for(i = 0; i < 32; i++)
				//{
				//	s_ucTempBuff[i] = count++;
				//}
				//Lora_beginPacket(FALSE);
				////Lora_writeBuf("Hello", 6);
				//Lora_writeBuf(s_ucTempBuff, 32);
				//Lora_endPacket();
//			Menu_UpdateFrame();

			//uint16_t adc;

			//adc = bsp_GetAdc_Average(1);

			///* 注意： 末尾只有 \r回车, 没有\n换行，可以使PC超级终端界面稳定在1行显示 */
			//{
			//	/* 超级终端界面上会显示一个不断旋转的字符
			//	增加这个功能，是为了避免程序死机的假象，因为ADC采样值很稳定
			//	*/
			//	static uint8_t pos = 0;

			//	if (pos == 0)
			//		printf("|");
			//	else if (pos == 1)
			//		printf("/");
			//	else if (pos == 2)
			//		printf("-");
			//	else if (pos == 3)
			//		printf("\\");		/* 注意：这个特殊字符需要转义 */

			//	if (++pos >= 4)
			//	{
			//		pos = 0;
			//	}

			//	printf(" PC4口线ADC采样值 = %5d , 电压 = %4dmV\r",
			//		adc, ((uint32_t)adc * 2500) / 4095);
			//}
			
		}
		
		len = Lora_parsePacket(0);
		if ( len )
		{
			i = 0;
			//printf("Receive Data %d byte:\r\n", len);
		    while(Lora_available())
			{	
				s_ucTempBuff[i++] = Lora_read();
			} 	
			s_ucTempRSSI = Lora_packetRssi();
			if ((s_ucTempBuff[0] == 0x55) && (s_ucTempBuff[1] == 0x33) && (s_ucTempBuff[2] == 0x66))
			{
			    Heartbeat_RSSI = s_ucTempRSSI;
				Heartbeat_flag = 1;
				tt = 0;
				Menu_UpdateFrame();
				s_ucTempBuff[0] = 0;
				s_ucTempBuff[1] = 0;
				s_ucTempBuff[2] = 0;
				super_flag = 1;
			}
			else if((s_ucTempBuff[0] == 0x33) && (s_ucTempBuff[1] == 0x11))
			{
				hitb_dxb_led2(s_ucTempBuff[2]);
				s_ucTempBuff[0] = 0;
				s_ucTempBuff[1] = 0;
				s_ucTempBuff[2] = 0;
			}
			else if((s_ucTempBuff[0] == 0x22) && ((s_ucTempBuff[1]&0xf0) == 0x60))
			{
				getkey_rssi = s_ucTempRSSI;
				if ( getkey_rssi > -80 )
				{
					//for ( i = 0 ; i < 12 ; i++ )
					//{
					//	if ( get_key[i] == s_ucTempBuff[2])
					//	{
					//		break;
					//	}
					//    else if ( get_key[i] == 0)
					//    {
					//        get_key[i] = s_ucTempBuff[2];
					//		break;
					//    }
					//}
					get_key[s_ucTempBuff[1]&0x0f] = s_ucTempBuff[2];
					s_ucTempBuff[0] = 0;
					s_ucTempBuff[1] = 0;
					s_ucTempBuff[2] = 0;
					getkey_flag = 1;
				}
				else
				{
					getkey_flag = 2;
				}
			}
			//printf("\r\nRSSI: %d\r\n", Lora_packetRssi());
		}
		//if ( Heartbeat_flag == 1 )
		//{
		//	Heartbeat_flag = 0;
		//	bsp_RGB_ledoff();
		//}


//		bsp_DelayMS(100);
		/* 处理按键事件 */
		//ucKeyCode = bsp_GetKey();
		//if (ucKeyCode > 0)
		//{
		//	/* 有键按下 */
		//	switch (ucKeyCode)
		//	{
		//		case KEY_DOWN_L:		/* 摇杆LEFT键按下, 控制LED显示流动 */
		//			printf("KEY_L\n");
		//			bsp_fillScreen(GREEN);
		//			break;		
		//		
		//		case KEY_DOWN_R:		/* 摇杆RIGHT键按下 */
		//			printf("KEY_R\n");
		//			bsp_fillScreen(RED);
		//			break;

		//		case KEY_DOWN_U:		/* 摇杆UP键按下 */
		//			printf("KEY_U\n");
		//			bsp_fillScreen(YELLOW);
		//			break;				
		//		
		//		case KEY_DOWN_D:		/* 摇杆DOWN键按下 */
		//			printf("KEY_D\n");
		//			bsp_fillScreen(BLUE);
		//			break;	
		//		
		//		case KEY_DOWN_OK:		/* 摇杆LEFT键按下, 控制LED显示流动 */
		//			printf("KEY_A\n");
		//			bsp_fillScreen(GRAY);
		//			break;		
		//		
		//		case KEY_DOWN_ESC:		/* 摇杆RIGHT键按下 */
		//			printf("KEY_B\n");
		//			bsp_fillScreen(BLACK);
		//			break;
		//		
		//		default:
		//			break;
		//	}
		//}
	}
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
