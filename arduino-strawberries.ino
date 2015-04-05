#include "Adafruit_WS2801.h"
#include "SPI.h" // Comment out this line if using Trinket or Gemma
#ifdef __AVR_ATtiny85__
 #include <avr/power.h>
#endif

#define u8 uint8_t
#define u32 uint32_t

// BE SURE TO CHECK YOUR PIXELS TO SEE WHICH WIRES TO USE!
uint8_t dataPin  = 2;    // Yellow wire on Adafruit Pixels
uint8_t clockPin = 3;    // Green wire on Adafruit Pixels
uint8_t numberOfLeds = 50;

Adafruit_WS2801 strip = Adafruit_WS2801(numberOfLeds, dataPin, clockPin);

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

//HSLtoRGB from http://www.alexkuhl.org/code/#colorspace
struct RGB hslToRgb( struct HSL hsl){
	float h, s, l;
	int r, g, b;
	h = fmod(hsl.h, 360);
	s = hsl.s;
	l = hsl.l;
	float q ;
	if( l < .5 )
		q = l*( 1 + s ) ;
	else
		q = l + s - ( l*s ) ;
	float p = 2*l - q ;
	h /= 360 ;
	// t holds r, g, and b values
	float t[ 3 ] = { h + 1/3.0, h, h - 1/3.0 } ;
	for( int i = 0 ; i < 3 ; ++i )
	{
		if( t[ i ] < 0 )
			t[ i ] += 1 ;
		else if( t[ i ] > 1 )
			t[ i ] -= 1 ;
		// calculate the color
		if( t[ i ] < 1.0/6.0 )
			t[ i ] = p + ( ( q - p )*6*t[ i ] ) ;
		else if( 1.0/6.0 <= t[ i ] && t[ i ] < .5 )
			t[ i ] = q ;
		else if( .5 <= t[ i ] && t[ i ] < 2.0/3.0 )
			t[ i ] = p + ( ( q - p )*6*( 2.0/3.0 - t[ i ] ) ) ;
		else
			t[ i ] = p ;
	}	
	r = round( t[ 0 ]*255 ) ;
	g = round( t[ 1 ]*255 ) ;
	b = round( t[ 2 ]*255 ) ;
	RGB rgb;
	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return rgb;
}


//wipes the whole spectrum from a starting hsl
void rainbowWipe(struct HSL hsl, uint8_t wait){
	int i;
	float shift;
	RGB rgb;
	shift = 255 / numberOfLeds;
	for (i=0; i < numberOfLeds; i++){
		hsl.h = hsl.h + shift;
		rgb = hslToRgb(hsl);
		strip.setPixelColor(i, rgb.packed);
		strip.show();
		delay(wait);
	}
	strip.show();
}

//displays a single hsl color
void oneColor (struct HSL hsl){
	int i;
	RGB rgb;
	rgb = hslToRgb(hsl);
	for (i = 0; i < numberOfLeds; i++) {
		strip.setPixelColor(i, rgb.packed);
	}
	strip.show();
}

//wipes a single hsl color
void wipeColor (struct HSL hsl, uint8_t wait){
	int i;
	RGB rgb;
	rgb = hslToRgb(hsl);
	for (i=0; i < numberOfLeds; i++){
		strip.setPixelColor(i, rgb.packed);
		strip.show();
		delay(wait);
	}
}

//drips a single colour
// todo: add luminence tail off for drip - add to dripfill too
void drip (struct HSL hsl, int wait){
	int i;
	RGB rgb;
	rgb = hslToRgb(hsl);
		for (i=0; i < numberOfLeds; i++){
		strip.setPixelColor(i, rgb.packed);
		if (i > 0){
			strip.setPixelColor(i-1, 0);
		};
		strip.show();
		delay(wait);
	}
	
}

void drip2 (struct HSL hsl, int wait, int duration){
	int i;
	RGB rgb;
	HSL hsl2;
	int led;

		for (i=0; i < duration; i++){
			led = i % numberOfLeds;
			rgb = hslToRgb(hsl);
			strip.setPixelColor(led, rgb.packed);
			strip.show();
			delay(wait/5);
			hsl2.l = hsl.l /2;
			rgb = hslToRgb(hsl2);
			led = (i-1) % numberOfLeds;
			strip.setPixelColor(led, rgb.packed);
			strip.show();
			delay(wait/5);
			hsl2.l = hsl2.l /2;
			rgb = hslToRgb(hsl2);
						led = (i-2) % numberOfLeds;
			strip.setPixelColor(led, rgb.packed);
			strip.show();
			delay(wait/5);
			hsl2.l = hsl2.l /2;
			rgb = hslToRgb(hsl2);
						led = (i-3) % numberOfLeds;
			strip.setPixelColor(led, rgb.packed);
			strip.show();
			delay(wait/5);
			hsl2.l = 0;
			rgb = hslToRgb(hsl2);
						led = (i-4) % numberOfLeds;
			strip.setPixelColor(led, rgb.packed );
			strip.show();
			
			delay(wait/5);
		}
	/*
		strip.setPixelColor(5, rgb.packed);
	hsl.l = 0.01;
	hsl.s = 0.5;
	rgb = hslToRgb(hsl);
	strip.setPixelColor(6, rgb.packed);
	strip.show();
		strip.setPixelColor(7, rgb.packed);
	hsl.l = 0.01;
	hsl.s = 0.01;
	rgb = hslToRgb(hsl);
	strip.setPixelColor(8, rgb.packed);
	strip.show();
		hsl.l = 0.003;
	hsl.s = 0.003;
	rgb = hslToRgb(hsl);
	strip.setPixelColor(9, rgb.packed);
	strip.show();
*/
}



//fixed version of drip for use in dripFill
void dripForFill (struct HSL hsl, int wait, int fill){
	int i;
	RGB rgb;
	rgb = hslToRgb(hsl);
		for (i=0; i < numberOfLeds - fill; i++){
		strip.setPixelColor(i, rgb.packed);
		if (i > 0){
			strip.setPixelColor(i-1, 0);
		};
		strip.show();
		delay(wait);
	}
	
}

//drips single led and slowly fills from bottom
void dripFill (struct HSL hsl, int wait){
	int i;
	RGB rgb;
	rgb = hslToRgb(hsl);
	for (i=0; i < numberOfLeds; i++){
		dripForFill(hsl, wait, i);
		int i2;
		for (i2=0; i2 < i; i2++){
			strip.setPixelColor(numberOfLeds-i2, rgb.packed);
		}
	}
}

//rainbow sweep
void rainbowSweep(int duration, int wait){
	int i;
	RGB rgb;
	HSL hsl;
	HSL hsl2;
	hsl.h = 1;
	hsl.l = 0.1;
	hsl.s = 1;
		int offset;
		int speed;
		int i2;
		int led;
		offset = 10; //experiment with this, difference in hue between consecutive LEDs

	for (i=0; i < duration; i++) {


		for (i2 = 0; i2 < numberOfLeds; i2++){
			rgb = hslToRgb(hsl2);
			strip.setPixelColor(i2, rgb.packed);
			hsl2.h = hsl2.h + offset;
		}
		strip.show();
		hsl.h = hsl.h + offset;
		hsl2 = hsl;
		delay (wait);
	}
}

//untested - still being written - brightness wipe which moves
void brightnessWipe(struct HSL hsl, int duration, int shift){
	int i;
	int i2;
	RGB rgb;
	hsl.l = 0;
	shift = 0;
	for (i2=0; i2 < duration; i2++){
		shift = shift + 1;
		for (i=shift; i < numberOfLeds; i++){
			float shift;
			shift = 100 / numberOfLeds;
			rgb  = hslToRgb(hsl);
			strip.setPixelColor(i, rgb.packed);
			hsl.l = hsl.l + shift;
		}
	strip.show();
	}
}

//to implement
//Wipe through offset hsl.l covers

void setup() {

  strip.begin();

  // Update LED contents, to start they are all 'off'
  strip.show();
};

void loop() {


	HSL hsl;
	RGB rgb;
	hsl.h = 280;
	hsl.s = 1;
	hsl.l = 0.5;
	rgb  = hslToRgb(hsl);
	//dripFill(hsl, 10);
	//rainbowSweep(1000,50);
	drip2(hsl,200, 1000);
	

	
};