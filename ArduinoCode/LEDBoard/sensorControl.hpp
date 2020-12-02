//----------------------------------------------------------------------------------------------------------------------
//
//  Nicholas Kopec, 2020
//
//  This file contains all the functions necessary for controlling the sensors connected to the control board
//
//----------------------------------------------------------------------------------------------------------------------

#ifndef SENSOR_CONTROL_HPP
#define SENSOR_CONTROL_HPP

#include "Arduino.h"
#include "Sensors.h"

//all the switch inputs
SwitchInput switch0(39);
SwitchInput switch1(38);
SwitchInput switch2(37);
SwitchInput switch3(36);
SwitchInput switch4(35);
SwitchInput switch5(34);
SwitchInput switch6(33);

//the micropohones
Microphone mic0(A9);
Microphone mic1(A8);

//the photoresistor
PhotoResistor photoRes(A7);

//the sonar sensors
MaxSonar distance0(A13, 29);
MaxSonar distance1(A12, 28);


//initializes all the sensors by calling their init functions
void sensorsInit(){

  //initialize the switches
  switch0.init();
  switch1.init();
  switch2.init();
  switch3.init();
  switch4.init();
  switch5.init();
  switch6.init();

  //initialize the mics
  mic0.init();
  mic1.init();

  //initialize the photoresistor
  photoRes.init();

  //initialize the distance sensors
  distance0.init();
  distance1.init();

}

//samples all the switches and prints their state if the debug is enabled
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

//samples the mics and prints their readings if the debug is enabled
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

//samples the photoRes and prints its reading if the debug is enabled
void samplePhotoRes(){

  photoRes.sample();


  if(PHOTORES_DEBUG){
    Serial.println();
    Serial.print("(samplePhotoRes) photoRes: ");
    Serial.println(photoRes.getReading());
    Serial.println();
  }

}

//samples the distance sensors and prints their readings if the debug is enabled
void sampleDistances(){

  distance0.sample();
  distance1.sample();


  if(DISTANCE_DEBUG){
    Serial.println();
    Serial.print("(sampleDistances) distance0: ");
    Serial.println(distance0.getReadingIn());
    Serial.print("(sampleDistances) distance1: ");
    Serial.println(distance1.getReadingIn());
    Serial.println();
  }

}


#endif
