/******************************************************************************
 * Name: Patricia Booth, Josh Jones, Lindsey Olmstead, Jason Rash
 * Date: 6-21-19
 * Description: Validation of user input header file.
******************************************************************************/

#include "Validation.hpp"


// NOTE: If input from user is " 1" or "	1" (\t then a number) it doesn't consider it an Integer.
/******************************************************************************
 * Description: getInt(int, int) Takes in min and max range as parameters.
                The user inputs a string and the function checks if the string
				contains only numbers before the first white space.  It also
				checks if the integer is within the specified range and that
				the string is not empty.
******************************************************************************/

int getInt(int min, int max, std::string message)
{
	int num = -1;
	std::string str = "";
	while (!isInt(str) || !isWithinRange(num, min, max) || str.empty())
	{
		str = "";
		num = 0;
		std::cout<<message<<std::endl;
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
            std::cout<<"\033[2J\033[0;0H";
		    std::cout << "Please input a number between " << min
				<< " and " << max << ".\n";
		}
	}

	return num;
}

/******************************************************************************
 * Description: getInt(std::string) process a string from the data file to an
                integer.
 ******************************************************************************/
long long getInt(std::string stringToProcess) //added this to process strings from the data file
{
	std::string str = stringToProcess;
	long long num = 0;
	    	
	for (unsigned i = 0; i < str.length(); i++)
	{
		num = num * 10 + (str[i] - 48);    // 0 = 48 in ascii
	}

	return num;
}

/******************************************************************************
 * Description: isInt(std::string) check that the string contains only numbers
 ******************************************************************************/
bool isInt(std::string str)
{
	for (unsigned i = 0; i < str.length(); i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return false;
	}
	return true;
}

/******************************************************************************
 * Description: isWithinRange(int, int, int) takes in three arguments the number
                that was converted for user input in the getInt(int, int)
				function, the minimum number that is valid input, and the
				maximum number that is valid input.  Returns true if number is
				within range and false if is not.
 ******************************************************************************/

bool isWithinRange(int num, int min, int max)
{
	if (num < min || num > max)
		return false;
	return true;
}

/******************************************************************************
 * Description: noSpace(std::string) takes a string and returns a new string
                that returns only the characters before the first white space.
 ******************************************************************************/
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

/******************************************************************************
 * Description: splitString(std::string) takes in a string from a text file.
                The data is delimited with the '|' symbol.  The program takes
				data between the '|' symbols and puts it into an array of
				strings.  The function returns a pointer to the array.
 ******************************************************************************/
StringCarrier splitString(std::string str)
{
	std::string newStr[4] = {"","","",""};
	StringCarrier newCarrier;

	int delimCount = 0;
	int count = 0;
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
	
	newStr[delimCount] = str[str.length() - 1]; //store enum val
    newCarrier.creationString = newStr[0];
    newCarrier.nameString = newStr[1];
    newCarrier.targetString = newStr[2];
    newCarrier.enumString = newStr[3];

	return newCarrier;
}

/**********************************************************************************
 * Function that takes a string from the data file and processes it into a
 * Countdown object, which it then returns to the calling function
 **********************************************************************************/
//Countdown processDataString(std::string dataSet) {
//    std::string *dataArray = splitString(dataSet);
//    time_t creationTime, targetTime;
//    eventType eType;
//    std::string eventName;
//
//    creationTime = getInt(dataArray[0]);
//    eventName = dataArray[1];
//    targetTime = getInt(dataArray[2]);
//    eType = static_cast<eventType>(getInt(dataArray[3]));
//    Countdown temp = Countdown(eventName, targetTime, creationTime, eType);
//    return temp;
//}


std::string sanitizeString(std::string message){
    std::string stringToSanizize = "";

    while(stringToSanizize.empty()){
        std::cout<<message<<std::endl;
        getline(std::cin, stringToSanizize);
        if(stringToSanizize.empty()){
            std::cout<<"Invalid entry."<<std::endl;
        }
    }

    int indexAdjust = 0;
    for (int i = 0; i < stringToSanizize.length()+indexAdjust; ++i) {
        if(stringToSanizize[i+indexAdjust] == '|'){
            indexAdjust++;
        }

        if(indexAdjust > 0){
            stringToSanizize[i] = stringToSanizize[i+indexAdjust];
        }

    }

    if(indexAdjust>0){
        stringToSanizize = stringToSanizize.substr(0, stringToSanizize.length()-indexAdjust);
    }

    if(stringToSanizize.empty() || stringToSanizize[0] == '|'){
        stringToSanizize = " ";
    }

    return stringToSanizize;
}