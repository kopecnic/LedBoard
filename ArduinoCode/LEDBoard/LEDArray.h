#ifndef LED_ARRAY_H
#define LED_ARRAY_H

#include "Arduino.h"
#include <FastLED.h>

/*TODO
  -add function to mix arrays (take a base array and a modifier array, where modifier array is 0 dont modify origional)
  -add function to dim whole array
  -add function to dim array with pixle by pixle control ((take a base array and a modifier array, where modifier array is 0 dont modify origional)
  -add new class for frame/animation
  -add new funcion to play animation
*/

//specify teensy type i.e. Teensy 3.6 = 36
#define TEENSY_VERSION 36

#define LED_CHIPSET NEOPIXEL //for Teensy 3.6
//#define LED_CHIPSET WS2812B //Teensy 4.x

//number of columns in the led array
#define LED_ARRAY_NUM_COLS 4

//number of rows int the led array
#define LED_ARRAY_NUM_ROWS 1

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


class LEDArray{

  public:

    //constructor
    LEDArray(int numCols, int numRows, int numPorts, int ledsPerPort);

    //destructor
    ~LEDArray();

    //public member functions
    void printInputArray();
    void printOutputArray();
    void initArray();
    void updateArray();
    void setSolidColor(CRGB color);
    void clearArray();

    //public member variables
    CRGB** ledInputArray;


  private:

    //private member functions
    void updateOutputArray_();

    //private member variables
    int numRows_;
    int numCols_;
    int numPorts_;
    int ledsPerPort_;
    int numLeds_;
    CRGB* ledOutputArray_;



};

class LEDAnimation{

public:

  //constructor
  LEDAnimation(int numRows, int numCols, int numFrames, int refreshRate);

  //destructor
  ~LEDAnimation();

  //public member functions
  void addPixle(int frameNum, int row, int col, CRGB data);
  int getNumFrames();
  int getRefreshRate();
  void printFrames();

  //public member variables

private:

  //private member functions

  //private member variables
  int numFrames_;
  int numRows_;
  int numCols_;
  int refreshRate_;
  CRGB*** frameArray_;

};



#endif
