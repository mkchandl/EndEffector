/** @file  main.cpp
 *         This file contains a test for the FSR
 * 
 *  @author Michelle Chandler
 *  @date   18 Nov 2021
 */ 

#include <Arduino.h>
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "FSR.h"

#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  int FSR_pin = PA5;
  FSR FSR_obj(FSR_pin);
}

void loop() {
  // put your main code here, to run repeatedly:
}