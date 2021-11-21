/** @file ConversionTask.cpp
 *  This file contains a task that takes the x,y coords of a finger pointer and then converts it 
 *  into the theta desired by the motor
 * 
 *  @author  Michelle Chandler
 *  @date    18 Nov 2021 Original file
 */

#include <Arduino.h> 
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "ConversionTask.h"


/** @brief   Task which 
 *  @details This task 
 *  @param   .
 */

int32_t task_conversion(int16_t x, int16_t y, int32_t enc_feedback_thetam)
{
    // create encoder objects
    // create motor object
    // takes in x and y
    // uses eqn 6 from paper to get the value theta 2
    // theta 2 will be plugged into an empiracally found eqn to get theta m
    // find error signal theta m using encoder feedback
    // convert from thetam to thetam_d by dividing by desired response time
    // give the thetam_d signal to controler
    // convert from thetam_d to duty cycle
    // give duty cycle to motor

    //IN A SEPARATE TASK THAT I HAVE YET TO MAKE
    // take encoder readings, return motor position, thetam
    
}