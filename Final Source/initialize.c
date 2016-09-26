#include "include.h"

void Reset_Sources_Init()//关闭看门狗
{
    WDTCN     = 0xDE;
    WDTCN     = 0xAD;
}

void Timer_Init() //timer1工作在8位重装载，生成9600bps波特
//timer2工作在重装载，为ADC0提供溢出信号
{
    CKCON     = 0x30;
    TCON      = 0x40;
	TMOD      = 0x22;
    TH1       = 0xF4;
    T2CON     = 0x04;
    RCAP2L    = 0xBF;
    TL2       = 0xBf; 
}

void ADC_Init()//使能ADC0，连续跟踪，信号来源于TIMER2，增益0.5，当前引脚AIN0.1
{
    AMX0SL    = 0x01;
    ADC0CN    = 0x8C;
	ADC0CF    = 0xFE;
}

void Voltage_Reference_Init()//基准电压来自VREF0输入，使能内部参考，不使用温度传感器
{
    REF0CN    = 0x03;
}

void PCA_Init()//初始pwm波全部都是100%占空比
{
    PCA0CN    = 0x40;
    PCA0MD    = 0x08;
    PCA0CPM0  = 0x42;
    PCA0CPM1  = 0x42;
    PCA0CPM2  = 0x42;
    PCA0CPM3  = 0x42;
    PCA0CPM4  = 0x42;
}

void UART_Init()	//启用UART0并允许接收
{
    PCON      = 0x80;
    SCON0     = 0x50;
}

void Port_IO_Init()	
{
	// P0.0  -  TX0 (UART0), Push-Pull,  Digital
    // P0.1  -  RX0 (UART0), Push-Pull,  Digital
    // P0.2  -  CEX0 (PCA),  Push-Pull,  Digital
    // P0.3  -  CEX1 (PCA),  Push-Pull,  Digital
    // P0.4  -  CEX2 (PCA),  Push-Pull,  Digital
    // P0.5  -  CEX3 (PCA),  Push-Pull,  Digital
    // P0.6  -  CEX4 (PCA),  Push-Pull,  Digital
    // P0.7  -  INT0 (Tmr0), Push-Pull,  Digital

    // P1.0  -  Unassigned,  Open-Drain, Digital
    // P1.1  -  Unassigned,  Open-Drain, Digital
    // P1.2  -  Unassigned,  Open-Drain, Digital
    // P1.3  -  Unassigned,  Open-Drain, Digital
    // P1.4  -  Unassigned,  Open-Drain, Digital
    // P1.5  -  Unassigned,  Open-Drain, Digital
    // P1.6  -  Unassigned,  Push-Pull,  Digital
    // P1.7  -  Unassigned,  Open-Drain, Digital

    // P2.0  -  Unassigned,  Open-Drain, Digital
    // P2.1  -  Unassigned,  Open-Drain, Digital
    // P2.2  -  Unassigned,  Open-Drain, Digital
    // P2.3  -  Unassigned,  Open-Drain, Digital
    // P2.4  -  Unassigned,  Open-Drain, Digital
    // P2.5  -  Unassigned,  Open-Drain, Digital
    // P2.6  -  Unassigned,  Open-Drain, Digital
    // P2.7  -  Unassigned,  Open-Drain, Digital

    // P3.0  -  Unassigned,  Open-Drain, Digital
    // P3.1  -  Unassigned,  Push-Pull,  Digital
    // P3.2  -  Unassigned,  Push-Pull,  Digital
    // P3.3  -  Unassigned,  Push-Pull,  Digital
    // P3.4  -  Unassigned,  Open-Drain, Digital
    // P3.5  -  Unassigned,  Open-Drain, Digital
    // P3.6  -  Unassigned,  Open-Drain, Digital
    // P3.7  -  Unassigned,  Open-Drain, Digital

    P0MDOUT   = 0xFF;
    P1MDOUT   = 0x40;
    P3MDOUT   = 0x0E;
    XBR0      = 0x2C;
    XBR1      = 0x04;
    XBR2      = 0x40;
}

void Oscillator_Init()//内部晶振16mhz
{
	int i = 0;
    OSCXCN    = 0x67;
    for (i = 0; i < 3000; i++);  // Wait 1ms for initialization
    while ((OSCXCN & 0x80) == 0);
    OSCICN    = 0x0B;

}

void Interrupts_Init()//开启全局中断，/int0中断以及UART0中断，并全部设置为高优先级；使能ADC0中断
{
    IE        = 0x91;
    IP        = 0x11;
	EIE2	  = 0x02;
	EIP2      = 0x02;
}

void Init_Device(void)
{
    Reset_Sources_Init();
    Timer_Init();
    PCA_Init();
    UART_Init();
    ADC_Init();
    Voltage_Reference_Init();
    Port_IO_Init();
	Init_lcd();
    Oscillator_Init();
    Interrupts_Init();	
}