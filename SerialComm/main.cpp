#include <Arduino.h>
#include <Arduino.h>
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "SerialComm.h"

void setup() {
  // put your setup code here, to run once:
  //set up serial port
  Serial.begin (115200);
  // delay (2000);
  // Serial << endl << endl << "Hello" << endl; // send a message to test serial connection
  // delay (2000);

  // create serial comm class object
  SerialComm ser_obj;
  //Serial <<"P" ;
  //Serial <<", " ;
 // Serial << 3;
  //Serial <<", " ;
  //Serial.print(4);
  //Serial <<", " ;
  //Serial.println(5);


  for (;;)
  {
    ser_obj.read();
    delay(2000);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
}