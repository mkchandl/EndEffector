/** @file shares.h
 *  This file contains extern declarations of shares and queues which are used
 *  in more than one file of a demonstration project.
 * 
 *  @author JR Ridgely
 *  @date   2021-Oct-23 Original file
 *  @copyright (c) 2021 by JR Ridgely, released under the LGPL 3.0. 
 */

#ifndef _SHARES_H_
#define _SHARES_H_

#include "FSR.h"

// A share which holds a counter of how many times a simulated event occurred
extern Share<int> motor_shutoff;

// A queue which triggers a task to print the count at certain times
// extern Queue<uint16_t> data_queue;


#endif // _SHARES_H_
