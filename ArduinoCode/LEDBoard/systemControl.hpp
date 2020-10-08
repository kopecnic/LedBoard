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

//name of the file to read the animation file names
char animationInFileName[] = "aniName.txt";

//stores all the data relative to a animation
LEDAnimation animation(LED_ARRAY_NUM_ROWS, LED_ARRAY_NUM_COLS, ANIMATION_NUM_MAX_FRAMES);

//stores all the data relative to the led array
LEDArray ledArray(LED_ARRAY_NUM_COLS, LED_ARRAY_NUM_ROWS, NUM_DATA_PINS, LEDS_PER_DATA_PIN);


//initialize all components on the system
void systemInit(){

  //initialize the led array
  ledArrayInit(ledArray);

  //initialize communications with the sd card
  sdCardInit();

  //get animation file names
  animationGetAnimations(animationInFileName);

  animationLoadAnimation(animation, 0);

  animation.setBrightness(100);
}



//determine what mode to run in
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
