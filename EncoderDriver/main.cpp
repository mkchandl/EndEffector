/** @file  main.cpp
 *         This file contains a test for the Motor Driver Class
 *  @author Michelle Chandler
 *  @date   4 Nov 2021
 */

#include <Arduino.h>
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "EncoderDriver.h"


void setup() {
  // put your setup code here, to run once:
  Serial.begin (115200);
  delay (2000);
  Serial << endl << endl << "Hello" << endl;

  STM32Encoder timer_X (TIM3, PB4, PB5);      // Set up once
  for(;;)
  {
    int16_t where_am_I = timer_X.getCount ();   // In a loop
    delay (2000);
    Serial.println(where_am_I);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}