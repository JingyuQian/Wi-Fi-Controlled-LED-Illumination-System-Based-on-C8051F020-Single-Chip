#include <include.h>
//�����ϡ���������ʹ�á�
uchar idata led[]={0x14,0x24,0x34,0x44,0x54};
uchar idata led_lock[]={0x09,0x09,0x09,0x09,0x09};//09����������0a��������
uint idata led_code[5]={0,0,0,0,0};
uint idata led_entered;
uchar idata c_i=0;//��ʾ��ǰ��������һλ

uchar idata screen_present=0;//��������һ����Ļ.0Ϊ������1Ϊ��������2Ϊ�������3Ϊ��������4Ϊ˵����
uchar idata screen_level=0;//�鿴��ǰ��Ļ����
uchar idata led_select=0;//��ǰѡ��ĵ�
uchar idata temp,key=16;
bit pwm_on=0;
uchar idata breathe_now=2;

void delay_20ms(void)		  //���ھ���������õ�
{
    unsigned char a,b,c;
    for(c=195;c>0;c--)
        for(b=234;b>0;b--)
            for(a=2;a>0;a--);
    _nop_();  
    _nop_();  
}
uchar keyfind(void)
{
	
	P7=0xfe;//��һ��
    temp=P7;
    temp=temp&0xf0;
    if(temp!=0xf0)
	{
    	delay_20ms();
      	if(temp!=0xf0)
      	{
       		temp=P7;
        	switch(temp)
        	{
          		case 0xee:key=0;break;
				case 0xde:key=1;break;
				case 0xbe:key=2;break;
				case 0x7e:key=3;break;
				
         	}
     	}
    }
    P7=0xfd;
    temp=P7;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
    	delay_20ms();
      	if(temp!=0xf0)
      	{
        	temp=P7;
        	switch(temp)
        	{
          		case 0xed:key=4;break;
				case 0xdd:key=5;break;
				case 0xbd:key=6;break;
				case 0x7d:key=7;break;
				
         	}
      	}
   	}
    P7=0xfb;
    temp=P7;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      	delay_20ms();
      	if(temp!=0xf0)
      	{
        	temp=P7;
        	switch(temp)
        	{
          		case 0xeb:key=8;break;
				case 0xdb:key=9;break;
				case 0xbb:key=10;break;
				case 0x7b:key=11;break;
				
         	}
        }
    }
    P7=0xf7;
    temp=P7;
    temp=temp&0xf0;
    if(temp!=0xf0)
    {
      	delay_20ms();
      	if(temp!=0xf0)
      	{
        	temp=P7;
        	switch(temp)
        	{
          		case 0xe7:key=12;break;
				case 0xd7:key=13;break;
				case 0xb7:key=14;break;
				case 0x77:key=15;break;
				
         	}
      	}
	}
	delay(150);
	return key;
}

void keyprocess(uchar key)
{
	if(key==0)					//��ʾ����Ļ
	{
		if(screen_present==0)
		{
			screen_present=1;
			screen_level=1;
			screen_draw();
			dis_led();
		}
		if((screen_present==1)&&(screen_level==2))
		{
			if(c_i!=4)
			{
				if(led_lock[led_select]==0x09)
				{
					led_code[led_select]=led_code[led_select]*10;	
				}
				else 
				{
					led_entered*=10;
				}
				lcd_pos(1,c_i++);
				write_dat(48);
			}
		}
		if((screen_present==3)&&(screen_level>1))
		{
			if((c_i!=8)&&(screen_level==2))
			{
				new_name[c_i]=48;	
			}
			if((c_i!=8)&&(screen_level==3))
			{
				new_code[c_i]=48;
			}
			lcd_pos(1,c_i++);
			write_dat(48);
		}
	}
	if(key==1)
	{
		if(screen_present==0)//�����ؽ���
		{
			screen_present=2;
			screen_level=1;
			screen_draw();
			lcd_pos(0,1);
			write_dat(number[led_select]+1);
			lcd_pos(0,4);
			write_dat((led[led_select]%16)+48);
			lcd_pos(0,7);
			write_dat(led_lock[led_select]);			
		}
		if((screen_present==1)&&(screen_level==2))
		{
			if(c_i!=4)
			{
				if(led_lock[led_select]==0x09)
				{
					led_code[led_select]=led_code[led_select]*10+1;	
				}
				else 
				{
					led_entered=led_entered*10+1;
				}
			lcd_pos(1,c_i++);
			write_dat(49);
			}
		}
		if((screen_present==3)&&(screen_level>1))
		{
			if((c_i!=8)&&(screen_level==2))
			{
				new_name[c_i]=49;	
			}
			if((c_i!=8)&&(screen_level==3))
			{
				new_code[c_i]=49;
			}
			lcd_pos(1,c_i++);
			write_dat(49);
		}	
	}
	if(key==2)
	{
		if(screen_present==0)
		{
			screen_present=3;
			screen_level=1;
			write_cmd(0x01);
			lcd_pos(0,0);
			dis_string(dis7);
			lcd_pos(1,0);
			dis_string(dis8);
			lcd_pos(2,0);
			dis_string(dis9);
		}
		if((screen_present==1)&&(screen_level==2))
		{
			if(c_i!=4)
			{
				if(led_lock[led_select]==0x09)
				{
					led_code[led_select]=led_code[led_select]*10+2;	
				}
				else 
				{
					led_entered=led_entered*10+2;
				}
				lcd_pos(1,c_i++);
				write_dat(50);
			}
		}
		if((screen_present==3)&&(screen_level>1))
		{
			if((c_i!=8)&&(screen_level==2))
			{
				new_name[c_i]=50;	
			}
			if((c_i!=8)&&(screen_level==3))
			{
				new_code[c_i]=50;
			}
			lcd_pos(1,c_i++);
			write_dat(50);
		}
	}
	if(key==3)
	{
		if(screen_present==0)
		{
			screen_present=4;
			screen_level=1;
			screen_draw();	
		}
		if((screen_present==1)&&(screen_level==2))
		{
			if(c_i!=4)
			{
				if(led_lock[led_select]==0x09)
				{
					led_code[led_select]=led_code[led_select]*10+3;	
				}
				else 
				{
					led_entered=led_entered*10+3;
				}
				lcd_pos(1,c_i++);
				write_dat(51);
			}
		}
		if((screen_present==3)&&(screen_level>1))
		{
			if((c_i!=8)&&(screen_level==2))
			{
				new_name[c_i]=51;	
			}
			if((c_i!=8)&&(screen_level==3))
			{
				new_code[c_i]=51;
			}
			lcd_pos(1,c_i++);
			write_dat(51);
		}
   	}
	if(key==4)
	{
		if((screen_present==1)&&(screen_level==1))
		{
			if(led_select>0)
			{
				led_select--;
				dis_led();
			}
		}
		if((screen_present==1)&&(screen_level==2))
		{
			if(c_i!=4)
			{
				if(led_lock[led_select]==0x09)
				{
					led_code[led_select]=led_code[led_select]*10+4;	
				}
				else 
				{
					led_entered=led_entered*10+4;
				}
				lcd_pos(1,c_i++);
				write_dat(52);
			}
		}
		if((screen_present==2)&&(led_select>0))
		{
			led_select--;
			lcd_pos(0,1);
			write_dat(number[led_select]+1);
			lcd_pos(0,4);
			write_dat((led[led_select]%16)+48);
			lcd_pos(0,7);
			write_dat(led_lock[led_select]);
		}
		if((screen_present==3)&&(screen_level>1))
		{
			if((c_i!=8)&&(screen_level==2))
			{
				new_name[c_i]=52;	
			}
			if((c_i!=8)&&(screen_level==3))
			{
				new_code[c_i]=52;
			}
			lcd_pos(1,c_i++);
			write_dat(52);
		}	
	}
   	if(key==5)
	{
		if((screen_present==1)&&(screen_level==1))
		{
			if(led_select<4)
			{
				led_select++;
				dis_led();
			}
		}
		if((screen_present==1)&&(screen_level==2))
		{
			if(c_i!=4)
			{
				if(led_lock[led_select]==0x09)
				{
					led_code[led_select]=led_code[led_select]*10+5;	
				}
				else 
				{
					led_entered=led_entered*10+5;
				}
				lcd_pos(1,c_i++);
				write_dat(53);
			}
		}
		if((screen_present==2)&&(screen_level==1)&&(led_select<4))
		{
			led_select++;
			lcd_pos(0,1);
			write_dat(number[led_select]+1);
			lcd_pos(0,4);
			write_dat((led[led_select]%16)+48);
			lcd_pos(0,7);
			write_dat(led_lock[led_select]);
		}
		if((screen_present==3)&&(screen_level>1))
		{
			if((c_i!=8)&&(screen_level==2))
			{
				new_name[c_i]=53;	
			}
			if((c_i!=8)&&(screen_level==3))
			{
				new_code[c_i]=53;
			}
			lcd_pos(1,c_i++);
			write_dat(53);
		}
	}
	if(key==6)
	{
		if((screen_present==1)&&(screen_level==1)&&(led[led_select]%16!=0)&&(led_lock[led_select]!=0x0a))
		{
			led_pwm(--led[led_select]);
			dis_led();	
		}
		if((screen_present==1)&&(screen_level==2))
		{
			if(c_i!=4)
			{
				if(led_lock[led_select]==0x09)
				{
					led_code[led_select]=led_code[led_select]*10+6;	
				}
				else 
				{
					led_entered=led_entered*10+6;
				}
				lcd_pos(1,c_i++);
				write_dat(54);
			}
		}
		if((screen_present==3)&&(screen_level>1))
		{
			if((c_i!=8)&&(screen_level==2))
			{
				new_name[c_i]=54;	
			}
			if((c_i!=8)&&(screen_level==3))
			{
				new_code[c_i]=54;
			}
			lcd_pos(1,c_i++);
			write_dat(54);
		}	
	}
   	if(key==7)
	{
		if((screen_present==1)&&(screen_level==1)&&(led[led_select]%16!=4)&&(led_lock[led_select]!=0x0a))
		{
			led_pwm(++led[led_select]);
			dis_led();	
		}
		if((screen_present==1)&&(screen_level==2))
		{
			if(c_i!=4)
			{
				if(led_lock[led_select]==0x09)
				{
					led_code[led_select]=led_code[led_select]*10+7;	
				}
				else 
				{
					led_entered=led_entered*10+7;
				}
				lcd_pos(1,c_i++);
				write_dat(55);
			}
		}
		if((screen_present==3)&&(screen_level>1))
		{
			if((c_i!=8)&&(screen_level==2))
			{
				new_name[c_i]=55;	
			}
			if((c_i!=8)&&(screen_level==3))
			{
				new_code[c_i]=55;
			}
			lcd_pos(1,c_i++);
			write_dat(55);
		}
	}
	if(key==8)
	{
		if((screen_present==1)&&(screen_level==2))
		{
			if(c_i!=4)
			{
				if(led_lock[led_select]==0x09)
				{
					led_code[led_select]=led_code[led_select]*10+8;	
				}
				else 
				{
					led_entered=led_entered*10+8;
				}
				lcd_pos(1,c_i++);
				write_dat(56);
			}
		}
		if((screen_present==3)&&(screen_level>1))
		{
			if((c_i!=8)&&(screen_level==2))
			{
				new_name[c_i]=56;	
			}
			if((c_i!=8)&&(screen_level==3))
			{
				new_code[c_i]=56;
			}
			lcd_pos(1,c_i++);
			write_dat(56);
		}
	}
	if(key==9)
	{
		if((screen_present==1)&&(screen_level==2))
		{
			if(c_i!=4)
			{
				if(led_lock[led_select]==0x09)
				{
					led_code[led_select]=led_code[led_select]*10+9;	
				}
				else 
				{
					led_entered=led_entered*10+9;
				}
				lcd_pos(1,c_i++);
				write_dat(57);
			}
		}
		if((screen_present==3)&&(screen_level>1))
		{
			if((c_i!=8)&&(screen_level==2))
			{
				new_name[c_i]=57;	
			}
			if((c_i!=8)&&(screen_level==3))
			{
				new_code[c_i]=57;
			}
			lcd_pos(1,c_i++);
			write_dat(57);
		}
	}
	if(key==10)
	{
		if((screen_present==1)&&(screen_level==2))
		{
			if(c_i!=4)	//�����������벻����Ҫ����ʾ �������
			{										
				led_code[led_select]=0;
				led_entered=0;c_i=0;
				write_cmd(0x01);
				lcd_pos(0,0);dis_string(dis16);
				delay(50000);delay(50000);delay(50000);delay(50000);
				screen_level=1;
				screen_draw();
				dis_led();
			}
			else		 							//����������ʽ������λ
			{
				if(led_lock[led_select]==0x09)		//���������δ���������ھ��Ǽ���������
				{
					led_lock[led_select]=0x0a;	   	//������ǰΪ����״̬
					write_cmd(0x01);			   	//���
					screen_level=1;					//������һ��
					c_i=0;
					led_entered=0;
					screen_draw();
					dis_led();
				}
				else	   //���������������������Ҫ����
				{
					if(led_entered==led_code[led_select])						 //���������ȷ������
					{
						led_lock[led_select]=0x09;								 //����
						led_code[led_select]=0;									 //�����ǰ������
						screen_level=1;					//������һ��
						c_i=0;
						screen_draw();
						dis_led();
					}
					else								 //������������ʾ ������󣬷�����һ��
					{
						led_entered=0;
						c_i=0;
						write_cmd(0x01);lcd_pos(0,0);dis_string(dis16);
						delay(50000);delay(50000);delay(50000);delay(50000);
						screen_level=1;
						screen_draw();
						dis_led();
					}
				}
			}
		}
		if((screen_present==3)&&(screen_level>1))
		{
			if((screen_level==2)&&(c_i>3))
			{
				UART_command=1;//Ҫ������
			}
			else if((screen_level==3)&&(c_i==8))
			{
				UART_command=2;//Ҫ������
			}
			else
			{
				write_cmd(0x01);lcd_pos(0,0);dis_string(dis16);
				delay(50000);delay(50000);delay(50000);delay(50000);	
			}
			c_i=0;
			screen_level=1;
			write_cmd(0x01);
			lcd_pos(1,0);
			dis_string(dis26);
		}
	}

	if(key==11)
	{
		if(screen_level>1)
		{
		   	lcd_pos(1,0);
			dis_string("                ");
			c_i=0;
			led_entered=0;
		}
	}			
   	if(key==12)
	{
		if(screen_present==0)breathe_now=(breathe_now+1)%3;
		if((screen_present==3)&&(screen_level==1))
		{
			screen_level=2;
			screen_draw();
			lcd_pos(1,0);
		}
	}
	if(key==13)
	{
		if(screen_present==0)
		{
			pwm_on=~pwm_on;
			if(pwm_on==1)
			{
				lcd_pos(3,0);
				dis_string("                ");
				lcd_pos(3,0);
				dis_string(dis21);
			}
			else
			{
				lcd_pos(3,0);
				dis_string("                ");
				lcd_pos(3,0);
				dis_string(dis10);
				pwm_on=0;
			}
		}
		if((screen_present==3)&&(screen_level==1))
		{
			screen_level=3;
			screen_draw();
			lcd_pos(1,0);
		}
	}
	if(key==14)
	{
		if(screen_present==1)//���龰��������������
		{
			screen_level=2;
			write_cmd(0x01);
			lcd_pos(0,0);
			dis_string(dis14);
			lcd_pos(3,0);
			dis_string(dis15);
			//lcd_pos(1,0);

		}
	}
	if(key==15)
	{
		c_i=0;
		if(screen_level>1)	 screen_level=1;
		else screen_level=0;
		if(screen_level==0)
		{
			screen_present=0;
		}
		screen_draw();
		if((screen_present==1)&&(screen_level==1))
		{
			dis_led();
		}
	}
} 

void keyscan(void) interrupt 0  
{
	key=keyfind();
	keyprocess(key);
	key=16;
	delay(20);
	P7=0xf0;
}