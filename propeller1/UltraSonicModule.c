/*
* Read from the Ultrasonic ranging module HC - SR04
  Start Read: 10 microseconds high on trigger input (pin 0)
  Read Pulse Output and measure high time
  Convert to value
  microseconds / 58 = centimeters
  microseconds / 148 = inch

  NOTE: Currently only works at 80mhz Clock cycle

  Using internal CounterA as numerically controlled oscillator
  Set PLL mode to 2 - Frequency Register to Phase Register accumulator
  Send 10 microsecond high pulse to device
  Wait for echo pin to go high
  Start Counter
  Wait for echo pin to go low
  Calculate distance from counter time
  Wait 60 milliseconds to avoid detecting echo
  
*/

#include "CogFunctions.h"
int ticksForMicrosecond;

void ultrasonicModuleSendStartSignal(int);
static int tenMicroseconds();
void ultrasonicModuleMain(struct CogInit *);

int tenMicroseconds() {
  return 10 * ticksForMicrosecond;
}

inline void ultrasonicModuleSendStartSignal(int pin) {
  setHigh(pin); 
  waitcnt(tenMicroseconds());
  setLow(pin);
}

void ultrasonicModuleMain(struct CogInit *init) {
  int pin1, pin2, pin3, pin4;
  pin1 = init->pin1;
  pin2 = init->pin2;
  pin3 = init->pin3;
  pin4 = init->pin4;
  ticksForMicrosecond = init->ticksForMicrosecond;
  setOutput(pin1);
  
  CTRA = 0; // Stop counter
  PHSA = 0; // reset accumulator
  ultrasonicModuleSendStartSignal(pin1);
  while( readPin(pin2) != 1);
  CTRA = counterA_logicAlways();
  while( readPin(pin2) != 0);
  int result = PHSA;
  CTRA = 0;
}
