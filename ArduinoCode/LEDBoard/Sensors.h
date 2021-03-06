#ifndef SENSORS_H
#define SENSORS_H

#include "Arduino.h"

class SwitchInput{

  public:

    //constructor
    SwitchInput(int pinNum);

    //destructor
    ~SwitchInput();

    //public member functions
    void init();
    bool getState();
    bool sample();


    //public member variables



  private:

    //private member functions


    //private member variables
    int pinNum_;
    bool state_;


};

class Microphone{

  public:

    //constructor
    Microphone(int pinNum);

    //destructor
    ~Microphone();

    //public member functions
    void init();
    uint16_t getReading();
    uint16_t sample();

    //public member variables

  private:

    //private member functions

    //private member variables
    int pinNum_;
    int reading_;

};

class PhotoResistor{

  public:

    //constructor
    PhotoResistor(int pinNum, int filterAlpha);

    //destructor
    ~PhotoResistor();

    //public member functions
    void init();
    uint16_t getReading();
    uint16_t sample();
    uint16_t getAverage();
    void setFilterAlpha(int alpha);

    //public member variables

  private:

    //private member functions

    //private member variables
    int pinNum_;
    int reading_;
    int average_;
    int filterAlpha_;

};

class MaxSonar{

  public:

    //constructor
    MaxSonar(int sensePinNum, int controlPinNum);

    //destructor
    ~MaxSonar();

    //public member functions
    void init();
    uint16_t getReadingIn();
    uint16_t sample();

    //public member variables

  private:

    //private member functions

    //private member variables
    int sensePinNum_;
    int controlPinNum_;
    int reading_;

};

#endif
