/*---------only for ultrasound module-------------------*/
/*
 AUTHOR: GANG CHEN
 gangchen1170@gmail.com
 */
#include "altera_avalon_uart.h"
#include "altera_avalon_uart_regs.h"
#include "uart0.h"
#include "stdio.h"

void Uart_init(long Address)
{
	IOWR_ALTERA_AVALON_UART_CONTROL(Address, 0x00);
    IOWR_ALTERA_AVALON_UART_STATUS(Address, 0x00);
    //IOWR_ALTERA_AVALON_UART_RXDATA(NEW_ULTRASOUND1_BASE, 0x00);
    //alt_irq_register(NEW_ULTRASOUND1_BASE,0,Uart_ISR);
}


void Uart_send_byte(long Address, unsigned char data)
{
	unsigned int status;
    IOWR_ALTERA_AVALON_UART_TXDATA(Address,data);
    status=IORD_ALTERA_AVALON_UART_STATUS(Address);
    while(!(status&0x0040))
    {
    	status=IORD_ALTERA_AVALON_UART_STATUS(Address);
    }
}

unsigned char Uart_receive_byte(long Address)
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
}


