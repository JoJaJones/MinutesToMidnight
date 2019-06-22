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

int getInt(std::string stringToProcess) //added this to process strings from the data file
{
	int num = -1;
	std::string str = "";
	while (!isInt(str) || !isWithinRange(num, min, max) || str.empty())
	{
		str = "";
		num = 0;
	    	
		str = stringToProcess;
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

std::string[] splitString(std::string str) //hey Jason updated this because I'm not sure how you'd process subsequent data points as it was written
{
	std::string newStr[4] = {"","","",""};
	
	int delimCount = 0;
	int count = 0
	while(delimCount < 3)
	{
		if (str[count] != '|') 
		{
			newStr[delimCount] += str[count];
		}
		else
		{
			delimCount++;
		}
		count++;
	}
	
	newStr[delimCount] = str[str.length-1]; //store enum val

	return newStr;
}

/**********************************************************************************
 * Function that takes a string from the data file and processes it into a
 * Countdown object, which it then returns to the calling function
 **********************************************************************************/
Countdown processDataString(std::string dataSet) {
    std::string dataArray[4] = splitString(dataSet);
    time_t creationTime, targetTime;
    eventType eType;
    std::string eventName;

    creationTime = getInt(dataArray[0]);
    eventName = dataArray[1];
    targetTime = getInt(dataArray[2]);
    eType = getInt(dataArray[3]);

    return Countdown(eventName, targetTime, creationTime, eType);
}
