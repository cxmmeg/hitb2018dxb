#include "bsp.h"

u8 Key_V_temp = 0;     				//ȡ���ϴΰ���ֵ
u8 Key_Value = 0;     				//ȡ���ϴΰ���ֵ
uint8_t snake_flag = 0;

//uint8_t game_sel;

struct Fd Food;//����
struct Se Snake;//��

//=================================================================
//�������ƣ�Trun_On_Point(u8 x,u8 y)
//�������ܣ�����һ���� ������ʾ�ߵ�����
//��ڲ������ߵ��������
//���ڲ�������
//�ر�˵�����˺������������ľͿ��Լ���������Һ��
//          ���� 8*8 ����   12864 ��
//=================================================================
void Trun_On_Point(u8 x, u8 y)
{
	bsp_fillRect2((u16)(x * 4), (u16)(y * 4), (u16)(x * 4 + 4), (u16)(y * 4 + 4), RED);
}

//=================================================================
//�������ƣ�Trun_Off_Point(u8 x,u8 y)
//�������ܣ�Ϩ��һ���� ���������ߵ�����
//��ڲ�����
//���ڲ�������
//�ر�˵������ Trun_On���������������ľͿ��Լ���������Һ��
//          ���� 8*8 ����   12864 ��
//=================================================================
void Trun_Off_Point(u8 x, u8 y)
{
	bsp_fillRect2((u16)(x * 4), (u16)(y * 4), (u16)(x * 4 + 4), (u16)(y * 4 + 4), BLACK);
}

//=================================================================
//�������ƣ�void Init_SNAKE(void)  
//�������ܣ�������Ϸ���棬��ʼ����Ϸ�ȼ��Ȳ���
//��ڲ�������
//���ڲ�������
//=================================================================
void Init_SNAKE(void)
{
	u8 i;

	//***********������Ϸ����********************//
	//Snake.Score = 0;
	
	bsp_fillScreen(BLACK);
	bsp_drawRect(0, 0, 128, 128, DARKBLUE);
	bsp_drawFastHLine(0, 11, 127, DARKBLUE);

	bsp_setTextSize(1);
	bsp_lcd_setCursor(4, 3);
	bsp_setTextColor2(WHITE, BLACK);
	bsp_lcd_print("Level:");
	bsp_lcd_setCursor(64, 3);
	bsp_lcd_print("Score:");
	bsp_setTextColor2(RED, BLACK);
	bsp_lcd_setCursor(40, 3);
	bsp_lcd_printf("%d",(u32)Snake.Level);
	bsp_lcd_setCursor(100, 3);
	bsp_lcd_printf("%d",(u32)Snake.Score);

	//***********��ʼ������********************//
	Snake.Long = 2;	    			//�����ʼ���ߵĳ���
	Snake.Life = 0;	    			//��ʼ���߻�����
	Snake.Score = 0;          //����Ϊ0
	Food.Yes = 1;					    //
	Key_Value = 0;
	Key_V_temp = KEY_DOWN_R;//��ʼ������

	for (i = 0; i < Snake.Long; i++)		//���߸���ֵ
	{
		Snake.X[i] = i + 10;//����ߵ�4*4������������ ���ݳ���ѭ��ÿ������һ�������
		Snake.Y[i] = 12;//�����(12,12)��Ϊ�ߵ��������
	}
	for (i = 0; i < Snake.Long; i++)		//�������꽫�߸�������
	{
		Trun_On_Point(Snake.X[i], Snake.Y[i]);
	}
	snake_flag = 1;
}

//=================================================================
//�������ƣ�void Display_dead(u8 i) 
//�������ܣ���ʾ��������
//��ڲ�������
//���ڲ�������
//=================================================================
void Display_dead(void)
{
	bsp_fillScreen(BLACK);

	bsp_drawRect(0, 0, 128, 128, DARKBLUE);
	bsp_drawFastHLine(0, 11, 127, DARKBLUE);

	bsp_setTextColor2(WHITE, BLACK);
	bsp_lcd_setCursor(4, 3);
	bsp_lcd_print("Level:");
	bsp_lcd_setCursor(64, 3);
	bsp_lcd_print("Score:");
	bsp_setTextColor2(RED, BLACK);
	bsp_lcd_setCursor(40, 3);
	bsp_lcd_printf("%d",(u32)Snake.Level);
	bsp_lcd_setCursor(100, 3);
	bsp_lcd_printf("%d",(u32)Snake.Score);

	bsp_setTextColor2(WHITE, BLACK);
	bsp_lcd_setCursor(34, 46);
	bsp_lcd_print("GAME OVER!");
	bsp_lcd_setCursor(7, 62);
	bsp_lcd_print("PRESS OK TO RESTART");

	Snake.Level = 0;
	Snake.Score = 0;

	while ((Key_Value != KEY_DOWN_OK) && Key_Value != KEY_DOWN_ESC)
	{
		Key_Value = bsp_GetKey();
	}
	if ( Key_Value == KEY_DOWN_OK )
	{
	    Init_SNAKE();//���³�ʼ������ �ȴ������´���Ϸ
	}
	else if ( Key_Value == KEY_DOWN_ESC )
	{
		snake_flag = 0;
		Key_V_temp = KEY_DOWN_ESC;
		Key_Value = 0;
	}
	//bsp_fillScreen(BLACK);
}

//=================================================================
//�������ƣ�void Display_Pass(void)
//�������ܣ���ʾ���ؽ���
//��ڲ�������
//���ڲ�������
//=================================================================
void Display_Pass(void)
{
	Snake.Level++;
	if (Snake.Level >= 21)
	{
		while (1)
		{
			bsp_fillScreen(WHITE);
			bsp_setTextColor2(RED, BLACK);
			bsp_lcd_setCursor(19, 54);
		}
	}
	bsp_fillScreen(BLACK);

	bsp_drawRect(0, 0, 128, 128, DARKBLUE);
	bsp_drawFastHLine(0, 11, 127, DARKBLUE);

	bsp_setTextColor2(WHITE, BLACK);
	bsp_lcd_setCursor(4, 3);
	bsp_lcd_print("Level:");
	bsp_lcd_setCursor(64, 3);
	bsp_lcd_print("Score:");
	bsp_setTextColor2(RED, BLACK);
	bsp_lcd_setCursor(40, 3);
	bsp_lcd_printf("%d",(u32)Snake.Level);
	bsp_lcd_setCursor(100, 3);
	bsp_lcd_printf("%d",(u32)Snake.Score);


	bsp_setTextColor2(GREEN, BLACK);
	bsp_lcd_setCursor(19, 46);
	bsp_lcd_print("COOL! LEVEL UP!");
	bsp_lcd_setCursor(7, 62);
	bsp_lcd_print("PRESS OK TO RESTART");

	while ((Key_Value != KEY_DOWN_OK) && Key_Value != KEY_DOWN_ESC)
	{
		Key_Value = bsp_GetKey();
	}
	if ( Key_Value == KEY_DOWN_OK )
	{
	    Init_SNAKE();//���³�ʼ������ �ȴ������´���Ϸ
	}
	else if ( Key_Value == KEY_DOWN_ESC )
	{
		snake_flag = 0;
		Key_V_temp = KEY_DOWN_ESC;
		Key_Value = 0;
	}
}

//=================================================================
//�������ƣ�void Run_Ahead(void)
//�������ܣ�ֱ�к���
//��ڲ�������
//���ڲ�������
//=================================================================
void Run_Ahead(void)
{
	u8 i;

	Trun_Off_Point(Snake.X[0], Snake.Y[0]); 	       //�Ȱ���β��Ϩ��� 

	if (Key_V_temp == KEY_DOWN_L)//��ֱ��
	{
		for (i = 0; i < Snake.Long - 1; i++)                    //��������ǰһ�ε������λ��
		{
			Snake.X[i] = Snake.X[i + 1];
			Snake.Y[i] = Snake.Y[i + 1];
		}
		Snake.X[Snake.Long - 1] = Snake.X[Snake.Long - 2] - 1;//������ͷ
		Snake.Y[Snake.Long - 1] = Snake.Y[Snake.Long - 2] + 0;
	}
	else if (Key_V_temp == KEY_DOWN_R)//��ֱ��
	{
		for (i = 0; i < Snake.Long - 1; i++)                    //��������ǰһ�ε������λ��
		{
			Snake.X[i] = Snake.X[i + 1];
			Snake.Y[i] = Snake.Y[i + 1];
		}
		Snake.X[Snake.Long - 1] = Snake.X[Snake.Long - 2] + 1;//������ͷ
		Snake.Y[Snake.Long - 1] = Snake.Y[Snake.Long - 2] + 0;
	}
	else if (Key_V_temp == KEY_DOWN_U)//��ֱ��
	{
		for (i = 0; i < Snake.Long - 1; i++)                    //��������ǰһ�ε������λ��
		{
			Snake.X[i] = Snake.X[i + 1];
			Snake.Y[i] = Snake.Y[i + 1];
		}
		Snake.X[Snake.Long - 1] = Snake.X[Snake.Long - 2] + 0;//������ͷ
		Snake.Y[Snake.Long - 1] = Snake.Y[Snake.Long - 2] - 1;
	}
	else if (Key_V_temp == KEY_DOWN_D)//��ֱ��
	{
		for (i = 0; i < Snake.Long - 1; i++)                    //��������ǰһ�ε������λ��
		{
			Snake.X[i] = Snake.X[i + 1];
			Snake.Y[i] = Snake.Y[i + 1];
		}
		Snake.X[Snake.Long - 1] = Snake.X[Snake.Long - 2] + 0;//������ͷ
		Snake.Y[Snake.Long - 1] = Snake.Y[Snake.Long - 2] + 1;
	}

	for (i = 0; i < Snake.Long; i++)			            //������ʾ����
	{
		Trun_On_Point(Snake.X[i], Snake.Y[i]);
	}
}

//=================================================================
//�������ƣ�void Run_SNAKE(void)
//�������ܣ����˶����� ����Ϸ������
//��ڲ�������
//���ڲ�������
//=================================================================
void Run_SNAKE(void)
{
	u8 i = 0;
	u16 iSeed = 0;

	iSeed = bsp_GetRunTimeUS()%100000;//ͨ��ģ�������ȡ�������ŵĵ�ƽ�����������
	srand(iSeed);

	/*********************���ݰ���ѡ���ߵ��˶�����*******************/
  //��ת
	if (Key_Value == KEY_DOWN_R && Key_V_temp != KEY_DOWN_L)
	{
		Trun_Off_Point(Snake.X[0], Snake.Y[0]); 	       //�Ȱ���β��Ϩ��� 

		for (i = 0; i < Snake.Long - 1; i++)                    //��������ǰһ�ε������λ��
		{
			Snake.X[i] = Snake.X[i + 1];
			Snake.Y[i] = Snake.Y[i + 1];
		}

		Snake.X[Snake.Long - 1] = Snake.X[Snake.Long - 2] + 1;
		Snake.Y[Snake.Long - 1] = Snake.Y[Snake.Long - 2] + 0; //��ͷ����Ҫ��ķ����ƶ�

		for (i = 0; i < Snake.Long; i++)			            //���������ʾ�����ĺ���
		{
			Trun_On_Point(Snake.X[i], Snake.Y[i]);
		}
		Key_V_temp = KEY_DOWN_R;

		Key_Value = 0;
		//while(RmtCnt!=0);//���ּ��
	}

	//��ת
	if (Key_Value == KEY_DOWN_L && Key_V_temp != KEY_DOWN_R)
	{
		Trun_Off_Point(Snake.X[0], Snake.Y[0]); 		   //�Ȱ���β��Ϩ��� 

		for (i = 0; i < Snake.Long - 1; i++)                     //��������ǰһ�ε������λ��
		{
			Snake.X[i] = Snake.X[i + 1];
			Snake.Y[i] = Snake.Y[i + 1];
		}

		Snake.X[Snake.Long - 1] = Snake.X[Snake.Long - 2] - 1;
		Snake.Y[Snake.Long - 1] = Snake.Y[Snake.Long - 2] + 0; //��ͷ����Ҫ��ķ����ƶ�

		for (i = 0; i < Snake.Long; i++)			            //���������ʾ�����ĺ���
		{
			Trun_On_Point(Snake.X[i], Snake.Y[i]);
		}
		Key_V_temp = KEY_DOWN_L;

		Key_Value = 0;
		//while(RmtCnt!=0);//���ּ��    
	}

	//����
	if (Key_Value == KEY_DOWN_U && Key_V_temp != KEY_DOWN_D)
	{

		Trun_Off_Point(Snake.X[0], Snake.Y[0]); 		  //�Ȱ���β��Ϩ��� 

		for (i = 0; i < Snake.Long - 1; i++)                   //��������ǰһ�ε������λ��
		{
			Snake.X[i] = Snake.X[i + 1];
			Snake.Y[i] = Snake.Y[i + 1];
		}

		Snake.X[Snake.Long - 1] = Snake.X[Snake.Long - 2] + 0;
		Snake.Y[Snake.Long - 1] = Snake.Y[Snake.Long - 2] - 1; //��ͷ����Ҫ��ķ����ƶ�

		for (i = 0; i < Snake.Long; i++)			           //���������ʾ�����ĺ���
		{
			Trun_On_Point(Snake.X[i], Snake.Y[i]);
		}
		Key_V_temp = KEY_DOWN_U;

		Key_Value = 0;
		//while(RmtCnt!=0);//���ּ��    
	}

	//����
	if (Key_Value == KEY_DOWN_D && Key_V_temp != KEY_DOWN_U)
	{

		Trun_Off_Point(Snake.X[0], Snake.Y[0]); 		 //�Ȱ���β��Ϩ��� 

		for (i = 0; i < Snake.Long - 1; i++)                  //��������ǰһ�ε������λ��
		{
			Snake.X[i] = Snake.X[i + 1];
			Snake.Y[i] = Snake.Y[i + 1];
		}

		Snake.X[Snake.Long - 1] = Snake.X[Snake.Long - 2] + 0;
		Snake.Y[Snake.Long - 1] = Snake.Y[Snake.Long - 2] + 1; //��ͷ����Ҫ��ķ����ƶ�

		for (i = 0; i < Snake.Long; i++)			           //���������ʾ�����ĺ���
		{
			Trun_On_Point(Snake.X[i], Snake.Y[i]);
		}
		Key_V_temp = KEY_DOWN_D;

		Key_Value = 0;
		//while(RmtCnt!=0);//���ּ��    
	}
	if (Key_Value == KEY_DOWN_ESC) // check if button left is pressed
	{
		//bsp_fillScreen(BLACK);
		//game_sel = 0;
		snake_flag = 0;
		Key_V_temp = KEY_DOWN_ESC;
		Key_Value = 0;
	}

	/****************���ݰ���ѡ���ߵ��˶��������*******************/
	/////////////////////////////////////////////////////////////////

	/************************�ж����Ƿ�����***********************/

  //����ͷ�Ƿ�ײ��ǽ��
	if (Snake.X[Snake.Long - 1] <= 0 || Snake.X[Snake.Long - 1] >= 31 || Snake.Y[Snake.Long - 1] <= 3 || Snake.Y[Snake.Long - 1] >= 31)
	{
		Snake.Life = 1;//����
	}

	for (i = 3; i < Snake.Long; i++)//�ӵ����ڿ�ʼ�ж���ͷ�Ƿ�ҧ���Լ�
	{
		if (Snake.X[i] == Snake.X[0] && Snake.Y[i] == Snake.Y[0])
		{
			Snake.Life = 1;//����
		}
	}

	if (Snake.Life == 1)//����
	{
		Display_dead();//GAME OVER
	}
	/******************�ж����Ƿ������������***********************/
	/////////////////////////////////////////////////////////////////


	/************************�ж����Ƿ����**********************/
	if (Snake.Long == SNAKE_Max_Long)
	{
		Display_Pass();//����
	}
	/////////////////////////////////////////////////////////////////										   

	/*************************�����Ƿ�Ե�ʳ��**********************/
	if (Snake.X[Snake.Long - 1] == Food.X && Snake.Y[Snake.Long - 1] == Food.Y)//
	{
		//Trun_Off_Point(Food.X,Food.Y); 		 //����ʳ��
		Snake.Long++;//�߽�����1
		Snake.X[Snake.Long - 1] = Food.X;
		Snake.Y[Snake.Long - 1] = Food.Y;
		Snake.Score += 10;
		bsp_setTextColor2(RED, BLACK);
		bsp_lcd_setCursor(100, 3);
		bsp_lcd_printf("%d",(u32)Snake.Score);
		Food.Yes = 1;  //ʳ���־��1
	}
	/////////////////////////////////////////////////////////////////

	/***************************�Ź��ӳ���*************************/
	if (Food.Yes == 0)
	{
		Trun_On_Point(Food.X, Food.Y);
	}
	if (Food.Yes == 1)
	{
		while (1)
		{
			Food.X = rand() % 28 + 1;      			//��������
			Food.Y = rand() % 28 + 3;

			for (i = 0; i < Snake.Long; i++)				//�жϲ�����ʳ�������Ƿ�������غ�
			{
				if ((Food.X == Snake.X[i]) && (Food.X == Snake.Y[i])) break;
			}
			if (i == Snake.Long)
			{
				Food.Yes = 0;
				break;								//������Ч��ʳ������
			}
		}
	}

	Run_Ahead();//ֱ��

	/**************************������Ϸ�ٶ�************************/
	bsp_DelayMS(201 - Snake.Level * 10);
	/////////////////////////////////////////////////////////////////			
}

u8 RUN_SNK(void)
{
	if (snake_flag == 0)
	{
		Init_SNAKE();
	}
	else
	{
		Key_Value = bsp_GetKey();
		if ( Key_Value == KEY_DOWN_ESC )
		{
			Run_SNAKE();
		    return 0;
		}
		else
		{
			Run_SNAKE();
			return 1;
		}
	}
	return 1;
}

