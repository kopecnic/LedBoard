#include "LEDBoard.h"
#include "ledArrayControl.hpp"
#include "sdCardControl.hpp"
#include "animationControl.hpp"
#include "systemControl.hpp"



void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  if(WAIT_FOR_SERIAL){
    while (!Serial) {
      ; // wait for serial port to connect. Needed for Leonardo only
    }
  }

  systemInit();

}

void loop() {
  // put your main code here, to run repeatedly:
  modeControl(1);

  
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
