#include <Arduino.h>
#include <Arduino.h>
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "SerialComm.h"
#include <fstream>
#include <iostream>
 

void setup() {
  // put your setup code here, to run once:
  //set up serial port
  Serial.begin (115200);

  // create serial comm class object
  SerialComm ser_obj;

  Serial.setTimeout(10000);
  byte buf[4];

  //std::ofstream myfile;
  //myfile.open ("example.csv");
  
 // String string;
  char term = ']';
  for (int i = 0; i < 5; i++)
  {
    //string = Serial.readStringUntil(term);
    //myfile << python;

    // delay(2000);
  }
  Serial.end();
  delay(10000);
  String string = "['t', 360, 447, 4.043892860412598";

  Serial.begin (115200);  

  //remove the spaces
  string.replace(" ","");
  Serial.println(string);

  // find location of first comma
  int index = string.indexOf(',');
  //get everything before that (this also gets rid of the bracket)
  String finger = string.substring(1, index);
  Serial.println(finger);

  // now erase all that
  string = string.substring(index+1);
  Serial.println(string);

  // repeat
  index = string.indexOf(',');
  int x = string.substring(0, index).toInt();
  Serial.println(string);
  Serial.println(x);

  string = string.substring(index+1);
  int y = string.substring(0, index).toInt();
  Serial.println(string);
  Serial.println(y);

  string = string.substring(index+1);
  float time = string.toFloat();
  Serial.println(string);
  Serial.println(time);


  
  


  for(;;)
  {

  }


}

void loop() {
  // put your main code here, to run repeatedly:
}