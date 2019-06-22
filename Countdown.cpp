/**********************************************************************************
 * Class to represent the countdown objects created by the user
 *
 * Will get the creation time when it is created and determine the target time
 * based on current date and user input date
 **********************************************************************************/

#include "Countdown.hpp"

using std::ios;

/**********************************************************************************
 * Constructor for initial creation of a countdown object
 *
 * Takes the name as a string and the target time as a time struct pointer
 * and uses them to initialize the member variables
 **********************************************************************************/
Countdown::Countdown(std::string eventName, struct tm* targetTime) {
    this->eventName = eventName;
    this->targetTime = targetTime;

    time_t now = time(NULL); //get current time and store in temp
    creationTime = localtime_r(&now, &temp[0]); //convert time to a tm* and store in creation time
}

/**********************************************************************************
 * Constructor for recreating a countdown object from the data file
 *
 * Takes the name as a string, the target time as a long and the creation time
 * as a long and uses them to initialize the member variables
 **********************************************************************************/
Countdown::Countdown(std::string eventName, long targetTime, long creationTime) {
    this->eventName = eventName;
    this->creationTime = localtime_r(&creationTime, &temp[0]);
    this->targetTime = localtime_r(&targetTime, &temp[1]);
}

/**********************************************************************************
 * Function to save the data stored in the countdown object to a target save file
 **********************************************************************************/
void Countdown::saveData(){

    std::ofstream outFile;
    outFile.open("data.txt", ios::app); //open file in append mod

    //add data for the countdown to the end of the data file
    outFile << mktime(creationTime) << "|" << eventName << "|" << mktime(targetTime) << std::endl;
    outFile.close();
    //TODO(set the save code to reinitialize save file before saving all the countdowns or
    //     to save the data only if the data does not already exist)
}

void Countdown::timeCopier(struct tm &destination, time_t source) {

}


//accessors below this comment
struct tm* Countdown::getTargetTime(){
    return targetTime;
}

struct tm* Countdown::getCreationTime(){
    return creationTime;
}

std::string Countdown::getName(){
    return eventName;
}