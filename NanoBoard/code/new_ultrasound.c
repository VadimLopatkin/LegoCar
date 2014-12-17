/*---------only for ultrasound module-------------------*/
/*
 AUTHOR: GANG CHEN
 gangchen1170@gmail.com
 */
#include "uart0.h"
#include "new_ultrasound.h"

void Ultrasound_init(long Address)
{
	Uart_init(Address);
}

unsigned int Ultrasound_read(long Address, unsigned char settings)
{
	unsigned int i;
	unsigned char res_l,res_h;
	Uart_send_byte(Address,0xe8);
	for(i=0;i<1000;i++); //
	Uart_send_byte(Address,0x02);
	for(i=0;i<1000;i++);
	if(settings)
		Uart_send_byte(Address,0xb2);  //can measure maximum 5m distance
	else
		Uart_send_byte(Address,0xba);  //can measure maximum 11m distance
	res_h=Uart_receive_byte(Address);
	res_l=Uart_receive_byte(Address);
	return ((unsigned int)res_h<<8)+res_h;
}

