/** @file EncoderTask.cpp
 *  This file contains the function for a task that records the motor shaft position of both motors and 
 *  converts the ticks into angular position which is then used for to generate the error signal
 *  in the conversiont task
 * 
 *  @author  Michelle Chandler
 *  @date    18 Nov 2021 Original file
 */
#include <Arduino.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "EncoderTask.h"
#include "EncoderDriver.h"
#include "shares.h"


void task_encoder(void)
{
    /// Create encoder timer objects
    STM32Encoder timer_1 (TIM2, PA0, PA1); // timer 2. Arudino pins A0/A1
    STM32Encoder timer_2 (TIM8, PB0, PA5); // timer 8. Arduino pins A3/D13

    for(;;)
    {
        data_queue1.put(timer_1.getCount()); // read a data point and stuff it into queue
        data_queue2.put(timer_2.getCount());
    }
    
}