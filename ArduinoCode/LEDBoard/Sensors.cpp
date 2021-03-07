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

PhotoResistor::PhotoResistor(int pinNum, int filterAlpha) {

  average_ = 0;
  pinNum_ = pinNum;
  reading_ = this->sample();
  filterAlpha_ = pow(2, -filterAlpha);
  average_ = reading_;

}

PhotoResistor::~PhotoResistor(){

}

void PhotoResistor::init(){

  pinMode(pinNum_, INPUT);
  this->sample();
}

uint16_t PhotoResistor::getReading(){

  return reading_;
}

uint16_t PhotoResistor::sample(){

  reading_ = analogRead(pinNum_);

  //y[n] = y[n-1] + a(x[n] - y[n-1])
  average_ = average_ + this->filterAlpha_ * (this->reading_ - this->average_);

  return reading_;
}

uint16_t PhotoResistor::getAverage()
{
	return average_;
}

void PhotoResistor::setFilterAlpha(int filterAlpha)
{
	this->filterAlpha_ = filterAlpha_ = pow(2, -filterAlpha);
}



MaxSonar::MaxSonar(int sensePinNum, int controlPinNum){

  sensePinNum_ = sensePinNum;
  controlPinNum_ = controlPinNum;

}

MaxSonar::~MaxSonar(){

}

void MaxSonar::init(){

  pinMode(sensePinNum_, INPUT);
  pinMode(controlPinNum_, OUTPUT);
  digitalWrite(controlPinNum_, LOW);
  this->sample();
}

uint16_t MaxSonar::getReadingIn(){

  return reading_;
}

uint16_t MaxSonar::sample(){

  digitalWrite(controlPinNum_, HIGH);
  delayMicroseconds(30);
  reading_ = analogRead(sensePinNum_);
  digitalWrite(controlPinNum_, LOW);
  reading_ *= 5;
  Serial.println(reading_);
  return reading_;
}


#endif
