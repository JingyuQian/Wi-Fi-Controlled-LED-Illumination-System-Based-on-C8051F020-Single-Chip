#include "include.h"

uchar idata Buf[20]; //定义接收数据缓存
uchar idata SendCounter=0;//数组下标变量
uchar idata UART_command=0;//0代表无请求，1代表改名称，2代表改密码
uchar idata new_name[20];
uchar idata new_code[20];
bit idata send_param=0;

void delay_1s(void)   //误差 -0.000000000125us
{
    unsigned char a,b,c,n;
    for(c=217;c>0;c--)
        for(b=225;b>0;b--)
            for(a=225;a>0;a--);
    for(n=10;n>0;n--);
}
/*函数名称: void UART_SendData(u8 *data_buf) 串口发送字符串数据*/
void UART_SendData(uchar *data_buf)
{
	uchar iSendCounter = 0;
	
	while(data_buf[iSendCounter] != '\0')
	{
		SBUF0 = data_buf[iSendCounter];	
		while(!TI0);  //当这边退出循环之后肯定率先进入中断，而在中断中我不让TI0清零，白跑一次中断，在外面清零
        TI0=0;
		iSendCounter++;
	} 
}

void UART_SendH(uchar data_buf)
{
	SBUF0 = data_buf;	
	while(!TI0);
    TI0=0;
}

void UART_Process(void)
{
	uchar send_ssid[45]={"AT+WAP=11BGN,"};
	uchar send_password[45]={"AT+WAKEY=WPA2PSK,AES,"};
	uchar pre_send[]={"AT+WMODE=AP\n"};
	UART_SendData("+++");
	delay_1s();
	UART_SendData("a");
	delay_1s();
	UART_SendData(pre_send);
	delay_1s();
	if(UART_command==1)//改SSID
	{
		strcat(send_ssid,new_name);
		strcat(send_ssid,",CH1\n");
		UART_SendData(send_ssid);
	}
	if(UART_command==2)	   //改密码
	{
		strcat(send_password,new_code);
		strcat(send_password,"\n");
		UART_SendData(send_password);
	}
	//}		
	delay_1s();
	UART_SendData("AT+Z\n");
	delay_1s();
		
	//}
	UART_command=0;//置0表示一次信息处理结束

	write_cmd(0x01);
	lcd_pos(1,0);
	dis_string(dis24);
	lcd_pos(2,0);
	dis_string(dis25);
	delay(50000);delay(50000);delay(50000);
	screen_draw();
}

/*UART接收中断程序*/
void Serial_Interrupt() interrupt 4//收进来的数据可能有如下几种:控灯的数据、进入透明传输、改密码、改ID时从wifi芯片传回来的数据 
{
	uchar id,level;
	uchar i;
	if(RI0==1)// 接收来自串口的信息
	{	    
    	RI0=0; //软件清除接收中断
		if(SendCounter==21) SendCounter=0;
		Buf[SendCounter]=SBUF0; //取数据
		SendCounter++;//数组下标自增，使下一个接收数据存到数组的下一位置

	}
	//如果是控灯，则直接在中断函数处理，当前需要利用两位数据进行灯的控制
	if((Buf[0]==0x01)&&(SendCounter==2))//当发现收了两数据且第一字节0x01的时候，意味着要调灯
	{
		led_pwm(Buf[1]);//调用pwm控制函数对灯进行控制
		id=Buf[1]/16; //得到被控制灯的id
		level=Buf[1]%16;//得到被控制灯的目标亮度
		led_select=id-1;	  //修改当前选中的灯
		led[led_select]=level;					//修改当前选中灯的亮度
		if((screen_present==1)&&(screen_level==1))
		{
			lcd_pos(3,0);
			dis_led();
		}
		SendCounter=0;
	}
	if((Buf[0]==0x02)&&(SendCounter==21))
	{
		for (i=0; i<20; i++)
		{
			if(Buf[i+1]!='\0')
			{
				new_name[i]=Buf[i+1];
			}
			else break;
		}
		UART_command=1;
		SendCounter=0;
		write_cmd(0x01);lcd_pos(0,0);dis_string(dis26);
		delay(50000);
	}
	if((Buf[0]==0x03)&&(SendCounter==21))
	{
		for (i=0; i<20; i++)
		{
			if(Buf[i+1]!='\0')
			{
				new_code[i]=Buf[i+1];
			}
			else break;
		}
		UART_command=2;
		SendCounter=0;
		write_cmd(0x01);lcd_pos(0,0);dis_string(dis26);
		delay(50000);
	}
	if(Buf[0]==0x04)
	{
		send_param=1;
	   	SendCounter=0;
	}
	if(Buf[0]==0x05)
	{
		send_param=0;
		SendCounter=0;
	}
}



