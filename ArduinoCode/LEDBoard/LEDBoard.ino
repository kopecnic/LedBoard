//changing the order of these includes may cause issues as some use classes that
//are defined in others

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


  if(WAIT_FOR_SERIAL){
    while (!Serial) {
      ; // wait for serial port to connect. Needed for Leonardo only
    }
  }

  systemInit();

}

void loop() {
  // put your main code here, to run repeatedly:

  //run the mode baised on the current mode and sub mode
  modeControl(getMode(), getSubMode());


}
