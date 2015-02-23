/*
  AUTHOR: GANG CHEN
 gangchen1170@gmail.com
 */
#ifndef __UART_H_
#define __UART_H_

void Uart_init(long Address);
void Uart_send_byte(long Address,unsigned char data);
unsigned char Uart_receive_byte(long Address);

#endif
