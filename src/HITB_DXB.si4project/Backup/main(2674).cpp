/*
*********************************************************************************************************
*
*	ģ������ : ���������
*	�ļ����� : main.c
*	��    �� : V1.0
*	˵    �� : ����ͨ�����ӣ���PC�������ն�������н���
*	�޸ļ�¼ :
*		�汾��  ����       ����    ˵��
*		V1.0    2015-08-30 armfly  �׷�
*
*	Copyright (C), 2015-2016, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#include "bsp.h"				/* �ײ�Ӳ������ */
#include "bsp_bitmap.h"

int8_t Heartbeat_RSSI = 0;
uint8_t Heartbeat_flag = 0;
extern uint8_t get_key[12];
extern uint8_t getkey_flag;
extern int8_t getkey_rssi;
extern uint8_t snake_flag;
/*
*********************************************************************************************************
*	�� �� ��: main
*	����˵��: c�������
*	��    �Σ���
*	�� �� ֵ: �������(���账��)
*********************************************************************************************************
*/
int main(void)
{
	//uint8_t ucKeyCode;	
	uint8_t s_ucTempBuff[64]; /* ���ݽ��ջ��߷��ͻ��� */
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
		ST�̼����е������ļ��Ѿ�ִ���� SystemInit() �������ú����� system_stm32f4xx.c �ļ�����Ҫ������
	����CPUϵͳ��ʱ�ӣ��ڲ�Flash����ʱ������FSMC�����ⲿSRAM
	*/
	
	bsp_Init();		/* Ӳ����ʼ�� */
	
//	PrintfID();	/* ��ӡ�������ƺͰ汾����Ϣ */
	//bsp_DelayMS(5000);

	bsp_fillScreen(BLACK);
	bsp_drawBitmap(8,0,(u8 *)gImage_hitb_logo_2,111,128,WHITE,BLACK);

	bsp_StartAutoTimer(0,300);	/* ����1��1000ms���Զ���װ�Ķ�ʱ�� */
	bsp_StartAutoTimer(1,200);	/* ����1��1000ms���Զ���װ�Ķ�ʱ�� */
#if	 DXB_Super > 0
	bsp_StartAutoTimer(2,50);	/* ����1��1000ms���Զ���װ�Ķ�ʱ�� */
#endif
//******************************* Menu *********************************//

	/* �������ѭ�� */
	while (1)
	{
		bsp_Idle();		/* CPU����ʱִ�еĺ������� bsp.c */
		Menu_Loop();
#if	 DXB_Super > 0
		if (bsp_CheckTimer(2))	/* �ж϶�ʱ����ʱʱ�� */
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
		if (bsp_CheckTimer(1))	/* �ж϶�ʱ����ʱʱ�� */
		{
			hitb_dxb_led(count++);
			if ( count == 12 )
			{
				Menu_DrawFrame();
				Menu_Init();
			    bsp_StopTimer(1);
			}
		}
		if (bsp_CheckTimer(0))	/* �ж϶�ʱ����ʱʱ�� */
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

			///* ע�⣺ ĩβֻ�� \r�س�, û��\n���У�����ʹPC�����ն˽����ȶ���1����ʾ */
			//{
			//	/* �����ն˽����ϻ���ʾһ��������ת���ַ�
			//	����������ܣ���Ϊ�˱�����������ļ�����ΪADC����ֵ���ȶ�
			//	*/
			//	static uint8_t pos = 0;

			//	if (pos == 0)
			//		printf("|");
			//	else if (pos == 1)
			//		printf("/");
			//	else if (pos == 2)
			//		printf("-");
			//	else if (pos == 3)
			//		printf("\\");		/* ע�⣺��������ַ���Ҫת�� */

			//	if (++pos >= 4)
			//	{
			//		pos = 0;
			//	}

			//	printf(" PC4����ADC����ֵ = %5d , ��ѹ = %4dmV\r",
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
		/* �������¼� */
		//ucKeyCode = bsp_GetKey();
		//if (ucKeyCode > 0)
		//{
		//	/* �м����� */
		//	switch (ucKeyCode)
		//	{
		//		case KEY_DOWN_L:		/* ҡ��LEFT������, ����LED��ʾ���� */
		//			printf("KEY_L\n");
		//			bsp_fillScreen(GREEN);
		//			break;		
		//		
		//		case KEY_DOWN_R:		/* ҡ��RIGHT������ */
		//			printf("KEY_R\n");
		//			bsp_fillScreen(RED);
		//			break;

		//		case KEY_DOWN_U:		/* ҡ��UP������ */
		//			printf("KEY_U\n");
		//			bsp_fillScreen(YELLOW);
		//			break;				
		//		
		//		case KEY_DOWN_D:		/* ҡ��DOWN������ */
		//			printf("KEY_D\n");
		//			bsp_fillScreen(BLUE);
		//			break;	
		//		
		//		case KEY_DOWN_OK:		/* ҡ��LEFT������, ����LED��ʾ���� */
		//			printf("KEY_A\n");
		//			bsp_fillScreen(GRAY);
		//			break;		
		//		
		//		case KEY_DOWN_ESC:		/* ҡ��RIGHT������ */
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

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
