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

#include "taskqueue.h"
#include "taskshare.h"
 
using std::endl; // from stack overflow to fix compiler errors

// A share which holds a bool of whether or not to shutoff the motors
extern Share<int> motor_shutoff;

// A queue which holds encoder1 positions
extern Queue<uint16_t> data_queue1;

// A queue which holds encoder2 positions
extern Queue<uint16_t> data_queue2;

// A queue which holds finger 1 coordinates
// extern Queue<uint16_t> coord1;

// A queue which holds finger 2 coordinates
// extern Queue<uint16_t> coord2;


#endif // _SHARES_H_
