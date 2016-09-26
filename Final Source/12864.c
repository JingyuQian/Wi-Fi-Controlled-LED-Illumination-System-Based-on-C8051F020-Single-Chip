#include "include.h" 

uchar code number[]={"0123456789"};
char qian,ge,shi,bai;


uchar code name[]={"  WIFI-LED系统"};
uchar code dis1[]={"调光[0]  [1]监控"};
uchar code dis2[]={"网络[2]  [3]说明"};
uchar code dis10[]={"    呼吸[CD] off"};
uchar code dis21[]={"    呼吸[CD]  on"};
uchar code dis3[]={"温度：        C"};

uchar code choose_led[]={"请选择光源  [F]>"};
uchar code dis4[]={"前灯[4]  [5]后灯"};
uchar code dis5[]={"调暗[6]  [7]调亮"};
uchar code dis6[]={"灯  亮度  状态  "}; 
//网络界面1
uchar code dis7[]={"请选择功能  [F]>"};
uchar code dis8[]={"[C] 修改网络名称"};
uchar code dis9[]={"[D] 修改网络密码"};
uchar code dis22[]={">4位新网络名称"};
uchar code dis23[]={"八位新网络密码"};
uchar code dis24[]={"  修改已经执行"};
uchar code dis25[]={"  重连接以查看"};
uchar code dis26[]={"  修改正在执行.."};
//监控界面
uchar code dis11[]={"电压：        mV"};
uchar code dis12[]={"功率：        mW"};

//光源锁定
uchar code dis14[]={"请输入四位密码:"};
uchar code dis15[]={"确认[A]  [B]清空"};
uchar code dis16[]={"    输入错误"};

//其他
uchar code dis17[]={"   0-9用作输入"};
uchar code dis18[]={"A 确认    B 清空"};
uchar code dis19[]={"E 锁灯    F 返回"};
uchar code dis20[]={"其余请按屏幕指示"};
void delay(uint x)		  //在12864、18b20和主函数中用到
{
   uint i,j;
     for(j=0;j<x;j++)
           for(i=0;i<10;i++);
}

/*写指令数据到LCD*/
/*RS=L，RW=L，E=高脉冲，D0-D7=指令码。*/
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
/*写显示数据到LCD*/
/*RS=H,RW=L,E=高脉冲，D0-D7=数据。*/
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
/*设定显示位置*/
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
   	write_cmd(pos);    //显示地址
}
/*LCD初始化设定*/
void Init_lcd()
{
   set(PSB);        //并口方式
   write_cmd(0x30);  //基本指令操作
   delay(40);
   write_cmd(0x0c);  //显示开，关光标
   delay(40);
   write_cmd(0x01);  //清楚LCD的显示内容
   delay(40);
}
/*显示字符串*/
void dis_string(char *str)
{
	int i=0;
	while(str[i]!='\0')
    {    
     	write_dat(str[i]);
     	i++;
    }
} 
/*显示温度*/
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
//显示当前灯以及灯的亮度
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
		lcd_pos(0,0);    	//设置显示位置为第一行的第一个字符
	   	dis_string(name);
		lcd_pos(1,0);      	//设置显示位置为第二行的第一个字符
	    dis_string(dis1);
	   	lcd_pos(2,0);      	//设置显示位置为第二行的第一个字符
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
