/******************************************************************************
 * Name: Patricia Booth, Josh Jones, Lindsey Olmstead, Jason Rash
 * Date: 6-21-19
 * Description: Validation of user input header file.
******************************************************************************/

#include "Validation.hpp"


// NOTE: If input from user is " 1" or "	1" (\t then a number) it doesn't consider it an Integer.

int getInt(int min, int max)
{
	int num = -1;
	std::string str = "";
	while (!isInt(str) || !isWithinRange(num, min, max) || str.empty())
	{
		str = "";
		num = 0;
	    std::getline(std::cin, str);
		str = noSpace(str);
		if (isInt(str))
		{
			for (unsigned i = 0; i < str.length(); i++)
			{
				num = num * 10 + (str[i] - 48);    // 0 = 48 in ascii
			}
		}
		
		if (!isInt(str) || !isWithinRange(num, min, max) || str.empty())
		{
			std::cout << "Please input a number between " << min
				<< " and " << max << ".\n";
		}
	}

	return num;
}

bool isInt(std::string str)
{
	for (unsigned i = 0; i < str.length(); i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return false;
	}
	return true;
}

bool isWithinRange(int num, int min, int max)
{
	if (num < min || num > max)
		return false;
	return true;
}

std::string noSpace(std::string str)
{
	std::string newStr;

	for (unsigned i = 0; i < str.length(); i++)
	{
		if (str[i] != '\t' && str[i] != ' ')
		{
			newStr += str[i];
		}
		else
		    return newStr;
	}
	return newStr;
}

std::string splitString(std::string str)
{
	std::string newStr = "";

	for (unsigned i = 0; i < str.length(); i++)
	{
		if (str[i] != '|')
			newStr += str[i];

		else
			newStr += " ";
	}
	return newStr;
}
