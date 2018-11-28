#include "bsp.h"
#include "LCDMenuLib2.h"
#include "LCDMenuLib2_menu.h"

static const char *about[6] = { "White-Alone","https://twitter.com/WhiteA10n3","xwings","https://twitter.com/sgniwx","Earl Marcus","https://twitter.com/klks84" };
static const char *conf_agenda27[64]= {	\
"9:15 am - 10:00 am","KEYNOTE 1: CROUCHING TIGER, SUDDEN KEYNOTE","Conf Track 1","Katie Moussouris", \
"10:00 am - 10:45 am","MORNING COFFEE BREAK", " ", " ", \
"10:45 am - 11:45 am","ROOTING ROUTERS USING SYMBOLIC EXECUTION","Conf Track 1","Mathy Vanhoef", \
"10:45 am - 11:45 am","SOMEBODY ANSWER THE PHONE: HACKING TELEPHONE SYSTEMS FOR FUN & PROFIT","Conf Track 2","Himanshu Mehta ,Sachin Wagh", \
"11:45 am - 12:45 pm","VIRTUALIZING IOT WITH CODE COVERAGE GUIDED FUZZING","Conf Track 1","Kai Jern Lau ,Nguyen Anh Quynh", \
"11:45 am - 12:45 pm","IPV666 - ADDRESS OF THE BEAST","Conf Track 2","Marc Newlin ,Chris Grayson", \
"12:45 pm - 2:00 pm","LUNCH", " ", " ", \
"2:00 pm - 3:00 pm","THE PHANTOM MENACE: INTEL ME MANUFACTURING MODE","Conf Track 1","Maxim Goryachy ,Mark Ermolov", \
"2:00 pm - 3:00 pm","IOT WOODPECKER: INTRUSION-DETECTION ON THE HARDWARE BUS","Conf Track 2","Congyuan Xu", \
"3:00 pm - 4:00 pm","HUNTING FOR BACKDOORS IN IOT FIRMWARE AT UNPRECEDENTED SCALE","Conf Track 1","John Toterhi", \
"3:00 pm - 4:00 pm","A MULTIDIMENSIONAL HARDWARE ATTACK AND DEFENSE TOOL SET","Conf Track 2","Kunzhe Chai ,Jie Fu ,Mingchuang Qin", \
"4:00 pm - 4:30 pm","AFTERNOON COFFEE BREAK", " ", " ", \
"4:30 pm - 5:30 pm","AI MODEL SECURITY: REVERSE ENGINEERING MACHINE LEARNING MODELS","Conf Track 1","Kang Li", \
"4:30 pm - 5:30 pm","CLOUDY WITH A CHANCE OF MESSAGES: EXTRACTING MESSAGES FROM ICLOUD","Conf Track 2","Vladimir Katalov", \
"5:30 pm - 6:30 pm","SPANISH FLY: INFECTING FILES ON-THE-FLY","Conf Track 1","Leonardo Nve", \
"5:30 pm - 6:30 pm","GOLD DIGGING: DISCOVERING HIDDEN GEMS IN APKS","Conf Track 2","Marc Schoenefeld" \
};
static const char *conf_agenda28[68]= {	\
"9:00 am - 9:15 am","HITB 10TH YEAR ANNIVERSARY LUCKY DRAW: WIN A TRIP TO AMSTERDAM!","Conf Track 1", " ", \
"9:15 am - 10:00 am","KEYNOTE 2: CYBER ARMS RACE","Conf Track 1","Mikko Hypponen", \
"10:00 am - 10:45 am","MORNING COFFEE BREAK", " ", " ", \
"10:45 am - 11:45 am","HORROR ON THE BUS: HACKING COMBUS","Conf Track 1","Kirils Solovjovs", \
"10:45 am - 11:45 am","ARE YOU LISTENING? AUDITABLE & PROVABLE PRIVACY OF SMART SPEAKERS","Conf Track 2","Wang Kang ,Yang Bo", \
"11:45 am - 12:45 pm","DHCP IS HARD","Conf Track 1","Felix Wilhelm", \
"11:45 am - 12:45 pm","BACK ON THE CHAIN GANG: BLOCKCHAIN, PUBLIC CHAIN AND CONTRACT SECURITY","Conf Track 2","Li Jiafeng ,Yang Changcheng", \
"12:45 pm - 2:00 pm","LUNCH", " ", " ", \
"2:00 pm - 3:00 pm","IT WISN’T ME: ATTACKING INDUSTRIAL WIRELESS MESH NETWORKS","Conf Track 1","Mattijs van Ommeren ,Erwin Paternotte", \
"2:00 pm - 3:00 pm","CAPTURE THIS: REAL TIME PACKET PROCESSING WITH FPGAS","Conf Track 2","Matteo Collura", \
"3:00 pm - 4:00 pm","GLITCH CHRONICLES: TURNING WEBGL INTO A HAMMER","Conf Track 1","Pietro Frigo", \
"3:00 pm - 4:00 pm","NTLM RELAY IS DEAD, LONG LIVE NTLM RELAY","Conf Track 2","Jianing Wang ,Junyu Zhou", \
"4:00 pm - 4:30 pm","AFTERNOON COFFEE BREAK", " ", " ", \
"4:30 pm - 5:30 pm","VOTE OF NO CONFIDENCE: SECOND FACTOR CORRECTNESS","Conf Track 1","Victor Mateu", \
"4:30 pm - 5:30 pm","USING MACHINE-LEARNING TO INVESTIGATE WEB CAMPAIGNS AT LARGE","Conf Track 2","Federico Maggi", \
"5:30 pm - 6:30 pm","CLOSING KEYNOTE: BLIND DIGITAL SIGNATURES (BDS)","Conf Track 1","Dr. Manar Abu Talib ,Dr. Qassim Nasir", \
"6:30 pm - 7:00 pm","CTF PRIZE GIVING + CLOSING CEREMONY + LOCKNOTE","Conf Track 1", " " \
};
static const char *commsec_agenda27[48]= {	\
"10:00 - 10:40","MORNING COFFEE BREAK"," ", \
"10:40 - 10:45","Welcome Comments","Andrea Zapparoli Manzoni", \
"10:45 - 11:15","COMMSEC: Hacking The 0day Market ","Andrea Zapparoli Manzoni (Director, Crowdfense) ", \
"11:15 - 11:45","COMMSEC: Get Rich or Die Trying: Vulnerabilities in Digital Currency Exchanges","Zhang Qing (Security Researcher, Xiaomi) & Dr. Bai Guangdong (Faculty Member, Singapore Institute of Technology)", \
"11:45 - 12:45","COMMSEC: Offensive Memory Forensics– Hugo Teso (Independent Aviation Security Consultant)"," ", \
"12:45 - 14:00","LUNCH BREAK (for paid conference delegates)"," ", \
"14:00 - 14:15","BSIDES: Cyber Security of the Future","Dr. Bushra Al Belooshi (Manager, Research and Innovation, DESC)", \
"14:15 - 14:45","BSIDES: Blockchain: The New Line of Defense","Ramy AlDamati (CyberSecurity & Blockchain Influencer, Kaspersky Lab) ", \
"14:45 - 15:15","COMMSEC: Building Security Beyond the Genesis Block","Ryan Shepherd (Threat Hunter, Countercept)", \
"15:15 - 16:00","BSIDES: Creating Browser Extensions to Hunt for Low-Hanging Fruit","Rewanth Cool (Security Consultant, Payatu Software Labs LLP)", \
"16:00 - 16:30","COFFEE BREAK"," ", \
"16:30 - 17:00","COMMSEC: Hacking Yachts Remotely: IoT Hacking at Sea","Stephan Gerling (Electronics Specalist) ", \
"17:00 - 17:30","COMMSEC: Hacking into Broadband and Broadcast TV Systems","Chaouki Kasmi (Director, MT Lab, DarkMatter), Pierre Barre (Senior Security Researcher, MT Lab, DarkMatter) & Thomas Sabono (Lead Security Researcher, SW Lab, DarkMatter)", \
"17:30 - 18:00","COMMSEC: Taking Over Telecom Networks","Loay Hassan Abdelrazek (Security Researcher, Nile University) & Hardik Mehta (Independent Security Researcher) ", \
"18:00 - 18:30","COMMSEC: System-level Threats: Dangerous Assumptions in Modern Product Security","Cristofaro Mune (Independent Product Security Consultant)", \
"18:30 - ","END OF DAY 1 / NETWORKING BREAK"," " \
};
static const char *commsec_agenda28[48]= {	\
"10:00 - 10:30","MORNING COFFEE BREAK"," ", \
"10:30 - 10:45","BSIDES: Growth Hacking Your Community","Dr. Marwan Al-Zarouni (Director of Information Services, DESC)", \
"10:45 - 11:15","BSIDES: Hunting Threats in Your Enterprise","Abdulrahman Al-Nimari (Lead Cyber Security Architect, Mantech Corp)", \
"11:15 - 11:45","BSIDES: My Experience of Running CTF Competitions in 7 Arab Countries","Moataz Salah (MENA Cybersecurity Workforce Gap) ", \
"11:45 - 12:15","COMMSEC: Evolution of Security Threats to Telecommunications Infrastructures","Emmanuel Gadaix (Founder, TSTF)", \
"12:15 - 12:45","BSIDES: The Perimeter is Dead: Defending Compromised Networks","Hidayatullah Khan (SANS Instructor & Principal Security Consultant, SENTELIST)", \
"12:45 - 13:00","BSIDES: Women in Cyber Security in the Middle East","Heide Young (Co-Founder. Women in Cyber Security Middle East (WCSME))", \
"13:00 - 14:00","LUNCH BREAK (for paid conference delegates)"," ", \
"14:00 - 15:00","COMMSEC: Enhancing Deep Learning DGA Detection Models Using Separate Character Embedding","Vikash Yadav (Data Scientist, Royal Bank of Canada)", \
"15:00 - 15:30","COMMSEC: HWallet: The Simple Cryptocurrency Hardware Wallet","Nemanja Nikodijevic (Hacker / Engineer)", \
"15:30 - 16:00","COMMSEC: A Secured and Robust Wireless Communication System for Low-Latency Applications","Dr. Hussameldin Mukhtar (University of Sharjah)", \
"16:00 - 16:30","COFFEE BREAK"," ", \
"16:30 - 17:00","COMMSEC: Improved Blockchain Infrastructure with IoT for Critical/Smart Government Applications","Dr Qassim Nasir (University of Sharjah) & Dr Manar Abu Talib (University of Sharjah)", \
"17:00 - 17:30","COMMSEC: Hacking the International RFQ Process #killthebuzzwords","Dino Covotsos (Founder, Telspace Systems)", \
"17:30 - ","Closing Comments","Andrea Zapparoli Manzoni", \
"17:35 - ","END OF EVENT / NETWORKING BREAK"," " \
};
static const char *activities[10]= {	\
"Car Hacking Village by CHV Defcon","Capture the Signal by Trend Micro","Capture the Flag","Hack In The Class Village", \
"HITB .edu Capture The Flag Contest","HITB Armory - By ToolsWatch","Internet of Things Village by ISE","SCADA CTF & Village by NSHC", \
"Soldering Village with Mitch Altman","VXRL Hardware Chip Off Village" \
};

static uint8_t n_last = 0;
uint8_t get_key[12] = {0};
uint8_t getkey_flag = 0;
int8_t getkey_rssi = 0;


//屏幕设置
#define _LCDML_DISP_w             	  		LCD_MAX_HEIGHT          // lcd width
#define _LCDML_DISP_h                 		LCD_MAX_WIDTH           // lcd height
//字体设置
#define _LCDML_DISP_font              		1  			   //字号
#define _LCDML_DISP_font_w         		    6             // 字宽
#define _LCDML_DISP_font_h            		(8+4)           // 字高+行间距  

//颜色设置
#define _LCDML_DISP_fcolor              	GREEN  		   //前景色
#define _LCDML_DISP_scolor              	RED  		   //选中色
#define _LCDML_DISP_bgcolor         		BLACK          //背景色
//光标设置
#define _LCDML_DISP_cursor_string   	    ">"           // 光标样式
#define _LCDML_DISP_cursor_len              1              // 光标长度
#define _LCDML_DISP_cur_space_before        4              //光标前空白
#define _LCDML_DISP_cur_space_behind        2              // 光标后空白	
//菜单位置和大小
#define _LCDML_DISP_draw_frame     		   	0              // 菜单内边框宽度（区别于外边框，这是菜单显示区域边框）
#define _LCDML_DISP_box_x0         	 		2              // 显示开始的坐标start point (x0, y0)
#define _LCDML_DISP_box_y0          	    23             // 显示开始的坐标start point (x0, y0)，上面有菜单栏
#define _LCDML_DISP_box_x1         	  	    (125+1)          // 显示结束的坐标width x  (x0 + width)
#define _LCDML_DISP_box_y1            		(113+1)          // 显示结束的坐标hight y  (y0 + height)，下面有状态栏
#define _LCDML_DISP_menu_space            	8              //菜单栏到菜单空白间距


//滚动条宽度
#define _LCDML_DISP_scrollbar_w       		4  // 滚动条宽度（如果宽度小于3，滚动条不显示）    

// nothing change here
#define _LCDML_DISP_cols_max          ((_LCDML_DISP_box_x1-_LCDML_DISP_box_x0-_LCDML_DISP_draw_frame*2-_LCDML_DISP_scrollbar_w)/_LCDML_DISP_font_w) 
#define _LCDML_DISP_rows_max          ((_LCDML_DISP_box_y1-_LCDML_DISP_box_y0-_LCDML_DISP_draw_frame*2-_LCDML_DISP_menu_space-((_LCDML_DISP_box_y1-_LCDML_DISP_box_y0-_LCDML_DISP_draw_frame*2-_LCDML_DISP_menu_space)%_LCDML_DISP_font_h))/_LCDML_DISP_font_h) 

// 行列设置
// when you use more rows or cols as allowed change in LCDMenuLib.h the define "_LCDML_DISP_cfg_max_rows" and "_LCDML_DISP_cfg_max_string_length"
// the program needs more ram with this changes
#define _LCDML_DISP_rows              _LCDML_DISP_rows_max  // max rows 
#define _LCDML_DISP_cols              _LCDML_DISP_cols_max	// max cols

// *********************************************************************
// Prototypes
// *********************************************************************
  void lcdml_menu_display(); 
  void lcdml_menu_clear(); 
  void lcdml_menu_control();   


// *********************************************************************
// Objects
// *********************************************************************
LCDMenuLib2_menu LCDML_0 (255, 0, 0, NULL, NULL); // root menu element (do not change)
LCDMenuLib2 LCDML(LCDML_0, _LCDML_DISP_rows, _LCDML_DISP_cols, lcdml_menu_display, lcdml_menu_clear, lcdml_menu_control);

// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
  // LCDML_0        => layer 0 
  // LCDML_0_X      => layer 1 
  // LCDML_0_X_X    => layer 2 
  // LCDML_0_X_X_X  => layer 3 
  // LCDML_0_...      => layer ... 
//菜单层级
  // For beginners
  // LCDML_add(id, prev_layer, new_num, lang_char_array, callback_function)  
  //id，层级，编号，名称，回调函数

LCDML_add ( 0  , LCDML_0           , 1  , "01. Conference    ", NULL);
LCDML_add ( 1  , LCDML_0           , 2  , "02. Commsec Track ", NULL);
LCDML_add ( 2  , LCDML_0           , 3  , "03. Activities    ", NULL);
LCDML_add ( 3  , LCDML_0           , 4  , "04. Secret Menu   ", mFunc_secret);
LCDML_add ( 4  , LCDML_0           , 5  , "05. Game          ", mFunc_game);
LCDML_add ( 5  , LCDML_0           , 6  , "06. TFT Light     ", mFunc_lcd_setlight);
LCDML_add ( 6  , LCDML_0           , 7  , "07. About         ", NULL);
LCDML_add ( 7  , LCDML_0_7         , 1  , "01. WhiteA10n3    ", mFunc_about);
LCDML_add ( 8  , LCDML_0_7         , 2  , "02. xwings        ", mFunc_about);
LCDML_add ( 9  , LCDML_0_7         , 3  , "03. KLKS          ", mFunc_about);
LCDML_add ( 10 , LCDML_0_7         , 4  , "04. HACKERSBADGE  ", NULL);
LCDML_add ( 11 , LCDML_0_7         , 5  , "05. HACKNOWN      ", NULL);
LCDML_add ( 12 , LCDML_0_7         , 6  , "06. SHEPHERDLAB   ", NULL);
LCDML_add ( 13 , LCDML_0_1         , 1  , "01. 27th November ", NULL);
LCDML_add ( 14 , LCDML_0_1         , 2  , "02. 28th November ", NULL);
LCDML_add ( 15 , LCDML_0_2         , 1  , "01. 27th November ", NULL);
LCDML_add ( 16 , LCDML_0_2         , 2  , "02. 28th November ", NULL);

LCDML_add ( 17 , LCDML_0_1_1       , 1  , "9:15 am-10:00 am ", mFunc_confagenda27);
LCDML_add ( 18 , LCDML_0_1_1       , 2  , "10:00 am-10:45 am", mFunc_confagenda27);
LCDML_add ( 19 , LCDML_0_1_1       , 3  , "10:45 am-11:45 am", mFunc_confagenda27);
LCDML_add ( 20 , LCDML_0_1_1       , 4  , "10:45 am-11:45 am", mFunc_confagenda27);
LCDML_add ( 21 , LCDML_0_1_1       , 5  , "11:45 am-12:45 pm", mFunc_confagenda27);
LCDML_add ( 22 , LCDML_0_1_1       , 6  , "11:45 am-12:45 pm", mFunc_confagenda27);
LCDML_add ( 23 , LCDML_0_1_1       , 7  , "12:45 pm-2:00 pm ", mFunc_confagenda27);
LCDML_add ( 24 , LCDML_0_1_1       , 8  , "2:00 pm-3:00 pm  ", mFunc_confagenda27);
LCDML_add ( 25 , LCDML_0_1_1       , 9  , "2:00 pm-3:00 pm  ", mFunc_confagenda27);
LCDML_add ( 26 , LCDML_0_1_1       , 10 , "3:00 pm-4:00 pm  ", mFunc_confagenda27);
LCDML_add ( 27 , LCDML_0_1_1       , 11 , "3:00 pm-4:00 pm  ", mFunc_confagenda27);
LCDML_add ( 28 , LCDML_0_1_1       , 12 , "4:00 pm-4:30 pm  ", mFunc_confagenda27);
LCDML_add ( 29 , LCDML_0_1_1       , 13 , "4:30 pm-5:30 pm  ", mFunc_confagenda27);
LCDML_add ( 30 , LCDML_0_1_1       , 14 , "4:30 pm-5:30 pm  ", mFunc_confagenda27);
LCDML_add ( 31 , LCDML_0_1_1       , 15 , "5:30 pm-6:30 pm  ", mFunc_confagenda27);
LCDML_add ( 32 , LCDML_0_1_1       , 16 , "5:30 pm-6:30 pm  ", mFunc_confagenda27);


LCDML_add ( 33 , LCDML_0_1_2       , 1  , "9:00 am-9:15 am  ", mFunc_confagenda28);
LCDML_add ( 34 , LCDML_0_1_2       , 2  , "9:15 am-10:00 am ", mFunc_confagenda28);
LCDML_add ( 35 , LCDML_0_1_2       , 3  , "10:00 am-10:45 am", mFunc_confagenda28);
LCDML_add ( 36 , LCDML_0_1_2       , 4  , "10:45 am-11:45 am", mFunc_confagenda28);
LCDML_add ( 37 , LCDML_0_1_2       , 5  , "10:45 am-11:45 am", mFunc_confagenda28);
LCDML_add ( 38 , LCDML_0_1_2       , 6  , "11:45 am-12:45 pm", mFunc_confagenda28);
LCDML_add ( 39 , LCDML_0_1_2       , 7  , "11:45 am-12:45 pm", mFunc_confagenda28);
LCDML_add ( 40 , LCDML_0_1_2       , 8  , "12:45 pm-2:00 pm ", mFunc_confagenda28);
LCDML_add ( 41 , LCDML_0_1_2       , 9  , "2:00 pm-3:00 pm  ", mFunc_confagenda28);
LCDML_add ( 42 , LCDML_0_1_2       , 10 , "2:00 pm-3:00 pm  ", mFunc_confagenda28);
LCDML_add ( 43 , LCDML_0_1_2       , 11 , "3:00 pm-4:00 pm  ", mFunc_confagenda28);
LCDML_add ( 44 , LCDML_0_1_2       , 12 , "3:00 pm-4:00 pm  ", mFunc_confagenda28);
LCDML_add ( 45 , LCDML_0_1_2       , 13 , "4:00 pm-4:30 pm  ", mFunc_confagenda28);
LCDML_add ( 46 , LCDML_0_1_2       , 14 , "4:30 pm-5:30 pm  ", mFunc_confagenda28);
LCDML_add ( 47 , LCDML_0_1_2       , 15 , "4:30 pm-5:30 pm  ", mFunc_confagenda28);
LCDML_add ( 48 , LCDML_0_1_2       , 16 , "5:30 pm-6:30 pm  ", mFunc_confagenda28);
LCDML_add ( 49 , LCDML_0_1_2       , 17 , "6:30 pm-7:00 pm  ", mFunc_confagenda28);

LCDML_add ( 50 , LCDML_0_2_1       , 1  , "10:00 - 10:40    ", mFunc_commsecagenda27);
LCDML_add ( 51 , LCDML_0_2_1       , 2  , "10:40 - 10:45    ", mFunc_commsecagenda27);
LCDML_add ( 52 , LCDML_0_2_1       , 3  , "10:45 - 11:15    ", mFunc_commsecagenda27);
LCDML_add ( 53 , LCDML_0_2_1       , 4  , "11:15 - 11:45    ", mFunc_commsecagenda27);
LCDML_add ( 54 , LCDML_0_2_1       , 5  , "11:45 - 12:45    ", mFunc_commsecagenda27);
LCDML_add ( 55 , LCDML_0_2_1       , 6  , "12:45 - 14:00    ", mFunc_commsecagenda27);
LCDML_add ( 56 , LCDML_0_2_1       , 7  , "14:00 - 14:15    ", mFunc_commsecagenda27);
LCDML_add ( 57 , LCDML_0_2_1       , 8  , "14:15 - 14:45    ", mFunc_commsecagenda27);
LCDML_add ( 58 , LCDML_0_2_1       , 9  , "14:45 - 15:15    ", mFunc_commsecagenda27);
LCDML_add ( 59 , LCDML_0_2_1       , 10 , "15:15 - 16:00    ", mFunc_commsecagenda27);
LCDML_add ( 60 , LCDML_0_2_1       , 11 , "16:00 - 16:30    ", mFunc_commsecagenda27);
LCDML_add ( 61 , LCDML_0_2_1       , 12 , "16:30 - 17:00    ", mFunc_commsecagenda27);
LCDML_add ( 62 , LCDML_0_2_1       , 13 , "17:00 - 17:30    ", mFunc_commsecagenda27);
LCDML_add ( 63 , LCDML_0_2_1       , 14 , "17:30 - 18:00    ", mFunc_commsecagenda27);
LCDML_add ( 64 , LCDML_0_2_1       , 15 , "18:00 - 18:30    ", mFunc_commsecagenda27);
LCDML_add ( 65 , LCDML_0_2_1       , 16 , "18:30 -          ", mFunc_commsecagenda27);
                                                           
LCDML_add ( 66 , LCDML_0_2_2       , 1  , "10:00 - 10:30    ", mFunc_commsecagenda28);
LCDML_add ( 67 , LCDML_0_2_2       , 2  , "10:30 - 10:45    ", mFunc_commsecagenda28);
LCDML_add ( 68 , LCDML_0_2_2       , 3  , "10:45 - 11:15    ", mFunc_commsecagenda28);
LCDML_add ( 69 , LCDML_0_2_2       , 4  , "11:15 - 11:45    ", mFunc_commsecagenda28);
LCDML_add ( 70 , LCDML_0_2_2       , 5  , "11:45 - 12:15    ", mFunc_commsecagenda28);
LCDML_add ( 71 , LCDML_0_2_2       , 6  , "12:15 - 12:45    ", mFunc_commsecagenda28);
LCDML_add ( 72 , LCDML_0_2_2       , 7  , "12:45 - 13:00    ", mFunc_commsecagenda28);
LCDML_add ( 73 , LCDML_0_2_2       , 8  , "13:00 - 14:00    ", mFunc_commsecagenda28);
LCDML_add ( 74 , LCDML_0_2_2       , 9  , "14:00 - 15:00    ", mFunc_commsecagenda28);
LCDML_add ( 75 , LCDML_0_2_2       , 10 , "15:00 - 15:30    ", mFunc_commsecagenda28);
LCDML_add ( 76 , LCDML_0_2_2       , 11 , "15:30 - 16:00    ", mFunc_commsecagenda28);
LCDML_add ( 77 , LCDML_0_2_2       , 12 , "16:00 - 16:30    ", mFunc_commsecagenda28);
LCDML_add ( 78 , LCDML_0_2_2       , 13 , "16:30 - 17:00    ", mFunc_commsecagenda28);
LCDML_add ( 79 , LCDML_0_2_2       , 14 , "17:00 - 17:30    ", mFunc_commsecagenda28);
LCDML_add ( 80 , LCDML_0_2_2       , 15 , "17:30 -          ", mFunc_commsecagenda28);
LCDML_add ( 81 , LCDML_0_2_2       , 16 , "17:35 -          ", mFunc_commsecagenda28);


LCDML_add ( 82 , LCDML_0_3         , 1  , "Higlight 1       ", mFunc_activities);
LCDML_add ( 83 , LCDML_0_3         , 2  , "Higlight 2       ", mFunc_activities);
LCDML_add ( 84 , LCDML_0_3         , 3  , "Higlight 3       ", mFunc_activities);
LCDML_add ( 85 , LCDML_0_3         , 4  , "Higlight 4       ", mFunc_activities);
LCDML_add ( 86 , LCDML_0_3         , 5  , "Higlight 5       ", mFunc_activities);
LCDML_add ( 87 , LCDML_0_3         , 6  , "Higlight 6       ", mFunc_activities);
LCDML_add ( 88 , LCDML_0_3         , 7  , "Higlight 7       ", mFunc_activities);
LCDML_add ( 89 , LCDML_0_3         , 8  , "Higlight 8       ", mFunc_activities);
LCDML_add ( 90 , LCDML_0_3         , 9  , "Higlight 9       ", mFunc_activities);
LCDML_add ( 91 , LCDML_0_3         , 10 , "Higlight 10      ", mFunc_activities);

#if DXB_Supreme == 1
LCDML_add ( 92  , LCDML_0           , 8 , "08. Badge Control", NULL);
LCDML_add ( 93  , LCDML_0_8         , 1 , "00. OFF          ", mFunc_ledcontrol);
LCDML_add ( 94  , LCDML_0_8         , 2 , "01. RED          ", mFunc_ledcontrol);
LCDML_add ( 95  , LCDML_0_8         , 3 , "02. GREEN        ", mFunc_ledcontrol);
LCDML_add ( 96  , LCDML_0_8         , 4 , "03. BLUE         ", mFunc_ledcontrol);
LCDML_add ( 97  , LCDML_0_8         , 5 , "04. Rrainbow     ", mFunc_ledcontrol);
LCDML_add ( 98  , LCDML_0_8         , 6 , "05. RainbowCycle ", mFunc_ledcontrol);
LCDML_add ( 99  , LCDML_0_8         , 7 , "06. ChaseRainbow ", mFunc_ledcontrol);
LCDML_add ( 100 , LCDML_0_8         , 8 , "07. OFF          ", mFunc_ledcontrol);

#endif
/*
// Advanced menu (for profit) part with more settings
// Example for one function and different parameters
// It is recommend to use parameters for switching settings like, (small drink, medium drink, big drink) or (200ml, 400ml, 600ml, 800ml) ...
// the parameter change can also be released with dynParams on the next example
//高级菜单设置，选项更多
//例子是一个函数不同参数的示例
//建议用参数来切换设置，比如（小号饮料、中号饮料、大号饮料）或者（200ml, 400ml, 600ml, 800ml）
//再后面的一个示例中，也可以使用dynParams返回值更改设置
// LCDMenuLib_add(id, prev_layer,	  new_num, condition,	lang_char_array, callback_function, parameter (0-255), menu function type  )
//id，层级，编号，条件，名称，回调函数，参数，菜单函数类型
LCDML_addAdvanced (16 , LCDML_0 		, 5  , NULL,		  "Parameter"	   , NULL,				  0,			_LCDML_TYPE_default);					 // NULL = no menu function
LCDML_addAdvanced (17 , LCDML_0_5		, 1  , NULL,		  "Parameter 1" 	 , mFunc_para,		 10,			_LCDML_TYPE_default);					 // NULL = no menu function
LCDML_addAdvanced (18 , LCDML_0_5		, 2  , NULL,		  "Parameter 2" 	 , mFunc_para,		 20,			_LCDML_TYPE_default);					 // NULL = no menu function
LCDML_addAdvanced (19 , LCDML_0_5		, 3  , NULL,		  "Parameter 3" 	 , mFunc_para,		 30,			_LCDML_TYPE_default);					 // NULL = no menu function
LCDML_add		  (20 , LCDML_0_5		, 4  , "Back"			  , mFunc_back);			  // this menu function can be found on "LCDML_display_menuFunction" tab


// Example for dynamic content
// 1. set the string to ""
// 2. use type	_LCDML_TYPE_dynParam   instead of	 _LCDML_TYPE_default
// this function type can not be used in combination with different parameters
//动态内容示例
//1. 字符串要加""
//2. 使用_LCDML_TYPE_dynParam类型替代_LCDML_TYPE_default
// LCDMenuLib_add(id, prev_layer,	  new_num, condition,	lang_char_array, callback_function, parameter (0-255), menu function type  )
LCDML_addAdvanced (21 , LCDML_0 		, 6  , NULL,		  ""				  , mDyn_para,				  0,   _LCDML_TYPE_dynParam);					  // NULL = no menu function

//
// Example for conditions (for example for a screensaver)
// 1. define a condition as a function of a boolean type -> return false = not displayed, return true = displayed
// 2. set the function name as callback (remove the braces '()' it gives bad errors)
//条件示例（例子是屏保）
//1. 定义一个条件，比如bool返回值的函数，返回false不显示，返回true显示
//2. 设置函数名为回调函数（记得去掉'()'，否则会报错）
// LCDMenuLib_add(id, prev_layer,	  new_num, condition,	lang_char_array, callback_function, parameter (0-255), menu function type  )
LCDML_addAdvanced (22 , LCDML_0 		, 7  , COND_hide,  "screensaver"		, mFunc_screensaver,		0,	 _LCDML_TYPE_default);		 // this menu function can be found on "LCDML_display_menuFunction" tab

*/

// ***TIP*** Try to update _LCDML_DISP_cnt when you add a menu element.
//提示：如果添加了菜单选项，请更改_LCDML_DISP_cnt数值


// menu element count - last element id
// this value must be the same as the last menu element

#if DXB_Attendee == 1
#define _LCDML_DISP_cnt    91
#endif

#if DXB_Supreme == 1
#define _LCDML_DISP_cnt    100
#endif


// create menu
LCDML_createMenu(_LCDML_DISP_cnt);


//// LCDMenuLib Setup
//LCDML_setup(_LCDML_DISP_cnt);

void lcdml_menu_control(void)
{
	uint8_t keysta;
	
	// If something must init, put in in the setup condition
	if(LCDML.BT_setup()) {
	  // runs only once
	}

	keysta = bsp_GetKey();
	if (keysta == KEY_DOWN_OK) { LCDML.BT_enter(); }
	else if (keysta == KEY_DOWN_U) { LCDML.BT_up();    }
	else if (keysta == KEY_DOWN_D) { LCDML.BT_down();  }
	else if (keysta == KEY_DOWN_ESC) { LCDML.BT_quit();  }
	else if (keysta == KEY_DOWN_L) { LCDML.BT_left();  }
	else if (keysta == KEY_DOWN_R) { LCDML.BT_right(); }        
}

// =====================================================================
//
// Output function
//
// =====================================================================

/* ******************************************************************** */
void lcdml_menu_clear()
/* ******************************************************************** */
{

}

/* ******************************************************************** */
void lcdml_menu_display()
/* ******************************************************************** */
{
  //设置字体和颜色
  bsp_setTextSize(_LCDML_DISP_font);
  bsp_setTextColor2(_LCDML_DISP_fcolor, _LCDML_DISP_bgcolor);

  // decalration of some variables
  // ***************    
  // content variable
  char content_text[_LCDML_DISP_cols];  // save the content text of every menu element 
  // menu element object
  LCDMenuLib2_menu *tmp;    
  // some limit values
  uint8_t i = LCDML.MENU_getScroll();
  uint8_t maxi = _LCDML_DISP_rows + i;
  uint8_t n = 0;  

   // init vars
  uint8_t n_max             = (LCDML.MENU_getChilds() >= _LCDML_DISP_rows) ? _LCDML_DISP_rows : (LCDML.MENU_getChilds());
 
  //uint8_t scrollbar_min     = 0;
  uint8_t scrollbar_max     = LCDML.MENU_getChilds();
  uint8_t scrollbar_cur_pos = LCDML.MENU_getCursorPosAbs();
//  uint8_t scroll_pos        = ((1.*n_max * _LCDML_DISP_rows) / (scrollbar_max - 1) * scrollbar_cur_pos); 
	 // generate content
  //do {

    n = 0;
    i = LCDML.MENU_getScroll();	
    // update content
    // ***************
      // clear menu
      // ***************      
	if ( n_last != n_max )
	{
		n_last = n_max;
		bsp_fillRect(_LCDML_DISP_box_x1 - _LCDML_DISP_scrollbar_w-_LCDML_DISP_draw_frame, _LCDML_DISP_box_y0+_LCDML_DISP_draw_frame, \
								_LCDML_DISP_scrollbar_w, _LCDML_DISP_box_y1-_LCDML_DISP_box_y0-_LCDML_DISP_draw_frame*2, _LCDML_DISP_bgcolor);    //清除滚动条
	    bsp_fillRect2(_LCDML_DISP_box_x0 + _LCDML_DISP_cur_space_before, \
						_LCDML_DISP_box_y0 + _LCDML_DISP_menu_space + _LCDML_DISP_font_h*n_max, \
						_LCDML_DISP_box_x1-1, _LCDML_DISP_box_y1-1, _LCDML_DISP_bgcolor);       //清菜单显示多余的行，避免刷新全部，减少刷新时间
	}
	
  //画菜单边框
  if(_LCDML_DISP_draw_frame > 0) 
  {
	  int8_t i;
	  for ( i = 0 ; i < _LCDML_DISP_draw_frame; i++ )
	  {
		  bsp_drawRect(_LCDML_DISP_box_x0+i, _LCDML_DISP_box_y0+i, \
					  	(_LCDML_DISP_box_x1-_LCDML_DISP_box_x0)-2*i, \
					  	(_LCDML_DISP_box_y1-_LCDML_DISP_box_y0)-2*i, _LCDML_DISP_fcolor);
	  }
  }

    // check if this element has children
  tmp = LCDML.MENU_getObj()->getChild(LCDML.MENU_getScroll());
    if (tmp) 
    {
      // loop to display lines       
      //逐行显示菜单
      do
      {            
        // check if a menu element has a condetion and if the condetion be true               
        if (tmp->checkCondition()) 
        {          
          // check the type off a menu element
          if(tmp->checkType_menu() == true)
          {          
            // display normal content
            LCDML_getContent(content_text, tmp->getID());
			if ( LCDML.MENU_getCursorPos() == n )
			{
				bsp_drawColorText(_LCDML_DISP_box_x0+_LCDML_DISP_cur_space_before+_LCDML_DISP_draw_frame, \
									_LCDML_DISP_box_y0 + _LCDML_DISP_font_h * n+_LCDML_DISP_menu_space+_LCDML_DISP_draw_frame, \
									_LCDML_DISP_cursor_string, _LCDML_DISP_scolor, _LCDML_DISP_bgcolor);    //显示光标
			    bsp_drawColorText(_LCDML_DISP_box_x0+_LCDML_DISP_cur_space_before+_LCDML_DISP_font_w*_LCDML_DISP_cursor_len + _LCDML_DISP_cur_space_behind+_LCDML_DISP_draw_frame,   \
									_LCDML_DISP_box_y0 + _LCDML_DISP_font_h * n+_LCDML_DISP_menu_space+_LCDML_DISP_draw_frame, \
									content_text, _LCDML_DISP_scolor, _LCDML_DISP_bgcolor);    //显示选中菜单内容
									
			    //显示滚动条，只有当行数大于2才会显示
			    if (scrollbar_max > n_max && _LCDML_DISP_scrollbar_w > 2) 
			    {
			    	bsp_fillRect(_LCDML_DISP_box_x1 - _LCDML_DISP_scrollbar_w-_LCDML_DISP_draw_frame+1, _LCDML_DISP_box_y0+_LCDML_DISP_draw_frame, \
								_LCDML_DISP_scrollbar_w-1, _LCDML_DISP_box_y1-_LCDML_DISP_box_y0-_LCDML_DISP_draw_frame*2, _LCDML_DISP_bgcolor);    //清除滚动条
			      // set frame for scrollbar
			      bsp_drawFastVLine(_LCDML_DISP_box_x1 - _LCDML_DISP_scrollbar_w-_LCDML_DISP_draw_frame, _LCDML_DISP_box_y0+_LCDML_DISP_draw_frame, \
				  				_LCDML_DISP_box_y1-_LCDML_DISP_box_y0-_LCDML_DISP_draw_frame*2, _LCDML_DISP_fcolor);    //显示滚动条框线
			      // calculate scrollbar length
			      uint8_t scrollbar_block_length = scrollbar_max - n_max;
			      scrollbar_block_length = (_LCDML_DISP_box_y1-_LCDML_DISP_box_y0-_LCDML_DISP_draw_frame*2) / (scrollbar_block_length + _LCDML_DISP_rows);

			      //set scrollbar
				if (scrollbar_cur_pos == 0) 
				{                                   // top position     (min)
					bsp_fillRect(_LCDML_DISP_box_x1 - (_LCDML_DISP_scrollbar_w-1)-_LCDML_DISP_draw_frame, _LCDML_DISP_box_y0+_LCDML_DISP_draw_frame, \
								(_LCDML_DISP_scrollbar_w-1), scrollbar_block_length, _LCDML_DISP_fcolor);
				} 
				else if (scrollbar_cur_pos == (scrollbar_max-1)) 
				{            // bottom position  (max)         
					bsp_fillRect(_LCDML_DISP_box_x1 - (_LCDML_DISP_scrollbar_w-1)-_LCDML_DISP_draw_frame, _LCDML_DISP_box_y1 - scrollbar_block_length-_LCDML_DISP_draw_frame, \
								(_LCDML_DISP_scrollbar_w-1), scrollbar_block_length, _LCDML_DISP_fcolor);
				} 
				else 
				{                                                                // between top and bottom
					bsp_fillRect(_LCDML_DISP_box_x1 - (_LCDML_DISP_scrollbar_w-1)-_LCDML_DISP_draw_frame, \
								_LCDML_DISP_box_y0 + (scrollbar_block_length * scrollbar_cur_pos + 1)+_LCDML_DISP_draw_frame, \
								(_LCDML_DISP_scrollbar_w-1), scrollbar_block_length, _LCDML_DISP_fcolor);
				}       
    }
			}
			else
			{
				bsp_drawColorText(_LCDML_DISP_box_x0+_LCDML_DISP_cur_space_before+_LCDML_DISP_draw_frame, \
								_LCDML_DISP_box_y0 + _LCDML_DISP_font_h * n +_LCDML_DISP_menu_space+_LCDML_DISP_draw_frame, \
								_LCDML_DISP_cursor_string, _LCDML_DISP_bgcolor, _LCDML_DISP_bgcolor);    //清除光标
			    bsp_drawColorText(_LCDML_DISP_box_x0+_LCDML_DISP_cur_space_before+_LCDML_DISP_font_w*_LCDML_DISP_cursor_len + _LCDML_DISP_cur_space_behind+_LCDML_DISP_draw_frame, \
				    			_LCDML_DISP_box_y0 + _LCDML_DISP_font_h * n + _LCDML_DISP_menu_space+_LCDML_DISP_draw_frame, \
				    			content_text, _LCDML_DISP_fcolor, _LCDML_DISP_bgcolor);//正显菜单内容
			}
	
          }            
          else 
          { 
            if(tmp->checkType_dynParam()) {                      
              tmp->callback(n);
            }                 
          }
          // increment some values 
          i++; 
          n++;     
        } 
      // try to go to the next sibling and check the number of displayed rows           
      } while (((tmp = tmp->getSibling(1)) != NULL) && (i < maxi));
    }
}

void Menu_DrawFrame(void)
{
	uint32_t CPU_Sn0;

	//bsp_lcd_rotate(RLOOK);
	bsp_fillScreen(BLACK);	
	//画框
	bsp_drawRect(0, 0, 128, 128, GREEN);
	bsp_drawRect(1, 1, 126, 126, GREEN);
	//LCD_DrawLine(0, 13, 315, 13, RED);
	bsp_drawFastHLine(0, 114, 126, GREEN);

	bsp_setTextSize(1);
	bsp_setTextColor(GREEN);
	bsp_drawText(2, 8, "    HITB 2018 DXB  ");	//一行最多39个字符
	bsp_drawFastHLine(0, 22, 126, GREEN);

	//bsp_setTextSize(1);
	////display_string_ascii(4, 4, "ID:000000",1, RED, WHITE);           // ID显示 
	bsp_drawText(4, 4+113, "ID:");           // ID显示 
	//
	CPU_Sn0 = *(__IO uint32_t*)(0x1ffff7e8);
	//display_num_format(22, 4, CPU_Sn0, 1, "%06X", RED, WHITE);	//长度9*6
	bsp_drawNum_Format(22, 4+113, CPU_Sn0, "%08X");	//长度9*6

	////display_string_ascii(264, 4, " --.--Ca", 1, RED, WHITE);//长度8*6
	//bsp_drawText(264, 4+225, " --.--Ca");//长度8*6
	//display_rtc_time(RTC_EX, 100, 4, 1, RED, WHITE);//长度19*6
	//display_rtc_time(RTC_EX, 100, 4+225, 1, RED, WHITE);//长度19*6

}

extern int8_t Heartbeat_RSSI;
extern uint8_t Heartbeat_flag;
extern uint8_t snake_flag;


void Menu_UpdateFrame(void)
{
	//int16_t temp = 0;

	//display_rtc_time(RTC_EX, 100, 4+225, 1, RED, WHITE);
	//temp = DS18B20_ReadTemp();
	//
	//if ( temp<0 )
	//{
	//	display_char_ascii(264, 4+225, '-', 1, RED, WHITE); 	//显示负号
	//	temp = -temp;	//转为正数
	//}
	//else
	//{
	//	display_char_ascii(264, 4+225, ' ', 1, RED, WHITE); 	//去掉负号
	//}
	//display_num_format(270, 4+225, temp/100 , 1, "%2d", RED, WHITE);
	//display_num_format(288, 4+225, temp%100 , 1, "%02d", RED, WHITE);
	if ( Heartbeat_flag )
	{
		if ( snake_flag == 0 )
		{
		    bsp_setTextSize(1);
			bsp_setTextColor2(GREEN,BLACK);
			bsp_lcd_setCursor(88, 4+113);
			bsp_lcd_printf("%4ddB", Heartbeat_RSSI);
		}
	}
}


void Menu_Init(void)
{
	Menu_DrawFrame();
    // LCDMenuLib Setup
    LCDML_setup(_LCDML_DISP_cnt);

    // Enable Menu Rollover
    LCDML.MENU_enRollover();
}

void Menu_Loop(void)
{
	// this function must called here, do not delete it
	LCDML.loop();
}

/* ===================================================================== *
 *                                                                       *
 * Conditions to show or hide a menu element on the display              *
 *                                                                       *
 * ===================================================================== *
 */

//示例中bool返回函数
//// *********************************************************************
//boolean COND_hide()  // hide a menu element
//// ********************************************************************* 
//{ 
//  return false;  // hidden
//} 

/* ===================================================================== *
 *                                                                       *
 * Dynamic content                                                       *
 *                                                                       *
 * ===================================================================== *
 */


//uint8_t g_dynParam = 100; // when this value comes from an EEPROM, load it in setup
//                          // at the moment here is no setup function (To-Do)
//void mDyn_para(uint8_t line)
//// *********************************************************************
//{
//  // check if this function is active (cursor stands on this line)
//  if (line == LCDML.MENU_getCursorPos())
//  {
//    // make only an action when the cursor stands on this menu item
//    //check Button
//    if(LCDML.BT_checkAny())
//    {
//      if(LCDML.BT_checkEnter())
//      {
//        // this function checks returns the scroll disable status (0 = menu scrolling enabled, 1 = menu scrolling disabled)
//        if(LCDML.MENU_getScrollDisableStatus() == 0)
//        {
//          // disable the menu scroll function to catch the cursor on this point
//          // now it is possible to work with BT_checkUp and BT_checkDown in this function
//          // this function can only be called in a menu, not in a menu function
//          LCDML.MENU_disScroll();
//        }
//        else
//        {
//          // enable the normal menu scroll function
//          LCDML.MENU_enScroll();
//        }

//        // do something
//        // ...
//        
//        LCDML.BT_resetEnter();
//      }

//      // This check have only an effect when MENU_disScroll is set
//      if(LCDML.BT_checkUp())
//      {
//        g_dynParam++;
//        LCDML.BT_resetUp();
//      }

//      // This check have only an effect when MENU_disScroll is set
//      if(LCDML.BT_checkDown())
//      {
//        g_dynParam--;
//        LCDML.BT_resetDown();
//      }


//      if(LCDML.BT_checkLeft())
//      {
//        g_dynParam++;
//        LCDML.BT_resetLeft();
//      }
//      
//      if(LCDML.BT_checkRight())
//      {
//        g_dynParam--;
//        LCDML.BT_resetRight();
//      }
//    }
//  }

//  char buf[20];
//  sprintf (buf, "dynValue: %d", g_dynParam);

//  // setup function
//  bsp_drawText( _LCDML_DISP_box_x0+_LCDML_DISP_font_w + _LCDML_DISP_cur_space_behind,  (_LCDML_DISP_font_h * (1+line)), buf);     // the value can be changed with left or right
//}

/* ===================================================================== *
 *                                                                       *
 * Menu Callback Function                                                *
 *                                                                       *
 * ===================================================================== *
 *
 * EXAMPLE CODE:

// *********************************************************************
void your_function_name(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // setup
    // is called only if it is started

    // starts a trigger event for the loop function every 100 milliseconds
    LCDML.FUNC_setLoopInterval(100);
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
    // loop
    // is called when it is triggered
    // - with LCDML_DISP_triggerMenu( milliseconds )
    // - with every button status change

    // check if any button is pressed (enter, up, down, left, right)
    if(LCDML.BT_checkAny()) {
      LCDML.FUNC_goBackToMenu();
    }
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    // loop end
    // you can here reset some global vars or delete it
  }
}


// * ===================================================================== *
// */

//// *********************************************************************
//void mFunc_information(uint8_t param)
//// *********************************************************************
//{
//  if(LCDML.FUNC_setup())          // ****** SETUP *********
//  {
//    // setup function
//    u8g2.setFont(_LCDML_DISP_font);
//    u8g2.firstPage();
//    do {
//      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), "To close this");
//      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), "function press");
//      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 3), "any button or use");
//      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 4), "back button");
//    } while( u8g2.nextPage() );
//  }

//  if(LCDML.FUNC_loop())           // ****** LOOP *********
//  {
//    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
//    // the quit button works in every DISP function without any checks; it starts the loop_end function
//    if(LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
//    {
//      // LCDML_goToMenu stops a running menu function and goes to the menu
//      LCDML.FUNC_goBackToMenu();
//    }
//  }

//  if(LCDML.FUNC_close())      // ****** STABLE END *********
//  {
//    // you can here reset some global vars or do nothing
//  }
//}


//// *********************************************************************
//uint8_t g_func_timer_info = 0;  // time counter (global variable)
//unsigned long g_timer_1 = 0;    // timer variable (global variable)
//void mFunc_timer_info(uint8_t param)
//// *********************************************************************
//{
//  if(LCDML.FUNC_setup())          // ****** SETUP *********
//  {
//     g_func_timer_info = 20;       // reset and set timer

//    char buf[20];
//    sprintf (buf, "wait %d seconds", g_func_timer_info);

//    u8g2.setFont(_LCDML_DISP_font);
//    u8g2.firstPage();
//    do {
//      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), buf);
//      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), "or press back button");
//    } while( u8g2.nextPage() );



//    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds

//    LCDML.TIMER_msReset(g_timer_1);
//  }

//  if(LCDML.FUNC_loop())           // ****** LOOP *********
//  {
//    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
//    // the quit button works in every DISP function without any checks; it starts the loop_end function

//    // reset screensaver timer
//    LCDML.SCREEN_resetTimer();

//     // this function is called every 100 milliseconds

//    // this method checks every 1000 milliseconds if it is called
//    if(LCDML.TIMER_ms(g_timer_1, 1000))
//    {
//      g_timer_1 = millis();
//      g_func_timer_info--;                // increment the value every second
//      char buf[20];
//      sprintf (buf, "wait %d seconds", g_func_timer_info);

//      u8g2.setFont(_LCDML_DISP_font);
//      u8g2.firstPage();
//      do {
//        u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), buf);
//        u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), "or press back button");
//      } while( u8g2.nextPage() );

//    }

//    // this function can only be ended when quit button is pressed or the time is over
//    // check if the function ends normally
//    if (g_func_timer_info <= 0)
//    {
//      // leave this function
//      LCDML.FUNC_goBackToMenu();
//    }
//  }

//  if(LCDML.FUNC_close())      // ****** STABLE END *********
//  {
//    // you can here reset some global vars or do nothing
//  }
//}

//// *********************************************************************
//uint8_t g_button_value = 0; // button value counter (global variable)
//void mFunc_p2(uint8_t param)
//// *********************************************************************
//{
//  if(LCDML.FUNC_setup())          // ****** SETUP *********
//  {
//    // setup function
//    // print LCD content
//    char buf[17];
//    sprintf (buf, "count: %d of 3", 0);

//    u8g2.setFont(_LCDML_DISP_font);
//    u8g2.firstPage();
//    do {
//      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), "press a or w button");
//      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), buf);
//    } while( u8g2.nextPage() );

//    // Reset Button Value
//    g_button_value = 0;

//    // Disable the screensaver for this function until it is closed
//    LCDML.FUNC_disableScreensaver();
//  }

//  if(LCDML.FUNC_loop())           // ****** LOOP *********
//  {
//    // loop function, can be run in a loop when LCDML_DISP_triggerMenu(xx) is set
//    // the quit button works in every DISP function without any checks; it starts the loop_end function

//    // the quit button works in every DISP function without any checks; it starts the loop_end function
//    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
//    {
//      if (LCDML.BT_checkLeft() || LCDML.BT_checkUp()) // check if button left is pressed
//      {
//        LCDML.BT_resetLeft(); // reset the left button
//        LCDML.BT_resetUp(); // reset the left button
//        g_button_value++;

//        // update LCD content
//        char buf[20];
//        sprintf (buf, "count: %d of 3", g_button_value);

//        u8g2.setFont(_LCDML_DISP_font);
//        u8g2.firstPage();
//        do {
//          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), "press a or w button");
//          u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), buf);
//        } while( u8g2.nextPage() );
//      }
//    }

//   // check if button count is three
//    if (g_button_value >= 3) {
//      LCDML.FUNC_goBackToMenu();      // leave this function
//    }
//  }

//  if(LCDML.FUNC_close())     // ****** STABLE END *********
//  {
//    // you can here reset some global vars or do nothing
//  }
//}


//// *********************************************************************
//void mFunc_screensaver(uint8_t param)
//// *********************************************************************
//{
//  if(LCDML.FUNC_setup())          // ****** SETUP *********
//  {
//    // setup function
//    u8g2.setFont(_LCDML_DISP_font);
//    u8g2.firstPage();
//    do {
//      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), "screensaver");
//      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), "press any key");
//      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 3), "to leave it");
//    } while( u8g2.nextPage() );

//    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds
//  }

//  if(LCDML.FUNC_loop())           // ****** LOOP *********
//  {
//    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
//    {
//      LCDML.FUNC_goBackToMenu();  // leave this function
//    }
//  }

//  if(LCDML.FUNC_close())          // ****** STABLE END *********
//  {
//    // The screensaver go to the root menu
//    LCDML.MENU_goRoot();
//  }
//}



//// *********************************************************************
//void mFunc_back(uint8_t param)
//// *********************************************************************
//{
//  if(LCDML.FUNC_setup())          // ****** SETUP *********
//  {
//    // end function and go an layer back
//    LCDML.FUNC_goBackToMenu(1);      // leave this function and go a layer back
//  }
//}


//// *********************************************************************
//void mFunc_goToRootMenu(uint8_t param)
//// *********************************************************************
//{
//  if(LCDML.FUNC_setup())          // ****** SETUP *********
//  {
//    // go to root and display menu
//    LCDML.MENU_goRoot();
//  }
//}

//// *********************************************************************
//void mFunc_jumpTo_timer_info(uint8_t param)
//// *********************************************************************
//{
//  if(LCDML.FUNC_setup())          // ****** SETUP *********
//  {
//    // Jump to main screen
//    if(!LCDML.OTHER_jumpToFunc(mFunc_timer_info))
//    {
//      // function not found or not callable
//      LCDML.MENU_goRoot();
//    }
//  }
//}


//// *********************************************************************
//void mFunc_para(uint8_t param)
//// *********************************************************************
//{
//  if(LCDML.FUNC_setup())          // ****** SETUP *********
//  {

//    char buf[20];
//    sprintf (buf, "parameter: %d", param);

//    // setup function
//    u8g2.setFont(_LCDML_DISP_font);
//    u8g2.firstPage();
//    do {
//      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 1), buf);
//      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 2), "press any key");
//      u8g2.drawStr( 0, (_LCDML_DISP_font_h * 3), "to leave it");
//    } while( u8g2.nextPage() );

//    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds
//  }

//  if(LCDML.FUNC_loop())               // ****** LOOP *********
//  {
//    // For example
//    switch(param)
//    {
//      case 10:
//        // do something
//        break;

//      case 20:
//        // do something
//        break;

//      case 30:
//        // do something
//        break;

//      default:
//        // do nothing
//        break;
//    }


//    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
//    {
//      LCDML.FUNC_goBackToMenu();  // leave this function
//    }
//  }

//  if(LCDML.FUNC_close())      // ****** STABLE END *********
//  {
//    // you can here reset some global vars or do nothing
//  }
//}


// *********************************************************************
// check some errors - do not change here anything
// *********************************************************************
//# if(_LCDML_DISP_rows > _LCDML_DISP_cfg_max_rows)
//# error change value of _LCDML_DISP_cfg_max_rows in LCDMenuLib2.h
//# endif

//# if(_LCDML_glcd_tft_box_x1 > _LCDML_glcd_tft_w)
//# error _LCDML_glcd_tft_box_x1 is to big
//# endif

//# if(_LCDML_glcd_tft_box_y1 > _LCDML_glcd_tft_h)
//# error _LCDML_glcd_tft_box_y1 is to big
//# endif

void mFunc_about(uint8_t param)
{
	u16 agenda_id;
	if (LCDML.FUNC_setup())          // ****** SETUP *********
	{
		agenda_id = LCDML.FUNC_getID() - 7;
		bsp_setTextSize(1);
		bsp_fillRect(2, 2, 124, 124, BLACK);
		bsp_setTextColor2(GREEN, BLACK);
		bsp_lcd_setCursor(4,8);
		bsp_lcd_print("ID: "); 
		bsp_setTextColor2(RED, BLACK); 
		bsp_lcd_println(&about[agenda_id * 2][0]);
		bsp_setTextColor2(GREEN, BLACK);
		bsp_lcd_setCursor(4,22);
		bsp_lcd_print("Twitter: "); 
		bsp_display_qrcode(4, 36, &about[agenda_id*2+1][0], 3, BLACK);
		//ws2812_rainbow(5);
		
	}
	if (LCDML.FUNC_loop())           // ****** LOOP *********
	{
	}
	if (LCDML.FUNC_close())     // ****** STABLE END *********
	{
		// you can here reset some global vars or do nothing
		//ws2812_clear();
		bsp_fillRect(2, 2, 124, 124, BLACK);
		Menu_DrawFrame();

	}
}

void mFunc_ledcontrol(uint8_t param)
{
	uint8_t s_ucTempBuff[3] = {0x33,0x11,0x00}; /* 数据接收或者发送缓冲 */
	if (LCDML.FUNC_setup())          // ****** SETUP *********
	{	
		bsp_setTextSize(1);
		bsp_fillRect(2, 2, 124, 124, BLACK);
		
		s_ucTempBuff[0] = 0x33;
		s_ucTempBuff[1] = 0x11;
		s_ucTempBuff[2] = LCDML.FUNC_getID() - 93;
		Lora_beginPacket(FALSE);
		Lora_writeBuf(s_ucTempBuff, 3);
		Lora_endPacket();
		bsp_setTextColor2(GREEN, BLACK);
		bsp_lcd_setCursor(16,64);
		bsp_lcd_print("Send OK!"); 
		LCDML.FUNC_goBackToMenu();
	}
	if (LCDML.FUNC_loop())           // ****** LOOP *********
	{
	}
	if (LCDML.FUNC_close())     // ****** STABLE END *********
	{
		// you can here reset some global vars or do nothing
		//ws2812_clear();
		bsp_fillRect(2, 2, 124, 124, BLACK);
		Menu_DrawFrame();

	}
}

void mFunc_game(uint8_t param)
{
	static u8 game_flag = 0;
	if (LCDML.FUNC_setup())          // ****** SETUP *********
	{
		//u16 iSeed = 0;
		//u8 i, j;
		uint16_t crack_temp = 0;
		bsp_fillRect(2, 2, 124, 124, BLACK);

		bsp_ReadCpuFlash(CRACK_ADDR, (uint8_t *)&crack_temp, 2);

		if (crack_temp != 0x0301)
		{
			bsp_setTextColor2(WHITE, BLACK);
			bsp_lcd_setCursor(5,48);
			bsp_setTextSize(1);
			bsp_lcd_print("  Touch me please! ");
			bsp_DelayMS(2000);
			LCDML.MENU_goRoot();
		}
		else
		{
			game_flag = 1;
		}
	}
	if (LCDML.FUNC_loop())           // ****** LOOP *********
	{
		if ( game_flag )
		{
		    while (RUN_SNK());
		}
		//bsp_fillScreen(BLACK);
	}
	if (LCDML.FUNC_close())     // ****** STABLE END *********
	{
		// you can here reset some global vars or do nothing
		bsp_fillRect(2, 2, 124, 124, BLACK);
		Menu_DrawFrame();
	}
}

void mFunc_lcd_setlight(uint8_t param)
{
	static uint16_t t_light = 5;
	if (LCDML.FUNC_setup())          // ****** SETUP *********
	{
		//bsp_ReadCpuFlash(LIGHT_ADDR, (uint8_t *)&t_light, 2);

		LCDML.FUNC_setLoopInterval(1);
		bsp_fillRect(2, 2, 124, 124, BLACK);
		bsp_setTextSize(1);
		bsp_setTextColor2(GREEN, BLACK);
		bsp_lcd_setCursor(4,8);

		bsp_setTextColor2(WHITE, BLACK);
		bsp_lcd_setCursor(2,16);
		bsp_lcd_print("  TFT LIGHT (1 - 9)");
		bsp_lcd_setCursor(2,40);
		bsp_lcd_print("  <<==         ==>>");
		bsp_lcd_setCursor(61,40);
		bsp_setTextColor2(GREEN, BLACK);
		bsp_lcd_printf("%d",t_light);
		bsp_drawRect(15, 64, 101, 16, WHITE);
		bsp_fillRect(16, 65, 99, 14, BLACK);
		bsp_fillRect(16 + (t_light - 1) * 11, 65, 11, 14, WHITE);
	}
	if (LCDML.FUNC_loop())           // ****** LOOP *********
	{
		if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
		{
			if (LCDML.BT_checkLeft() || LCDML.BT_checkDown()) // check if button left is pressed
			{
				LCDML.BT_resetLeft(); // reset the left button
				LCDML.BT_resetDown(); // reset the left button
				if (t_light > 1)
				{
					t_light--;
				}
				bsp_lcd_setlight(t_light);
				bsp_lcd_setCursor(61,40);
				bsp_setTextColor2(GREEN, BLACK);
				bsp_lcd_printf("%d",t_light);
				bsp_drawRect(15, 64, 101, 16, WHITE);
				bsp_fillRect(16, 65, 99, 14, BLACK);
				bsp_fillRect(16 + (t_light - 1) * 11, 65, 11, 14, WHITE);
			}
			else  if (LCDML.BT_checkRight() || LCDML.BT_checkUp()) // check if button left is pressed
			{
				LCDML.BT_resetRight(); // reset the left button
				LCDML.BT_resetDown(); // reset the left button

				if (t_light < 9)
				{
					t_light++;
				}
				bsp_lcd_setlight(t_light);
				bsp_lcd_setCursor(61,40);
				bsp_setTextColor2(GREEN, BLACK);
				bsp_lcd_printf("%d",t_light);
				bsp_drawRect(15, 64, 101, 16, WHITE);
				bsp_fillRect(16, 65, 99, 14, BLACK);
				bsp_fillRect(16 + (t_light - 1) * 11, 65, 11, 14, WHITE);

			}
			else  if (LCDML.BT_checkEnter()) // check if button left is pressed
			{
				bsp_WriteCpuFlash(LIGHT_ADDR, (uint8_t *)&t_light, 2);
				LCDML.FUNC_goBackToMenu();
			}
		}
	}
	if (LCDML.FUNC_close())     // ****** STABLE END *********
	{
		// you can here reset some global vars or do nothing
		bsp_fillRect(2, 2, 124, 124, BLACK);
		Menu_DrawFrame();
	}
}


uint8_t g_button_value = 0;
u16 g_agenda_id = 0;
void mFunc_confagenda27(uint8_t param)
{
	u16 agenda_id;
	if (LCDML.FUNC_setup())          // ****** SETUP *********
	{
		agenda_id = LCDML.FUNC_getID() - 17;
		bsp_fillScreen(BLACK);
		bsp_lcd_setCursor(0,8);
		bsp_setTextColor2(WHITE, BLACK);
		bsp_lcd_print("    27th November    ");
		bsp_lcd_setCursor(0,24);
		bsp_setTextColor2(RED, BLACK);
		bsp_lcd_println(&conf_agenda27[agenda_id * 4][0]);
		bsp_lcd_setCursor(0,40);
		bsp_setTextColor2(GREEN, BLACK);
		bsp_lcd_println(&conf_agenda27[agenda_id * 4+1][0]);
		bsp_lcd_setCursor(0,80);
		bsp_setTextColor2(RED, BLACK);
		bsp_lcd_println(&conf_agenda27[agenda_id * 4+2][0]);
		bsp_lcd_setCursor(0,96);
		bsp_setTextColor2(GREEN, BLACK);
		bsp_lcd_println(&conf_agenda27[agenda_id * 4+3][0]);
		g_button_value = 0;
		g_agenda_id = agenda_id;
	}
	if (LCDML.FUNC_loop())           // ****** LOOP *********
	{
		if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
		{
			if (LCDML.BT_checkLeft() || LCDML.BT_checkUp()) // check if button left is pressed
			{
				LCDML.BT_resetLeft(); // reset the left button
				LCDML.BT_resetUp(); // reset the left button
				g_button_value++;
				//agenda_id = LCDML.FUNC_getID() - 8;
				if (g_agenda_id > 0)
				{
					g_agenda_id--;
					bsp_fillScreen(BLACK);
					bsp_lcd_setCursor(0,8);
					bsp_setTextColor2(WHITE, BLACK);
					bsp_lcd_print("    27th November    ");
					bsp_lcd_setCursor(0,24);
					bsp_setTextColor2(RED, BLACK);
					bsp_lcd_println(&conf_agenda27[g_agenda_id * 4][0]);
					bsp_lcd_setCursor(0,40);
					bsp_setTextColor2(GREEN, BLACK);
					bsp_lcd_println(&conf_agenda27[g_agenda_id * 4+1][0]);
					bsp_lcd_setCursor(0,80);
					bsp_setTextColor2(RED, BLACK);
					bsp_lcd_println(&conf_agenda27[g_agenda_id * 4+2][0]);
					bsp_lcd_setCursor(0,96);
					bsp_setTextColor2(GREEN, BLACK);
					bsp_lcd_println(&conf_agenda27[g_agenda_id * 4+3][0]);
				}

			}
			else  if (LCDML.BT_checkRight() || LCDML.BT_checkDown()) // check if button left is pressed
			{
				LCDML.BT_resetRight(); // reset the left button
				LCDML.BT_resetDown(); // reset the left button
				g_button_value++;
				//agenda_id = LCDML.FUNC_getID() - 8;

				if (g_agenda_id < 15)
				{
					g_agenda_id++;
					bsp_fillScreen(BLACK);
					bsp_lcd_setCursor(0,8);
					bsp_setTextColor2(WHITE, BLACK);
					bsp_lcd_print("    27th November    ");
					bsp_lcd_setCursor(0,24);
					bsp_setTextColor2(RED, BLACK);
					bsp_lcd_println(&conf_agenda27[g_agenda_id * 4][0]);
					bsp_lcd_setCursor(0,40);
					bsp_setTextColor2(GREEN, BLACK);
					bsp_lcd_println(&conf_agenda27[g_agenda_id * 4+1][0]);
					bsp_lcd_setCursor(0,80);
					bsp_setTextColor2(RED, BLACK);
					bsp_lcd_println(&conf_agenda27[g_agenda_id * 4+2][0]);
					bsp_lcd_setCursor(0,96);
					bsp_setTextColor2(GREEN, BLACK);
					bsp_lcd_println(&conf_agenda27[g_agenda_id * 4+3][0]);
				}
			}
		}
	}
	if (LCDML.FUNC_close())     // ****** STABLE END *********
	{
		// you can here reset some global vars or do nothing
		bsp_fillScreen(BLACK);
		Menu_DrawFrame();
	}
}

void mFunc_confagenda28(uint8_t param)
{
	u16 agenda_id;
	if (LCDML.FUNC_setup())          // ****** SETUP *********
	{
		LCDML.FUNC_setLoopInterval(1);
		agenda_id = LCDML.FUNC_getID() - 33;
		bsp_fillScreen(BLACK);
		bsp_lcd_setCursor(0,8);
		bsp_setTextColor2(WHITE, BLACK);
		bsp_lcd_print("    28th November    ");
		bsp_lcd_setCursor(0,24);
		bsp_setTextColor2(RED, BLACK);
		bsp_lcd_println(&conf_agenda28[agenda_id * 4][0]);
		bsp_lcd_setCursor(0,40);
		bsp_setTextColor2(GREEN, BLACK);
		bsp_lcd_println(&conf_agenda28[agenda_id * 4+1][0]);
		bsp_lcd_setCursor(0,80);
		bsp_setTextColor2(RED, BLACK);
		bsp_lcd_println(&conf_agenda28[agenda_id * 4+2][0]);
		bsp_lcd_setCursor(0,96);
		bsp_setTextColor2(GREEN, BLACK);
		bsp_lcd_println(&conf_agenda28[agenda_id * 4+3][0]);
		g_button_value = 0;
		g_agenda_id = agenda_id;
	}
	if (LCDML.FUNC_loop())           // ****** LOOP *********
	{
		if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
		{
			if (LCDML.BT_checkLeft() || LCDML.BT_checkUp()) // check if button left is pressed
			{
				LCDML.BT_resetLeft(); // reset the left button
				LCDML.BT_resetUp(); // reset the left button
				g_button_value++;
				//agenda_id = LCDML.FUNC_getID() - 8;
				if (g_agenda_id > 0)
				{
					g_agenda_id--;
					bsp_fillScreen(BLACK);
					bsp_lcd_setCursor(0,8);
					bsp_setTextColor2(WHITE, BLACK);
					bsp_lcd_print("    28th November    ");
					bsp_lcd_setCursor(0,24);
					bsp_setTextColor2(RED, BLACK);
					bsp_lcd_println(&conf_agenda28[g_agenda_id * 4][0]);
					bsp_lcd_setCursor(0,40);
					bsp_setTextColor2(GREEN, BLACK);
					bsp_lcd_println(&conf_agenda28[g_agenda_id * 4+1][0]);
					bsp_lcd_setCursor(0,80);
					bsp_setTextColor2(RED, BLACK);
					bsp_lcd_println(&conf_agenda28[g_agenda_id * 4+2][0]);
					bsp_lcd_setCursor(0,96);
					bsp_setTextColor2(GREEN, BLACK);
					bsp_lcd_println(&conf_agenda28[g_agenda_id * 4+3][0]);
				}

			}
			else  if (LCDML.BT_checkRight() || LCDML.BT_checkDown()) // check if button left is pressed
			{
				LCDML.BT_resetRight(); // reset the left button
				LCDML.BT_resetDown(); // reset the left button
				g_button_value++;
				//agenda_id = LCDML.FUNC_getID() - 8;

				if (g_agenda_id < 16)
				{
					g_agenda_id++;
					bsp_fillScreen(BLACK);
					bsp_lcd_setCursor(0,8);
					bsp_setTextColor2(WHITE, BLACK);
					bsp_lcd_print("    28th November    ");
					bsp_lcd_setCursor(0,24);
					bsp_setTextColor2(RED, BLACK);
					bsp_lcd_println(&conf_agenda28[g_agenda_id * 4][0]);
					bsp_lcd_setCursor(0,40);
					bsp_setTextColor2(GREEN, BLACK);
					bsp_lcd_println(&conf_agenda28[g_agenda_id * 4+1][0]);
					bsp_lcd_setCursor(0,80);
					bsp_setTextColor2(RED, BLACK);
					bsp_lcd_println(&conf_agenda28[g_agenda_id * 4+2][0]);
					bsp_lcd_setCursor(0,96);
					bsp_setTextColor2(GREEN, BLACK);
					bsp_lcd_println(&conf_agenda28[g_agenda_id * 4+3][0]);
				}
			}
		}
	}
	if (LCDML.FUNC_close())     // ****** STABLE END *********
	{
		// you can here reset some global vars or do nothing
		bsp_fillScreen(BLACK);
		Menu_DrawFrame();
	}
}

void mFunc_commsecagenda27(uint8_t param)
{
	u16 agenda_id;
	if (LCDML.FUNC_setup())          // ****** SETUP *********
	{
		agenda_id = LCDML.FUNC_getID() - 50;
		bsp_fillScreen(BLACK);
		bsp_lcd_setCursor(0,8);
		bsp_setTextColor2(WHITE, BLACK);
		bsp_lcd_print("    27th November    ");
		bsp_lcd_setCursor(0,24);
		bsp_setTextColor2(RED, BLACK);
		bsp_lcd_println(&commsec_agenda27[agenda_id * 3][0]);
		bsp_lcd_setCursor(0,40);
		bsp_setTextColor2(GREEN, BLACK);
		bsp_lcd_println(&commsec_agenda27[agenda_id * 3+1][0]);
		bsp_lcd_setCursor(0,80);
		bsp_setTextColor2(RED, BLACK);
		bsp_lcd_println(&commsec_agenda27[agenda_id * 3+2][0]);
		g_button_value = 0;
		g_agenda_id = agenda_id;
	}
	if (LCDML.FUNC_loop())           // ****** LOOP *********
	{
		if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
		{
			if (LCDML.BT_checkLeft() || LCDML.BT_checkUp()) // check if button left is pressed
			{
				LCDML.BT_resetLeft(); // reset the left button
				LCDML.BT_resetUp(); // reset the left button
				g_button_value++;
				//agenda_id = LCDML.FUNC_getID() - 8;
				if (g_agenda_id > 0)
				{
					g_agenda_id--;
					bsp_fillScreen(BLACK);
					bsp_lcd_setCursor(0,8);
					bsp_setTextColor2(WHITE, BLACK);
					bsp_lcd_print("    27th November    ");
					bsp_lcd_setCursor(0,24);
					bsp_setTextColor2(RED, BLACK);
					bsp_lcd_println(&commsec_agenda27[g_agenda_id * 3][0]);
					bsp_lcd_setCursor(0,40);
					bsp_setTextColor2(GREEN, BLACK);
					bsp_lcd_println(&commsec_agenda27[g_agenda_id * 3+1][0]);
					bsp_lcd_setCursor(0,80);
					bsp_setTextColor2(RED, BLACK);
					bsp_lcd_println(&commsec_agenda27[g_agenda_id * 3+2][0]);
				}

			}
			else  if (LCDML.BT_checkRight() || LCDML.BT_checkDown()) // check if button left is pressed
			{
				LCDML.BT_resetRight(); // reset the left button
				LCDML.BT_resetDown(); // reset the left button
				g_button_value++;
				//agenda_id = LCDML.FUNC_getID() - 8;

				if (g_agenda_id < 15)
				{
					g_agenda_id++;
					bsp_fillScreen(BLACK);
					bsp_lcd_setCursor(0,8);
					bsp_setTextColor2(WHITE, BLACK);
					bsp_lcd_print("    27th November    ");
					bsp_lcd_setCursor(0,24);
					bsp_setTextColor2(RED, BLACK);
					bsp_lcd_println(&commsec_agenda27[g_agenda_id * 3][0]);
					bsp_lcd_setCursor(0,40);
					bsp_setTextColor2(GREEN, BLACK);
					bsp_lcd_println(&commsec_agenda27[g_agenda_id * 3+1][0]);
					bsp_lcd_setCursor(0,80);
					bsp_setTextColor2(RED, BLACK);
					bsp_lcd_println(&commsec_agenda27[g_agenda_id * 3+2][0]);
				}
			}
		}
	}
	if (LCDML.FUNC_close())     // ****** STABLE END *********
	{
		// you can here reset some global vars or do nothing
		bsp_fillScreen(BLACK);
		Menu_DrawFrame();
	}
}


void mFunc_commsecagenda28(uint8_t param)
{
	u16 agenda_id;
	if (LCDML.FUNC_setup())          // ****** SETUP *********
	{
		agenda_id = LCDML.FUNC_getID() - 66;
		bsp_fillScreen(BLACK);
		bsp_lcd_setCursor(0,8);
		bsp_setTextColor2(WHITE, BLACK);
		bsp_lcd_print("    28th November    ");
		bsp_lcd_setCursor(0,24);
		bsp_setTextColor2(RED, BLACK);
		bsp_lcd_println(&commsec_agenda28[agenda_id * 3][0]);
		bsp_lcd_setCursor(0,40);
		bsp_setTextColor2(GREEN, BLACK);
		bsp_lcd_println(&commsec_agenda28[agenda_id * 3+1][0]);
		bsp_lcd_setCursor(0,80);
		bsp_setTextColor2(RED, BLACK);
		bsp_lcd_println(&commsec_agenda28[agenda_id * 3+2][0]);
		g_button_value = 0;
		g_agenda_id = agenda_id;
	}
	if (LCDML.FUNC_loop())           // ****** LOOP *********
	{
		if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
		{
			if (LCDML.BT_checkLeft() || LCDML.BT_checkUp()) // check if button left is pressed
			{
				LCDML.BT_resetLeft(); // reset the left button
				LCDML.BT_resetUp(); // reset the left button
				g_button_value++;
				//agenda_id = LCDML.FUNC_getID() - 8;
				if (g_agenda_id > 0)
				{
					g_agenda_id--;
					bsp_fillScreen(BLACK);
					bsp_lcd_setCursor(0,8);
					bsp_setTextColor2(WHITE, BLACK);
					bsp_lcd_print("    28th November    ");
					bsp_lcd_setCursor(0,24);
					bsp_setTextColor2(RED, BLACK);
					bsp_lcd_println(&commsec_agenda28[g_agenda_id * 3][0]);
					bsp_lcd_setCursor(0,40);
					bsp_setTextColor2(GREEN, BLACK);
					bsp_lcd_println(&commsec_agenda28[g_agenda_id * 3+1][0]);
					bsp_lcd_setCursor(0,80);
					bsp_setTextColor2(RED, BLACK);
					bsp_lcd_println(&commsec_agenda28[g_agenda_id * 3+2][0]);
				}

			}
			else  if (LCDML.BT_checkRight() || LCDML.BT_checkDown()) // check if button left is pressed
			{
				LCDML.BT_resetRight(); // reset the left button
				LCDML.BT_resetDown(); // reset the left button
				g_button_value++;
				//agenda_id = LCDML.FUNC_getID() - 8;

				if (g_agenda_id < 15)
				{
					g_agenda_id++;
					bsp_fillScreen(BLACK);
					bsp_lcd_setCursor(0,8);
					bsp_setTextColor2(WHITE, BLACK);
					bsp_lcd_print("    28th November    ");
					bsp_lcd_setCursor(0,24);
					bsp_setTextColor2(RED, BLACK);
					bsp_lcd_println(&commsec_agenda28[g_agenda_id * 3][0]);
					bsp_lcd_setCursor(0,40);
					bsp_setTextColor2(GREEN, BLACK);
					bsp_lcd_println(&commsec_agenda28[g_agenda_id * 3+1][0]);
					bsp_lcd_setCursor(0,80);
					bsp_setTextColor2(RED, BLACK);
					bsp_lcd_println(&commsec_agenda28[g_agenda_id * 3+2][0]);
				}
			}
		}
	}
	if (LCDML.FUNC_close())     // ****** STABLE END *********
	{
		// you can here reset some global vars or do nothing
		bsp_fillScreen(BLACK);
		Menu_DrawFrame();
	}
}

void mFunc_activities(uint8_t param)
{
	u16 agenda_id;
	if (LCDML.FUNC_setup())          // ****** SETUP *********
	{
		agenda_id = LCDML.FUNC_getID() - 82;
		bsp_fillScreen(BLACK);
		bsp_lcd_setCursor(2,16);
		bsp_setTextColor2(WHITE, BLACK);
		bsp_lcd_print("Highlight Activities");
		bsp_lcd_setCursor(0,40);
		bsp_setTextColor2(RED, BLACK);
		bsp_lcd_println(&activities[agenda_id][0]);
		g_button_value = 0;
		g_agenda_id = agenda_id;
	}
	if (LCDML.FUNC_loop())           // ****** LOOP *********
	{
		if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
		{
			if (LCDML.BT_checkLeft() || LCDML.BT_checkUp()) // check if button left is pressed
			{
				LCDML.BT_resetLeft(); // reset the left button
				LCDML.BT_resetUp(); // reset the left button
				g_button_value++;
				//agenda_id = LCDML.FUNC_getID() - 8;
				if (g_agenda_id > 0)
				{
					g_agenda_id--;
					bsp_fillScreen(BLACK);
					bsp_lcd_setCursor(2,16);
					bsp_setTextColor2(WHITE, BLACK);
					bsp_lcd_print("Highlight Activities");
					bsp_lcd_setCursor(0,40);
					bsp_setTextColor2(RED, BLACK);
					bsp_lcd_println(&activities[g_agenda_id][0]);
				}

			}
			else  if (LCDML.BT_checkRight() || LCDML.BT_checkDown()) // check if button left is pressed
			{
				LCDML.BT_resetRight(); // reset the left button
				LCDML.BT_resetDown(); // reset the left button
				g_button_value++;
				//agenda_id = LCDML.FUNC_getID() - 8;

				if (g_agenda_id < 9)
				{
					g_agenda_id++;
					bsp_fillScreen(BLACK);
					bsp_lcd_setCursor(2,16);
					bsp_setTextColor2(WHITE, BLACK);
					bsp_lcd_print("Highlight Activities");
					bsp_lcd_setCursor(0,40);
					bsp_setTextColor2(RED, BLACK);
					bsp_lcd_println(&activities[g_agenda_id][0]);
				}
			}
		}
	}
	if (LCDML.FUNC_close())     // ****** STABLE END *********
	{
		// you can here reset some global vars or do nothing
		bsp_fillScreen(BLACK);
		Menu_DrawFrame();
	}
}

void mFunc_secret(uint8_t param)
{
	static uint8_t n_pos = 0;	//位置
	static uint16_t crack_temp = 0;
	const uint8_t data[13] = {"#HITB2018DXB"};
	static uint8_t pwd[12] = { 0x30, 0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30 };
	static uint8_t CPU_ID[12] = { 0 };
	if (LCDML.FUNC_setup())          // ****** SETUP *********
	{
		uint8_t i;
		uint32_t CPU_Sn0, CPU_Sn1;

		CPU_Sn0 = *(__IO uint32_t*)(0x1ffff7e8);
		CPU_Sn1 = *(__IO uint32_t*)(0x1ffff7e8 + 4);

		for (i = 0; i < 8; i++)
		{
			CPU_ID[11-i] = ((CPU_Sn0 >> (i * 4)) & 0x0f);
		}
		for (i = 0; i < 4; i++)
		{
			CPU_ID[3-i] = ((CPU_Sn1 >> (i * 4)) & 0x0f);
		}

		for ( i = 0 ; i < 12 ; i++ )
		{
		    CPU_ID[i] ^= data[i];
			CPU_ID[i] &= 0x0f;
			if ( CPU_ID[i] < 10 )
			{
			    CPU_ID[i] += '0';
			}
			else
			{
				CPU_ID[i] += 'A'-10;
			}
		}

		bsp_fillScreen(BLACK);	
		//画框
		bsp_drawRect(0, 0, 128, 128, GREEN);
		bsp_drawRect(1, 1, 126, 126, GREEN);

		bsp_setTextSize(1);
		bsp_setTextColor2(WHITE, BLACK);
		bsp_drawText(8, 8, "UID: ");	//一行最多39个字符
		bsp_drawFastHLine(0, 22, 126, GREEN);
		bsp_lcd_printf("%04X %08X",CPU_Sn1 & 0xffff,CPU_Sn0);

		bsp_ReadCpuFlash(CRACK_ADDR, (uint8_t *)&crack_temp, 2);

		if (crack_temp == 0x0301)
		{
			bsp_setTextColor2(WHITE, BLACK);
			bsp_lcd_setCursor(2,80);
			bsp_lcd_print("       pwned!     ");
		}
		else
		{
			bsp_setTextColor2(WHITE, BLACK);
			bsp_lcd_setCursor(8,32);
			bsp_lcd_print("Get Key: ");
			bsp_lcd_setCursor(14, 48);
			bsp_setTextColor2(GREEN, BLACK);
			for ( i = 0; i < 12 ; i++ )
			{
				if ( get_key[i] != 0 )
				{
				    bsp_lcd_printf("%c",get_key[i]);
				}
			}
			
			bsp_setTextColor2(WHITE, BLACK);
			bsp_lcd_setCursor(14,64);
			bsp_lcd_print("PASSWORD:");
			bsp_lcd_setCursor(14,96);
			bsp_lcd_print("____________");
		}

		LCDML.FUNC_setLoopInterval(100);
	}
	if (LCDML.FUNC_loop())           // ****** LOOP *********
	{
		uint8_t i;
		if (crack_temp != 0x0301)
		{
			if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
			{
				if (LCDML.BT_checkLeft()) // check if button left is pressed
				{
					LCDML.BT_resetLeft(); // reset the left button

					if (n_pos > 0)
					{
						bsp_drawChar(14 + n_pos * 6, 96, pwd[n_pos], WHITE, BLACK,1);
						n_pos--;
						bsp_drawChar(14 + n_pos * 6, 96, pwd[n_pos], RED, BLACK,1);
						//if (n_pos == 0)
						//{
						//	LCD_DrawChar(14 + n_pos * 6, 80, pwd[n_pos], RED, BLACK, 1);
						//}
					}
				}
				else if (LCDML.BT_checkRight()) // check if button left is pressed
				{
					LCDML.BT_resetRight(); // reset the left button

					if (n_pos < 11)
					{
						//if (n_pos == 0)
						//{
						//	LCD_DrawChar(14 + n_pos * 6, 80, pwd[n_pos], RED, BLACK, 1);
						//}
						bsp_drawChar(14 + n_pos * 6, 96, pwd[n_pos], WHITE, BLACK,1);
						n_pos++;
						bsp_drawChar(14 + n_pos * 6, 96, pwd[n_pos], RED, BLACK,1);
					}
				}
				else if (LCDML.BT_checkUp())
				{
					LCDML.BT_resetUp(); // reset the left button

					if (pwd[n_pos] == 0x20)
					{
						pwd[n_pos] = 0x7f;
					}
					pwd[n_pos]--;
					bsp_drawChar(14 + n_pos * 6, 96, pwd[n_pos], RED, BLACK,1);
				}
				else if (LCDML.BT_checkDown())
				{
					if (pwd[n_pos] == 0x7f)
					{
						pwd[n_pos] = 0x19;
					}
					pwd[n_pos]++;
					bsp_drawChar(14 + n_pos * 6, 96, pwd[n_pos], RED, BLACK,1);
				}
				else if (LCDML.BT_checkEnter())
				{
					LCDML.BT_resetEnter(); // reset the left button

					uint8_t cmp_flag = 0;
					for (i = 0; i < 12; i++)
					{
						if (pwd[i] != CPU_ID[i])
						{
							cmp_flag = 1;
							break;
						}
					}
					if (cmp_flag == 0)
					{
						bsp_setTextColor2(RED, BLACK);
						bsp_lcd_setCursor(78,64);
						bsp_lcd_print("Cool!");
						bsp_DelayMS(1000);
						bsp_lcd_setCursor(78,64);
						bsp_lcd_print("      ");
						crack_temp = 0x0301;
						bsp_WriteCpuFlash(CRACK_ADDR, (uint8_t *)&crack_temp, 2);

						bsp_setTextColor2(WHITE, BLACK);
						bsp_lcd_setCursor(2,80);
						bsp_lcd_print("       pwned!     ");
						LCDML.FUNC_close();
					}
					else
					{
						bsp_setTextColor2(RED, BLACK);
						bsp_lcd_setCursor(78,64);
						bsp_lcd_print("Error!");
						bsp_DelayMS(1000);
						bsp_lcd_setCursor(78,64);
						bsp_lcd_print("      ");
					}
				}
			}
			if ( getkey_flag ==   1 )
			{
			    bsp_lcd_setCursor(14, 48);
				bsp_setTextColor2(RED, BLACK);
				for ( i = 0; i < 12 ; i++ )
				{
					if ( get_key[i] != 0 )
					{
					    bsp_lcd_printf("%c",get_key[i]);
					}
				}
				bsp_lcd_setCursor(80,32);
				bsp_setTextColor2(GREEN, BLACK);
				bsp_lcd_printf("%ddB  ", getkey_rssi);
				getkey_flag = 0;
			}
			else if ( getkey_flag ==   2 )
			{
				bsp_lcd_setCursor(80,32);
				bsp_setTextColor2(BLUE, BLACK);
				bsp_lcd_printf("%ddB  ", getkey_rssi);
				getkey_flag = 0;
			}
		}
	}
	if (LCDML.FUNC_close())     // ****** STABLE END *********
	{
		// you can here reset some global vars or do nothing
		bsp_fillScreen(BLACK);
		Menu_DrawFrame();
	}
}

void mFunc_Lora_TX(uint8_t param)
{
	uint8_t s_ucTempBuff[32]; /* 数据接收或者发送缓冲 */
	static uint8_t count = 0;
	static uint8_t autoflag = 0;
	static uint16_t tt = 100;
	uint8_t i;
	if(LCDML.FUNC_setup())          // ****** SETUP *********
	{
		// setup
		// is called only if it is started

		// starts a trigger event for the loop function every 100 milliseconds
		LCDML.FUNC_setLoopInterval(tt);

		bsp_Init_Lora();
		Lora_RegConfig();
		
		//bsp_fillRect2(2, 30, 317, 225, _LCDML_DISP_bgcolor);
		//bsp_setTextSize(1);
		//bsp_setTextColor(_LCDML_DISP_fcolor);
		//bsp_drawText(2, 36, "  Press OK:    Send 32 Byte       ");	//一行最多39个字符
		//bsp_drawText(2, 46, "  Press Left:  Auto Send Data     ");	//一行最多39个字符
		//bsp_drawText(2, 56, "  Press Right: Stop Auto Send     ");	//一行最多39个字符
		//bsp_drawText(2, 66, "  Press Up:    Time Interval -10ms");	//一行最多39个字符
		//bsp_drawText(2, 76, "  Press Down:  Time Interval +10ms");	//一行最多39个字符

		//CC1101_writeCmd(CC1101_STX);
		//nRF24L01_powerUp();
		//bsp_nRF24L01_TxMode();
	}

	if(LCDML.FUNC_loop())           // ****** LOOP *********
	{
		// loop
		// is called when it is triggered
		// - with LCDML_DISP_triggerMenu( milliseconds )
		// - with every button status change

		// check if any button is pressed (enter, up, down, left, right)
		if(LCDML.BT_checkAny()) 
		{
			if (LCDML.BT_checkLeft()) // check if button left is pressed
			{
				LCDML.BT_resetLeft(); // reset the left button
				//bsp_setTextColor2(_LCDML_DISP_scolor, _LCDML_DISP_bgcolor);
				//bsp_lcd_setCursor(2,86);
				//bsp_lcd_printf("  Auto Send...  Time Interval: %5dms",tt);
				autoflag = 1;
			}
			if (LCDML.BT_checkRight()) // check if button left is pressed
			{
				LCDML.BT_resetRight(); // reset the left button
				autoflag = 0;
			}
			if (LCDML.BT_checkUp()) // check if button left is pressed
			{
				LCDML.BT_resetUp(); // reset the left button
				if ( tt > 10 )
				{
				    tt -=10;
					//bsp_lcd_setCursor(2,86);
					//bsp_lcd_printf("  Auto Send...  Time Interval: %5dms",tt);
					LCDML.FUNC_setLoopInterval(tt);
				}
			}
			if (LCDML.BT_checkDown()) // check if button left is pressed
			{
				LCDML.BT_resetDown(); // reset the left button
				if ( tt < 10000 )
				{
				    tt +=10;
					//bsp_lcd_setCursor(2,86);
					//bsp_lcd_printf("  Auto Send...  Time Interval: %5dms",tt);
					LCDML.FUNC_setLoopInterval(tt);
				}
			}
			if (LCDML.BT_checkEnter()) // check if button left is pressed
			{
				LCDML.BT_resetEnter(); // reset the left button
				for(i = 0; i < 32; i++)
				{
					s_ucTempBuff[i] = i;
				}
				Lora_beginPacket(FALSE);
				//Lora_writeBuf("Hello", 6);
				Lora_writeBuf(s_ucTempBuff, 32);
				Lora_endPacket();
			}
		}
		if(autoflag)
		{
			for(i = 0; i < 32; i++)
			{
				s_ucTempBuff[i] = count++;
			}
			Lora_beginPacket(FALSE);
			Lora_writeBuf(s_ucTempBuff, 32);
			Lora_endPacket();
		}
	}

	if(LCDML.FUNC_close())      // ****** STABLE END *********
	{
	// loop end
	// you can here reset some global vars or delete it
		autoflag = 0;
		Menu_DrawFrame();
	}
}


//void mFunc_lcd_setlight(uint8_t param)
//{
//	static uint16_t t_light;
//	if (LCDML.FUNC_setup())          // ****** SETUP *********
//	{
//		bsp_ReadCpuFlash(LIGHT_ADDR, (uint8_t *)&t_light, 2);
//		LCD_Fill(1, 1, 158, 126, BLACK);
//		LCD_DrawRect(0, 0, 159, 127, GREEN);
//		LCD_DrawLine(0, 32, 159, 32, GREEN);
//		LCD_setTextColor(WHITE, BLACK);
//		//LCD_text("      TFT LIGHT SET       ", 1, 12);
//		LCD_text("    TFT LIGHT ( 1 - 9 )   ", 1, 12);
//		LCD_text("    <<==           ==>>   ", 1, 56);

//		LCD_setCursor(79, 56);
//		LCD_write(t_light+0x30);
//		LCD_DrawRect(26, 86, 134, 96, WHITE);
//		LCD_Fill(27, 87, 133, 95, BLACK);
//		LCD_DrawBox(27 + (t_light - 1) * 12, 87, 12, 9, WHITE);
//	}
//	if (LCDML.FUNC_loop())           // ****** LOOP *********
//	{
//		if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
//		{
//			if (LCDML.BT_checkLeft() || LCDML.BT_checkDown()) // check if button left is pressed
//			{
//				LCDML.BT_resetLeft(); // reset the left button
//				LCDML.BT_resetDown(); // reset the left button
//				if (t_light > 1)
//				{
//					t_light--;
//				}
//				LCD_Light_Set(t_light);
//				LCD_setCursor(79, 56);
//				LCD_write(t_light + 0x30);
//				//LCD_DrawRect(26, 86, 134, 96, WHITE);
//				LCD_Fill(27, 87, 133, 95, BLACK);
//				LCD_DrawBox(27 + (t_light - 1) * 12, 87, 12, 9, WHITE);
//			}
//			else  if (LCDML.BT_checkRight() || LCDML.BT_checkUp()) // check if button left is pressed
//			{
//				LCDML.BT_resetRight(); // reset the left button
//				LCDML.BT_resetDown(); // reset the left button

//				if (t_light < 9)
//				{
//					t_light++;
//				}
//				LCD_Light_Set(t_light);
//				LCD_setCursor(79, 56);
//				LCD_write(t_light + 0x30);
//				//LCD_DrawRect(26, 86, 134, 96, WHITE);
//				LCD_Fill(27, 87, 133, 95, BLACK);
//				LCD_DrawBox(27 + (t_light - 1) * 12, 87, 12, 9, WHITE);
//			}
//			else  if (LCDML.BT_checkEnter()) // check if button left is pressed
//			{
//				bsp_WriteCpuFlash(LIGHT_ADDR, (uint8_t *)&t_light, 2);
//				LCDML.FUNC_goBackToMenu();
//			}
//		}
//	}
//	if (LCDML.FUNC_close())     // ****** STABLE END *********
//	{
//		// you can here reset some global vars or do nothing
//		LCD_Fill(1, 1, 158, 126, BLACK);
//		Menu_DrawFrame();
//	}
//}


#if 0
void Menu_nRF24L01_TX(uint8_t param)
{
	uint8_t s_ucTempBuff[32]; /* 数据接收或者发送缓冲 */
	static uint8_t count = 0;
	static uint8_t autoflag = 0;
	static uint16_t tt = 500;
	uint8_t i;
	uint8_t TX_ADDRESS[5] = {0x34,0x43,0x10,0x10,0x01};  
	if(LCDML.FUNC_setup())          // ****** SETUP *********
	{
		// setup
		// is called only if it is started

		// starts a trigger event for the loop function every 100 milliseconds
		LCDML.FUNC_setLoopInterval(tt);
		bsp_Init_nRF24L01();
		nRF24L01_EasyConfig();
		nRF24L01_setChannel(40);
		nRF24L01_setAutoAck2(0, ENABLE);
		nRF24L01_setCRCLength(RF24_CRC_16);
		nRF24L01_openWritingPipe(TX_ADDRESS);
		nRF24L01_openReadingPipe(0, TX_ADDRESS);
		nRF24L01_setRetries(1,10);
		nRF24L01_setDataRate(RF24_2MBPS);
		nRF24L01_setPALevel(RF24_PA_MAX);
		nRF24L01_printDetails();
		
		bsp_fillRect2(2, 30, 317, 225, _LCDML_DISP_bgcolor);
		bsp_setTextSize(1);
		bsp_setTextColor(_LCDML_DISP_fcolor);
		bsp_drawText(2, 36, "  Press OK:    Send 32 Byte       ");	//一行最多39个字符
		bsp_drawText(2, 46, "  Press Left:  Auto Send Data     ");	//一行最多39个字符
		bsp_drawText(2, 56, "  Press Right: Stop Auto Send     ");	//一行最多39个字符
		bsp_drawText(2, 66, "  Press Up:    Time Interval -10ms");	//一行最多39个字符
		bsp_drawText(2, 76, "  Press Down:  Time Interval +10ms");	//一行最多39个字符
		
		nRF24L01_powerUp();
		//bsp_nRF24L01_TxMode();
	}

	if(LCDML.FUNC_loop())           // ****** LOOP *********
	{
		// loop
		// is called when it is triggered
		// - with LCDML_DISP_triggerMenu( milliseconds )
		// - with every button status change

		// check if any button is pressed (enter, up, down, left, right)
		if(LCDML.BT_checkAny()) 
		{
			if (LCDML.BT_checkLeft()) // check if button left is pressed
			{
				LCDML.BT_resetLeft(); // reset the left button
				bsp_setTextColor2(_LCDML_DISP_scolor, _LCDML_DISP_bgcolor);
				bsp_lcd_setCursor(2,86);
				bsp_lcd_printf("  Auto Send...  Time Interval: %5dms",tt);
				autoflag = 1;
			}
			if (LCDML.BT_checkRight()) // check if button left is pressed
			{
				LCDML.BT_resetRight(); // reset the left button
				autoflag = 0;
			}
			if (LCDML.BT_checkUp()) // check if button left is pressed
			{
				LCDML.BT_resetUp(); // reset the left button
				if ( tt > 10 )
				{
				    tt -=10;
					bsp_lcd_setCursor(2,86);
					bsp_lcd_printf("  Auto Send...  Time Interval: %5dms",tt);
					LCDML.FUNC_setLoopInterval(tt);
				}
			}
			if (LCDML.BT_checkDown()) // check if button left is pressed
			{
				LCDML.BT_resetDown(); // reset the left button
				if ( tt < 10000 )
				{
				    tt +=10;
					bsp_lcd_setCursor(2,86);
					bsp_lcd_printf("  Auto Send...  Time Interval: %5dms",tt);
					LCDML.FUNC_setLoopInterval(tt);
				}
			}
			if (LCDML.BT_checkEnter()) // check if button left is pressed
			{
				LCDML.BT_resetEnter(); // reset the left button
				for(i = 0; i < 32; i++)
				{
					s_ucTempBuff[i] = count++;
				}
				nRF24L01_writeFast2(s_ucTempBuff, 32);
				//bsp_nRF24L01_TxData(s_ucTempBuff);
			}
		}
		if(autoflag)
		{
			for(i = 0; i < 32; i++)
			{
				s_ucTempBuff[i] = count++;
			}
			nRF24L01_writeFast2(s_ucTempBuff, 32);
			//bsp_nRF24L01_TxData(s_ucTempBuff);
		}
	}

	if(LCDML.FUNC_close())      // ****** STABLE END *********
	{
	// loop end
	// you can here reset some global vars or delete it
		autoflag = 0;
		Menu_DrawFrame();
	}
}

void Menu_nRF24L01_RX(uint8_t param)
{
	uint8_t s_ucTempBuff[32]; /* 数据接收或者发送缓冲 */
	//uint8_t s_ucRxStatus; 
	uint8_t TX_ADDRESS[5] = {0x34,0x43,0x10,0x10,0x01};  
//	static uint8_t count = 0;
	//static uint8_t autoflag = 0;
//	static uint16_t tt = 500;
	//uint8_t i;
	if(LCDML.FUNC_setup())          // ****** SETUP *********
	{
		// setup
		// is called only if it is started

		// starts a trigger event for the loop function every 100 milliseconds
		LCDML.FUNC_setLoopInterval(1);
		bsp_Init_nRF24L01();
		nRF24L01_EasyConfig();
		nRF24L01_setChannel(40);
		nRF24L01_setAutoAck2(0, ENABLE);
		nRF24L01_setCRCLength(RF24_CRC_16);
		nRF24L01_openWritingPipe(TX_ADDRESS);
		nRF24L01_openReadingPipe(0, TX_ADDRESS);
		nRF24L01_setRetries(1,10);
		nRF24L01_setDataRate(RF24_2MBPS);
		nRF24L01_setPALevel(RF24_PA_MAX);
		
		nRF24L01_startListening();
		nRF24L01_printDetails();

		bsp_fillRect2(2, 30, 317, 225, _LCDML_DISP_bgcolor);
	}

	if(LCDML.FUNC_loop())           // ****** LOOP *********
	{
		// loop
		// is called when it is triggered
		// - with LCDML_DISP_triggerMenu( milliseconds )
		// - with every button status change

		// check if any button is pressed (enter, up, down, left, right)
		if(LCDML.BT_checkAny()) 
		{
			if (LCDML.BT_checkLeft()) // check if button left is pressed
			{
				LCDML.BT_resetLeft(); // reset the left button
				//bsp_setTextColor2(_LCDML_DISP_scolor, _LCDML_DISP_bgcolor);
				//bsp_drawText(2, 86, "  Auto Send...  Time Interval:      ms");	//一行最多39个字符
				//bsp_drawNum_Format(188, 86, tt, "%05d");	//长度9*6
				//autoflag = 1;
			}
			if (LCDML.BT_checkRight()) // check if button left is pressed
			{
				LCDML.BT_resetRight(); // reset the left button
				//autoflag = 0;
			}
			if (LCDML.BT_checkUp()) // check if button left is pressed
			{
				LCDML.BT_resetUp(); // reset the left button
				//if ( tt > 10 )
				//{
				//    tt -=10;
				//	//bsp_drawText(180, 86, "     ");	//一行最多39个字符
				//	bsp_drawNum_Format(188, 86, tt, "%05d");	//长度9*6
				//	LCDML.FUNC_setLoopInterval(tt);
				//}
			}
			if (LCDML.BT_checkDown()) // check if button left is pressed
			{
				LCDML.BT_resetDown(); // reset the left button
				//if ( tt < 10000 )
				//{
				//    tt +=10;
				//	//bsp_drawText(180, 86, "     ");	//一行最多39个字符
				//	bsp_drawNum_Format(188, 86, tt, "%05d");	//长度9*6
				//	LCDML.FUNC_setLoopInterval(tt);
			}
			if (LCDML.BT_checkEnter()) // check if button left is pressed
			{
				LCDML.BT_resetEnter(); // reset the left button
				//for(i = 0; i < 32; i++)
				//{
				//	s_ucTempBuff[i] = count++;
				//}
				//bsp_nRF24L01_TxData(s_ucTempBuff);
			}
		}
		//s_ucRxStatus = bsp_nRF24L01_RxData(s_ucTempBuff);

		/* 成功接收数据，将数据更新到TFT屏上 */
		while(nRF24L01_available())
		{	
			nRF24L01_read(s_ucTempBuff,32);
			//printf("Receive Data:\r\n");
			//for ( i = 0 ; i < 32 ; i++ )
			//{
			//    printf("%03d ",s_ucTempBuff[i]);
			//}
			//printf("\r\n");
		} 	
	}

	if(LCDML.FUNC_close())      // ****** STABLE END *********
	{
	// loop end
	// you can here reset some global vars or delete it
		Menu_DrawFrame();
	}
}

void Menu_nRF24L01_Monitor(uint8_t param)
{
	static u8 mode;

	if(LCDML.FUNC_setup())          // ****** SETUP *********
	{
		// setup
		// is called only if it is started
		
		// starts a trigger event for the loop function every 100 milliseconds
		LCDML.FUNC_setLoopInterval(1);
		bsp_Init_nRF24L01();
		mode = 0;
		nRF24L01_Scan(mode);
		mode++;
	}

	if(LCDML.FUNC_loop())           // ****** LOOP *********
	{
		// loop
		// is called when it is triggered
		// - with LCDML_DISP_triggerMenu( milliseconds )
		// - with every button status change

		// check if any button is pressed (enter, up, down, left, right)
		if(LCDML.BT_checkAny()) 
		{
			if (LCDML.BT_checkLeft()) // check if button left is pressed
			{
				LCDML.BT_resetLeft(); // reset the left button
			}
			if (LCDML.BT_checkRight()) // check if button left is pressed
			{
				LCDML.BT_resetRight(); // reset the left button
			}
			if (LCDML.BT_checkUp()) // check if button left is pressed
			{
				LCDML.BT_resetUp(); // reset the left button
			}
			if (LCDML.BT_checkDown()) // check if button left is pressed
			{
				LCDML.BT_resetDown(); // reset the left button
			}
			if (LCDML.BT_checkEnter()) // check if button left is pressed
			{
				LCDML.BT_resetEnter(); // reset the left button
				if ( mode == 1 )
				{
				    mode = 2;
				}
				else if (mode == 2)
				{
					mode = 3;
				}
				
			}
		}
		
		nRF24L01_Scan(mode);
		if ( mode == 3 )
		{
		    mode = 1;
		}
	}
	if(LCDML.FUNC_close())   
	{
		Menu_DrawFrame();
	}
}

void Menu_CC1101_TX(uint8_t param)
{
	uint8_t s_ucTempBuff[32]; /* 数据接收或者发送缓冲 */
	static uint8_t count = 0;
	static uint8_t autoflag = 0;
	static uint16_t tt = 100;
	uint8_t i;
	if(LCDML.FUNC_setup())          // ****** SETUP *********
	{
		// setup
		// is called only if it is started

		// starts a trigger event for the loop function every 100 milliseconds
		LCDML.FUNC_setLoopInterval(tt);

		bsp_Init_CC1101();
		CC1101_Reset();
		CC1101_RegConfig();
		CC1101_setPA(PA_0dBm);
		
		bsp_fillRect2(2, 30, 317, 225, _LCDML_DISP_bgcolor);
		bsp_setTextSize(1);
		bsp_setTextColor(_LCDML_DISP_fcolor);
		bsp_drawText(2, 36, "  Press OK:    Send 32 Byte       ");	//一行最多39个字符
		bsp_drawText(2, 46, "  Press Left:  Auto Send Data     ");	//一行最多39个字符
		bsp_drawText(2, 56, "  Press Right: Stop Auto Send     ");	//一行最多39个字符
		bsp_drawText(2, 66, "  Press Up:    Time Interval -10ms");	//一行最多39个字符
		bsp_drawText(2, 76, "  Press Down:  Time Interval +10ms");	//一行最多39个字符

		//CC1101_writeCmd(CC1101_STX);
		//nRF24L01_powerUp();
		//bsp_nRF24L01_TxMode();
	}

	if(LCDML.FUNC_loop())           // ****** LOOP *********
	{
		// loop
		// is called when it is triggered
		// - with LCDML_DISP_triggerMenu( milliseconds )
		// - with every button status change

		// check if any button is pressed (enter, up, down, left, right)
		if(LCDML.BT_checkAny()) 
		{
			if (LCDML.BT_checkLeft()) // check if button left is pressed
			{
				LCDML.BT_resetLeft(); // reset the left button
				bsp_setTextColor2(_LCDML_DISP_scolor, _LCDML_DISP_bgcolor);
				bsp_lcd_setCursor(2,86);
				bsp_lcd_printf("  Auto Send...  Time Interval: %5dms",tt);
				autoflag = 1;
			}
			if (LCDML.BT_checkRight()) // check if button left is pressed
			{
				LCDML.BT_resetRight(); // reset the left button
				autoflag = 0;
			}
			if (LCDML.BT_checkUp()) // check if button left is pressed
			{
				LCDML.BT_resetUp(); // reset the left button
				if ( tt > 10 )
				{
				    tt -=10;
					bsp_lcd_setCursor(2,86);
					bsp_lcd_printf("  Auto Send...  Time Interval: %5dms",tt);
					LCDML.FUNC_setLoopInterval(tt);
				}
			}
			if (LCDML.BT_checkDown()) // check if button left is pressed
			{
				LCDML.BT_resetDown(); // reset the left button
				if ( tt < 10000 )
				{
				    tt +=10;
					bsp_lcd_setCursor(2,86);
					bsp_lcd_printf("  Auto Send...  Time Interval: %5dms",tt);
					LCDML.FUNC_setLoopInterval(tt);
				}
			}
			if (LCDML.BT_checkEnter()) // check if button left is pressed
			{
				LCDML.BT_resetEnter(); // reset the left button
				for(i = 0; i < 32; i++)
				{
					s_ucTempBuff[i] = count++;
				}
				//nRF24L01_writeFast2(s_ucTempBuff, 32);
				CC1101_sendPacket(s_ucTempBuff,32);
				//CC1101_setIdle();
				//bsp_nRF24L01_TxData(s_ucTempBuff);
			}
		}
		if(autoflag)
		{
			for(i = 0; i < 32; i++)
			{
				s_ucTempBuff[i] = count++;
			}
			CC1101_sendPacket(s_ucTempBuff,32);
				//CC1101_setIdle();
		}
	}

	if(LCDML.FUNC_close())      // ****** STABLE END *********
	{
	// loop end
	// you can here reset some global vars or delete it
		autoflag = 0;
		Menu_DrawFrame();
	}
}

void Menu_CC1101_RX(uint8_t param)
{
	uint8_t s_ucTempBuff[32]; /* 数据接收或者发送缓冲 */
	//uint8_t s_ucRxStatus; 
	//uint8_t TX_ADDRESS[5] = {0x34,0x43,0x10,0x10,0x01};  
//	static uint8_t count = 0;
	//static uint8_t autoflag = 0;
//	static uint16_t tt = 500;
	uint8_t i;
	if(LCDML.FUNC_setup())          // ****** SETUP *********
	{
		// setup
		// is called only if it is started

		// starts a trigger event for the loop function every 100 milliseconds
		LCDML.FUNC_setLoopInterval(1);
		
		bsp_Init_CC1101();
		CC1101_Reset();
		CC1101_RegConfig();
		CC1101_setPA(PA_0dBm);
		CC1101_writeReg(CC1101_IOCFG0, 06);
		CC1101_setRXMode();

		bsp_fillRect2(2, 30, 317, 225, _LCDML_DISP_bgcolor);
	}

	if(LCDML.FUNC_loop())           // ****** LOOP *********
	{
		// loop
		// is called when it is triggered
		// - with LCDML_DISP_triggerMenu( milliseconds )
		// - with every button status change

		// check if any button is pressed (enter, up, down, left, right)
		if(LCDML.BT_checkAny()) 
		{
			if (LCDML.BT_checkLeft()) // check if button left is pressed
			{
				LCDML.BT_resetLeft(); // reset the left button
				//bsp_setTextColor2(_LCDML_DISP_scolor, _LCDML_DISP_bgcolor);
				//bsp_drawText(2, 86, "  Auto Send...  Time Interval:      ms");	//一行最多39个字符
				//bsp_drawNum_Format(188, 86, tt, "%05d");	//长度9*6
				//autoflag = 1;
			}
			if (LCDML.BT_checkRight()) // check if button left is pressed
			{
				LCDML.BT_resetRight(); // reset the left button
				//autoflag = 0;
			}
			if (LCDML.BT_checkUp()) // check if button left is pressed
			{
				LCDML.BT_resetUp(); // reset the left button
				//if ( tt > 10 )
				//{
				//    tt -=10;
				//	//bsp_drawText(180, 86, "     ");	//一行最多39个字符
				//	bsp_drawNum_Format(188, 86, tt, "%05d");	//长度9*6
				//	LCDML.FUNC_setLoopInterval(tt);
				//}
			}
			if (LCDML.BT_checkDown()) // check if button left is pressed
			{
				LCDML.BT_resetDown(); // reset the left button
				//if ( tt < 10000 )
				//{
				//    tt +=10;
				//	//bsp_drawText(180, 86, "     ");	//一行最多39个字符
				//	bsp_drawNum_Format(188, 86, tt, "%05d");	//长度9*6
				//	LCDML.FUNC_setLoopInterval(tt);
			}
			if (LCDML.BT_checkEnter()) // check if button left is pressed
			{
				LCDML.BT_resetEnter(); // reset the left button
				//for(i = 0; i < 32; i++)
				//{
				//	s_ucTempBuff[i] = count++;
				//}
				//bsp_nRF24L01_TxData(s_ucTempBuff);
			}
		}
		//s_ucRxStatus = bsp_nRF24L01_RxData(s_ucTempBuff);

		/* 成功接收数据，将数据更新到TFT屏上 */
		while(CC1101_available())
		{	
			CC1101_read(s_ucTempBuff,32);
			//printf("Receive Data:\r\n");
			//for ( i = 0 ; i < 32 ; i++ )
			//{
			//    printf("%03d ",s_ucTempBuff[i]);
			//}
			//printf("\r\n");
			bsp_LedToggle(3);
			CC1101_setRXMode();
		} 	
	}

	if(LCDML.FUNC_close())      // ****** STABLE END *********
	{
	// loop end
	// you can here reset some global vars or delete it
		Menu_DrawFrame();
	}
}

void Menu_Lora_TX(uint8_t param)
{
	uint8_t s_ucTempBuff[32]; /* 数据接收或者发送缓冲 */
	static uint8_t count = 0;
	static uint8_t autoflag = 0;
	static uint16_t tt = 100;
	uint8_t i;
	if(LCDML.FUNC_setup())          // ****** SETUP *********
	{
		// setup
		// is called only if it is started

		// starts a trigger event for the loop function every 100 milliseconds
		LCDML.FUNC_setLoopInterval(tt);

		bsp_Init_Lora();
		Lora_RegConfig();
		
		bsp_fillRect2(2, 30, 317, 225, _LCDML_DISP_bgcolor);
		bsp_setTextSize(1);
		bsp_setTextColor(_LCDML_DISP_fcolor);
		bsp_drawText(2, 36, "  Press OK:    Send 32 Byte       ");	//一行最多39个字符
		bsp_drawText(2, 46, "  Press Left:  Auto Send Data     ");	//一行最多39个字符
		bsp_drawText(2, 56, "  Press Right: Stop Auto Send     ");	//一行最多39个字符
		bsp_drawText(2, 66, "  Press Up:    Time Interval -10ms");	//一行最多39个字符
		bsp_drawText(2, 76, "  Press Down:  Time Interval +10ms");	//一行最多39个字符

		//CC1101_writeCmd(CC1101_STX);
		//nRF24L01_powerUp();
		//bsp_nRF24L01_TxMode();
	}

	if(LCDML.FUNC_loop())           // ****** LOOP *********
	{
		// loop
		// is called when it is triggered
		// - with LCDML_DISP_triggerMenu( milliseconds )
		// - with every button status change

		// check if any button is pressed (enter, up, down, left, right)
		if(LCDML.BT_checkAny()) 
		{
			if (LCDML.BT_checkLeft()) // check if button left is pressed
			{
				LCDML.BT_resetLeft(); // reset the left button
				bsp_setTextColor2(_LCDML_DISP_scolor, _LCDML_DISP_bgcolor);
				bsp_lcd_setCursor(2,86);
				bsp_lcd_printf("  Auto Send...  Time Interval: %5dms",tt);
				autoflag = 1;
			}
			if (LCDML.BT_checkRight()) // check if button left is pressed
			{
				LCDML.BT_resetRight(); // reset the left button
				autoflag = 0;
			}
			if (LCDML.BT_checkUp()) // check if button left is pressed
			{
				LCDML.BT_resetUp(); // reset the left button
				if ( tt > 10 )
				{
				    tt -=10;
					bsp_lcd_setCursor(2,86);
					bsp_lcd_printf("  Auto Send...  Time Interval: %5dms",tt);
					LCDML.FUNC_setLoopInterval(tt);
				}
			}
			if (LCDML.BT_checkDown()) // check if button left is pressed
			{
				LCDML.BT_resetDown(); // reset the left button
				if ( tt < 10000 )
				{
				    tt +=10;
					bsp_lcd_setCursor(2,86);
					bsp_lcd_printf("  Auto Send...  Time Interval: %5dms",tt);
					LCDML.FUNC_setLoopInterval(tt);
				}
			}
			if (LCDML.BT_checkEnter()) // check if button left is pressed
			{
				LCDML.BT_resetEnter(); // reset the left button
				for(i = 0; i < 32; i++)
				{
					s_ucTempBuff[i] = i;
				}
				Lora_beginPacket(FALSE);
				//Lora_writeBuf("Hello", 6);
				Lora_writeBuf(s_ucTempBuff, 32);
				Lora_endPacket();
			}
		}
		if(autoflag)
		{
			for(i = 0; i < 32; i++)
			{
				s_ucTempBuff[i] = count++;
			}
			Lora_beginPacket(FALSE);
			Lora_writeBuf(s_ucTempBuff, 32);
			Lora_endPacket();
		}

		/* 成功接收数据，将数据更新到TFT屏上 */
		while(CC1101_available())
		{	
			CC1101_read(s_ucTempBuff,32);
			//printf("Receive Data:\r\n");
			//for ( i = 0 ; i < 32 ; i++ )
			//{
			//    printf("%03d ",s_ucTempBuff[i]);
			//}
			//printf("\r\n");
			bsp_LedToggle(3);
			CC1101_setRXMode();
		}
	}

	if(LCDML.FUNC_close())      // ****** STABLE END *********
	{
	// loop end
	// you can here reset some global vars or delete it
		autoflag = 0;
		Menu_DrawFrame();
	}
}

void Menu_Lora_RX(uint8_t param)
{
	uint8_t s_ucTempBuff[32]; /* 数据接收或者发送缓冲 */
	uint8_t temp;
	//uint8_t s_ucRxStatus; 
	//uint8_t TX_ADDRESS[5] = {0x34,0x43,0x10,0x10,0x01};  
//	static uint8_t count = 0;
	//static uint8_t autoflag = 0;
//	static uint16_t tt = 500;

	uint8_t i;
	if(LCDML.FUNC_setup())          // ****** SETUP *********
	{
		// setup
		// is called only if it is started

		// starts a trigger event for the loop function every 100 milliseconds
		LCDML.FUNC_setLoopInterval(1);
		
		bsp_Init_Lora();
		Lora_RegConfig();

		bsp_fillRect2(2, 30, 317, 225, _LCDML_DISP_bgcolor);
	}

	if(LCDML.FUNC_loop())           // ****** LOOP *********
	{
		// loop
		// is called when it is triggered
		// - with LCDML_DISP_triggerMenu( milliseconds )
		// - with every button status change

		// check if any button is pressed (enter, up, down, left, right)
		if(LCDML.BT_checkAny()) 
		{
			if (LCDML.BT_checkLeft()) // check if button left is pressed
			{
				LCDML.BT_resetLeft(); // reset the left button
				//bsp_setTextColor2(_LCDML_DISP_scolor, _LCDML_DISP_bgcolor);
				//bsp_drawText(2, 86, "  Auto Send...  Time Interval:      ms");	//一行最多39个字符
				//bsp_drawNum_Format(188, 86, tt, "%05d");	//长度9*6
				//autoflag = 1;
			}
			if (LCDML.BT_checkRight()) // check if button left is pressed
			{
				LCDML.BT_resetRight(); // reset the left button
				//autoflag = 0;
			}
			if (LCDML.BT_checkUp()) // check if button left is pressed
			{
				LCDML.BT_resetUp(); // reset the left button
				//if ( tt > 10 )
				//{
				//    tt -=10;
				//	//bsp_drawText(180, 86, "     ");	//一行最多39个字符
				//	bsp_drawNum_Format(188, 86, tt, "%05d");	//长度9*6
				//	LCDML.FUNC_setLoopInterval(tt);
				//}
			}
			if (LCDML.BT_checkDown()) // check if button left is pressed
			{
				LCDML.BT_resetDown(); // reset the left button
				//if ( tt < 10000 )
				//{
				//    tt +=10;
				//	//bsp_drawText(180, 86, "     ");	//一行最多39个字符
				//	bsp_drawNum_Format(188, 86, tt, "%05d");	//长度9*6
				//	LCDML.FUNC_setLoopInterval(tt);
			}
			if (LCDML.BT_checkEnter()) // check if button left is pressed
			{
				LCDML.BT_resetEnter(); // reset the left button
				//for(i = 0; i < 32; i++)
				//{
				//	s_ucTempBuff[i] = count++;
				//}
				//bsp_nRF24L01_TxData(s_ucTempBuff);
			}
		}
		//s_ucRxStatus = bsp_nRF24L01_RxData(s_ucTempBuff);

		/* 成功接收数据，将数据更新到TFT屏上 */
		while(Lora_available())
		{	
			temp = Lora_read();
			printf("Receive Data%d:\r\n", &temp);
			//printf("Receive Data:\r\n");
			//for ( i = 0 ; i < 32 ; i++ )
			//{
			//    printf("%03d ",s_ucTempBuff[i]);
			//}
			//printf("\r\n");
			bsp_LedToggle(3);
			//CC1101_setRXMode();
		} 	
	}

	if(LCDML.FUNC_close())      // ****** STABLE END *********
	{
	// loop end
	// you can here reset some global vars or delete it
		Menu_DrawFrame();
	}
}

void Menu_RGBLED(uint8_t param)
{
	static uint16_t tt = 500;
	uint8_t i;  
	static uint16_t bright = 50;
	if(LCDML.FUNC_setup())          // ****** SETUP *********
	{
		// setup
		// is called only if it is started

		// starts a trigger event for the loop function every 100 milliseconds
		LCDML.FUNC_setLoopInterval(tt);
		bsp_Init_RgbLed();
		bsp_RGB_ledoff();
		
		bsp_fillRect2(2, 30, 317, 225, _LCDML_DISP_bgcolor);
		bsp_setTextSize(1);
		bsp_setTextColor(_LCDML_DISP_fcolor);
		bsp_drawText(2, 36, "  Press OK:    Send 32 Byte       ");	//一行最多39个字符
		bsp_drawText(2, 46, "  Press Left:  Auto Send Data     ");	//一行最多39个字符
		bsp_drawText(2, 56, "  Press Right: Stop Auto Send     ");	//一行最多39个字符
		bsp_drawText(2, 66, "  Press Up:    RGBLED OFF         ");	//一行最多39个字符
		bsp_drawText(2, 76, "  Press Down:  RGBLED OFF         ");	//一行最多39个字符
	}

	if(LCDML.FUNC_loop())           // ****** LOOP *********
	{
		// loop
		// is called when it is triggered
		// - with LCDML_DISP_triggerMenu( milliseconds )
		// - with every button status change

		// check if any button is pressed (enter, up, down, left, right)
		if(LCDML.BT_checkAny()) 
		{
			if (LCDML.BT_checkLeft()) // check if button left is pressed
			{
				LCDML.BT_resetLeft(); // reset the left button
				bsp_RGB_colorWipe(0xff0000, 10);
			}
			if (LCDML.BT_checkRight()) // check if button left is pressed
			{
				LCDML.BT_resetRight(); // reset the left button
				bsp_RGB_colorWipe(0x00ff00, 10);
			}
			if (LCDML.BT_checkUp()) // check if button left is pressed
			{
				LCDML.BT_resetUp(); // reset the left button
				if ( bright < 246 )
				{
				    bright += 10;
				}
				bsp_RGB_setBrightness(bright);
			}
			if (LCDML.BT_checkDown()) // check if button left is pressed
			{
				LCDML.BT_resetDown(); // reset the left button
				if ( bright > 10 )
				{
				    bright -= 10;
				}
				bsp_RGB_setBrightness(bright);
			}
			if (LCDML.BT_checkEnter()) // check if button left is pressed
			{
				LCDML.BT_resetEnter(); // reset the left button
				bsp_RGB_ledoff();
			}
		}
	}

	if(LCDML.FUNC_close())      // ****** STABLE END *********
	{
	// loop end
	// you can here reset some global vars or delete it
		Menu_DrawFrame();
	}
}
#endif

