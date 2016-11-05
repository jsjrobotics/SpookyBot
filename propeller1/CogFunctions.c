#include "CogFunctions.h"

inline void sendStartSignal(int pin) {
  setHigh(pin); 
  // Wait 10 microseconds
  waitcnt(CNT + 800);
  setLow(pin);
}

inline void setOutput(int pin) {
  int mask = 1 << pin;
  DIRA |= mask;
}

inline void setLow(int pin) {
  int mask = 1 << pin;
  OUTA &= ~mask; 
}
inline void setHigh(int pin) {
  int mask = 1 << pin;
  OUTA |= mask;
}

inline void setInput(int pin) {
  int mask = 1 << pin; 
  DIRA &= ~mask;
}

inline int readPin(int pin) {
  int mask = 1 << pin;   
  return (INA & mask) >> pin;
}