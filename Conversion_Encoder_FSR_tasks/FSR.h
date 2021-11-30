/** @file FSR.ch
 *    This file contains the headers for a class that deals with the 
 *    FSR for the end effector
 *  @author Michelle Chandler
 *  @date  2021-Nov-18 Original file
 */


/** @brief   Class which controls the FSR
 *  @details This class represents the FSR that controls emergency shutoff of 
 *           the motors to protect the physical system
 */
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "shares.h" // idk if i need this here
#ifndef _FSR_H_ // idk what this is and if its necessary, 
#define _FSR_H_// just included it bs its in shares.h

class FSR
{
protected:
    // values that are only accessed by objects of that class

    // if constructor needs pins as params, need to put them here probs
    int _FSR_pin;
    
    /// This is the bool that is shared between classes
    Share <bool> motor_shutoff;

public:
    FSR(int FSR_pin); // constructor. may need to input FSR pin(s) as parameters

    void checkforcontact(void);     // this method checks to see if the fingers r in contact


};

#endif