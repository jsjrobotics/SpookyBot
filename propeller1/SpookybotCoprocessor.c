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
  1 core will run batch writing data to eeprom (0)
  1 core will communicate with host over i2c (6)
*/
#include "simpletools.h"  
#include "TemperatureModule.h"
#include "TestCog.h"
#define COG_MIN_MEMORY 40
#define SENSOR_DETECT_STACK_SIZE 60


typedef struct ApplicationArguments {
  void (*module1)(struct cogInit *init);
  void (*module2)(struct cogInit *init);
  void (*module3)(struct cogInit *init);
  void (*module4)(struct cogInit *init);
  void (*module5)(struct cogInit *init);
  void (*module6)(struct cogInit *init);
} Application;


void loadModules(Application *application){
  cogstart(testCog, application->module1, stack, sizeof(stack));
}  

void waitOneSecond(){
  waitcnt(CNT + CLKFREQ);
}  

void writeToEeprom(){
  
}  

int isShuttingDown(){
  return 0;
}  

int main() {
  Application application;
  loadModules(&application);
  while (1){
    if (isShuttingDown()){
      break; 
    }      
    waitOneSecond();
    writeToEeprom();
  }    
  return 0;    
}

