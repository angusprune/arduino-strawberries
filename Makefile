%.o: %.c
	g++ -DDEBUG -o $@ -I /cygdrive/c/Users/James/AppData/Roaming/Arduino15/packages/arduino/hardware/avr/1.6.2/cores/arduino -I /cygdrive/c/Users/James/AppData/Roaming/Arduino15/packages/arduino/hardware/avr/1.6.2/variants/standard -I /cygdrive/c/Users/James/Documents/GitHub/libraries/Adafruit-WS2801-Library -I /cygdrive/c/Users/James/Documents/GitHub/Adafruit-WS2801-Library -I /cygdrive/c/Users/James/AppData/Roaming/Arduino15/packages/arduino -I /cygdrive/c/Users/James/AppData/Roaming/Arduino15/packages/arduino/hardware/avr/1.6.2/libraries/SPI/ -I /cygdrive/c/Users/James/Documents/Arduino/libraries $<

strawberries: arduino-strawberries.o

