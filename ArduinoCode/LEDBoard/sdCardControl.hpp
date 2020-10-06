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
    if(SD_DEBUG) Serial.println("initialization failed!");
    return;
  }
  if(SD_DEBUG) Serial.println("initialization done.");

}

void sdCardTest(LEDAnimation &animation){

  if(SD_DEBUG) Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  String buffer = "";
  int linePos = 0;
  int numFrames = 0;
  int refreshRate = 0;
  int numRows = 0;
  int numCols = 0;

  inFile = SD.open("Test.txt");
  if (inFile) {

    Serial.println("Input.txt");

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

    Serial.print("numFrames:");
    Serial.println(numFrames);
    Serial.print("refreshRate:");
    Serial.println(refreshRate);
    Serial.print("numRows:");
    Serial.println(numRows);
    Serial.print("numCols:");
    Serial.println(numCols);

    animation.setRefreshRate(refreshRate);
    animation.setNumFrames(numFrames);

    for(int i = 0; i < numFrames; i++){
      //read frame number line
      inFile.readStringUntil('\n');
      for(int j = 0; j < numRows; j++){
        buffer = inFile.readStringUntil('\n');
        for(int k = 0; k < numCols; k++){
          linePos = buffer.indexOf(",");
          char charBuffer[linePos+1];
          buffer.substring(0, linePos).toCharArray(charBuffer, linePos+1);
          animation.addPixle(i, j, k, strtol(charBuffer, NULL, 16));
          buffer = buffer.substring(linePos + 1, buffer.length());
        }
      }
    }

    // close the file:
    inFile.close();
  }
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening Input.txt");
  }


}

#endif
