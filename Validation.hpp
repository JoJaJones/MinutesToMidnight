/******************************************************************************
 * Name: Patricia Booth, Josh Jones, Lindsey Olmstead, Jason Rash
 * Date: 6-21-19
 * Description: Validation of user input.
******************************************************************************/

#ifndef Validation_HPP
#define Validation_HPP

#include <iostream>
#include <string>
#include "Countdown.hpp"

struct StringCarrier{
    std::string creationString;
    std::string targetString;
    std::string enumString;
    std::string nameString;
};

int getInt(int, int, std::string);
long long getInt(std::string);
bool isInt(std::string);
bool isWithinRange(int num, int min, int max);
std::string noSpace(std::string str);
std::string sanitizeString(std::string);
StringCarrier splitString(std::string str);
Countdown processDataString(std::string);


#endif