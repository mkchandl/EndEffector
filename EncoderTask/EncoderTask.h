/** @file EncoderTask.h
 *  This file contains headers for a task that records the motor shaft position of both motors and 
 *  converts the ticks into angular position which is then used for to generate the error signal
 *  in the conversiont task
 * 
 *  @author  Michelle Chandler
 *  @date    18 Nov 2021 Original file
 */
#include <iostream>
#include <Arduino.h>
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "shares.h"

void task_encoder(void* p_params);

