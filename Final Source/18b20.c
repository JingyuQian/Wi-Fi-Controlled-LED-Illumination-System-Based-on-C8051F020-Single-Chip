#include "include.h"

sbit  DQ = P3^0;
uint data temperature;
float data f_temp;

void Delay77(void)   //��ʱ77΢��
{
    unsigned char a,b;
    for(b=16;b>0;b--)
        for(a=25;a>0;a--);
}
void Delay700(void)   //��ʱ700΢��
{
    unsigned char a,b;
    for(b=146;b>0;b--)
        for(a=25;a>0;a--);
}

void Delay50(void)   //��ʱ50΢��
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
		DQ = 0; // �������ź�
		_nop_();
		DQ = 1; // �������ź�
		_nop_();
		dat>>=1;
		if(DQ)
		dat|=0x80;
		Delay77();
	  }
	return dat;
}
//дһ���ֽ�	  
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
	DQ = 1;         //DQ��λ
	Delay77();      //��ʱ77΢��
	DQ = 0;         //��Ƭ����DQ����
    Delay700();     //��ȷ��ʱ700us����480us
	DQ = 1;         //��������
	Delay50();      //������ʱ�� ���x=0���ʼ���ɹ� x=1���ʼ��ʧ��
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
	//Disp_String(0,3,"��ʼ������");
	else{
	WriteOneChar(0xCC); // ����������кŵĲ���
	WriteOneChar(0x44); // �����¶�ת��
	Init_DS18B20();
	WriteOneChar(0xCC); //����������кŵĲ���
	WriteOneChar(0xBE); //��ȡ�¶ȼĴ���
	a=ReadOneChar();  //����8λ
	b=ReadOneChar(); //����8λ
	t=b;
	t<<=8;
	t=t|a;
	tt=t*0.0625;
	t= tt*10+0.5; //�Ŵ�10���������������
	}
	temperature=t;
	return t;
}