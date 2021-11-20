/** @file Task1FrontEnd.h
 *  This file contains a task 
 * 
 *  @author  Michelle Chandler
 *  @date    18 Nov 2021 Original file
 */

/*
 * A class to read data from a csv file.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
class CSVReader
{
    std::string fileName;
    std::string delimeter;
public:
    CSVReader(std::string filename, std::string delm = ",") :
            fileName(filename), delimeter(delm)
    { }
    // Function to fetch data from a CSV File
    std::vector<std::vector<std::string> > getData();
};