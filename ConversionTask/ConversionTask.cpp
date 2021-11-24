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
#include "SerialComm.h"

//have the gains be the peranent variables up here
// static lenths?
static int8_t l1 = 1.67; // inches
static int8_t l2 = 2; //in
static int8_t l3 = 1.67;
static int theta_1 = 45; // degrees



//WILL INT16_T BE LARG ENOUGH FOR THESE VARIABLES?

/** @brief   Task which provides motors with duty cycles to match the computer-vision hand
 *  @details This task calls a number of classes including the motor driver, serial, and FSR task
 *           in order to grab the coordinates provided by the computer-vision program running on the 
 *           desktop and converting them into the angular displacement of the first joint of the finger.
 *           The equation that was used for this was found here: 
 *           https://www.researchgate.net/publication/290740307_A_Three_Finger_Tendon_Driven_Robotic_Hand_Design_and_Its_Kinematics_Model
 *           This angular displacement is translated into angular velocity, fed through a controller, 
 *           converted to duty cycle using a linear relationship between 100% duty and max motor speed.
 *           This duty cycle is fed to the motors
 *  @param   .
 */

// idk if the Print& device is the correct thing here. Look into 
// what would need to be put in here if we want to read from serial within the funct
int32_t task_conversion(int32_t enc_feedback_thetam1, int32_t enc_feedback_thetam2, int Kp, int Kd)
{
    // create motor object
    MotorDriver mot_obj1(PA15, D5, D4, PB2);
    MotorDriver mot_obj2(PA15, D14, D15, PB2);

    // takes in x and y by reading from serial port?
    /* this isnt right cause 
     i currently have the x,y array as an input. would it be better
     to do the serial port reading within this task or outside of it.
    */
    SerialComm serial_obj; // create serial object
    int16_t old_timestamp1 = coords1[2]; // save old time stamps of last coords for finger 1
    int16_t old_timestamp2 = coords2[2];
    serial_obj.read(); // grab the newest coords and time stamps
    int16_t x1 = coords1[0];
    int16_t y1 = coords1[1];
    int16_t t1 = coords1[2]
    int16_t x2 = coords2[0];
    int16_t y2 = coords2[1];
    int16_t t2 = coords2[2]
    int16_t delta_t1 = t1 - old_timestamp1; //delta for the thetam_d
    int16_t delta_t2 = t2 - old_timestamp2; //delta for the thetam_d



    // uses eqn 6 from paper to get the value theta 2
    int16_t c_3 = ( pow((x - l1*sin(theta_1)),2) + pow(y,2) + pow((z - l1*cos(theta_1)), 2) - pow(l_2, 2 ) - pow(l_3, 2))
    /(2*l1*l2);
    int16_t s_3 = sqrt(1 - pow(c_3,2));
    int16_t k_1 = l2 + l3*c_3;
    int16_t k_2 = l3*s_3;
    int16_t theta_2_1 = atan2(sqrt( pow((x1 - l1*sin(theta_1)),2) + pow((0 - l1*cos(theta_1)), 2)), y1) - atan2(k_2, k_1) ; 
    int16_t theta_2_2 = atan2(sqrt( pow((x2 - l1*sin(theta_1)),2) + pow((0 - l1*cos(theta_1)), 2)), y2) - atan2(k_2, k_1) ; 
    //^^^ this needs a plus/minus in front of the swaure root, or an if statement and 2 equations?


    // theta 2 will be plugged into an empiracally found eqn to get theta m
    int16_t theta_m1 = theta_2_1 * 1; // will fill in later
    int16_t theta_m2 = theta_2_2 * 1;

    // find error signal theta m using encoder feedback
    int16_t error1 = theta_m1 - enc_feedback_thetam1;
    int16_t error2 = theta_m2 - enc_feedback_thetam2;

    // convert from thetam to thetam_d by dividing by desired response time
    int16_t thetam_d1 = theta_m1/delta_t1;
    int16_t thetam_d2 = theta_m2/delta_t2;

    // give the thetam_d signal to controler
    int16_t proportional = Kp*thetam_d1;
    int16_t derivative = Kd*thetam_d1;
    int16_t controlled_thetam_d1 = proportional + derivative;
    int16_t proportional2 = Kp*thetam_d2;
    int16_t derivative2 = Kd*thetam_d2;
    int16_t controlled_thetam_d2 = proportional2 + derivative2;

    // convert from thetam_d to duty cycle
    // give duty cycle to motor
    float duty1 = 0.0138*controlled_thetam_d1 -1.38;
    float duty2 = 0.0138*controlled_thetam_d2 -1.38;
    mot_obj1.set_duty(duty1);
    mot_obj2.set_duty(duty2);
    //IN A SEPARATE TASK THAT I HAVE YET TO MAKE
    // take encoder readings, return motor position, thetam

}