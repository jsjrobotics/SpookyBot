#include "TestCog.h"
i2c *eeBus;                                   // I2C bus ID

void testCog(struct CogInit *init){
  high(init->runningLed);
  eeBus = i2c_newbus(28,  29,   0);           // Set up I2C bus, get bus ID
  unsigned int address = 0b1010001;
  while (1){
                                               // Use eeBus to write to device
    i2c_out(eeBus, address,                   // with I2C address 0b1010000,
          32768, 2, "abcdefg", 8);            // send 2 byte address of 32768
                                  // and 8 byte data string.
    print("startWait\n");
    while(i2c_busy(eeBus, address));          // Wait for EEPROM to finish
    print("endWait\n");
    char testStr[] = {0, 0, 0, 0, 0, 0, 0, 0};  // Set up test string
     
                                              // Use eeBus to read from device
    i2c_in(eeBus, address,                    // with I2C address 0b1010000,   
         32768, 2, testStr, 8);               // send 2 byte address of 32768
                                              // & store data in 8 byte array.

    print("testStr = %s \n", testStr);
    waitcnt(CNT + CLKFREQ/10);
  }    
             // Display result
}
