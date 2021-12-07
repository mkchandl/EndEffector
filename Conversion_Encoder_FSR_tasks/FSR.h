/** @file FSR.ch
 *    This file contains the headers for a class that deals with the 
 *    FSR for the end effector
 *  @author Michelle Chandler and Cole Andrews
 *  @date  2021-Nov-18 Original file
 */



#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "shares.h" 
#ifndef _FSR_H_ 
#define _FSR_H_

/** @brief   Class which controls the FSR
 *  @details This class represents the FSR that controls emergency shutoff of 
 *           the motors to protect the physical system
 */

class FSR
{
protected:
    // values that are only accessed by objects of that class
    int _FSR_pin;

public:
    FSR(int FSR_pin); // constructor. may need to input FSR pin(s) as parameters
    void checkforcontact(void);     // this method checks to see if the fingers r in contact

};

#endif