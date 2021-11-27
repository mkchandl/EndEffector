#include <iostream>
#include <Arduino.h>
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "EncoderTask.h"
#include "EncoderDriver.h"

void setup() {
  // put your setup code here, to run once:

  Serial.begin (115200);
  delay (2000);

  xTaskCreate (task_encoder,
                  "EncoderTask",                   // Task name for printouts
                  4096,                            // Stack size
                  NULL,                            // Parameters for task fn.
                  9,                               // Priority
                  NULL);  

  #if (defined STM32L4xx || defined STM32F4xx)
        vTaskStartScheduler ();
    #endif
}

void loop() {
  // put your main code here, to run repeatedly:
}