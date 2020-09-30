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

#define SD_DEBUG 0


void sdCardInit(){

  if(SD_DEBUG 0) Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  inFile = SD.open("Input.txt");
  if (inFile) {

    Serial.println("Input.txt");
    char data[8];
    int frameNum = 0;
    // read from the file until there's nothing else in it:
    while (inFile.available()) {
      inFile.read(data, 3);
      //frameNum = strtol(data, NULL, 10);
      Serial.println(frameNum);

      for(int pixle = 0; pixle < NUM_LEDS; pixle++){

        inFile.read(data, 8);
        Serial.write(data, 8);
        Serial.println();
        ledBuff[frameNum][pixle] = strtol(data, NULL, 16);
        ledBuff[frameNum][pixle] %= 5;
        inFile.read();

      }
      inFile.read(data, 2);
      frameNum++;
    }

    // close the file:
    inFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening Input.txt");
  }

}


#endif
