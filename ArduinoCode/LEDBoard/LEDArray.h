#ifndef LED_ARRAY_H
#define LED_ARRAY_H

#include "Arduino.h"
#include "LEDBoard.h"
#include <FastLED.h>

/*TODO
  -add function to mix arrays (take a base array and a modifier array, where modifier array is 0 dont modify origional)
  -add function to dim whole array
  -add function to dim array with pixle by pixle control ((take a base array and a modifier array, where modifier array is 0 dont modify origional)
  -add new funcion to play animation
*/

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
    CRGB ledInputArray[LED_ARRAY_NUM_ROWS][LED_ARRAY_NUM_COLS];


  private:

    //private member functions
    void updateOutputArray_();

    //private member variables
    int numRows_;
    int numCols_;
    int numPorts_;
    int ledsPerPort_;
    int numLeds_;
    CRGB ledOutputArray_[LED_ARRAY_NUM_LEDS];



};

class LEDAnimation{

public:

  //constructor
  LEDAnimation(int numRows, int numCols, int numMaxFrames);

  //destructor
  ~LEDAnimation();

  //public member functions
  void addPixle(int frameNum, int row, int col, CRGB data);
  CRGB getPixle(int frameNum, int row, int col);
  int getNumFrames();
  int advanceFrame();
  int getRefreshRate();
  void setRefreshRate(int refreshRate);
  void setNumFrames(int numFrames);
  void addFrame();
  void printFrames();

  //public member variables

private:

  //private member functions

  //private member variables
  int numFrames_;
  int currentFrame_;
  int numMaxFrames_;
  int numRows_;
  int numCols_;
  int refreshRate_;
  CRGB frameArray_[ANIMATION_NUM_MAX_FRAMES][LED_ARRAY_NUM_ROWS][LED_ARRAY_NUM_COLS];


};



#endif
