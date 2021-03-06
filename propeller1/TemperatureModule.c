/*
* Read from the DH-11 Temperature Humidity sensor
  Uses single wire interface
  Pull pin down and hold for 500 microseconds
  Set pin input
  Wait 20 to 40 microseconds for sensor to ack
  detect pin pull down as ack (80 microseconds)
  detect pin pull up (80 microseconds)
  Begin reading 40 bits of data:
    detect 50 microsecond pull down 
    reset counter
    detect high input (26 - 28 microsecond) as 0
    detect high input (70 microsecond) as 1
  
DATA is MSB first
RH = relative humidity
T = Temperature
DATA = 8 bit integral RH data + 8 bit decimal RH data +
       8 bit integral T data + 8 bit decimal T data +
       8 bit checksum

Checksum = 8 bit integral RH data + 8 bit decimal RH data +
       8 bit integral T data + 8 bit decimal T data


*/
#include "CogFunctions.h"

int ticksForMicrosecond;

int fiftyMicroseconds() {
  return 50 * ticksForMicrosecond;
}

int fiveHundredMicroseconds() {
  return 500 * ticksForMicrosecond;
}

void sendStartSignal(int pin) {
  setOutput(pin);
  setLow(pin);
  waitcnt(fiveHundredMicroseconds());
}

void detectStart(int pin) {
    
  setInput(pin);
  while( readPin(pin) );
  // Pin is low
  while( !readPin(pin) );
  // Pin is high
  int index;
  for(index = 0; index < 40; index++){
    CTRA = 0; // Stop counter
    PHSA = 0; // reset accumulator
    while( readPin(pin) );
    // Pin is low    
    waitcnt(fiftyMicroseconds());
    CTRA = counterA_logicAlways();
    while( !readPin(pin) );
    // Pin is high
    while( readPin(pin) );
    // Pin is low
    int result = PHSA;    
  }  
  
}


void temperatureModuleMain(struct CogInit *init) {
  int pin1, pin2, pin3, pin4;
  pin1 = init->pin1;
  pin2 = init->pin2;
  pin3 = init->pin3;
  pin4 = init->pin4;
  ticksForMicrosecond = init->ticksForMicrosecond;
  sendStartSignal(pin1);
  detectStart(pin1);
}