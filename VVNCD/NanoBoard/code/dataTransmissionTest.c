/*
  AUTHOR: GANG CHEN
 gangchen1170@gmail.com
 */

#include "system.h"
#include "io.h"
#include "stdio.h"
#include "uart0.h"
#include "uartcom.h"
#include "new_ultrasound.h"
#include "motor_setting.h"
#include "motor_setting_servo.h"

#define Test_Com
//#define Test_UartSound
//#define Test_Motor


#ifdef Test_Com
int main()
{
    int i;
    int j;
    unsigned int returndata[2]={0,0};
    unsigned char *chr;
    //unsigned char index=0;
    //unsigned char sensor_type;
    //unsigned char sensor_index;
    //unsigned char sensor_RW;

    //Uart_init(UART_0_BASE);
    //Uart_send_byte(UART_0_BASE, 'a');
    	Uartcom_send_byte(EndByte);
    	Uartcom_send_byte(HeaderByte);
    	for(i=0;i<256;i++)
    	{
    		Uartcom_send_byte((unsigned char)(i));
    		usleep(100);
    		Uartcom_send_byte((unsigned char)(i));
    		usleep(100);
    		Uartcom_send_byte((unsigned char)(i));
    		usleep(100);
		    Uartcom_send_byte((unsigned char)(i));
		    usleep(100);
		    Uartcom_send_byte((unsigned char)(i));
		    usleep(100);
		    Uartcom_send_byte((unsigned char)(i));
		    usleep(100);
    		Uartcom_send_byte((unsigned char)(i));
    		usleep(100);
    		Uartcom_send_byte((unsigned char)(i));
    		usleep(1000);

    	}
    	Uartcom_send_byte(EndByte);


    //while(1) {
    	//Uartcom_send_byte('A');
    	//printf("hello!");
    	//Uartcom_send_frame(returndata, 2);
    	//printf("%c", Uart_receive_byte(UART_0_BASE));
    	/*if(frame_done)
    	{
    		//printf("...");
    		//Uartcom_send_byte('b');
    		//test receive the frame message from Imx6
    		/*frame_done=0;
    		printf("The frame message is:\t");
    		for(i=0;i<InFrameByteNum;i++)
    			printf(" %d \t",message_frame[i]);
    		printf("\n");
    		//return the messgae to Imx6
    		Uartcom_send_frame(returndata, 2);
    		/*
    		 * protocal example code
    		index=0;
    		if(message_frame[index++]==0xaa)
    		{
    			sensor_type=(message_frame[index]&0x70)>>4;
    			sensor_index=message_frame[index]&0x0f;
    			sensor_RW=(message_frame[index]&0x80)>>7;
    			switch(sensor_type)
    			{
    				case 0: //ulrasound
    					//add your code
    					break;
    				case 1: //PWM
    					//add your code here
    					break;
    				default:
    				    break;
    			}
    		}
    		else
    		{
    			//error
    			printf("Message header is incorrect!!\n");
    			//throw execption
    		}
    		*/
    	//}
    //}
    return 0;
}
#endif

#ifdef Test_UartSound
int main()
{
	// turn off leds
	IOWR(LED_BASE,0,0);

	//servo
	motor_setting(PWM0_BASE, 2000, 8000, 10000, 1);

	unsigned int res;
	unsigned int i;
	unsigned int direction = 1;
//	motor_setting(PWM0_BASE, 1000, 9000, 10000, 0);

	while(1)
	{
		Ultrasound_init(NEW_ULTRASOUND1_BASE);
		res=Ultrasound_read(NEW_ULTRASOUND1_BASE,0);
		/*
		 *   0.20m: 1028
		 *   0.15m: 771
		 *   0.10m: 514
		 *   0.05m: 257
		 * < 0.05m: 0
		 *   => calculate distance in cm: x*0.019455252918288
		 *   accuracy of 5 cm
		 */
		//res = res*0.019455252918288;

		//printf("The distance is %f m.\n",res*340/1000000.0);
		printf("The distance is %f cm. %i\n",res*0.019455252918288, res);
		printf("Key: %i\n", IORD(KEY_BASE,0));

//		speed <-> distance
		unsigned int key = IORD(KEY_BASE,0);
		if(key == 2) {
			direction = 2;
		} else if (key == 1) {
			direction = 1;
		}
		if(direction == 1) {
			switch(res) {
			case 0:
				IOWR(LED_BASE,0,0b11111111);
				motor_setting(PWM0_BASE, 0, 10000, 10000, 0);
				break;
			case 257:
				IOWR(LED_BASE,0,0b11111110);
				motor_setting(PWM0_BASE, 3000, 7000, 10000, 1);
				break;
			case 514:
				IOWR(LED_BASE,0,0b11111100);
				motor_setting(PWM0_BASE, 4000, 6000, 10000, 1);
				break;
			case 771:
				IOWR(LED_BASE,0,0b11111000);
				motor_setting(PWM0_BASE, 5000, 5000, 10000, 1);
				break;
			case 1028:
				IOWR(LED_BASE,0,0b11110000);
				motor_setting(PWM0_BASE, 6000, 4000, 10000, 1);
				break;
			case 1285:
				IOWR(LED_BASE,0,0b11100000);
				motor_setting(PWM0_BASE, 7000, 3000, 10000, 1);
				break;
			case 1542:
				IOWR(LED_BASE,0,0b11000000);
				motor_setting(PWM0_BASE, 8000, 2000, 10000, 1);
				break;
			case 1799:
				IOWR(LED_BASE,0,0b10000000);
				motor_setting(PWM0_BASE, 9000, 1000, 10000, 1);
				break;
			default:
				IOWR(LED_BASE,0,0b00000000);
				motor_setting(PWM0_BASE, 10000, 0, 10000, 1);
			}
		} else {
			switch(res) {
				case 0:
				IOWR(LED_BASE,0,0b11111111);
				motor_setting(PWM0_BASE, 10000, 0, 10000, 0);
				break;
			case 257:
				IOWR(LED_BASE,0,0b11111110);
				motor_setting(PWM0_BASE, 7000, 3000, 10000, 2);
				break;
			case 514:
				IOWR(LED_BASE,0,0b11111100);
				motor_setting(PWM0_BASE, 6000, 4000, 10000, 2);
				break;
			case 771:
				IOWR(LED_BASE,0,0b11111000);
				motor_setting(PWM0_BASE, 5000, 5000, 10000, 2);
				break;
			case 1028:
				IOWR(LED_BASE,0,0b11110000);
				motor_setting(PWM0_BASE, 4000, 6000, 10000, 2);
				break;
			case 1285:
				IOWR(LED_BASE,0,0b11100000);
				motor_setting(PWM0_BASE, 3000, 7000, 10000, 2);
				break;
			case 1542:
				IOWR(LED_BASE,0,0b11000000);
				motor_setting(PWM0_BASE, 2000, 8000, 10000, 2);
				break;
			case 1799:
				IOWR(LED_BASE,0,0b10000000);
				motor_setting(PWM0_BASE, 1000, 9000, 10000, 2);
				break;
			default:
				IOWR(LED_BASE,0,0b00000000);
				motor_setting(PWM0_BASE, 0, 10000, 10000, 2);
			}
		}
//		switch(res) {
//		case 0:
//			IOWR(LED_BASE,0,0b11111111);
//			motor_setting(PWM0_BASE, 10000, 0, 10000, 0);
//			break;
//		case 257:
//			IOWR(LED_BASE,0,0b11111110);
//			motor_setting(PWM0_BASE, 7000, 3000, 10000, 2);
//			break;
//		case 514:
//			IOWR(LED_BASE,0,0b11111100);
//			motor_setting(PWM0_BASE, 6000, 4000, 10000, 2);
//			break;
//		case 771:
//			IOWR(LED_BASE,0,0b11111000);
//			motor_setting(PWM0_BASE, 5000, 5000, 10000, 2);
//			break;
//		case 1028:
//			IOWR(LED_BASE,0,0b11110000);
//			motor_setting(PWM0_BASE, 4000, 6000, 10000, 2);
//			break;
//		case 1285:
//			IOWR(LED_BASE,0,0b11100000);
//			motor_setting(PWM0_BASE, 3000, 7000, 10000, 2);
//			break;
//		case 1542:
//			IOWR(LED_BASE,0,0b11000000);
//			motor_setting(PWM0_BASE, 2000, 8000, 10000, 2);
//			break;
//		case 1799:
//			IOWR(LED_BASE,0,0b10000000);
//			motor_setting(PWM0_BASE, 1000, 9000, 10000, 2);
//			break;
//		default:
//			IOWR(LED_BASE,0,0b00000000);
//			motor_setting(PWM0_BASE, 0, 10000, 10000, 2);
//		}

		for(i=0;i<100000;i++);
		// unsigned long phase1=0x0,phase2=0x000,duty1=2000,duty2=4000,period=10000,enable=0x2;


//		printf("...");

	}
	return 0;
}

#endif

#ifdef Test_Motor

int main()
{
	// turn off leds
	IOWR(LED_BASE,0,0);

	//servo
	motor_setting(PWM0_BASE, 1000, 19000, 20000, 2);

	return 0;
}

#endif
