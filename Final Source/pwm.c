/*P2为输出口*/
#include "include.h"
sfr led_1=0xfa;
sfr led_2=0xfb;
sfr led_3=0xfc;
sfr led_4=0xfd;
sfr led_5=0xfe;
sfr onoff_1=0xda;
sfr onoff_2=0xdb;
sfr onoff_3=0xdc;
sfr onoff_4=0xdd;
sfr onoff_5=0xde;


void led_pwm(uchar command)//0位关，1,2,3,   4为开
{
	uchar id=command/16;
	uchar level=command%16;
	uchar highvalue;
	if(level==0)
	{
		switch(id)
		{
			case 1: onoff_1&=0xbf;break;
			case 2: onoff_2&=0xbf;break;
			case 3: onoff_3&=0xbf;break;
			case 4: onoff_4&=0xbf;break;
			case 5: onoff_5&=0xbf;break;
			default: break;
		}
	}
	else
	{
		switch(level)
		{
			case 1:highvalue=FIVEPERCENT;break;
			case 2:highvalue=QUATER;break;
			case 3:highvalue=SIXTY;break;
			case 4:highvalue=ON;break;
			default: break;
		}
		switch(id)
		{
			case 1: led_1=highvalue;onoff_1|=0x40;break;
			case 2: led_2=highvalue;onoff_2|=0x40;break;
			case 3: led_3=highvalue;onoff_3|=0x40;break;
			case 4: led_4=highvalue;onoff_4|=0x40;break;
			case 5: led_5=highvalue;onoff_5|=0x40;break;
		default: break;
		}
	}
}