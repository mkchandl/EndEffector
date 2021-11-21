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
#include "MotorDriver.h"


//have the gains be the peranent variables up here

/** @brief   Task which 
 *  @details This task 
 *  @param   .
 */

int32_t task_conversion(int16_t coords[2], int32_t enc_feedback_thetam)
{
    // create motor object
    MotorDriver mot_obj(PA15, D5, D4, D14, D15, PB2);

    // takes in x and y by reading from serial port?
    /* this isnt right cause 
     i currently have the x,y array as an input. would it be better
     to do the serial port reading within this task or outside of it.
    */

    // uses eqn 6 from paper to get the value theta 2
    int16_t theta_2 = 1+1; // will fill in later

    // theta 2 will be plugged into an empiracally found eqn to get theta m
    int16_t theta_m = theta_2 * 0.5; // will fill in later

    // find error signal theta m using encoder feedback
    int16_t error = theta_m - enc_feedback_thetam;

    // convert from thetam to thetam_d by dividing by desired response time
    int desired_delta_t = 0.5; //seconds; randomly chosen value
    int16_t thetam_d = theta_m/desired_delta_t;

    // give the thetam_d signal to controler
    int16_t proportional = 

    // convert from thetam_d to duty cycle
    // give duty cycle to motor

    //IN A SEPARATE TASK THAT I HAVE YET TO MAKE
    // take encoder readings, return motor position, thetam

}