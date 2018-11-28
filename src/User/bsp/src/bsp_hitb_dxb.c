#include "bsp.h"

void hitb_dxb_led(uint8_t sel)
{
	switch ( sel )
	{
	    case 0 :
	        bsp_RGB_ledoff();
	        break;
	    case 1 :
	        bsp_RGB_setPixelColor(8, 0x00ff00);
			bsp_RGB_setPixelColor(9, 0x00ff00);
			bsp_RGB_setPixelColor(10, 0x00ff00);
			bsp_RGB_setPixelColor(11, 0x00ff00);
			bsp_RGB_Show();
	        break;
	    case 2 :
			bsp_RGB_setPixelColor(7, 0x00ff00);
			bsp_RGB_setPixelColor(12, 0x00ff00);
			bsp_RGB_Show();
	        break;
	    case 3 :
	        bsp_RGB_setPixelColor(6, 0x00ff00);
			bsp_RGB_setPixelColor(13, 0x00ff00);	
			bsp_RGB_Show();
	        break;
	    case 4 :
        	bsp_RGB_setPixelColor(5, 0x00ff00);
			bsp_RGB_setPixelColor(14, 0x00ff00);
			bsp_RGB_Show();
	        break;
	    case 5 :
	        bsp_RGB_setPixelColor(4, 0x00ff00);
			bsp_RGB_setPixelColor(15, 0x00ff00);
			bsp_RGB_Show();
	        break;
	    case 6 :
	        bsp_RGB_setPixelColor(16, 0x00ff00);
			bsp_RGB_Show();
	        break;
	    case 7 :
	        bsp_RGB_setPixelColor(3, 0x00ff00);
			bsp_RGB_Show();
	        break;
	    case 8 :
	        bsp_RGB_setPixelColor(2, 0x00ff00);
			bsp_RGB_setPixelColor(17, 0x00ff00);
			bsp_RGB_Show();
	        break;
	    case 9 :
	        bsp_RGB_setPixelColor(1, 0x00ff00);
			bsp_RGB_Show();
	        break;
	    case 10 :
	        bsp_RGB_setPixelColor(0, 0x00ff00);
			bsp_RGB_Show();
	        break;
		case 11 :
	        bsp_RGB_ledoff();
	        break;
		case 12:
			break;
	    default:
	        break;
	}
}

void hitb_dxb_led2(uint8_t sel)
{
	switch ( sel )
	{
	    case 0 :
	        bsp_RGB_ledoff();
			bsp_DelayMS(10);
			bsp_RGB_ledoff();
	        break;
	    case 1 :
	        bsp_RGB_colorWipe(0xff0000, 20);
	        break;
	    case 2 :
			bsp_RGB_colorWipe(0x00ff00, 20);
	        break;
	    case 3 :
	        bsp_RGB_colorWipe(0x0000ff, 20);
	        break;
	    case 4 :
        	bsp_RGB_rainbow(10);
	        break;
	    case 5 :
	        bsp_RGB_rainbowCycle(10);
	        break;
		case 6 :
			bsp_RGB_theaterChaseRainbow(3);
			bsp_DelayMS(100);
			bsp_RGB_ledoff();
			break;
	    case 7 :
	        bsp_RGB_ledoff();
			bsp_DelayMS(10);
			bsp_RGB_ledoff();
	        break;
	    default:
	        break;
	}
}
















