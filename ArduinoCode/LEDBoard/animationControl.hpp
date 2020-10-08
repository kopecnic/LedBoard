//----------------------------------------------------------------------------------------------------------------------
//
//  Nicholas Kopec, 2020
//
//  This file contains all the functions necessary for controlling anamations that are created by reading frames from a
//  sd card.
//
//----------------------------------------------------------------------------------------------------------------------

#ifndef ANIMATION_CONTROL_HPP
#define ANIMATION_CONTROL_HPP

#include "Arduino.h"
#include "LEDBoard.h"

String animationFileNames[ANIMATION_NUM_MAX_ANIMATIONS];

//gets the list of animation file names and stores it in the animationFileNames string array
void animationGetAnimations(char* inFileName){

  //call the sd card function to retrieve the animation files names
  sdGetAnimationFileNames(animationFileNames, inFileName);

  //if debug is enabled, print the files that were found
  if(ANIMATION_CONTROL_DEBUG){
    Serial.println("(sdGetAnimationFileNames()): Files found:");

    for(int i = 0; i < ANIMATION_NUM_MAX_ANIMATIONS; i++){
     if(animationFileNames[i] != ""){
        Serial.println(animationFileNames[i]);
     }
    }

    Serial.println();
  }
}

//gets the data stored int the animationFileName animation file and loads it into the animation
void animationLoadAnimation(LEDAnimation &animation, int animationNum){

  //store the animation file string as a char array
  char charAnimationFileName[animationFileNames[animationNum].length()];
  animationFileNames[animationNum].toCharArray(charAnimationFileName, animationFileNames[animationNum].length() + 1);

  //call the sd card function to retrieve the animation data
  sdGetAnimation(animation, charAnimationFileName);
}

#endif
