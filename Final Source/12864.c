#include "include.h" 

uchar code number[]={"0123456789"};
char qian,ge,shi,bai;


uchar code name[]={"  WIFI-LEDϵͳ"};
uchar code dis1[]={"����[0]  [1]���"};
uchar code dis2[]={"����[2]  [3]˵��"};
uchar code dis10[]={"    ����[CD] off"};
uchar code dis21[]={"    ����[CD]  on"};
uchar code dis3[]={"�¶ȣ�        C"};

uchar code choose_led[]={"��ѡ���Դ  [F]>"};
uchar code dis4[]={"ǰ��[4]  [5]���"};
uchar code dis5[]={"����[6]  [7]����"};
uchar code dis6[]={"��  ����  ״̬  "}; 
//�������1
uchar code dis7[]={"��ѡ����  [F]>"};
uchar code dis8[]={"[C] �޸���������"};
uchar code dis9[]={"[D] �޸���������"};
uchar code dis22[]={">4λ����������"};
uchar code dis23[]={"��λ����������"};
uchar code dis24[]={"  �޸��Ѿ�ִ��"};
uchar code dis25[]={"  �������Բ鿴"};
uchar code dis26[]={"  �޸�����ִ��.."};
//��ؽ���
uchar code dis11[]={"��ѹ��        mV"};
uchar code dis12[]={"���ʣ�        mW"};

//��Դ����
uchar code dis14[]={"��������λ����:"};
uchar code dis15[]={"ȷ��[A]  [B]���"};
uchar code dis16[]={"    �������"};

//����
uchar code dis17[]={"   0-9��������"};
uchar code dis18[]={"A ȷ��    B ���"};
uchar code dis19[]={"E ����    F ����"};
uchar code dis20[]={"�����밴��Ļָʾ"};
void delay(uint x)		  //��12864��18b20�����������õ�
{
   uint i,j;
     for(j=0;j<x;j++)
           for(i=0;i<10;i++);
}

/*дָ�����ݵ�LCD*/
/*RS=L��RW=L��E=�����壬D0-D7=ָ���롣*/
void write_cmd(uchar cmd)
{
    clr(RS);
    clr(RW);
    clr(E);
    P6=cmd;
    delay(40);
    set(E);
    delay(40);
    clr(E);
}
/*д��ʾ���ݵ�LCD*/
/*RS=H,RW=L,E=�����壬D0-D7=���ݡ�*/
void write_dat(uchar dat)
{
   	set(RS);
   	clr(RW);
   	clr(E);
   	P6=dat;
   	delay(40);
   	set(E);
   	delay(40);
   	clr(E);
}
/*�趨��ʾλ��*/
void lcd_pos(uchar X,uchar Y)
{
   	uchar pos;
  	if(X==0)
    {X=0x80;}
   	else if(X==1)
    {X=0x90;}
   	else if(X==2)
    {X=0x88;}
   	else if(X==3)
    {X=0x98;}
   	pos=X+Y;
   	write_cmd(pos);    //��ʾ��ַ
}
/*LCD��ʼ���趨*/
void Init_lcd()
{
   set(PSB);        //���ڷ�ʽ
   write_cmd(0x30);  //����ָ�����
   delay(40);
   write_cmd(0x0c);  //��ʾ�����ع��
   delay(40);
   write_cmd(0x01);  //���LCD����ʾ����
   delay(40);
}
/*��ʾ�ַ���*/
void dis_string(char *str)
{
	int i=0;
	while(str[i]!='\0')
    {    
     	write_dat(str[i]);
     	i++;
    }
} 
/*��ʾ�¶�*/
void dis_temp(uint t) 
{
    uchar i,j,k;  	
    i=t/100;
    lcd_pos(3,3); 
    write_dat(number[i]);

    j=t%100/10;  
    lcd_pos(3,4); 
    write_dat(number[j]);	

    lcd_pos(3,5);
    write_dat('.');

    k=t%10;  
    lcd_pos(3,6); 
    write_dat(number[k]); 
}
//��ʾ��ǰ���Լ��Ƶ�����
void dis_led(void)
{
	lcd_pos(3,1);
	write_dat(number[led_select]+1);
	lcd_pos(3,4);
	write_dat((led[led_select]%16)+48);
	lcd_pos(3,7);
	write_dat(led_lock[led_select]);
}

void screen_draw()
{
	write_cmd(0x01);
	if(screen_present==0)
	{
		write_cmd(0x01);
		lcd_pos(0,0);    	//������ʾλ��Ϊ��һ�еĵ�һ���ַ�
	   	dis_string(name);
		lcd_pos(1,0);      	//������ʾλ��Ϊ�ڶ��еĵ�һ���ַ�
	    dis_string(dis1);
	   	lcd_pos(2,0);      	//������ʾλ��Ϊ�ڶ��еĵ�һ���ַ�
	   	dis_string(dis2);
		lcd_pos(3,0);
		dis_string(dis10);
	}
	if(screen_present==1)
	{
		if(screen_level==1)
		{
			lcd_pos(0,0);    
   			dis_string(choose_led);
			lcd_pos(1,0);     
    		dis_string(dis4);
   			lcd_pos(2,0);      	
   			dis_string(dis5);
    		lcd_pos(3,0);      	
    		dis_string(dis6);
		}
		
	}
	if(screen_present==2)
	{
		lcd_pos(0,0);
		dis_string(dis6);
		lcd_pos(1,0);
		dis_string(dis11);
		lcd_pos(2,0);
		dis_string(dis12);
		lcd_pos(3,0);
		dis_string(dis3);
	}
	if(screen_present==3)
	{
		if(screen_level==2)
		{
			lcd_pos(0,0);
			dis_string(dis22);
			lcd_pos(3,0);
			dis_string(dis15);
		}
		else if(screen_level==3)
		{
			lcd_pos(0,0);
			dis_string(dis23);
			lcd_pos(3,0);
			dis_string(dis15);
		}
		else
		{
			lcd_pos(0,0);
			dis_string(dis7);
			lcd_pos(1,0);
			dis_string(dis8);
			lcd_pos(2,0);
			dis_string(dis9);
		}
	}
	if(screen_present==4)
	{
		lcd_pos(0,0);
		dis_string(dis17);
		lcd_pos(1,0);
		dis_string(dis18);
		lcd_pos(2,0);
		dis_string(dis19);
		lcd_pos(3,0);
		dis_string(dis20);
	}	
}
