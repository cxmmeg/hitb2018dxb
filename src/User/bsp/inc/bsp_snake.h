#ifndef __SNAKE_H__
#define __SNAKE_H__

#ifdef __cplusplus
extern "C" {
#endif 

#define SNAKE_Max_Long 12   //蛇的最大长度

	//=================================================================
	//    使用结构体定义变量   使程序的名称更加的清楚
	//=================================================================
	struct Fd
	{
		u8 X;
		u8 Y;
		u8 Yes;
	};	//食物结构体

	struct Se
	{
		u8 X[SNAKE_Max_Long];
		u8 Y[SNAKE_Max_Long];
		u8 Long;          //蛇的长度
		u8 Life;
		u8 Score;					//蛇的分数
		u8 Level;					//蛇的等级              
	};	//蛇结构体

	extern u8 Key_V_temp;     			//取出上次按键值
	extern u8 Key_Value;     				//取出上次按键值

	void Init_SNAKE(void);
	void Run_Ahead(void);
	void Run_SNAKE(void);
	void Display_Pass(void);
	void Display_dead(void);
	void Trun_On_Point(u8 x, u8 y);
	void Trun_Off_Point(u8 x, u8 y);
	u8 RUN_SNK(void);

	//extern void Trun_On_Point (uchar x,uchar y,uchar color);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


