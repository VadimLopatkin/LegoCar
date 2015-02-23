#include "system.h"
#include "io.h"
#include "stdio.h"
#include "uart0.h"
#include "uartcom.h"
#include "new_ultrasound.h"
#include "ultrasound_sensor_abstact.h"

#define Test_Com
//#define Test_UartSound


#ifdef Test_Com
int main()
{
    int i;
    Uartcom_init();
    while(1) {
    	if(frame_done)
    	{
    		//test receive the frame message from Imx6
    		frame_done=0;
    		int l = 18, r = 35 ,s = 70 , b = 39, f = 38,h = 9;
    		for(i=0;i<InFrameByteNum;i++)
    			if(message_frame[0] == l){ //left
    				printf("left");
    				motor_setting(PWM1_BASE, 0, 10000, 10000, 2);
    			}
    			if(message_frame[0] == r){ // right
					printf("right");
					motor_setting(PWM1_BASE, 10000, 0, 10000, 1);
				}
				if(message_frame[0] == s){ // straight
					printf("straight");
					motor_setting(PWM1_BASE, 0, 10000, 10000, 0);
				}
				if(message_frame[0] == b){ // backwards
					printf("backwards");
					motor_setting(PWM0_BASE, 5000, 5000, 10000, 2);
				}
				if(message_frame[0] ==f){ // forwards
					printf("forwards");
					motor_setting(PWM0_BASE, 5000, 5000, 10000, 1);
				}
				if(message_frame[0] ==h){ // stop
					printf("stop");
					motor_setting(PWM0_BASE, 0, 10000, 10000, 0);
				}
    	}
    }
    return 0;
}
#endif

#ifdef Test_UartSound
int main()
{
	unsigned int res;
	unsigned int i;
	while(1)
	{
		Ultrasound_init(NEW_ULTRASOUND1_BASE);
		res=Ultrasound_read(NEW_ULTRASOUND1_BASE,0);
		printf("The distance is %f m.\n",res*340/1000000.0);
		for(i=0;i<100000;i++);
	}
	return 0;
}
#endif
