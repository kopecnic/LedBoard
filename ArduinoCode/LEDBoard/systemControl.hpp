//----------------------------------------------------------------------------------------------------------------------
//
//  Nicholas Kopec, 2020
//
//  This file contains all the functions necessary for controlling anamations that are created by reading frames from a
//  sd card.
//
//----------------------------------------------------------------------------------------------------------------------

#ifndef SYSTEM_CONTROL_HPP
#define SYSTEM_CONTROL_HPP

#include "Arduino.h"
#include "LEDBoard.h"

//name of the file to read the animation file names
char animationInFileName[] = "aniName.txt";

//stores all the data relative to a animation
LEDAnimation animation(LED_ARRAY_NUM_ROWS, LED_ARRAY_NUM_COLS, ANIMATION_NUM_MAX_FRAMES);

//stores all the data relative to the led array
LEDArray ledArray(LED_ARRAY_NUM_COLS, LED_ARRAY_NUM_ROWS, NUM_DATA_PINS, LEDS_PER_DATA_PIN, BASE_LED_BRIGHTNESS);


//initialize all components on the system
void systemInit(){

  //initialize the led array
  ledArrayInit(ledArray);

  //initialize the sensors
  sensorsInit();

  //initialize communications with the sd card
  sdCardInit();

  //get animation file names
  animationGetAnimations(animationInFileName);

  //load an animation
  animationLoadAnimation(animation, 0);

  //set the animation brightness
  animation.setBrightness(100);

  //initialize the spectrumAnalyzer
  spectrumAnalyzerInit();
}

int getMode(){
    return getModeFromSwitches(switch0, switch1);
}

int getSubMode(){
  return getModeFromSwitches(switch2, switch3);
}

//determine what mode to run in
void modeControl(int mode, int subMode){

  switch(mode){

    //off
    case 0:
    {
      switch(subMode){

        case 0:
        {
          ledArray.clearArray();
          break;
        }

        case 1:
        {
          ledArray.setSolidColor(CRGB::Red);
          break;
        }

        case 2:
        {
          ledArray.setSolidColor(CRGB::Green);
          break;
        }

        case 3:
        {
          ledArray.setSolidColor(CRGB::Blue);
          break;
        }

        default:
          ledArray.clearArray();
          break;
      }
      ledArray.updateArray();
      break;
    }
    case 1:
    {
      animationPlayAnimation(animation, ledArray, true);
      break;
    }
    case 2:
    {
      //ledArray.setSolidColor(CRGB::White);
      //ledArray.updateArray();

      delay(500);

      ledArray.setSolidColor(CRGB::Red);
      ledArray.updateArray();

      delay(500);

      ledArray.setSolidColor(CRGB::Green);
      ledArray.updateArray();

      delay(500);

      ledArray.setSolidColor(CRGB::Blue);
      ledArray.updateArray();

      delay(500);

      ledArray.setSolidColor(CRGB::Black);
      ledArray.updateArray();

      //delay(500);

      break;
    }
    case 3:
    {
      int pos = 0;
      int lastPos = 0;
      for(int i = 0; i < 25; i++){
        pos = i;

        if(pos){
            lastPos = pos - 1;
        }

        if((pos/5) % 2 == 0){
          ledArray.ledInputArray[lastPos/5][lastPos%5] = CRGB::Green;
          ledArray.ledInputArray[pos/5][pos%5] = CRGB::White;
          ledArray.updateArray();
          ledArray.ledInputArray[lastPos/5][lastPos%5] = CRGB::Black;
          delay(100);
        }
        else{
          ledArray.ledInputArray[lastPos/5][lastPos%5] = CRGB::Green;
          ledArray.ledInputArray[pos/5][pos%5] = CRGB::White;
          ledArray.updateArray();
          ledArray.ledInputArray[lastPos/5][lastPos%5] = CRGB::Black;
          delay(100);
        }

      }

      ledArray.ledInputArray[pos/5][pos%5] = CRGB::Green;
      ledArray.updateArray();
      delay(100);
      ledArray.ledInputArray[pos/5][pos%5] = CRGB::Black;
      ledArray.updateArray();
      delay(100);

      break;
    }

    case 4:
    {
      for(int i = 0; i < 5; i++){
        ledArray.ledInputArray[0][i] = CRGB::Green;
        ledArray.updateArray();
        delay(100);
      }
      for(int i = 1; i < 5; i++){
        ledArray.ledInputArray[i][4] = CRGB::Green;
        ledArray.updateArray();
        delay(100);
      }
      for(int i = 1; i < 5; i++){
        ledArray.ledInputArray[4][4-i] = CRGB::Green;
        ledArray.updateArray();
        delay(100);
      }
      for(int i = 1; i < 4; i++){
        ledArray.ledInputArray[4-i][0] = CRGB::Green;
        ledArray.updateArray();
        delay(100);
      }
      ledArray.clearArray();

      break;
    }

    //run the spectrumAnalyzer
    case 5:
    {
      spectrumAnalyzerRun(ledArray);
      delay(20);
      break;
    }

    //sample all the sensors at 2 Hz
    case 6:
    {
      sampleSwitches();
      sampleMics();
      samplePhotoRes();
      sampleDistances();
      delay(500);
      break;
    }

    case 7:
    {
      for(int i=0; i<LED_ARRAY_NUM_COLS; i++){
        ledArray.ledInputArray[0][i] = CRGB::Green;
        ledArray.updateArray();
        delay(100);
      }
      ledArray.clearArray();
      ledArray.updateArray();
      break;
    }

    case 8:{

      int dist = distance0.sample();
      int intensity = map(dist, 200, 4000, 0, 1000);
      int ledVal = int(255*30*intensity/1000);
      //ledVal = 110*5;
      for(int j = 0; j < 30; j++){

        int val = 0;

        if(ledVal - 255 > 0){
          val = 255;
          ledVal -= 255;
        }
        else{
          val = ledVal;
          ledVal = 0;
        }



        ledArray.ledInputArray[30-j-1][0] = val;
      }

      ledArray.updateArray();

      break;
    }

    //off
    default:
      ledArray.clearArray();
      ledArray.updateArray();
      break;
  }
}

#endif
