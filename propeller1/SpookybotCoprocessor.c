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
unsigned int cogOneStack[COG_MIN_MEMORY + SENSOR_DETECT_STACK_SIZE];
unsigned int cogTwoStack[COG_MIN_MEMORY + SENSOR_DETECT_STACK_SIZE];
unsigned int cogThreeStack[COG_MIN_MEMORY + SENSOR_DETECT_STACK_SIZE];
unsigned int cogFourStack[COG_MIN_MEMORY + SENSOR_DETECT_STACK_SIZE];
unsigned int cogFiveStack[COG_MIN_MEMORY + SENSOR_DETECT_STACK_SIZE];

char output[20];
int cogPins[20];
void sensorDetect(void * ptr);
void init(void);
void sensorDetect(void * input) {
  int * pins = cogPins[cogid()];
  snprintf(output, sizeof(output), "Cog %d starting with pins: %d %d %d %d\n", cogid(), cogPins[0], cogPins[1], cogPins[2], cogPins[3] );
      
}   

void init(){
  memset(output, 0, sizeof(output));
  for (int index = 0; index < 20; index++){
    cogPins[index] = index;
  }    
}  

int main() {
  init();
  // All cogs start at 0 and are loaded from there. Hence knowing how many cogs are started tells us next cog to start
  snprintf(output, sizeof(output), "Start");
  int startPins[5] = { 0, 0, 1, 2, 3};
  cogstart(sensorDetect, startPins, cogOneStack, sizeof(cogOneStack));
  for (int index= 0; index < 10; index++) {
    printf(output);
    printf("\n");
  }        
}

