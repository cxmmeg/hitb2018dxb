#ifndef __BSP_MENU_H__
#define __BSP_MENU_H__

#ifdef __cplusplus
 extern "C" {
#endif 

void Menu_Init(void);
void Menu_Loop(void);
void Menu_DrawFrame(void);
void Menu_UpdateFrame(void);
void mFunc_about(uint8_t param);
void mFunc_Lora_TX(uint8_t param);
void mFunc_confagenda27(uint8_t param);
void mFunc_confagenda28(uint8_t param);
void mFunc_commsecagenda27(uint8_t param);
void mFunc_commsecagenda28(uint8_t param);
void mFunc_game(uint8_t param);
void mFunc_lcd_setlight(uint8_t param);
void mFunc_activities(uint8_t param);
void mFunc_secret(uint8_t param);
void mFunc_ledcontrol(uint8_t param);


//void mFunc_agenda(uint8_t param);
//void mFunc_lcd_setlight(uint8_t param);
//void mFunc_secret(uint8_t param);
//void mFunc_guess_num(uint8_t param);
//void mFunc_light(uint8_t param);
//void Menu_nRF24L01_TX(uint8_t param);
//void Menu_nRF24L01_RX(uint8_t param);
//void Menu_nRF24L01_Monitor(uint8_t param);
//void Menu_CC1101_TX(uint8_t param);
//void Menu_CC1101_RX(uint8_t param);
//void Menu_Lora_TX(uint8_t param);
//void Menu_Lora_RX(uint8_t param);
//void Menu_RGBLED(uint8_t param);


#ifdef __cplusplus
		}
#endif /* __cplusplus */
	
	
#endif /* __BSP_MENU_H__ */




