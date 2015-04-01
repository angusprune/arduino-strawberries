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





//other stuff
void colorWipe(u8 c, uint8_t wait) {
  int i;
 
  for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

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


void oneColor (uint32_t rgb){
	int i;
	for (i = 0; i < numberOfLeds; i++) {
		strip.setPixelColor(i, rgb);
	}
	strip.show();
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
		hsl.h = (hsl.h + 100);
		rainbowWipe(hsl, 10);
	}

	
};