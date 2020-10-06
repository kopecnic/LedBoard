//----------------------------------------------------------------------------------------------------------------------
//
//  Nicholas Kopec, 2020
//
//  This file contains all the functions necessary for controlling anamations that are created by reading frames from a
//  sd card.
//
//----------------------------------------------------------------------------------------------------------------------

#ifndef ANIMATION_CONTROL_HPP
#define ANIMATION_CONTROL_HPP

#define MAX_NUM_FRAMES 4

#include "Arduino.h"
#include "LEDBoard.h"

LEDAnimation animation(LED_ARRAY_NUM_ROWS, LED_ARRAY_NUM_COLS, MAX_NUM_FRAMES);

void loadAnimation(){

  sdCardTest(animation);
  animation.printFrames();
}


#endif
