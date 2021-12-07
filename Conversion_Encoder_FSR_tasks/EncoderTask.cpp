/** @file EncoderTask.cpp
 *  This file contains the function for a task that records the motor shaft position of both motors and 
 *  converts the ticks into angular position which is then used for to generate the error signal
 *  in the conversiont task
 *  This task includes the encoder driver from the ME 507 support Git hub, found here: https://github.com/spluttflob/ME507-Support.git
 * 
 *  @author  Michelle Chandler and Cole Andrews
 *  @date    18 Nov 2021 Original file
 */
#include <iostream>
#include <Arduino.h>
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "EncoderTask.h"
#include "EncoderDriver.h"
#include "shares.h"


/** @brief   Task which reads from the motor encoders to track position for closed-loop position control 
 *  @details This task monitors the angular position of the motors, converts the position into degrees, 
 *           and writes the encoder values into two shared queues for use by the conversion task. 
 *  @param p_param This parameter was added to stop a compiler error
*/
void task_encoder(void* p_params)
{
    (void)p_params; 

    int32_t t1_count; 
    int32_t t2_count;
    int32_t t1_pos=0;
    int32_t t2_pos=0;

    /// Create encoder timer objects
    STM32Encoder timer_1 (TIM2, PA0, PA1); // timer 2. Arudino pins A0/A1
    STM32Encoder timer_2 (TIM8, PC6, PC7); // timer 8. Arduino pin D9 and nucleo pin PC6
    // set encoder values to zero. 
    timer_1.zero();
    timer_2.zero();
    

    for(;;)
    {
        Serial.println("ET: running");
        int32_t t1_old = t1_count; // save the old position for delta calc
        int32_t t2_old = t2_count; 
        
        t1_count = timer_1.getCount(); // get new position for delta calc
        t2_count = timer_2.getCount();
        //Serial.print("curr_count1:");
        //Serial.println(t1_count);

        int16_t delta1 = t1_count - t1_old; // calc delta
        int16_t delta2 = t2_count - t2_old; 
        //Serial.print("delta1:");
        //Serial.println(delta1);

        t1_pos += delta1;
        t2_pos += delta2;// in ticks

        /// Ticks to degrees
        int32_t ticks_per_deg = 2248/360; 
        int32_t t1_pos_deg = t1_pos/(ticks_per_deg*47);
        int32_t t2_pos_deg = t2_pos/(ticks_per_deg*47);

        data_queue1.put(t1_pos_deg); // read a data point and stuff it into queue
        data_queue2.put(t2_pos_deg);

        vTaskDelay (500); // delay task 0.5 seconds

    }
    
}