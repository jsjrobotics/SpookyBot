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
unsigned int stack[COG_MIN_MEMORY + SENSOR_DETECT_STACK_SIZE];

typedef struct ApplicationArguments {
  CogInit *module1;
  CogInit *module2;
  CogInit *module3;
  CogInit *module4;
  CogInit *module5;
  CogInit *module6;  
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
  Application * application = malloc( sizeof(Application) );
  application->module1 = malloc( sizeof(CogInit) );
  application->module2 = malloc( sizeof(CogInit) );
  application->module3 = malloc( sizeof(CogInit) );
  application->module4 = malloc( sizeof(CogInit) );
  application->module5 = malloc( sizeof(CogInit) );
  application->module6 = malloc( sizeof(CogInit) );
  
  application->module1->runningLed = 19;
  loadModules(application);
  while (1){
    if (isShuttingDown()){
      break; 
    }      
    waitOneSecond();
    writeToEeprom();
  }    
  return 0;    
}

