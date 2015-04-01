#include "FastLED.h"

//settings

uint8_t dataPin = 2;
uint8_t clockPin = 3;
numOfLEDs = 50;


//setup
CRGB leds[numOfLEDs];

void setup() {
	FastLED.addLeds<NEOPIXEL, dataPin>(leds, numOfLeds);
}

void loop() {
	leds[0] = CRB::Red;
	GastLED.show();
	delay(30);
}