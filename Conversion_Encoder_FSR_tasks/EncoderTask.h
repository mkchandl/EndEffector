/** @file EncoderTask.h
 *  This file contains headers for a task that records the motor shaft position of both motors and 
 *  converts the ticks into angular position which is then used for to generate the error signal
 *  in the conversiont task
 * 
 *  @author  Michelle Chandler and Cole Andrews
 *  @date    18 Nov 2021 Original file
 */
#ifndef _ENCODER_TASK_
#define _ENCODER_TASK_
void task_encoder(void* p_params);

#endif