/** @file FSRTask.cpp
 *  This file contains the method for a task that monitors the FSR and writes to a 
 *  shared variable called motor_shutoff, which is shared with the conversion task.
 * 
 *  @author  Michelle Chandler and Cole Andrews
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


/** @brief   Task which monitors the FSR attached to the tip of the finger 
 *  @details This task monitors the FSR and writes to a shared motor shutoff 
 *           variable if the pressure exceeds a certain range. 
 *  @param p_param This parameter was added to stop a compiler error
*/
void FSRTask(void* p_params)
{
    (void)p_params; 
    /// Create FSR object
    int FSR_pin = PC0;
    FSR fsr_obj(FSR_pin);
    /// Initialize the motor shutoff variable
    motor_shutoff.put(0);
    

    for(;;)
    {
        fsr_obj.checkforcontact();
        Serial.println("FT: checking for contact");
        vTaskDelay (2000);
    }

}