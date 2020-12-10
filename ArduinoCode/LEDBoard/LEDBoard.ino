#include "LEDBoard.h"
#include "sensorControl.hpp"
#include "ledArrayControl.hpp"
#include "sdCardControl.hpp"
#include "animationControl.hpp"
#include "spectrumAnalyzer.hpp"

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

}

void loop() {
  // put your main code here, to run repeatedly:

  modeControl(8);

}
