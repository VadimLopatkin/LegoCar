/*
 * motor_setting.c
 *
 *  Created on: 07.11.2012
 *      Author: karl_ee
 *          input parameters:
 *      	phase: range from 0 to value of period
 *     		duty cycle: set to number=period*percentage of duty cycle
 *      	period: according to the freq of cpu,
 *      			normally the period should be set to the value
 *      			that makes the freq of pwm waveform to be 15 k
 *      			e.g., for 50MHz, value should be 3333(0xD05)
 *      	enable:'0' represents off, '1' is on, lease significant bit is for channel 1
 *      			e.g., for channel 1 on and channel 2 off, enable=0x1
 *
 */

#include "motor_setting.h"
#include "io.h"

//#define PWM_EN PWM_GEN_0_BASE
//#define PWM_PERIOD PWM_GEN_0_BASE+1
//#define PWM_DUTY1 PWM_GEN_0_BASE+2
//#define PWM_DUTY2 PWM_GEN_0_BASE+3
//#define PWM_PHASE1 PWM_GEN_0_BASE+4
//#define PWM_PHASE2 PWM_GEN_0_BASE+5

void motor_setting(long Address, unsigned long duty1,unsigned long duty2,unsigned long period,unsigned long enable)
{
	//unsigned long * pwm_en= (unsigned long *)PWM_EN;
	//unsigned long * pwm_period=(unsigned long *)PWM_PERIOD;
	//unsigned long * pwm_duty1=(unsigned long *)PWM_DUTY1;
	//unsigned long * pwm_duty2=(unsigned long *)PWM_DUTY2;

	//* pwm_en=enable;
	IOWR(Address,0,enable);
	//* pwm_period=period;
	IOWR(Address,1,period);
	//* pwm_duty1=duty1;
	IOWR(Address,2,duty1);
	//* pwm_duty2=duty2;
	IOWR(Address,3,duty2);
}
