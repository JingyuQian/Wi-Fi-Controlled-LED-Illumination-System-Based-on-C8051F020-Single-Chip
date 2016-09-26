#ifndef __SERIAL_H
#define __SERIAL_H

extern void UART_SendData(uchar *data_buf);
extern void UART_SendH(uchar data_buf);
extern void UART_Process(void);
extern void delay_1s(void);
extern uchar idata Buf[20];
extern uchar idata SendCounter;
extern uchar idata UART_command;
extern uchar idata new_name[20];
extern uchar idata new_code[20];
extern bit idata send_param;
	


#endif
