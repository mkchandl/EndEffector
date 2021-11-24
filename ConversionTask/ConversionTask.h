/** @file ConversionTask.h
 *  This file contains headers for a task that takes the x,y coords of a finger pointer and then converts it 
 *  into the theta desired by the motor
 * 
 *  @author  Michelle Chandler
 *  @date    18 Nov 2021 Original file
 */

#include <Arduino.h>
int32_t task_conversion(int16_t coords[2], int16_t time_response[2], int32_t enc_feedback_thetam, Print& device = Serial);