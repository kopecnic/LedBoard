#ifndef SPECTRUM_ANALYZER_HPP
#define SPECTRUM_ANALYZER_HPP

#define ARM_MATH_CM4
#include <arm_math.h>

#include "Arduino.h"

////////////////////////////////////////////////////////////////////////////////
// CONIFIGURATION
// These values can be changed to alter the behavior of the spectrum display.
////////////////////////////////////////////////////////////////////////////////

int SAMPLE_RATE_HZ = 20000;             // Sample rate of the audio in hertz.
float SPECTRUM_MIN_DB = 40.0;          // Audio intensity (in decibels) that maps to low LED brightness.
float SPECTRUM_MAX_DB = 70.0;          // Audio intensity (in decibels) that maps to high LED brightness.
int LEDS_ENABLED = 1;                  // Control if the LED's should display the spectrum or not.  1 is true, 0 is false.
                                       // Useful for turning the LED display on and off with commands from the serial port.
const int FFT_SIZE = 256;              // Size of the FFT.  Realistically can only be at most 256
                                       // without running out of memory for buffers and other state.
const int AUDIO_INPUT_PIN = A9;        // Input ADC pin for audio data.
const int ANALOG_READ_RESOLUTION = 10; // Bits of resolution for the ADC.
const int ANALOG_READ_AVERAGING = 2;  // Number of samples to average with each ADC reading.
const int NEO_PIXEL_PIN = 1;           // Output pin for neo pixels.
const int NEO_PIXEL_COUNT = 5;         // Number of neo pixels.  You should be able to increase this without
                                       // any other changes to the program.

////////////////////////////////////////////////////////////////////////////////
// INTERNAL STATE
// These shouldn't be modified unless you know what you're doing.
////////////////////////////////////////////////////////////////////////////////

IntervalTimer samplingTimer;
float samples[FFT_SIZE*2];
float magnitudes[FFT_SIZE];
int sampleCounter = 0;
float frequencyWindow[NEO_PIXEL_COUNT+1];

////////////////////////////////////////////////////////////////////////////////
// UTILITY FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

// Compute the average magnitude of a target frequency window vs. all other frequencies.
void windowMean(float* magnitudes, int lowBin, int highBin, float* windowMean, float* otherMean) {
    *windowMean = 0;
    *otherMean = 0;
    // Notice the first magnitude bin is skipped because it represents the
    // average power of the signal.
    for (int i = 1; i < FFT_SIZE/2; ++i) {
      if (i >= lowBin && i <= highBin) {
        *windowMean += magnitudes[i];
      }
      else {
        *otherMean += magnitudes[i];
      }
    }
    *windowMean /= (highBin - lowBin) + 1;
    *otherMean /= (FFT_SIZE / 2 - (highBin - lowBin));
}

// Convert a frequency to the appropriate FFT bin it will fall within.
int frequencyToBin(float frequency) {
  float binFrequency = float(SAMPLE_RATE_HZ) / float(FFT_SIZE);
  return int(frequency / binFrequency);
}


////////////////////////////////////////////////////////////////////////////////
// SPECTRUM DISPLAY FUNCTIONS
///////////////////////////////////////////////////////////////////////////////

void spectrumSetup() {
  // Set the frequency window values by evenly dividing the possible frequency
  // spectrum across the number of neo pixels.
  // float windowSize = (SAMPLE_RATE_HZ / 2.0) / float(NEO_PIXEL_COUNT);
  // for (int i = 0; i < NEO_PIXEL_COUNT+1; ++i) {
  //   frequencyWindow[i] = i*windowSize;
  // }

  frequencyWindow[0] = 60;
  frequencyWindow[1] = 250;
  frequencyWindow[2] = 500;
  frequencyWindow[3] = 2000;
  frequencyWindow[4] = 4000;
  frequencyWindow[5] = 10000;
}

void spectrumLoop(LEDArray &ledArray) {

  ledArray.clearArray();
  // Update each LED based on the intensity of the audio
  // in the associated frequency window.
  float intensity, otherMean;
  for (int i = 0; i < NEO_PIXEL_COUNT; ++i) {
      windowMean(magnitudes, frequencyToBin(frequencyWindow[i]), frequencyToBin(frequencyWindow[i+1]), &intensity, &otherMean);
    // Convert intensity to decibels.
    intensity = 20.0*log10(intensity);
    // Scale the intensity and clamp between 0 and 1.0.
    intensity -= SPECTRUM_MIN_DB;
    intensity = intensity < 0.0 ? 0.0 : intensity;
    intensity /= (SPECTRUM_MAX_DB-SPECTRUM_MIN_DB);
    intensity = intensity > 1.0 ? 1.0 : intensity;
    //pixels.setPixelColor(i, pixelHSVtoRGBColor(hues[i], 1.0, intensity));
    //pixels.setPixelColor(i, pixels.Color(int(255*intensity), int(0), int(0)));

    int ledVal = int(255*5*intensity);
    //ledVal = 110*5;
    for(int j = 0; j < 5; j++){

      int val = 0;

      if(ledVal - 255 > 0){
        val = 255;
        ledVal -= 255;
      }
      else{
        val = ledVal;
        ledVal = 0;
      }



      ledArray.ledInputArray[i][j] = val;
    }

    // Serial.print(i);
    // Serial.print(":");
    // Serial.print(intensity);
    // Serial.print("  ");
  }
  //Serial.println();
  ledArray.updateArray();
  //pixels.show();
}


////////////////////////////////////////////////////////////////////////////////
// SAMPLING FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

void samplingCallback() {
  // Read from the ADC and store the sample data
  samples[sampleCounter] = (float32_t)analogRead(AUDIO_INPUT_PIN);
  // Complex FFT functions require a coefficient for the imaginary part of the input.
  // Since we only have real data, set this coefficient to zero.
  samples[sampleCounter+1] = 0.0;
  // Update sample buffer position and stop after the buffer is filled
  sampleCounter += 2;
  if (sampleCounter >= FFT_SIZE*2) {
    samplingTimer.end();
  }
}

void samplingBegin() {
  // Reset sample buffer position and start callback at necessary rate.
  sampleCounter = 0;
  samplingTimer.begin(samplingCallback, 1000000/SAMPLE_RATE_HZ);
}

boolean samplingIsDone() {
  return sampleCounter >= FFT_SIZE*2;
}

void spectrumAnalyzerInit(){

  // Set up ADC and audio input.
  pinMode(AUDIO_INPUT_PIN, INPUT);
  analogReadResolution(ANALOG_READ_RESOLUTION);
  analogReadAveraging(ANALOG_READ_AVERAGING);

  // Initialize spectrum display
  spectrumSetup();

  // Begin sampling audio
  samplingBegin();

}

void spectrumAnalyzerRun(LEDArray &ledArray){

  // Calculate FFT if a full sample is available.
  if (samplingIsDone()) {
    // Run FFT on sample data.
    arm_cfft_radix4_instance_f32 fft_inst;
    arm_cfft_radix4_init_f32(&fft_inst, FFT_SIZE, 0, 1);
    arm_cfft_radix4_f32(&fft_inst, samples);
    // Calculate magnitude of complex numbers output by the FFT.
    arm_cmplx_mag_f32(samples, magnitudes, FFT_SIZE);

    if (LEDS_ENABLED == 1)
    {
      spectrumLoop(ledArray);
    }

    // Restart audio sampling.
    samplingBegin();
  }

}



#endif
