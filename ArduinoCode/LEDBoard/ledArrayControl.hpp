//----------------------------------------------------------------------------------------------------------------------
//
//  Nicholas Kopec, 2020
//
//  This file contains all the functions necessary for controlling the led array
//
//----------------------------------------------------------------------------------------------------------------------


#ifndef LED_ARRAY_CONTROL_HPP
#define LED_ARRAY_CONTROL_HPP

#include "Arduino.h"
#include "LEDBoard.h"
#include "LEDArray.h"


LEDArray ledArray(LED_ARRAY_NUM_COLS, LED_ARRAY_NUM_ROWS, NUM_DATA_PINS, LEDS_PER_DATA_PIN);

//initializes led array
void ledArrayInit(){

  ledArray.initArray();

}

void ledArrayPlayAnimation(LEDAnimation &animation){

}


#endif
