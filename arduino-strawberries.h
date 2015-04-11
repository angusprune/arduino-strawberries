#ifndef __ARDUINO_STRAWBERRIES_H
#define __ARDUINO_STRAWBERRIES_H

#ifdef DEBUG
#include <stdio.h>
#endif

struct RGB {
  union {
    struct {
      byte b;
      byte g;
      byte r;
      byte extra;
    } ;
    uint32_t packed;
  } ;
} ;

struct HSL {
	float h;
	float s;
	float l;
};

#ifdef DEBUG

struct HSL led_array[numberOfLeds];

void printTerminalColor(struct HSL color);

void update_led(int id, struct HSL color);

void flush();

#else
#endif


#endif