#include "LEDBoard.h"
#include "ledArrayControl.hpp"
#include "sdCardControl.hpp"
#include "animationControl.hpp"
#include "spectrumAnalyzer.hpp"
#include "sensorControl.hpp"

#include "systemControl.hpp"



void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  //analogReadResolution(12);

  if(WAIT_FOR_SERIAL){
    while (!Serial) {
      ; // wait for serial port to connect. Needed for Leonardo only
    }
  }

  systemInit();

  spectrumAnalyzerInit();

}

void loop() {
  // put your main code here, to run repeatedly:

  // for(int i=0; i<1; i++){
  //   modeControl(2);
  // }
  // for(int i=0; i<2; i++){
  //   modeControl(3);
  // }
  modeControl(6);


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
