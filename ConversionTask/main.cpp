#include <Arduino.h>
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "ConversionTask.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin (115200);
  delay (2000);
  //int kp = 1;
  //int kd = 1;
  //int* p_Kp = &kp;
  //int* p_Kd = &kd;

   xTaskCreate (task_conversion,
                  "FSRTask",                   // Task name for printouts
                  2048,                            // Stack size
                  NULL,                            // Parameters for task fn.
                  8,                               // Priority
                  NULL); 

  #if (defined STM32L4xx || defined STM32F4xx)
          vTaskStartScheduler ();
  #endif
}

void loop() {
  // put your main code here, to run repeatedly:
}