/** @file EncoderTask.h
 *  This file contains headers for a task that records the motor shaft position of both motors and 
 *  converts the ticks into angular position which is then used for to generate the error signal
 *  in the conversiont task
 * 
 *  @author  Michelle Chandler
 *  @date    18 Nov 2021 Original file
 */

#include <Arduino.h>
void task_encoder(void);

