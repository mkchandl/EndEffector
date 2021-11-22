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
#include <cmath>


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

    // constants
    int16_t l_1 = 1; //[in]
    int16_t l_2 = 1; //[in]
    int16_t l_3 = 1; //[in]
    int16_t x = coords[0];
    int16_t y = coords[1];
    int16_t z = 0; //????   

    int16_t c_3 = ( pow((x - l_1*sin(theta_1)),2) + pow(y,2) + pow((z - l_1*cos(theta_1)), 2) - pow(l_2, 2 ) - pow(l_3, 2))
    /(2*l_1*l_2);

    int16_t s_3 = sqrt(1 - pow(c_3,2));

    int16_t k_1 = l_2 + l_3*c_3;
    int16_t k_2 = l_3*s_3;

    // uses eqn 6 from paper to get the value theta 2
    int16_t theta_2 = atan2(sqrt( pow((x - l_1*sin(theta_1)),2) + pow((z - l_1*cos(theta_1)), 2)), y) - atan2(k_2, k_1) ; 
    //^^^ this needs a plus/minus in front of the swaure root, or an if statement and 2 equations?

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