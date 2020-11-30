//----------------------------------------------------------------------------------------------------------------------
//
//  Nicholas Kopec, 2020
//
//  This file contains all the functions necessary for controlling anamations that are created by reading frames from a
//  sd card.
//
//----------------------------------------------------------------------------------------------------------------------

#ifndef SENSOR_CONTROL_HPP
#define SENSOR_CONTROL_HPP

#include "Arduino.h"
#include "Sensors.h"

SwitchInput switch0(39);
SwitchInput switch1(38);
SwitchInput switch2(37);
SwitchInput switch3(36);
SwitchInput switch4(35);
SwitchInput switch5(34);
SwitchInput switch6(33);

Microphone mic0(A9);
Microphone mic1(A8);

PhotoResistor photoRes(A7);

void sensorsInit(){

  switch0.init();
  switch1.init();
  switch2.init();
  switch3.init();
  switch4.init();
  switch5.init();
  switch6.init();

  mic0.init();
  mic1.init();

  photoRes.init();
}

void sampleSwitches(){
  switch0.sample();
  switch1.sample();
  switch2.sample();
  switch3.sample();
  switch4.sample();
  switch5.sample();
  switch6.sample();

  if(SWITCH_DEBUG){

    Serial.println();
    Serial.print("(sampleSwitches) Switch0: ");
    Serial.println(switch0.getState());
    Serial.print("(sampleSwitches) Switch1: ");
    Serial.println(switch1.getState());
    Serial.print("(sampleSwitches) Switch2: ");
    Serial.println(switch2.getState());
    Serial.print("(sampleSwitches) Switch3: ");
    Serial.println(switch3.getState());
    Serial.print("(sampleSwitches) Switch4: ");
    Serial.println(switch4.getState());
    Serial.print("(sampleSwitches) Switch5: ");
    Serial.println(switch5.getState());
    Serial.print("(sampleSwitches) Switch6: ");
    Serial.println(switch6.getState());
    Serial.println();

  }
}

void sampleMics(){

  mic0.sample();
  mic1.sample();

  if(MIC_DEBUG){
    Serial.println();
    Serial.print("(sampleMics) mic0: ");
    Serial.println(mic0.getReading());
    Serial.print("(sampleMics) mic1: ");
    Serial.println(mic1.getReading());
    Serial.println();
  }

}

void samplePhotoRes(){

  photoRes.sample();


  if(PHOTORES_DEBUG){
    Serial.println();
    Serial.print("(samplePhotoRes) photoRes: ");
    Serial.println(photoRes.getReading());
    Serial.println();
  }

}


#endif
