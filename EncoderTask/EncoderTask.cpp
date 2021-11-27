/** @file EncoderTask.cpp
 *  This file contains the function for a task that records the motor shaft position of both motors and 
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
#include "EncoderTask.h"
#include "EncoderDriver.h"
#include "shares.h"

using std::endl; // from stack overflow to fix compiler errorss

static int16_t t1_count;
static int16_t t2_count;
static int16_t t1_pos;
static int16_t t2_pos;
// const int16_t PERIOD = 65536; // or 32768 not sure which

void task_encoder(void* p_params)
{
    (void)p_params; 
    Serial.println("starting encoder task");
     

    Queue<uint16_t> data_queue1(1000, "enc1_pos");
    Queue<uint16_t> data_queue2(1000, "enc2_pos");
    Serial.println("created shared queues");

    // Create encoder timer objects
    STM32Encoder timer_1 (TIM2, PA0, PA1); // timer 2. Arudino pins A0/A1
    Serial.println("created enc1 object");

    // STM32Encoder timer_2 (TIM8, PB0, PA5); // timer 8. Arduino pins A3/D13
    STM32Encoder timer_2 (TIM8, PC6, PC7); // timer 8. Arduino pin D9 and nucleo pin PC6
    Serial.println("created enc2 object");
    Serial.println("about to enter for loop");

    for(;;)
    {
        Serial.println("just entered for loop");
        int16_t t1_old = t1_count; // save the old position for delta calc
        int16_t t2_old = t2_count; 
        

        t1_count = timer_1.getCount(); // get new position for delta calc
        t2_count = timer_2.getCount();
        Serial.print("curr_count1:");
        Serial.println(t1_count);

        int16_t delta1 = t1_count - t1_old; // calc delta
        int16_t delta2 = t2_count - t2_old; 
        Serial.print("delta1:");
        Serial.println(delta1);

        if(abs(delta1)> 0.5*65536) // or .5*32768 not sure which
        {
            if(delta1>0)
            {
                delta1 = delta1 - 65536;
                Serial.print("cw adjusted delta1: ");
                Serial.println(delta1);
            }
            else if(delta1<0)
            {
                delta1 = delta1 + 65536;
                Serial.print("ccw adjusted delta1: ");
                Serial.println(delta1);
            }
        }



                if(abs(delta2)> 0.5*65536) 
        {
            if(delta2>0)
            {
                delta2 = delta2 - 65536;
                Serial.print("cw adjusted delta2: ");
                Serial.println(delta2);
            }
            else if(delta2<0)
            {
                delta2 = delta2 + 65536;
                Serial.print("ccw adjusted delta2: ");
                Serial.println(delta2);
            }
        }

        t1_pos += delta1;
        t2_pos += delta2;

        Serial.print("t1_pos:");
        Serial.println(t1_pos);

        data_queue1.put(t1_pos); // read a data point and stuff it into queue
        data_queue2.put(t2_pos);
    }
    
}