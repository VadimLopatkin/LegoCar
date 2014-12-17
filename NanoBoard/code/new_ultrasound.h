/*
  AUTHOR: GANG CHEN
 gangchen1170@gmail.com
 */
#ifndef __NEW_ULTRASOUND_H_
#define __NEW_ULTRASOUND_H_

void Ultrasound_init(long Address);

unsigned int Ultrasound_read(long Address, unsigned char settings);

#endif




