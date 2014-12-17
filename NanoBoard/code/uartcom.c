/*---------the communication module between Imx6 Board and Nano Board-------------------*/
/*
 AUTHOR: GANG CHEN
 gangchen1170@gmail.com
 */
#include "altera_avalon_uart.h"
#include "altera_avalon_uart_regs.h"
#include "uartcom.h"
#include "stdio.h"
#include "sys/alt_irq.h"
#include "system.h"



void Uartcom_ISR(void * context,alt_u32 id)
{
    unsigned char temp;
    temp=IORD_ALTERA_AVALON_UART_RXDATA(UART_0_BASE);
    message_frame[frame_index++]=temp;
    if(frame_index>=InFrameByteNum)
    {
    	frame_index=0;
    	frame_done=1;
    }

}

void Uartcom_init()
{
	frame_index=0;
	frame_done=0;
	IOWR_ALTERA_AVALON_UART_CONTROL(UART_0_BASE, 0x80);
    IOWR_ALTERA_AVALON_UART_STATUS(UART_0_BASE, 0x00);
    //IOWR_ALTERA_AVALON_UART_RXDATA(NEW_ULTRASOUND1_BASE, 0x00);
    alt_irq_register(UART_0_IRQ,0,Uartcom_ISR);
}


void Uartcom_send_byte(unsigned char data)
{
	unsigned int status;
    IOWR_ALTERA_AVALON_UART_TXDATA(UART_0_BASE,data);
    status=IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE);
    while(!(status&0x0040))
    {
    	status=IORD_ALTERA_AVALON_UART_STATUS(UART_0_BASE);
    }
}

void Uartcom_send_frame(unsigned char *data, unsigned char size)
{
	int i;
	Uartcom_send_byte(HeaderByte);
	for(i=0;i<size;i++)
		Uartcom_send_byte(*(data+i));
	Uartcom_send_byte(EndByte);
}

/*
unsigned char Uartcom_receive_byte(long Address)
{
	unsigned int  status;
	unsigned char res;
    status=IORD_ALTERA_AVALON_UART_STATUS(Address);
    while(!(status&0x0080))
    {
    	status=IORD_ALTERA_AVALON_UART_STATUS(Address);
    }
    res=IORD_ALTERA_AVALON_UART_RXDATA(Address);
    return res;
}*/


