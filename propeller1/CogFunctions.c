#include "CogFunctions.h"


inline int counterA_logicAlways(){
  return CTRA | (0x1F << 26);  
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