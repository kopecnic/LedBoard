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

EasyTimer animationTimer(1000);



void initAnimations(){

}



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

  //print the contents of the animation if debug is enabled
  if(ANIMATION_CONTROL_DEBUG) animation.printFrames();
}



//display the currently loaded animation, should be called as fast as possible as it has a timer to limit the refresh rate
void animationPlayAnimation(LEDAnimation &animation, LEDArray &ledArray, bool updateArray){

  //set the timers refresh rate to the current refresh rate of the animation
  animationTimer.set_delay_millis(animation.getRefreshRate());

  //if it is time to refresh the display, refresh it
  if(animationTimer.isup()){

    //get the current frame to display, and advance the frame
    int currentFrame = animation.advanceFrame();

    //if debug is enabled, print what frame is currently being displayed
    if(ANIMATION_CONTROL_DEBUG){
      Serial.print("(animationPlayAnimation()): Currently displaying frame:");
      Serial.println(currentFrame);
    }

    //update the led array input array with the frame data
    for(int i = 0; i < LED_ARRAY_NUM_ROWS; i++){
      for(int j = 0; j < LED_ARRAY_NUM_COLS; j++){
        ledArray.ledInputArray[i][j] = animation.getPixle(currentFrame, i, j);
      }
    }

    //update the led array
    if(updateArray) ledArray.updateArray();
  }
}


#endif
