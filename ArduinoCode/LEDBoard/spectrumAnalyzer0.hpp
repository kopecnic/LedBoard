#ifndef SPECTRUM_ANALYZER_HPP
#define SPECTRUM_ANALYZER_HPP


#include <fix_fft.h>                                  // fixed point Fast Fourier Transform library
#include "Arduino.h"

#define audioIn A9                                    // audio input port

int8_t re[128], im[128];                                // real and imaginary FFT result arrays

void spectrumAnalyzerInit(){

analogReadResolution(10);

}

void spectrumAnalyzerRun(LEDArray &ledArray){

  // The FFT real/imaginary data are stored in a char data type as a signed -128 to 127 number
  // This allows a waveform to swing centered around a 0 reference data point
  // The ADC returns data between 0-1023 so it is scaled to fit within a char by dividing by 4 and subtracting 128.
  // eg (0 / 4) - 128 = -128 and (1023 / 4) - 128 = 127

  for (byte i = 0; i < 128; i++) {                    // read 128 analog input samples from ADC
    int sample = analogRead(audioIn);
    re[i] = sample / 4 - 128;                         // scale the samples to fit within a char variable
    im[i] = 0;                                        // there are no imaginary samples associated with the time domain so set to 0
  };

  fix_fft(re, im, 7, 0);                              // send the samples for FFT conversion, returning the real/imaginary results in the same arrays

  for (byte i = 0; i < 64; i++) {
    int dat = sqrt(re[i] * re[i] + im[i] * im[i]);     // frequency magnitude is the square root of the sum of the squares of the real and imaginary parts of a vector
    Serial.print(i);
    Serial.print(":");
    Serial.print(dat);
    Serial.print("  ");
  };
  Serial.println();

}



#endif
