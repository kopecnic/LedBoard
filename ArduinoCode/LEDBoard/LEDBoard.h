#ifndef LED_BOARD_H
#define LED_BOARD_H

/*
TODO
-modify sdGetAnimation() to accept a file name input
-add function to read file containing names of each animation
*/

#include <SimpleTimer.h>

//--------------------------------------------------------------------------------------
//Debug Enables
//--------------------------------------------------------------------------------------

//when enabled, program will wait for serial connection to begin
#define WAIT_FOR_SERIAL 1

//when enabled, program with print SD debug messages to serial
#define SD_DEBUG 1

#define ANIMATION_CONTROL_DEBUG 1

//--------------------------------------------------------------------------------------
//General Defines
//--------------------------------------------------------------------------------------

//number of columns in the led array
#define LED_ARRAY_NUM_COLS 4

//number of rows int the led array
#define LED_ARRAY_NUM_ROWS 2

//number of total leds in the array
#define LED_ARRAY_NUM_LEDS 8

//--------------------------------------------------------------------------------------
//LEDArray Defines
//--------------------------------------------------------------------------------------

//specify teensy type i.e. Teensy 3.6 = 36
#define TEENSY_VERSION 36

#define LED_CHIPSET NEOPIXEL //for Teensy 3.6
//#define LED_CHIPSET WS2812B //Teensy 4.x

/*
 *  If you are using the first set of pins with N number of data pins, you must select the first pin you are using
 *  and then use the next N pins in that set
 *
 *  First: 1,0,24,25,19,18,14,15,17,16,22,23,20,21,26,27
 *  Second: 10,12,11,13,6,9,32,8,7
 *  Third: 37, 36, 35, 34, 39, 38, 28, 31, 30
*/

//pin number of the first data pin used
#define DATA_PINS_STARTING_NUM 1

//number of ports being used on the microcontroller
#define NUM_DATA_PINS 1

//number of leds that are attatched to each port
#define LEDS_PER_DATA_PIN 4

//--------------------------------------------------------------------------------------
//Animation Control Defines
//--------------------------------------------------------------------------------------

//number of frames in the largest animation
#define ANIMATION_NUM_MAX_FRAMES 10

//max number of animation files
#define ANIMATION_NUM_MAX_ANIMATIONS 10

//--------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------



#endif
