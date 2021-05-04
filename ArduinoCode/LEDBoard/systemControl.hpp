//----------------------------------------------------------------------------------------------------------------------
//
//  Nicholas Kopec, 2020
//
//  This file contains all the functions necessary for controlling anamations that are created by reading frames from a
//  sd card.
//
//----------------------------------------------------------------------------------------------------------------------

//TODO
//-Remove constants from ultrasonic sensoring
//-

#ifndef SYSTEM_CONTROL_HPP
#define SYSTEM_CONTROL_HPP

#include "Arduino.h"
#include "LEDBoard.h"

const uint8_t lights[360] = {
  0,   0,   0,   0,   0,   1,   1,   2,
  2,   3,   4,   5,   6,   7,   8,   9,
 11,  12,  13,  15,  17,  18,  20,  22,
 24,  26,  28,  30,  32,  35,  37,  39,
 42,  44,  47,  49,  52,  55,  58,  60,
 63,  66,  69,  72,  75,  78,  81,  85,
 88,  91,  94,  97, 101, 104, 107, 111,
114, 117, 121, 124, 127, 131, 134, 137,
141, 144, 147, 150, 154, 157, 160, 163,
167, 170, 173, 176, 179, 182, 185, 188,
191, 194, 197, 200, 202, 205, 208, 210,
213, 215, 217, 220, 222, 224, 226, 229,
231, 232, 234, 236, 238, 239, 241, 242,
244, 245, 246, 248, 249, 250, 251, 251,
252, 253, 253, 254, 254, 255, 255, 255,
255, 255, 255, 255, 254, 254, 253, 253,
252, 251, 251, 250, 249, 248, 246, 245,
244, 242, 241, 239, 238, 236, 234, 232,
231, 229, 226, 224, 222, 220, 217, 215,
213, 210, 208, 205, 202, 200, 197, 194,
191, 188, 185, 182, 179, 176, 173, 170,
167, 163, 160, 157, 154, 150, 147, 144,
141, 137, 134, 131, 127, 124, 121, 117,
114, 111, 107, 104, 101,  97,  94,  91,
 88,  85,  81,  78,  75,  72,  69,  66,
 63,  60,  58,  55,  52,  49,  47,  44,
 42,  39,  37,  35,  32,  30,  28,  26,
 24,  22,  20,  18,  17,  15,  13,  12,
 11,   9,   8,   7,   6,   5,   4,   3,
  2,   2,   1,   1,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0,
  0,   0,   0,   0,   0,   0,   0,   0 };

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
            for (int k = 0; k < 360; k++)
            {
                ledArray.setSolidColor(CRGB(lights[(k + 120) % 360], lights[k], lights[(k + 240) % 360]));
                delay(30);
            }
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

          ledArray.setSolidColor(CRGB::Orange);
          ledArray.updateArray();

          delay(500);

          ledArray.setSolidColor(CRGB::Yellow);
          ledArray.updateArray();

          delay(500);

          ledArray.setSolidColor(CRGB::Green);
          ledArray.updateArray();

          delay(500);


          ledArray.setSolidColor(CRGB::Aqua);
          ledArray.updateArray();

          delay(500);

          ledArray.setSolidColor(CRGB::Blue);
          ledArray.updateArray();

          delay(500);


          ledArray.setSolidColor(CRGB::Purple);
          ledArray.updateArray();

          delay(500);

          ledArray.setSolidColor(CRGB::Pink);
          ledArray.updateArray();


          break;
        }

        //dual distance sensor readout
        case 1:
        {
          delay(100);
          //light up the distance for the left side
          int dist = distance0.sample();
          int intensity = map(dist, 200, 3000, 0, 1000);
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
          intensity = map(dist, 200, 3000, 0, 1000);
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
