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

  switch(mode)
  {

    //off, red, green, blue
    case 0:
    {
      switch(subMode)
      {

        //clear the array
        case 0:
        {
          ledArray.clearArray();
          ledArray.updateArray();
          break;
        }

        //set the array to red
        case 1:
        {
          ledArray.setSolidColor(CRGB::Red);
          ledArray.updateArray();
          break;
        }

        //set the array to green
        case 2:
        {
          ledArray.setSolidColor(CRGB::Green);
          ledArray.updateArray();
          break;
        }

        //set the array to blue
        case 3:
        {
          ledArray.setSolidColor(CRGB::Blue);
          ledArray.updateArray();
          break;
        }

        //clear the array
        default:
          ledArray.clearArray();
          ledArray.updateArray();
          break;
      }
      break;
    }

    //animation player
    case 1:
    {
      switch(subMode)
      {

        //play an animation
        case 0:
        {
          animationPlayAnimation(animation, ledArray, true);
          break;
        }

        //clear the array
        case 1:
        {
          ledArray.clearArray();
          ledArray.updateArray();
          break;
        }

        //clear the array
        case 2:
        {
          ledArray.clearArray();
          ledArray.updateArray();
          break;
        }

        //clear the array
        case 3:
        {
          ledArray.clearArray();
          ledArray.updateArray();
          break;
        }

        //clear the array
        default:
          ledArray.clearArray();
          ledArray.updateArray();
          break;
      }
      break;
    }

    //flash different colors, distance sensors
    case 2:
    {
      switch(subMode)
      {
        //flash through red, green, blue
        case 0:
        {
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

          break;
        }
        
        //dual distance sensor readout
        case 1:
        {
          //light up the distance for the left side
          int dist = distance0.sample();
          int intensity = map(dist, 200, 4000, 0, 1000);
          int ledVal = int(255*30*intensity/1000);
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

          //light up the distance for the right side
          dist = distance1.sample();
          intensity = map(dist, 200, 4000, 0, 1000);
          ledVal = int(255 * 30 * intensity / 1000);
          for (int j = 0; j < 30; j++) {

              int val = 0;

              if (ledVal - 255 > 0) {
                  val = 255;
                  ledVal -= 255;
              }
              else {
                  val = ledVal;
                  ledVal = 0;
              }
              ledArray.ledInputArray[30 - j - 1][29] = val;
          }

          ledArray.updateArray();
          break;
        }

        //clear the array
        case 2:
        {
          ledArray.clearArray();
          ledArray.updateArray();
          samplePhotoRes();
          break;
        }

        //clear the array
        case 3:
        {
          ledArray.clearArray();
          ledArray.updateArray();
          break;
        }

        //clear the array
        default:
          ledArray.clearArray();
          ledArray.updateArray();
          break;
      }
      break;
    }

    //spectrumAnalyzer
    case 3:
    {
      switch(subMode)
      {

        //run the spectrumAnalyzer
        case 0:
        {
          spectrumAnalyzerRun(ledArray);
          delay(20);
          break;
        }

        //clear the array
        case 1:
        {
          ledArray.clearArray();
          ledArray.updateArray();
          break;
        }

        //clear the array
        case 2:
        {
          ledArray.clearArray();
          ledArray.updateArray();
          break;
        }

        //clear the array
        case 3:
        {
          ledArray.clearArray();
          ledArray.updateArray();
          break;
        }

        //clear the array
        default:
          ledArray.clearArray();
          ledArray.updateArray();
          break;
      }
      break;
    }

    //clear the array
    default:
      ledArray.clearArray();
      ledArray.updateArray();
      break;
  }
}

#endif
