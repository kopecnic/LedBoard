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

#define SD_DEBUG 1

//for SD card
#include <SD.h>
#include <SPI.h>

//for SD card
File inFile;
const int chipSelect = BUILTIN_SDCARD;

void sdCardInit(){

  if(SD_DEBUG) Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

}

void sdCardTest(){

  if(SD_DEBUG) Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  inFile = SD.open("Test.txt");
  if (inFile) {

    Serial.println("Input.txt");

    String buffer = "";
    int pos = 0;
    int numFrames = 0;
    int refreshRate = 0;
    int numRows = 0;
    int numCols = 0;
    int frameNum = 0;

    while (inFile.available()) {

      buffer = inFile.readStringUntil('\n');

      if(buffer == "END_HEADER"){break;}

      pos = buffer.indexOf(":");

      if(pos == -1){break;}

      if(buffer.substring(0, pos) == "numFrames"){
        numFrames = buffer.substring(pos + 1, buffer.length()).toInt();
      }
      else if(buffer.substring(0, pos) == "refreshRate"){
        refreshRate = buffer.substring(pos + 1, buffer.length()).toInt();
      }
      else if(buffer.substring(0, pos) == "numRows"){
        numRows = buffer.substring(pos + 1, buffer.length()).toInt();
      }
      else if(buffer.substring(0, pos) == "numCols"){
        numCols = buffer.substring(pos + 1, buffer.length()).toInt();
      }

      Serial.print("numFrames:");
      Serial.println(numFrames);
      Serial.print("refreshRate:");
      Serial.println(refreshRate);
      Serial.print("numRows:");
      Serial.println(numRows);
      Serial.print("numCols:");
      Serial.println(numCols);


    }

    while (inFile.available()) {

      buffer = inFile.readStringUntil('\n');

      if(buffer.indexOf("frame:") == 0){
          frameNum = buffer.substring(pos + 1, buffer.length()).toInt();
      }
      for(int i = 0; i < numRows; i++){
        //add in code to get values from file for leds
      }


    }

    // close the file:
    inFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening Input.txt");
  }


}

#endif
