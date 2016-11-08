/*
  Created: 11/4/2016
  Runs on - Propeller 1 
  Responsible for 
   - Detecting attached sensors
   - Polling attached sensors for data
   - Batch writing polled data to eeprom
   - Detecting outside eeprom read
   - Communicating with host over i2c
  
  Parallax propeller has 8 cores. 
  6 cores will run sensor detect and poll data (1 -5)
  1 core will run batch writing data to eeprom and detecting outside eeprom read (0)
  1 core will communicate with host over i2c (6)
*/
#include "simpletools.h"                     

#define COG_MIN_MEMORY 40
#define SENSOR_DETECT_STACK_SIZE 60
int main() {
  
  return 0;    
}

