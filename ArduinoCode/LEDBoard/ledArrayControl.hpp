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

uint32_t prevTime = 0;


void ledArrayInit(){

/*
  for(int i = 0; i < LED_ARRAY_NUM_ROWS; i++){
    for(int j = 0; j < LED_ARRAY_NUM_COLS; j++){
        ledArray.ledInputArray[i][j] = CRGB::Black;
    }
  }
*/

  prevTime = micros();
  ledArray.initArray();
  Serial.println(micros()-prevTime);

}


#endif
