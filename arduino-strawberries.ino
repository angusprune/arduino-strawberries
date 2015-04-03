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
	rgb = hslTopRgb(hsl);
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
	for (i=0; i < numberofLeds; i++){
		strip.setPixelColor(i, rgb.packed);
		strip.show();
		delay(waait);
	}
}

//drips a single colour
//UNTESTED
void drip (struct HSL hsl){
	int i;
	RGB rgb;
	rgb = hslToRgb(hsl);
		for (i=0; i < numberofLeds; i++){
		Strip.setPixelColor(i, rgb.packed)
		if (i > 0){
			Strip.setPixelColor(i-1, 0);
		};
	}
	
}

//UNTESTED
void dripFill (struct HSL hsl){
	int i;
	RGB rgb;
	rgb = hslToRgb(hsl);
	for (i=0; i < numberofLeds; i++){
		drip(hsl);
		int i2;
		for (i2=0; i2 < i; i2++){
			Strip.setPixelColor(numberOfLeds-i2, rgb.packed);
		}
	}
}

//untested
void raindowSweep(int duration){
	int i;
	RGB rgb;
	HSL hsl;
	hsl.h = 1;
	hsl.l = 0.1;
	hsl.l = 1;
	for (i=0; i < duration; i++) {
		int offset;
		int speed;
		offset = 20; //experiment with this, difference in hue between consecutive LEDs
		int i2;
		for (i2=0; i2 < numberOfLeds; i2++){
			rgb = hslToRgb(hsl);
			strip.setPixelColor(i, rgb.packed);
			hsl.h = hsl.h + offset;
		}
		strip.show();
		hsl.h = hsl.h + offset;
		delay (wait);
	}
}
//untested - still being written - brightness wipe which moves
void brightnessWipe(struct HSL hsl, int duration){
	int i;
	int i2;
	RGB rgb;
	hsl.l = 0;
	shift = 0;
	for (i2=0; i2 < duration; i2++){
		shift = shift + 1;
		for (i=shift; i < numberofLeds; i++){
			float shift;
			shift = 100 / numberOfLeds;
			rgb  = hslToRgb(hsl);
			strip.setPixelColor(i, rgb.packed);
			hsl.l = hsl.l + shift;
		}
	strip.show();
	}
}


void setup() {

  strip.begin();

  // Update LED contents, to start they are all 'off'
  strip.show();
};

void loop() {


	HSL hsl;
	RGB rgb;
	hsl.h = 57;
	hsl.s = 1;
	hsl.l = 0.1;
	int i;
	for (i=0; i < 100; i++){
		hsl.h = (hsl.h + 30);
		rainbowWipe(hsl, 10);
	}

	
};