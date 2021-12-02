/** @file ConversionTask.cpp
 *  This file contains a task that takes the x,y coords of a finger pointer and then converts it 
 *  into the theta desired by the motor
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
#include "ConversionTask.h"
#include "MotorDriver.h"
#include <cmath>
#include "SerialComm.h"
#include "shares.h"

// Will both fingers have the same lengths? may need to add other finger dims here and then change them in eqn below
// const int8_t l1 = 1.67; // inches
// const int8_t l2 = 2; //in
// const int8_t l3 = 1.67;

const int8_t l1 = 40; // inches
const int8_t l2 = 60; //in
const int8_t l3 = 40;

const int Kp = 1;
const int Kd = 1;





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
 */

// idk if the Print& device is the correct thing here. Look into 
// what would need to be put in here if we want to read from serial within the funct
void task_conversion(void* p_params)
{
    (void)p_params; 
    /// create motor objects
    MotorDriver mot_obj1(PA15, PB4, PB5, PB2);
    MotorDriver mot_obj2(PA15, PB8, PB9, PB2);
    /// enable both motors
    mot_obj1.enable();
    mot_obj2.enable();
    /// create serial object
    SerialComm serial_obj;
    float t1= 0;
    float t2 = 0;

    for(;;)
    {
        Serial.println("CT: starting ");
        // check to make sure the fsr hasnt triggered a shutoff
         
        

        // takes in x and y by reading from serial port?
        /* this isnt right cause 
        i currently have the x,y array as an input. would it be better
        to do the serial port reading within this task or outside of it.
        */
        
        

         int16_t array_x1[] = {29,	31,	91,	58,	72,	84,	84,	75,	110,	114,	107,	98,	74,	61,	61,	58,	36,	61,	85,	81,	44,	89,	110,	130,	124,	121,	118,	108,	105,	105,	92,	59,	62,	47,	41,	100,	36,	39,	37,	37,	77,	54,	43,	50,	50,	45,	43,	53,	50,	57,	60,	47,	39,	39,	34,	48,	48,	58,	66,	57,	56,	50,	59,	35,	57,	75,	86,	43,	46,	35,	37,	33,	83,	107,	77,	84,	57,	58,	86,	95,	85,	86,	75,	59,	72,	87,	58,	64,	63,	80,	69,	88,	102,	69,	101,	55,	57,	61,	19,	49,	88,	35,	75,	14,	50,	57,	63,	41,	56,	94,	21,	30,	26,	45,	93,	51,	-15,	1,	13,	18,	26,	42,	5,	-13,	66,	63,	96,	93,	102,	98,	93,	98,	101,	97,	92,	88};
         int16_t array_y1[] = {4,	7,	-63,	-42,	-27,	-73,	-100,	-117,	-36,	-38,	-33,	-38,	-50,	-54,	-72,	-51,	-19,	-24,	-44,	-34,	-10,	-71,	-36,	-38,	22,	9,	4,	18,	10,	-5,	17,	3,	6,	-10,	-5,	-23,	15,	17,	13,	27,	-115,	9,	16,	18,	41,	36,	40,	37,	36,	33,	9,	40,	43,	45,	44,	28,	44,	45,	36,	34,	23,	51,	36,	34,	33,	29,	16,	17,	24,	13,	41,	53,	38,	27,	32,	-19,	8,	25,	26,	-13,	12,	16,	-11,	-1,	34,	12,	36,	32,	19,	21,	-4,	23,	-4,	39,	23,	34,	-18,	-39,	-25,	-79,	-29,	-49,	-22,	-125,	25,	-77,	61,	38,	30,	-11,	8,	-12,	-38,	1,	2,	-21,	17,	-119,	-135,	-80,	-20,	-77,	-76,	-45,	15,	16,	26,	15,	10,	-1,	0,	3,	-2,	-1,	0,	-5};
         float array_t1[] = { 2.37900972366333,	 2.443086862564087,	 2.728898763656616,	 2.7849035263061523,	 2.83512806892395,	 2.878408193588257,	 2.9532225131988525,	 2.9918668270111084,	 3.0441133975982666,	 3.088789939880371,	 3.1342833042144775,	 3.1850662231445312,	 3.2276265621185303,	 3.295459032058716,	 3.3435027599334717,	 3.392287492752075,	 3.435490608215332,	 3.4787254333496094,	 3.510849714279175,	 3.54058837890625,	 3.5820510387420654,	 3.6390304565429688,	 3.7012879848480225,	 3.7420127391815186,	 3.791975259780884,	 3.8398313522338867,	 3.8712494373321533,	 3.9018359184265137,	 3.9356653690338135,	 3.983764171600342,	 4.049932479858398,	 4.094818592071533,	 4.138554334640503,	 4.168176651000977,	 4.2015745639801025,	 4.2469482421875,	 4.29488468170166,	 4.322298765182495,	 4.37811017036438,	 4.444447994232178,	 4.494203329086304,	 4.547532558441162,	 4.582574844360352,	 4.635995388031006,	 4.685564756393433,	 4.7305309772491455,	 4.800760984420776,	 4.843681812286377,	 4.894083499908447,	 4.943371057510376,	 4.9908928871154785,	 5.035663604736328,	 5.087003469467163,	 5.134377956390381,	 5.177038669586182,	 5.206648349761963,	 5.246828317642212,	 5.295319557189941,	 5.3393659591674805,	 5.379717588424683,	 5.410040616989136,	 5.440037727355957,	 5.487179279327393,	 5.550535440444946,	 5.595181226730347,	 5.6476826667785645,	 5.702798843383789,	 5.73820948600769,	 5.766616106033325,	 5.8085150718688965,	 5.847972869873047,	 5.885896444320679,	 5.952123403549194,	 5.995136976242065,	 6.0477893352508545,	 6.095179796218872,	 6.144151210784912,	 6.195597171783447,	 6.239933490753174,	 6.301986217498779,	 6.350689172744751,	 6.398151874542236,	 6.447540044784546,	 6.503889560699463,	 6.594150543212891,	 6.635868072509766,	 6.673157215118408,	 6.738593101501465,	 6.797063112258911,	 6.829704523086548,	 6.860383749008179,	 6.987278938293457,	 7.050623178482056,	 7.098408460617065,	 7.447912931442261,	 7.5537824630737305,	 7.5950798988342285,	 7.639362335205078,	 7.667863368988037,	 7.804904937744141,	 7.855463266372681,	 7.89888072013855,	 7.961617469787598,	 8.032304286956787,	 8.104344367980957,	 8.199593544006348,	 8.295241355895996,	 8.351545095443726,	 8.395458221435547,	 8.43235969543457,	 8.463326930999756,	 8.496195077896118,	 8.554067373275757,	 8.791519403457642,	 8.89223575592041,	 9.706957340240479,	 10.268837928771973,	 10.34730863571167,	 10.406938791275024,	 12.128625869750977,	 12.165273427963257,	 12.205106258392334,	 12.255870580673218,	 12.322219848632812,	 13.177741765975952,	 13.220935344696045,	 13.819305419921875,	 13.874513626098633,	 13.912845373153687,	 13.956334590911865,	 13.986233711242676,	 14.017420768737793,	 14.0618736743927,	 14.107521772384644,	 14.158464431762695,	 14.219776153564453};
         Serial.println("CT: Made x1, y1, t1 arrays");
         int16_t array_x2[] = {0};
         int16_t array_y2[] = {0};
         float array_t2[] = {0};

         // int16_t x1 = serial_obj.return_x1(); // need to figure out unit conversion for this
         // int16_t y1 = serial_obj.return_y1();
         // int16_t t1 = serial_obj.return_t1();
         // int16_t x2 = serial_obj.return_x2();
         // int16_t y2 = serial_obj.return_y2();
         // int16_t t2 = serial_obj.return_t2();
         // Serial.print("t2: ");
         // Serial.println(t2);
        

         int len = sizeof(array_x1)/sizeof(array_x1[0]);
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
            Serial.print("theta1:  ");
            Serial.println(theta_1);
            float c_31 = ( pow((array_x1[index] - l1*sin(theta_1)),2) + pow(array_y1[index],2) + pow((0 - l1*cos(theta_1)), 2) - pow(l2, 2 ) - pow(l3, 2))/(2*l1*l2);
            float c_32 = ( pow((array_x2[index] - l1*sin(theta_1)),2) + pow(array_y2[index],2) + pow((0 - l1*cos(theta_1)), 2) - pow(l2, 2 ) - pow(l3, 2))/(2*l1*l2);
            Serial.print("c31:  ");
            Serial.println(c_31);
            float s_31 = sqrt(1 - pow(c_31,2));
            float s_32 = sqrt(1 - pow(c_32,2));
            Serial.print("s31:  ");
            Serial.println(s_31);
            float k_11 = l2 + l3*c_31;
            float k_12 = l2 + l3*c_32;
            Serial.print("k11:  ");
            Serial.println(k_11);
            float k_21 = l3*s_31;
            float k_22 = l3*s_32;
            Serial.print("k21:  ");
            Serial.println(k_21);
            float theta_2_1_rad = atan2(sqrt( pow((array_x1[index] - l1*sin(theta_1)),2) + pow((0 - l1*cos(theta_1)), 2)), array_y1[index]) - atan2(k_21, k_11) ; // [rad]
            float theta_2_2_rad = atan2(sqrt( pow((array_x2[index] - l1*sin(theta_1)),2) + pow((0 - l1*cos(theta_1)), 2)), array_x2[index]) - atan2(k_22, k_12) ; 
            Serial.print("Theta_2_1 [rad]:  ");
            Serial.println(theta_2_1_rad);
            //^^^ this needs a plus/minus in front of the swaure root, or an if statement and 2 equations?

            // //THETA2 RAD TO DEGREES
            int16_t theta_2_1 = theta_2_1_rad*(180); // [deg]
            // Serial.print("Theta_2_1 [deg]:  ");
            // Serial.println(theta_2_1);
            int16_t theta_2_2 = theta_2_2_rad*(180);

            // theta 2 will be plugged into an empiracally found eqn to get theta m
            int16_t theta_m1 = theta_2_1 * 0.375/0.25; // [deg] will fill in later. gear ratio? 
            //Serial.print("Theta_m1 [deg]:  ");
            //Serial.println(theta_m1);
            int16_t theta_m2 = theta_2_2 * 0.375/0.25; // if gear ratio: Theta_m = Theta_2 * (radius of joint) / (radius of motor pulley)

            // // find error signal theta m using encoder feedback
            int16_t enc_feedback_thetam1 = data_queue1.get(); // [deg]
            // Serial.print("Encoder position [deg]:  ");
            // Serial.println(enc_feedback_thetam1);
            int16_t enc_feedback_thetam2 = data_queue2.get(); //pull encoder data from queue

            int16_t error1 = theta_m1 - enc_feedback_thetam1; // [deg]
            //Serial.print("Error, E(s) [deg]:  ");
            //Serial.println(error1);
            int16_t error2 = theta_m2 - enc_feedback_thetam2;

            // convert from thetam to thetam_d by dividing by desired response time
            int16_t thetam_d1 = error1/delta_t1; // [deg/s]
            //Serial.print("thetam_d1 [deg/s]:  ");
            //Serial.println(thetam_d1);
            int16_t thetam_d2 = error2/delta_t2;

            // convert from deg/ to rpm for thetam_d1/2
            int16_t thetam_d1_rpm = thetam_d1/6; // [rpm]
            //Serial.print("thetam_d1_rpm [rpm]:  ");
            //Serial.println(thetam_d1_rpm);
            int16_t thetam_d2_rpm = thetam_d2/6;

            // give the thetam_d signal to controler
            int16_t proportional = Kp*thetam_d1_rpm; // [rpm]]
            int16_t derivative = Kd*thetam_d1_rpm/(delta_t1/60); // [rpm/m]*[s]
            int16_t controlled_thetam_d1 = proportional + derivative; //[rpm]
            //Serial.print("Controller Signal [rpm]:  ");
            //Serial.println(controlled_thetam_d1);
            int16_t proportional2 = Kp*thetam_d2_rpm;
            int16_t derivative2 = Kd*thetam_d2_rpm/(delta_t2/60);
            int16_t controlled_thetam_d2 = proportional2 + derivative2;

            // convert from thetam_d [rpm] to duty cycle [%]
            // give duty cycle to motor
            float duty1 = .012*controlled_thetam_d1;
            //Serial.print("Duty Cycle [%]:  ");
            
            float duty2 = .012*controlled_thetam_d2;
            
            mot_obj1.set_duty2(duty1);
            Serial.print("Duty: ");
            Serial.println(duty1);
            mot_obj2.set_duty2(duty2);

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