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

//initializes led array
void ledArrayInit(LEDArray &ledArray){

  ledArray.initArray();

}

#endif
