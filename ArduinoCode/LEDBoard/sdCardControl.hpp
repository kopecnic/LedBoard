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

  if(SD_DEBUG) Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    if(SD_DEBUG) Serial.println("initialization failed!");
    return;
  }

  if(SD_DEBUG) Serial.println("initialization done.");

}

//reads an animation file from the sd card
void sdGetAnimation(LEDAnimation &animation){

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
  inFile = SD.open("Test.txt");
  if (inFile) {

    if(SD_DEBUG) Serial.println("Input.txt");

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
      Serial.print("numFrames:");
      Serial.println(numFrames);
      Serial.print("refreshRate:");
      Serial.println(refreshRate);
      Serial.print("numRows:");
      Serial.println(numRows);
      Serial.print("numCols:");
      Serial.println(numCols);
    }

    //set the animation's refresh rate and number of frames to what was read in file
    animation.setRefreshRate(refreshRate);
    animation.setNumFrames(numFrames);

    //read each frame in the file pixle by pixle and store it in the animation's storage array
    for(int i = 0; i < numFrames; i++){

      //read frame number line
      inFile.readStringUntil('\n');

      //read each row in the frame
      for(int j = 0; j < numRows; j++){

        //store the read line into a buffer
        buffer = inFile.readStringUntil('\n');

        for(int k = 0; k < numCols; k++){

          //find the end of one pixel entry
          linePos = buffer.indexOf(",");

          //buffer to store char array version of the pixle value
          char charBuffer[linePos+1];

          //store a pixle value in the char buffer
          buffer.substring(0, linePos).toCharArray(charBuffer, linePos+1);

          //add the pixle to the animation storage array
          animation.addPixle(i, j, k, strtol(charBuffer, NULL, 16));

          //remove the pixle from the line buffer
          buffer = buffer.substring(linePos + 1, buffer.length());
        }
      }
    }

    // close the file:
    inFile.close();
  }

  else {
    // if the file didn't open, print an error:
    if(SD_DEBUG) Serial.println("error opening Input.txt");
  }
  
}

#endif
