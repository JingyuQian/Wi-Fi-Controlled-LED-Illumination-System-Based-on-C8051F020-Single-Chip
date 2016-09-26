#include "include.h"

uchar idata Buf[20]; //����������ݻ���
uchar idata SendCounter=0;//�����±����
uchar idata UART_command=0;//0����������1��������ƣ�2���������
uchar idata new_name[20];
uchar idata new_code[20];
bit idata send_param=0;

void delay_1s(void)   //��� -0.000000000125us
{
    unsigned char a,b,c,n;
    for(c=217;c>0;c--)
        for(b=225;b>0;b--)
            for(a=225;a>0;a--);
    for(n=10;n>0;n--);
}
/*��������: void UART_SendData(u8 *data_buf) ���ڷ����ַ�������*/
void UART_SendData(uchar *data_buf)
{
	uchar iSendCounter = 0;
	
	while(data_buf[iSendCounter] != '\0')
	{
		SBUF0 = data_buf[iSendCounter];	
		while(!TI0);  //������˳�ѭ��֮��϶����Ƚ����жϣ������ж����Ҳ���TI0���㣬����һ���жϣ�����������
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
	if(UART_command==1)//��SSID
	{
		strcat(send_ssid,new_name);
		strcat(send_ssid,",CH1\n");
		UART_SendData(send_ssid);
	}
	if(UART_command==2)	   //������
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
	UART_command=0;//��0��ʾһ����Ϣ�������

	write_cmd(0x01);
	lcd_pos(1,0);
	dis_string(dis24);
	lcd_pos(2,0);
	dis_string(dis25);
	delay(50000);delay(50000);delay(50000);
	screen_draw();
}

/*UART�����жϳ���*/
void Serial_Interrupt() interrupt 4//�ս��������ݿ��������¼���:�صƵ����ݡ�����͸�����䡢�����롢��IDʱ��wifiоƬ������������ 
{
	uchar id,level;
	uchar i;
	if(RI0==1)// �������Դ��ڵ���Ϣ
	{	    
    	RI0=0; //�����������ж�
		if(SendCounter==21) SendCounter=0;
		Buf[SendCounter]=SBUF0; //ȡ����
		SendCounter++;//�����±�������ʹ��һ���������ݴ浽�������һλ��

	}
	//����ǿصƣ���ֱ�����жϺ���������ǰ��Ҫ������λ���ݽ��еƵĿ���
	if((Buf[0]==0x01)&&(SendCounter==2))//�����������������ҵ�һ�ֽ�0x01��ʱ����ζ��Ҫ����
	{
		led_pwm(Buf[1]);//����pwm���ƺ����Եƽ��п���
		id=Buf[1]/16; //�õ������ƵƵ�id
		level=Buf[1]%16;//�õ������ƵƵ�Ŀ������
		led_select=id-1;	  //�޸ĵ�ǰѡ�еĵ�
		led[led_select]=level;					//�޸ĵ�ǰѡ�еƵ�����
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



