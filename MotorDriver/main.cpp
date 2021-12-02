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
#include "MotorDriver.h"


void setup() {
  // put your setup code here, to run once:

  int IN1A = D5; // set up pins for both motors
  int IN2A = D4;
  int IN1B = D15;
  int IN2B = D14;
  int sleep = PA15;  // i dont actually kno what pin to use. this is what we used in me405
  int nFault = PB2;  // idk what pin to use. this is what we used in me405

  Serial.begin (115200);
  delay (2000);
  Serial << endl << endl << "Hello" << endl;
  delay (2000);

  //analogWrite(PB8, 0);
  //analogWrite(PB9, 200);
  //while (true) { }

  MotorDriver motor_obj(sleep, IN1A, IN1B, IN2B, IN1B, nFault);  // make a class object
   Serial << endl << "enabling motor" << endl;
   motor_obj.enable();
  motor_obj.set_duty1(80);
  Serial << endl << "setting duty to 80" << endl;
  delay (10000);
  motor_obj.disable();
}

void loop() {
  // put your main code here, to run repeatedly:
}