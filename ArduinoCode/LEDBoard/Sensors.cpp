#ifndef SENSORS_CPP
#define SENSORS_CPP

#include "Arduino.h"
#include "Sensors.h"

SwitchInput::SwitchInput(int pinNum){

  pinNum_ = pinNum;

}

SwitchInput::~SwitchInput(){

}

void SwitchInput::init(){

  pinMode(pinNum_, INPUT_PULLUP);
  this->sample();

}

bool SwitchInput::sample(){

  state_ = !digitalRead(pinNum_);
  return state_;
}

bool SwitchInput::getState(){

  return state_;
}



Microphone::Microphone(int pinNum){

  pinNum_ = pinNum;

}

Microphone::~Microphone(){

}

void Microphone::init(){

  pinMode(pinNum_, INPUT);
  this->sample();
}

uint16_t Microphone::getReading(){

  return reading_;
}

uint16_t Microphone::sample(){

  reading_ = analogRead(pinNum_);
  return reading_;
}


#endif
