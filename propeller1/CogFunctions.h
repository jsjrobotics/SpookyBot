/**
 * All Functions in this file must be inline and defined here
 * since this file is supposed to be compiled into cog memory
 * 
 * Cog Register Description
 * PAR      Parameter register is used for sharing HUB RAM address info with the COG.
 * CNT      The system clock count
 * INA      Use to read the pins when corresponding DIRA bits are 0.
 * INB      Unused in P8X32A
 * OUTA     Use to set pin states when corresponding DIRA bits are 1.
 * OUTB     Unused in P8X32A
 * DIRA     Use to set pins to input (0) or output (1).
 * DIRB     Unused in P8X32A
 * CTRA     Counter A control register.
 * CTRB     Counter B control register.
 * FRQA     Counter A frequency register.
 * FRQB     Counter B frequency register.
 * PHSA     Counter A phase accumulation register.
 * PHSB     Counter B phase accumulation register.
 * VCFG     Video Configuration register can be used for other special output.
 * VSCL     Video Scale register for setting pixel and frame clocks.
*/

#ifndef COG_FUNCTIONS_H

#define COG_FUNCTIONS_H

#include <propeller.h>

void setOutput(int);
void setLow(int);
void setHigh(int);
void setInput(int);
int readPin(int);




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

#endif