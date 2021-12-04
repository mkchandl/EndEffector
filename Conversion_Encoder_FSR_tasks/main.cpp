#include <Arduino.h>
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "taskqueue.h"         // Header for inter-task data queues
#include "taskshare.h"         // Header for inter-task shared data
#include "shares.h"
#include "ConversionTask.h"
#include "EncoderTask.h"
#include "FSRTask.h"
Queue<uint32_t> data_queue1(100, "enc1_pos");
Queue<uint32_t> data_queue2(100, "enc2_pos");
Share<int> motor_shutoff ("Motor_shutoff");

void setup() {
  // put your setup code here, to run once:

  /// Set up the serial port
  Serial.begin (115200);
  delay (2000);
  Serial.println("Hello");



    xTaskCreate (task_encoder,
                  "EncoderTask",                   // Task name for printouts
                  2048,                            // Stack size
                  NULL,                            // Parameters for task fn.
                  8,                               // Priority
                  NULL); 

  xTaskCreate (task_conversion,
                  "ConversionTask",                   // Task name for printouts
                  2048,                            // Stack size
                  NULL,                            // Parameters for task fn.
                  9,                               // Priority
                  NULL); 

  // xTaskCreate (FSRTask,
  //                 "FSRTask",                   // Task name for printouts
  //                 1024,                            // Stack size
  //                 NULL,                            // Parameters for task fn.
  //                 7,                               // Priority
  //                 NULL); 

  #if (defined STM32L4xx || defined STM32F4xx)
          vTaskStartScheduler ();
  #endif
}

void loop() {
  // put your main code here, to run repeatedly:
}