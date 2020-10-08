#include "LEDBoard.h"
#include "ledArrayControl.hpp"
#include "sdCardControl.hpp"
#include "animationControl.hpp"

char animationInFileName[] = "aniName.txt";
LEDAnimation animation(LED_ARRAY_NUM_ROWS, LED_ARRAY_NUM_COLS, ANIMATION_NUM_MAX_FRAMES);


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  if(WAIT_FOR_SERIAL){
    while (!Serial) {
      ; // wait for serial port to connect. Needed for Leonardo only
    }
  }

 ledArrayInit();
 sdCardInit();

 animationGetAnimations(animationInFileName);
 animationLoadAnimation(animation, 0);

}

void loop() {
  // put your main code here, to run repeatedly:

  animationPlayAnimation(animation);

  // ledArray.setSolidColor(CRGB::White);
  // ledArray.updateArray();
  //
  // delay(1000);
  //
  // ledArray.setSolidColor(CRGB::Red);
  // ledArray.updateArray();
  //
  // delay(1000);
  //
  // ledArray.setSolidColor(CRGB::Green);
  // ledArray.updateArray();
  //
  // delay(1000);
  //
  // ledArray.setSolidColor(CRGB::Blue);
  // ledArray.updateArray();
  //
  // delay(1000);
  //
  // ledArray.setSolidColor(CRGB::Black);
  // ledArray.updateArray();
  //
  // delay(1000);

}
