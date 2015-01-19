/*
  AUTHOR: GANG CHEN
 gangchen1170@gmail.com
 */

#include "system.h"
#include "io.h"
#include "stdio.h"
#include "uart0.h"
//#include "uartcom.h"
#include "new_ultrasound.h"
#include "motor_setting.h"
#include "motor_setting_servo.h"


int main()
{
	/* turn off leds
	 * each bit controls one of the eight leds (1: on, 0: off)
	 */
	IOWR(LED_BASE,0,0b00000000);

	// measured value from ultrasound
	unsigned int res;

	unsigned int i;
	
	// spin direction of the motors
	unsigned int direction = 1;

	// for serial communication
    Uart_init(UART_0_BASE);

	while(1)
	{
    		
    		// receive (blocking)
    		//char r = Uart_receive_byte(UART_0_BASE);
    		//printf("\nrec: %d : %c", r, r);
    		// send
    		//Uart_send_byte(UART_0_BASE, r);


		// init Ultrasound
		Ultrasound_init(NEW_ULTRASOUND1_BASE);
		res=Ultrasound_read(NEW_ULTRASOUND1_BASE,0);

		/*	 measured values from sensor
		 *   0.20m: 1028
		 *   0.15m: 771
		 *   0.10m: 514
		 *   0.05m: 257
		 * < 0.05m: 0
		 *   => factor for calculation of the distance in cm: 0.019455252918288
		 *   sensor has an accuracy of 5 cm
		 */

		// mesured distance
		printf("The distance is %f cm. %i\n",res*0.019455252918288, res);
		
		/* key state
		 * 0: no key pressed
		 * 1: key one pressed
		 * 2: key two pressed
		 */
		unsigned int key = IORD(KEY_BASE,0);

		// change direction on key pressed
		if(key == 2) {
			direction = 2;
		} else if (key == 1) {
			direction = 1;
		}


		/* sets speed according to the measured distance from the sensor
		 * the direction can be changed with the two buttons on the board
		 */
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

		for(i=0;i<100000;i++);
	}
	
	/* servo
	
	while(1) {

		unsigned int key = IORD(KEY_BASE,0);

		if(key == 2) {
			IOWR(LED_BASE,0,0b1);
			motor_setting(PWM1_BASE, 0, 10000, 10000, 2);
		} else if (key == 1) {
			IOWR(LED_BASE,0,0b10000000);
			motor_setting(PWM1_BASE, 10000, 0, 10000, 1);
		} else {
			IOWR(LED_BASE,0,0b00011000);
			motor_setting(PWM1_BASE, 0, 10000, 10000, 0);
		}
	}
	
	*/
	
	return 0;
}
