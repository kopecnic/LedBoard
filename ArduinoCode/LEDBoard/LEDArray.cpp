#ifndef LED_ARRAY_CPP
#define LED_ARRAY_CPP

#include "Arduino.h"
#include "LEDArray.h"


//creates a LED array object and allocates memory for its arrays
LEDArray::LEDArray(int numCols, int numRows, int numPorts, int ledsPerPort){

  numRows_ = numRows;
  numCols_ = numCols;
  numPorts_ = numPorts;
  ledsPerPort_ = ledsPerPort;
  numLeds_ = numRows_ * numCols_;

  ledInputArray = new CRGB* [numRows_];
  for(int i = 0; i < numRows_; i++){
    ledInputArray[i] = new CRGB[numCols_];
  }

  ledOutputArray_ = new CRGB [numPorts_];

}



//deletes the allocated memory for its arrays
LEDArray::~LEDArray(){
  for(int i = 0; i < numRows_; i++){
    delete ledInputArray[i];
  }
  delete ledInputArray;
  ledInputArray = NULL;

  delete ledOutputArray_;
  ledOutputArray_ = NULL;
}



//prints the contents of the input array to serial
void LEDArray::printInputArray(){
  for(int i = 0; i < numRows_; i++){
    for(int j = 0; j < numCols_; j++){
      Serial.print(ledInputArray[i][j], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}



//prints the contencts of the output array to serial
void LEDArray::printOutputArray(){

  for(int i = 0; i < numPorts_ * ledsPerPort_; i++){
      Serial.print(ledOutputArray_[i], HEX);
      Serial.print(" ");
  }
  Serial.println();
}



//sets the the FastLED library depending on what uC is being used and initializes all leds to be off
void LEDArray::initArray(){

  #if (TEENSY_VERSION == 36)

      FastLED.addLeds<LED_CHIPSET,DATA_PINS_STARTING_NUM>(ledOutputArray_, numLeds_);

  #endif


  #if (TEENSY_VERSION == 40) || (TEENSY_VERSION == 41)

      FastLED.addLeds<NUM_DATA_PINS,LED_CHIPSET,DATA_PINS_STARTING_NUM,GRB>(ledOutputArray_, ledsPerPort_);

  #endif

  this->clearArray();
  this->updateArray();
  FastLED.show();
}



//updates the output array using the input array and updates the leds
void LEDArray::updateArray(){
  this->updateOutputArray_();
  FastLED.show();
}



//sets all leds to a specific color
void LEDArray::setSolidColor(CRGB color){
  for(int i = 0; i < numRows_; i++){
    for(int j = 0; j < numCols_; j++){
      ledInputArray[i][j] = color;
    }
  }
}



//turns off all leds
void LEDArray::clearArray(){
  for(int i = 0; i < numRows_; i++){
    for(int j = 0; j < numCols_; j++){
      ledInputArray[i][j] = CRGB::Black;
    }
  }
}



//updates the output array from the input array
void LEDArray::updateOutputArray_(){

 int pos;

  for(int i = 0; i < numRows_; i++){
    for(int j = 0; j < numCols_; j++){
      pos = (i * numCols_) + j;
      ledOutputArray_[pos] = ledInputArray[i][j];
    }
  }
}

#endif
