/*
  AUTHOR: GANG CHEN
 gangchen1170@gmail.com
 */
#ifndef __UARTCOM_H_
#define __UARTCOM_H_

//-----------------------------------
//Input message format
#define InFrameByteNum 5
#define HeaderByte 0xaa
#define EndByte 0x55

#define FrameHeader 0
#define SensorID 1
//The highest bit indicates read or write, 6-4 bits indicate the sensor type, 3-0 bits indicate sensor within sensor type
#define WrDate0 2
#define WrDate1 3
#define EndHeader 4
//-----------------------------------
//Output message format
#define OutFrameByteNum 4

#define OutFrameHeader 0
#define OutRdDate0 1
#define OutRdDate1 2
#define OutEndHeader 3

unsigned char message_frame[InFrameByteNum];
unsigned char frame_index;
unsigned char frame_done;

void Uartcom_init();
void Uartcom_send_byte(unsigned char data);
unsigned char Uartcom_receive_byte();
void Uartcom_send_frame(unsigned char *data, unsigned char size);

#endif
