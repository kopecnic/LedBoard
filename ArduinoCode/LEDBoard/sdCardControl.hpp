//----------------------------------------------------------------------------------------------------------------------
//
//  Nicholas Kopec, 2020
//
//  This file contains all the functions necessary for interfacing with the SD card
//
//----------------------------------------------------------------------------------------------------------------------

#ifndef SD_CARD_CONTROL_HPP
#define SD_CARD_CONTROL_HPP

#include "Arduino.h"
#include "LEDBoard.h"

//for SD card
#include <SD.h>
#include <SPI.h>

//for SD card
File inFile;
const int chipSelect = BUILTIN_SDCARD;

//begins communication with the SD card
void sdCardInit(){

  if(SD_DEBUG) Serial.println("(sdCardInit()): Initializing SD card...");

  //begin sd car communication
  if (!SD.begin(chipSelect)) {
    if(SD_DEBUG) Serial.println("(sdCardInit()): Initialization failed!");
    return;
  }

  if(SD_DEBUG) Serial.println("(sdCardInit()): Initialization done.");

  if(SD_DEBUG) Serial.println();

}

//retrieves all the animation file names from inFileName
void sdGetAnimationFileNames(String* animationFileNames, char* inFileName){

  //stores the line read from the sd card
  String buffer = "";

  //for storing position along the read line
  int linePos = 0;

  //stores number of frames present in the file
  int numAnimations = 0;

  //
  inFile = SD.open(inFileName);

  if(inFile){

    if(SD_DEBUG){
      Serial.print("(sdGetAnimationFileNames()): Opened ");
      Serial.println(inFileName);
    }

    //read numAnimations
    buffer = inFile.readStringUntil('\n');
    linePos = buffer.indexOf(":");
    numAnimations = buffer.substring(linePos + 1, buffer.length()).toInt();

    //read END_HEADER
    inFile.readStringUntil('\n');


    //store the found file names in the animationFileNames array
    for(int i = 0; i < numAnimations; i++){

      if(i < ANIMATION_NUM_MAX_ANIMATIONS){
        animationFileNames[i] = inFile.readStringUntil('\n');
      }
    }


  }

  else {

    // if the file didn't open, print an error:
    if(SD_DEBUG){
      Serial.print("(sdGetAnimationFileNames()): Error opening: ");
      Serial.println(inFileName);
    }
  }

  if(SD_DEBUG) Serial.println();

}

//reads an animation file from the sd card
void sdGetAnimation(LEDAnimation &animation, char* animationFileName){

  //stores the line read from the sd card
  String buffer = "";

  //for storing position along the read line
  int linePos = 0;

  //stores number of frames present in the file
  int numFrames = 0;

  //stores refresh rate specified by the file
  int refreshRate = 0;

  //stores number of rows present in the file
  int numRows = 0;

  //stores number of columns present in the file
  int numCols = 0;

  //open the input file
  inFile = SD.open(animationFileName);

  if (inFile) {

    if(SD_DEBUG){
      Serial.print("(sdGetAnimation()): Opened ");
      Serial.println(animationFileName);
    }

    //read numFrames
    buffer = inFile.readStringUntil('\n');
    linePos = buffer.indexOf(":");
    numFrames = buffer.substring(linePos + 1, buffer.length()).toInt();

    //read refreshRate
    buffer = inFile.readStringUntil('\n');
    linePos = buffer.indexOf(":");
    refreshRate = buffer.substring(linePos + 1, buffer.length()).toInt();

    //read numRows
    buffer = inFile.readStringUntil('\n');
    linePos = buffer.indexOf(":");
    numRows = buffer.substring(linePos + 1, buffer.length()).toInt();

    //read numCols
    buffer = inFile.readStringUntil('\n');
    linePos = buffer.indexOf(":");
    numCols = buffer.substring(linePos + 1, buffer.length()).toInt();

    //read END_HEADER
    inFile.readStringUntil('\n');

    if(SD_DEBUG){
      Serial.print("(sdGetAnimation()): numFrames:");
      Serial.println(numFrames);
      Serial.print("(sdGetAnimation()): refreshRate:");
      Serial.println(refreshRate);
      Serial.print("(sdGetAnimation()): numRows:");
      Serial.println(numRows);
      Serial.print("(sdGetAnimation()): numCols:");
      Serial.println(numCols);
    }

    //set the animation's refresh rate and number of frames to what was read in file
    animation.setRefreshRate(refreshRate);
    animation.setNumFrames(numFrames);

    //char input;
    //char inputBuff[8];

    //read each frame in the file pixle by pixle and store it in the animation's storage array
    for(int i = 0; i < numFrames; i++){

      //read frame number line
      Serial.println(inFile.readStringUntil('\n'));

      //read each row in the frame
      for(int j = 0; j < numRows; j++){

        // //store the read line into a buffer
        // buffer = inFile.readStringUntil('\n');

        for(int k = 0; k < numCols; k++){

            buffer = "";

            buffer = inFile.readStringUntil(',');

            // Serial.print(buffer);
            // Serial.print(" ");
              // buffer to store char array version of the pixle value
            char charBuffer[9];

            //store a pixle value in the char buffer
            buffer.toCharArray(charBuffer, 9);

            Serial.println(charBuffer);
            //Serial.print(" ");

            //add the pixle to the animation storage array
            animation.addPixle(i, j, k, strtol(charBuffer, NULL, 16));

        }

        inFile.read();
        inFile.read();

        // Serial.println(buffer);
        //
        // for(int k = 0; k < numCols; k++){
        //
        //   //find the end of one pixel entry
        //   linePos = buffer.indexOf(",");
        //
        //   //buffer to store char array version of the pixle value
        //   char charBuffer[linePos+1];
        //
        //   //store a pixle value in the char buffer
        //   buffer.substring(0, linePos).toCharArray(charBuffer, linePos+1);
        //
        //   //add the pixle to the animation storage array
        //   animation.addPixle(i, j, k, strtol(charBuffer, NULL, 16));
        //
        //   //remove the pixle from the line buffer
        //   buffer = buffer.substring(linePos + 1, buffer.length());
        // }
        }
    }

    // close the file:
    inFile.close();
  }

  else {
    // if the file didn't open, print an error:
    if(SD_DEBUG){
      Serial.print("(sdGetAnimation()): Error opening: ");
      Serial.println(animationFileName);
    }
  }

  if(SD_DEBUG) Serial.println();

}

#endif
