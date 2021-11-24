/** @file FSRTask.cpp
 *  This file contains the method for a task that monitors the FSR and writes to a 
 *  shared variable called motor_shutoff
 * 
 *  @author  Michelle Chandler
 *  @date    24 Nov 2021 Original file
 */

#include <Arduino.h> 
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "shares.h"
#include "FSRTask.h"
#include "FSR.h"

void FSRTask(void)
{
    FSR fsr_obj(A5);

    for(;;)
    {
        fsr_obj.checkforcontact();
    }

}