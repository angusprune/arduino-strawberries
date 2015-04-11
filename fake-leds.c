#include "strawberries.h"
#include "leds.h"
#include <stdio.h>

struct HSL led_array[numberOfLeds];

void printTerminalColor(struct HSL color) {
  
}

void update_led(int id, struct HSL color) {
  led_array[id] = color;
}

void flush() {
  for(int i=0; i<numberOfLeds; i++) {
    printTerminalColor(led_array[i]);
  }
  putchar('\n');
}

