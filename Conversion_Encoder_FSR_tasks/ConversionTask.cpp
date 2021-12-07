/** @file ConversionTask.cpp
 *  This file contains a task that takes the x,y coords of a finger pointer and then converts it 
 *  into the theta desired by the motor
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
#include "ConversionTask.h"
#include "MotorDriver.h"
#include <cmath>
#include "SerialComm.h"
#include "shares.h"

// const int8_t l1 = 1.67; // inches
// const int8_t l2 = 2; //in
// const int8_t l3 = 1.67;

const int8_t l1 = 40; // inches
const int8_t l2 = 60; //in
const int8_t l3 = 40;

const float Kp = 1;
//const float Kd = .01;


/** @brief   Task which provides motors with duty cycles to match the computer-vision hand
 *  @details This task calls a number of classes including the motor driver, serial, and FSR task
 *           in order to grab the coordinates provided by the computer-vision program running on the 
 *           desktop and converting them into the angular displacement of the first joint of the finger.
 *           The equation that was used for this was found here: 
 *           https://www.researchgate.net/publication/290740307_A_Three_Finger_Tendon_Driven_Robotic_Hand_Design_and_Its_Kinematics_Model
 *           This angular displacement is translated into angular velocity, fed through a controller, 
 *           converted to duty cycle using a linear relationship between 100% duty and max motor speed.
 *           This duty cycle is fed to the motors
 *  @param p_param This parameter was added to stop a compiler error
 */


void task_conversion(void* p_params)
{
    (void)p_params; 
    
    /// create motor objects
    MotorDriver mot_obj2(PA15, PB4, PB5, PB2);
    MotorDriver mot_obj1(PA15, PB8, PB9, PB2);
    /// disable motors to ensure no undesired motor movement
    mot_obj1.disable();
    mot_obj2.disable();
    /// enable both motors
    mot_obj1.enable();
    mot_obj2.enable();
    /// create serial object
    SerialComm serial_obj;
    float t1= 0;
    float t2 = 0;

    float array_x1[] = {1.14173228346457,	1.22047244094488,	3.58267716535433,	2.28346456692913,	2.83464566929134,	3.30708661417323,	3.30708661417323,	2.95275590551181,	4.33070866141732,	4.48818897637795,	4.21259842519685,	3.85826771653543,	2.91338582677165,	2.40157480314961,	2.40157480314961,	2.28346456692913,	1.41732283464567,	2.40157480314961,	3.34645669291339,	3.18897637795276,	1.73228346456693,	3.50393700787402,	4.33070866141732,	5.11811023622047,	4.88188976377953,	4.76377952755906,	4.64566929133858,	4.25196850393701,	4.13385826771654,	4.13385826771654,	3.62204724409449,	2.32283464566929,	2.44094488188976,	1.8503937007874,	1.61417322834646,	3.93700787401575,	1.41732283464567,	1.53543307086614,	1.45669291338583,	1.45669291338583,	3.03149606299213,	2.1259842519685,	1.69291338582677,	1.96850393700787,	1.96850393700787,	1.77165354330709,	1.69291338582677,	2.08661417322835,	1.96850393700787,	2.24409448818898,	2.36220472440945,	1.8503937007874,	1.53543307086614,	1.53543307086614,	1.33858267716535,	1.88976377952756,	1.88976377952756,	2.28346456692913,	2.59842519685039,	2.24409448818898,	2.20472440944882,	1.96850393700787,	2.32283464566929,	1.37795275590551,	2.24409448818898,	2.95275590551181,	3.38582677165354,	1.69291338582677,	1.81102362204724,	1.37795275590551,	1.45669291338583,	1.2992125984252,	3.26771653543307,	4.21259842519685,	3.03149606299213,	3.30708661417323,	2.24409448818898,	2.28346456692913,	3.38582677165354,	3.74015748031496,	3.34645669291339,	3.38582677165354,	2.95275590551181,	2.32283464566929,	2.83464566929134,	3.4251968503937,	2.28346456692913,	2.51968503937008,	2.48031496062992,	3.1496062992126,	2.71653543307087,	3.46456692913386,	4.01574803149606,	2.71653543307087,	3.97637795275591,	2.16535433070866,	2.24409448818898,	2.40157480314961,	0.748031496062992,	1.92913385826772,	3.46456692913386,	1.37795275590551,	2.95275590551181,	0.551181102362205,	1.96850393700787,	2.24409448818898,	2.48031496062992,	1.61417322834646,	2.20472440944882,	3.7007874015748,	0.826771653543307,	1.18110236220472,	1.02362204724409,	1.77165354330709,	3.66141732283465,	2.00787401574803,	-0.590551181102362,	0.0393700787401575,	0.511811023622047,	0.708661417322835,	1.02362204724409,	1.65354330708661,	0.196850393700787,	-0.511811023622047,	2.59842519685039,	2.48031496062992,	3.77952755905512,	3.66141732283465,	4.01574803149606,	3.85826771653543,	3.66141732283465,	3.85826771653543,	3.97637795275591,	3.81889763779528,	3.62204724409449,	3.46456692913386,};
    float array_y1[] = {0.15748031496063,	0.275590551181102,	-2.48031496062992,	-1.65354330708661,	-1.06299212598425,	-2.8740157480315,	-3.93700787401575,	-4.60629921259843,	-1.41732283464567,	-1.49606299212598,	-1.2992125984252,	-1.49606299212598,	-1.96850393700787,	-2.1259842519685,	-2.83464566929134,	-2.00787401574803,	-0.748031496062992,	-0.94488188976378,	-1.73228346456693,	-1.33858267716535,	-0.393700787401575,	-2.79527559055118,	-1.41732283464567,	-1.49606299212598,	0.866141732283465,	0.354330708661417,	0.15748031496063,	0.708661417322835,	0.393700787401575,	-0.196850393700787,	0.669291338582677,	0.118110236220472,	0.236220472440945,	-0.393700787401575,	-0.196850393700787,	-0.905511811023622,	0.590551181102362,	0.669291338582677,	0.511811023622047,	1.06299212598425,	-4.52755905511811,	0.354330708661417,	0.62992125984252,	0.708661417322835,	1.61417322834646,	1.41732283464567,	1.5748031496063,	1.45669291338583,	1.41732283464567,	1.2992125984252,	0.354330708661417,	1.5748031496063,	1.69291338582677,	1.77165354330709,	1.73228346456693,	1.10236220472441,	1.73228346456693,	1.77165354330709,	1.41732283464567,	1.33858267716535,	0.905511811023622,	2.00787401574803,	1.41732283464567,	1.33858267716535,	1.2992125984252,	1.14173228346457,	0.62992125984252,	0.669291338582677,	0.94488188976378,	0.511811023622047,	1.61417322834646,	2.08661417322835,	1.49606299212598,	1.06299212598425,	1.25984251968504,	-0.748031496062992,	0.31496062992126,	0.984251968503937,	1.02362204724409,	-0.511811023622047,	0.47244094488189,	0.62992125984252,	-0.433070866141732,	-0.0393700787401575,	1.33858267716535,	0.47244094488189,	1.41732283464567,	1.25984251968504,	0.748031496062992,	0.826771653543307,	-0.15748031496063,	0.905511811023622,	-0.15748031496063,	1.53543307086614,	0.905511811023622,	1.33858267716535,	-0.708661417322835,	-1.53543307086614,	-0.984251968503937,	-3.11023622047244,	-1.14173228346457,	-1.92913385826772,	-0.866141732283465,	-4.92125984251969,	0.984251968503937,	-3.03149606299213,	2.40157480314961,	1.49606299212598,	1.18110236220472,	-0.433070866141732,	0.31496062992126,	-0.47244094488189,	-1.49606299212598,	0.0393700787401575,	0.078740157480315,	-0.826771653543307,	0.669291338582677,	-4.68503937007874,	-5.31496062992126,	-3.1496062992126,	-0.78740157480315,	-3.03149606299213,	-2.99212598425197,	-1.77165354330709,	0.590551181102362,	0.62992125984252,	1.02362204724409,	0.590551181102362,	0.393700787401575,	-0.0393700787401575,	0,	0.118110236220472,	-0.078740157480315,	-0.0393700787401575,	0,	-0.196850393700787,};
    float array_t1[] = { 2.37900972366333,	 2.443086862564087,	 2.728898763656616,	 2.7849035263061523,	 2.83512806892395,	 2.878408193588257,	 2.9532225131988525,	 2.9918668270111084,	 3.0441133975982666,	 3.088789939880371,	 3.1342833042144775,	 3.1850662231445312,	 3.2276265621185303,	 3.295459032058716,	 3.3435027599334717,	 3.392287492752075,	 3.435490608215332,	 3.4787254333496094,	 3.510849714279175,	 3.54058837890625,	 3.5820510387420654,	 3.6390304565429688,	 3.7012879848480225,	 3.7420127391815186,	 3.791975259780884,	 3.8398313522338867,	 3.8712494373321533,	 3.9018359184265137,	 3.9356653690338135,	 3.983764171600342,	 4.049932479858398,	 4.094818592071533,	 4.138554334640503,	 4.168176651000977,	 4.2015745639801025,	 4.2469482421875,	 4.29488468170166,	 4.322298765182495,	 4.37811017036438,	 4.444447994232178,	 4.494203329086304,	 4.547532558441162,	 4.582574844360352,	 4.635995388031006,	 4.685564756393433,	 4.7305309772491455,	 4.800760984420776,	 4.843681812286377,	 4.894083499908447,	 4.943371057510376,	 4.9908928871154785,	 5.035663604736328,	 5.087003469467163,	 5.134377956390381,	 5.177038669586182,	 5.206648349761963,	 5.246828317642212,	 5.295319557189941,	 5.3393659591674805,	 5.379717588424683,	 5.410040616989136,	 5.440037727355957,	 5.487179279327393,	 5.550535440444946,	 5.595181226730347,	 5.6476826667785645,	 5.702798843383789,	 5.73820948600769,	 5.766616106033325,	 5.8085150718688965,	 5.847972869873047,	 5.885896444320679,	 5.952123403549194,	 5.995136976242065,	 6.0477893352508545,	 6.095179796218872,	 6.144151210784912,	 6.195597171783447,	 6.239933490753174,	 6.301986217498779,	 6.350689172744751,	 6.398151874542236,	 6.447540044784546,	 6.503889560699463,	 6.594150543212891,	 6.635868072509766,	 6.673157215118408,	 6.738593101501465,	 6.797063112258911,	 6.829704523086548,	 6.860383749008179,	 6.987278938293457,	 7.050623178482056,	 7.098408460617065,	 7.447912931442261,	 7.5537824630737305,	 7.5950798988342285,	 7.639362335205078,	 7.667863368988037,	 7.804904937744141,	 7.855463266372681,	 7.89888072013855,	 7.961617469787598,	 8.032304286956787,	 8.104344367980957,	 8.199593544006348,	 8.295241355895996,	 8.351545095443726,	 8.395458221435547,	 8.43235969543457,	 8.463326930999756,	 8.496195077896118,	 8.554067373275757,	 8.791519403457642,	 8.89223575592041,	 9.706957340240479,	 10.268837928771973,	 10.34730863571167,	 10.406938791275024,	 12.128625869750977,	 12.165273427963257,	 12.205106258392334,	 12.255870580673218,	 12.322219848632812,	 13.177741765975952,	 13.220935344696045,	 13.819305419921875,	 13.874513626098633,	 13.912845373153687,	 13.956334590911865,	 13.986233711242676,	 14.017420768737793,	 14.0618736743927,	 14.107521772384644,	 14.158464431762695,	 14.219776153564453};

    

    for(;;)
    {
        Serial.println("CT: starting ");
        
        //  Serial.println("CT: Made x1, y1, t1 arrays");
         int16_t array_x2[] = {0};
         int16_t array_y2[] = {0};
        float array_t2[] = {0};

        //  // int16_t x1 = serial_obj.return_x1(); // need to figure out unit conversion for this
        //  // int16_t y1 = serial_obj.return_y1();
        int16_t t1 = serial_obj.return_t1();
        //  // int16_t x2 = serial_obj.return_x2();
        //  // int16_t y2 = serial_obj.return_y2();
        int16_t t2 = serial_obj.return_t2();
        //  // Serial.print("t2: ");
        //  // Serial.println(t2);
        
        // float array_x1[] ={2.2};
        // float array_y1[] = {4.6};
        // float array_t1[] = { 2.37900972366333,	 2.443086862564087};

        int len = sizeof(array_t1)/sizeof(array_t1[0]);
        int index = 0;
        while(index<len)
         {
            Serial.print("index:  ");
            Serial.println(index);
            Serial.print("array_x1 value [??]:  ");
            Serial.println(array_x1[index]);
            Serial.print("array_y1 value [??]:  ");
            Serial.println(array_y1[index]);

            float old_timestamp1 = array_t1[index-1]; // save old time stamps of last coords for finger 1
            float old_timestamp2 = array_t2[index-1];

            float delta_t1 = array_t1[index] - old_timestamp1; //delta for the thetam_d
            float delta_t2 = array_t2[index] - old_timestamp2; //delta for the thetam_d
                
                // uses eqn 6 from paper to get the value theta 2
            const int theta_1 = 0; // degrees
            float c_31 = ( pow((array_x1[index] - l1*sin(theta_1)),2) + pow(array_y1[index],2) + pow((0 - l1*cos(theta_1)), 2) - pow(l2, 2 ) - pow(l3, 2))/(2*l1*l2);
            float c_32 = ( pow((array_x2[index] - l1*sin(theta_1)),2) + pow(array_y2[index],2) + pow((0 - l1*cos(theta_1)), 2) - pow(l2, 2 ) - pow(l3, 2))/(2*l1*l2);
            if(c_31 > 1)
            {
                c_31 = 0;
            }
            float s_31 = sqrt(1 - pow(c_31,2));
            float s_32 = sqrt(1 - pow(c_32,2));
            float k_11 = l2 + l3*c_31;
            float k_12 = l2 + l3*c_32;
            float k_21 = l3*s_31;
            float k_22 = l3*s_32;
            float theta_2_1_rad = atan2(sqrt( pow((array_x1[index] - l1*sin(theta_1)),2) + pow((0 - l1*cos(theta_1)), 2)), array_y1[index]) - atan2(k_21, k_11) ; // [rad]
            float theta_2_2_rad = atan2(sqrt( pow((array_x2[index] - l1*sin(theta_1)),2) + pow((0 - l1*cos(theta_1)), 2)), array_x2[index]) - atan2(k_22, k_12) ; 

            //^^^ this needs a plus/minus in front of the swaure root, or an if statement and 2 equations?

            //THETA2 RAD TO DEGREES
            float theta_2_1 = theta_2_1_rad*(180); // [deg]
             Serial.print("Theta_2_1 [deg]:  ");
             Serial.println(theta_2_1);
            float theta_2_2 = theta_2_2_rad*(180);

            //int16_t theta_2_1 = 60;
            //int16_t theta_2_2 = 60;

            // theta 2 will be plugged into an empiracally found eqn to get theta m
            float theta_m1 = theta_2_1 * 0.375/0.25; // [deg] will fill in later. gear ratio? 
            Serial.print("Theta_m1 [deg]:  ");
            Serial.println(theta_m1);
            float theta_m2 = theta_2_2 * 0.375/0.25; // if gear ratio: Theta_m = Theta_2 * (radius of joint) / (radius of motor pulley)

            // // find error signal theta m using encoder feedback
            int32_t enc_feedback_thetam1 = data_queue1.get(); // [deg]
            Serial.print("Encoder position [deg]:  ");
            Serial.println(enc_feedback_thetam1);
            int32_t enc_feedback_thetam2 = data_queue2.get(); //pull encoder data from queue

            float error1 = theta_m1 - enc_feedback_thetam1; // [deg]
            Serial.print("Error, E(s) [deg]:  ");
            Serial.println(error1);
            float error2 = theta_m2 - enc_feedback_thetam2;

            // convert from thetam to thetam_d by dividing by desired response time
            float thetam_d1 = error1/delta_t1; // [deg/s]
            Serial.print("thetam_d1 [deg/s]:  ");
            Serial.println(thetam_d1);
            float thetam_d2 = error2/delta_t2;

            // convert from deg/ to rpm for thetam_d1/2
            float thetam_d1_rpm = thetam_d1/6; // [rpm]
            Serial.print("thetam_d1_rpm [rpm]:  ");
            Serial.println(thetam_d1_rpm);
            float thetam_d2_rpm = thetam_d2/6;

            // give the thetam_d signal to controler
            float proportional = Kp*thetam_d1_rpm; // [rpm]]
            float controlled_thetam_d1 = proportional ; //[rpm]
            float proportional2 = Kp*thetam_d2_rpm;
            float controlled_thetam_d2 = proportional2;

            // convert from thetam_d [rpm] to duty cycle [%]
            // give duty cycle to motor
            float duty1 = 1.2*controlled_thetam_d1;
            //Serial.print("Duty Cycle [%]:  ");
            
            float duty2 = 1.2*controlled_thetam_d2;
            
            mot_obj1.set_duty2(duty1);
            Serial.print("Duty: ");
            Serial.println(duty1);
            mot_obj2.set_duty2(duty2);

            /// Check to make sure the fsr hasnt triggered a shutoff
            Serial.println("CT: getting motor shuttof value ");
        //  int _motor_shutoff = motor_shutoff.get();
        //  if (_motor_shutoff == 1)
        //  {
        //     mot_obj1.disable();
        //     mot_obj2.disable();
        //     Serial.println("CT: FSR TRIGGERED SHUTOFF ");
        //  }

             index++;
         }

        

        
        vTaskDelay (500);
    }
}