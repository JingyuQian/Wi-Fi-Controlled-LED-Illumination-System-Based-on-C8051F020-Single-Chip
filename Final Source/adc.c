#include "include.h"
#define INT_DEC 100
uint volt[5];
uchar current[5];
long power[5];
uchar volt1,volt2,volt3,volt4;
uchar power1,power2,power3;
uchar circle=0;
uchar data int_dec=INT_DEC;

/*void adc0change(uchar i)
{
	AD0EN=0;
	delay(20);
	AMX0SL=i+1;
	AD0EN=1;
} */
void adc0int(void) interrupt 15
{
	float data result;
	uchar data i;
	AD0INT=0;
	int_dec--;
	if(int_dec==0)
	{
		int_dec=INT_DEC;
		AD0EN=0;
		delay(20);
		AMX0SL=circle+1;

		result=(ADC0H<<8)|ADC0L;
		result=result/4095*2430;
		
		volt[circle]=2*result;//4位		 除以100发出
		current[circle]=(3360-volt[circle])/17; //假设电阻恒定170欧姆	 直接发
		power[circle]=volt[circle]*current[circle]/100;		  //直接发
		
		volt1=volt[led_select]/1000;
		volt2=(volt[led_select]/100)%10;
		volt3=(volt[led_select]/10)%10;
		volt4=volt[led_select]%10;
		power1=(power[led_select]/100)%10;
		power2=(power[led_select]/10)%10;
		power3=power[led_select]%10;

	   	circle=(circle+1)%5;

		if((screen_present==2)&&(screen_level==1))
		{
			for(i=0;i<10;i++)dis_temp(ds18b20_gettemp());
			delay(80);
			lcd_pos(1,3);write_dat(number[volt1]);
			lcd_pos(1,4);write_dat(number[volt2]);
			lcd_pos(1,5);write_dat(number[volt3]);
			lcd_pos(1,6);write_dat(number[volt4]);
			lcd_pos(2,3);write_dat(number[power1]);
			lcd_pos(2,4);write_dat(number[power2]);
			lcd_pos(2,5);write_dat('.');
			lcd_pos(2,6);write_dat(number[power3]);
		}
		AD0EN=1;
		temperature=ds18b20_gettemp();
	}		
}
