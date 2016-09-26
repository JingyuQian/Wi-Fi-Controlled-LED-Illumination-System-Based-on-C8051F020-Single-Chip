#include "include.h"

sbit  DQ = P3^0;
uint data temperature;
float data f_temp;

void Delay77(void)   //延时77微秒
{
    unsigned char a,b;
    for(b=16;b>0;b--)
        for(a=25;a>0;a--);
}
void Delay700(void)   //延时700微秒
{
    unsigned char a,b;
    for(b=146;b>0;b--)
        for(a=25;a>0;a--);
}

void Delay50(void)   //延时50微秒
{
    unsigned char a,b;
    for(b=61;b>0;b--)
        for(a=3;a>0;a--);
}

unsigned char ReadOneChar(void)
{
	unsigned char i=0;
	unsigned char dat = 0;
		for (i=8;i>0;i--)
	{
		DQ = 0; // 给脉冲信号
		_nop_();
		DQ = 1; // 给脉冲信号
		_nop_();
		dat>>=1;
		if(DQ)
		dat|=0x80;
		Delay77();
	  }
	return dat;
}
//写一个字节	  
void WriteOneChar(unsigned char dat)
{
	unsigned char i=0;
		for (i=8; i>0; i--)
	{	
		DQ = 0;
		dat>>=1;
		DQ = CY;
		Delay77();
		DQ = 1;
	
		}
}

 unsigned char Init_DS18B20(void)
{	unsigned char status;
	DQ = 1;         //DQ复位
	Delay77();      //延时77微秒
	DQ = 0;         //单片机将DQ拉低
    Delay700();     //精确延时700us大于480us
	DQ = 1;         //拉高总线
	Delay50();      //稍做延时后 如果x=0则初始化成功 x=1则初始化失败
	status = DQ;
	Delay700();
	return status;
}

unsigned int ds18b20_gettemp(void)
{
	unsigned char a=0;
	unsigned char b=0;
	unsigned int t=0;
	float tt=0;
	if(Init_DS18B20()==1);
	//Disp_String(0,3,"初始化错误");
	else{
	WriteOneChar(0xCC); // 跳过读序号列号的操作
	WriteOneChar(0x44); // 启动温度转换
	Init_DS18B20();
	WriteOneChar(0xCC); //跳过读序号列号的操作
	WriteOneChar(0xBE); //读取温度寄存器
	a=ReadOneChar();  //读低8位
	b=ReadOneChar(); //读高8位
	t=b;
	t<<=8;
	t=t|a;
	tt=t*0.0625;
	t= tt*10+0.5; //放大10倍输出并四舍五入
	}
	temperature=t;
	return t;
}