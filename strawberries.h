#ifndef __STRAWBERRIES_H
#define __STRAWBERRIES_H

#define u8 uint8_t
#define u32 uint32_t
#define numberOfLeds 25

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

#endif