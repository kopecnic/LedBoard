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

#include "Arduino.h"
#include "LEDBoard.h"

LEDAnimation animation(LED_ARRAY_NUM_ROWS, LED_ARRAY_NUM_COLS, ANIMATION_NUM_MAX_FRAMES);

//for testing rn; reads animation file into animation class and prints the contents
void loadAnimation(){

  sdGetAnimation(animation);
  animation.printFrames();
}


#endif
