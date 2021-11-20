/** @file main.cpp
 *    This file contains 
 * 
 *  @author Michelle Chandler
 *  @date   18 Nov 2021 Original file
*/

#include <Arduino.h>
#include <PrintStream.h>
#if (defined STM32L4xx || defined STM32F4xx)
    #include <STM32FreeRTOS.h>
#endif
#include "CSVReader.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>

void setup() {
  // put your setup code here, to run once:

  //set up serial
  Serial.begin (115200);
  delay (2000);
  Serial << endl << endl << "Hello, I am an RTOS demonstration" << endl;

  // testing read .csv class
  // create ClassFrontEnd object
  CSVReader reader("example.csv");
  // Get the data from CSV File
  std::vector<std::vector<std::string> > dataList = reader.getData();
  
  // Print the content of row by row on screen
    for(std::vector<std::string> vec : dataList)
    {
        for(std::string data : vec)
        {
            std::cout<<data << " , ";
        }
        std::cout<<std::endl;
    }
    return 0;
}

void loop() {
  // put your main code here, to run repeatedly:
}