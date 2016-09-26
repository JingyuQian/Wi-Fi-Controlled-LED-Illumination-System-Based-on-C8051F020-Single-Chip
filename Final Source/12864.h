#ifndef __12864_H
#define __12864_H

#define GPIO_LCD P6

#define  RS  0x80	//  RS=0 ���� RS��1 ����  
#define  RW  0x40   //  RW=0 д�� RW��1 ����
#define  E   0x20	//  E=1 ���� E �½��� д��
#define  PSB 0x10	// ST2920 �ӿڷ�ʽѡ�� PSB=0 ���� PSB=1 4b/8b����
#define  set(cbit) P5|=cbit	     //	 ��1
#define  clr(cbit) P5&=~cbit	 //	 ��0


extern uchar code number[];
extern uchar code name[];
extern uchar code dis1[];
extern uchar code dis2[];
extern uchar code dis3[];
extern uchar code dis4[];
extern uchar code dis5[];
extern uchar code dis6[];
extern uchar code dis7[];
extern uchar code dis8[];
extern uchar code dis9[];
extern uchar code dis10[];
extern uchar code dis11[];
extern uchar code dis12[];
extern uchar code dis14[];
extern uchar code dis15[];
extern uchar code dis16[];
extern uchar code dis17[];
extern uchar code dis18[];
extern uchar code dis19[];
extern uchar code dis20[];
extern uchar code dis21[];
extern uchar code dis22[];
extern uchar code dis23[];
extern uchar code dis24[];
extern uchar code dis25[];
extern uchar code dis26[];
extern uchar code choose_led[];

extern void delay(uint x);//����ʹ�õ���ʱ����������������18b20��12864�о����õ�

extern void write_cmd(uchar cmd);
extern void Init_lcd(void);
extern void dis_temp(uint t);
extern void lcd_pos(uchar x, uchar y);
extern void write_dat(uchar dat);
extern void dis_string(char *str);
extern void dis_led();
extern void screen_draw(void);
#endif