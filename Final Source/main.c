#include "include.h"

//2015年6月29日17:43:06。P7口为矩阵键盘口，P0.7口为矩阵键盘提供中断。P6口为LCD的数据口，P5的高位口为LCD的控制端口。
//当前系统时钟22.1184MHz
//波特率115200bps
//可以改名称和密码。qiandashuaier  Summer123456
//当前最终版。可正常运行。
#define CYCLE 1200
sbit LED0=P3^1;
sbit LED1=P3^2;
sbit LED2=P3^3;
uchar i;
void Dbreathe(uint t)
{
	while(--t);
}
void main()
{
	uint PWM_LOW=0;
	Init_Device();
	delay(400);
	screen_draw();
	P7=0xf0;
	LED0=0;LED1=0;LED2=0;
	while(1)//放入在特定设置下需要循环测试的代码
	{
		 
		 if((pwm_on==1)&&(screen_present==0))
		 {
			if(breathe_now==0)
			{
				LED0=1;LED1=0;LED2=0;
	 			Dbreathe(6000);    
	 			for(PWM_LOW=1;PWM_LOW<CYCLE;PWM_LOW++)
				{ 
	 				LED0=0;Dbreathe(PWM_LOW);LED0=1;Dbreathe((CYCLE-PWM_LOW));
				}
	 			LED0=0;
				Dbreathe(6000);Dbreathe(6000);Dbreathe(6000);
	 			for(PWM_LOW=CYCLE-1;PWM_LOW>0;PWM_LOW--)
				{ 
		   			LED0=0;Dbreathe(PWM_LOW);LED0=1;Dbreathe(CYCLE-PWM_LOW);
	   			}
			}
			if(breathe_now==1)
			{
				LED1=1;LED2=0;LED0=0;Dbreathe(6000);    
	 			for(PWM_LOW=1;PWM_LOW<CYCLE;PWM_LOW++)
				{ 
	 				LED1=0;Dbreathe(PWM_LOW);LED1=1;Dbreathe((CYCLE-PWM_LOW));
				}
	 			LED1=0;
				Dbreathe(6000);	Dbreathe(6000);Dbreathe(6000);
	 			for(PWM_LOW=CYCLE-1;PWM_LOW>0;PWM_LOW--)
				{ 
		   			LED1=0;Dbreathe(PWM_LOW);LED1=1;Dbreathe(CYCLE-PWM_LOW);
	   			}
			}
			if(breathe_now==2)
			{
				LED2=1;LED1=0;LED0=0;
	 			Dbreathe(6000);    
	 			for(PWM_LOW=1;PWM_LOW<CYCLE;PWM_LOW++)
				{ 
	 				LED2=0;Dbreathe(PWM_LOW);LED2=1;Dbreathe((CYCLE-PWM_LOW));
				}
	 			LED2=0;
				Dbreathe(6000);Dbreathe(6000);Dbreathe(6000);
	 			for(PWM_LOW=CYCLE-1;PWM_LOW>0;PWM_LOW--)
				{ 
		   			LED2=0;Dbreathe(PWM_LOW);LED2=1;Dbreathe(CYCLE-PWM_LOW);
	   			}
			}	
  		}
		else
		{
			LED0=0;
			LED1=0;
			LED2=0;
		}
		if(UART_command!=0)
		{
			UART_Process();		
		}
		if(send_param==1)
		{
			for(i=0;i<5;i++)
			{
				UART_SendH(led[i]%16);
				UART_SendH(0x01);
				UART_SendH(volt[i]/1000);
				UART_SendH((volt[i]%1000)/10);
				UART_SendH(current[i]/10);
				UART_SendH(current[i]%10);
				UART_SendH(power[i]/10);
				UART_SendH(power[i]%10);
			}
			UART_SendH(temperature/10);
			UART_SendH(temperature%10);
			delay_1s();
			//delay_1s();
		}	
   	}
}