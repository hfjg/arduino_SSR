/*
 SSR.h - Simple Arduino Library to control an SSR
 Copyright (c) 2020 Hermann Gebhard. All right reserved.

*/
 
#ifndef __SSR_H__
#define __SSR_H__
 
#include <Arduino.h>


class SSR
{
public:

typedef enum {MODE_ON_OFF, MODE_PULSE_PACKET} SSR_MODE_t;
 SSR(void);
 SSR(uint8_t pin);  //Constructor. attach pin to trigger SSR
 run(void);
 void setup(uint8_t pin);
 void setup(uint8_t pin, SSR_MODE_t mode);
 void setup(uint8_t pin, SSR_MODE_t mode, bool inverted);
 void setup(uint8_t pin, SSR_MODE_t mode, bool inverted, uint8_t mainsFrequency);
 
 void setPower(uint8_t value);
 
private:
 uint8_t _pin;
 SSR_MODE_t _mode;
 uint8_t _frequency;
 uint8_t _counter, _setting;
 uint8_t _periodTime;
 bool _inverted;
 uint32_t _lastRun;

 void setDefaults(void);
};

#endif
 
