//----------------------------------------------------------------------------------------------------------------------
//
//  Nicholas Kopec, 2020
//
//  This file contains all the functions necessary for controlling anamations that are created by reading frames from a
//  sd card.
//
//----------------------------------------------------------------------------------------------------------------------

#ifndef SYSTEM_CONTROL_HPP
#define SYSTEM_CONTROL_HPP

#include "Arduino.h"
#include "LEDBoard.h"

char animationInFileName[] = "aniName.txt";

LEDAnimation animation(LED_ARRAY_NUM_ROWS, LED_ARRAY_NUM_COLS, ANIMATION_NUM_MAX_FRAMES);

LEDArray ledArray(LED_ARRAY_NUM_COLS, LED_ARRAY_NUM_ROWS, NUM_DATA_PINS, LEDS_PER_DATA_PIN);

void systemInit(){

  //initialize the led array
  ledArrayInit(ledArray);

  //initialize communications with the sd card
  sdCardInit();

  //get animation file names
  animationGetAnimations(animationInFileName);

  animationLoadAnimation(animation, 0);
}

void modeControl(int mode){

  switch(mode){

    //off
    case 0:
      ledArray.clearArray();
      break;

    case 1:
      animationPlayAnimation(animation, ledArray, true);
      break;

    //off
    default:
      ledArray.clearArray();
      break;
  }
}

#endif
