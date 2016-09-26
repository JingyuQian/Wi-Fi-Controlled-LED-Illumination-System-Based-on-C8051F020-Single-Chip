#ifndef __12864_H
#define __12864_H

#define GPIO_LCD P6

#define  RS  0x80	//  RS=0 命令 RS＝1 数据  
#define  RW  0x40   //  RW=0 写入 RW＝1 读出
#define  E   0x20	//  E=1 读出 E 下降沿 写入
#define  PSB 0x10	// ST2920 接口方式选择 PSB=0 串行 PSB=1 4b/8b并行
#define  set(cbit) P5|=cbit	     //	 置1
#define  clr(cbit) P5&=~cbit	 //	 置0


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

extern void delay(uint x);//对外使用的延时函数，在主函数，18b20和12864中均有用到

extern void write_cmd(uchar cmd);
extern void Init_lcd(void);
extern void dis_temp(uint t);
extern void lcd_pos(uchar x, uchar y);
extern void write_dat(uchar dat);
extern void dis_string(char *str);
extern void dis_led();
extern void screen_draw(void);
#endif