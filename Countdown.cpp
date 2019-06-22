/**********************************************************************************
 * Class to represent the countdown objects created by the user
 *
 * Will get the creation time when it is created and determine the target time
 * based on current date and user input date
 **********************************************************************************/

#include "Countdown.hpp"

/**********************************************************************************
 * Constructor for initial creation of a countdown object
 *
 * Takes the name as a string and the target time as a time struct pointer
 * and uses them to initialize the member variables
 **********************************************************************************/
Countdown::Countdown(std::string eventName, struct tm targetTime, eventType eType) {
    this->eventName = eventName;
    timeCopier(this->targetTime,mktime(&targetTime));
    thisEvent = eType;

    time_t now = time(NULL); //get current time and store in temp
    timeCopier(creationTime, now); //convert time to a tm* and store in creation time
}

/**********************************************************************************
 * Constructor for recreating a countdown object from the data file
 *
 * Takes the name as a string, the target time as a long and the creation time
 * as a long and uses them to initialize the member variables
 **********************************************************************************/
Countdown::Countdown(std::string eventName, long targetTime, long creationTime, eventType eType) {
    this->eventName = eventName;
    timeCopier(this->targetTime, targetTime);
    timeCopier(this->creationTime, creationTime);
    thisEvent = eType;
}

Countdown::Countdown(Countdown &aCountdown) {
    this->eventName = aCountdown.eventName;
    this->targetTime = aCountdown.targetTime;
    this->creationTime = aCountdown.creationTime;
}

Countdown::Countdown() {}

/**********************************************************************************
 * Copy constructor for recreating a countdown object from the data file
 *
 * Takes the name as a string, the target time as a long and the creation time
 * as a long and uses them to initialize the member variables
 **********************************************************************************/
Countdown::Countdown(const Countdown &newCountdown) {
    this->creationTime = newCountdown.creationTime;
    this->targetTime = newCountdown.targetTime;
    this->eventName = newCountdown.eventName;
    this->thisEvent = newCountdown.thisEvent;
}

/**********************************************************************************
 * Default constructor to allow access to timeCopier functionality if needed
 **********************************************************************************/
Countdown::Countdown() {}

/**********************************************************************************
 * Function to save the data stored in the countdown object to a target save file
 **********************************************************************************/
void Countdown::saveData(){

    std::ofstream outFile;
    outFile.open("data.txt", std::ios::app); //open file in append mod

    //add data for the countdown to the end of the data file
    outFile << mktime(&creationTime) << "|" << eventName << "|" << mktime(&targetTime)
            << "|" << thisEvent << std::endl;
    outFile.close();
    //TODO(set the save code to reinitialize save file before saving all the countdowns or
    //     to save the data only if the data does not already exist)
}

/**********************************************************************************
 * Function to convert time_t to struct tm due to thread safety issues
 * inherent in the ctime function localtime
 *
 * Takes a target struct tm variable and a time_t time as parameters and uses the
 * info of the time_t time to fill the struct tm variable
 **********************************************************************************/
void Countdown::timeCopier(struct tm &destination, time_t source) {
    struct tm* temp = localtime(&source);
    destination.tm_year = temp->tm_year;
    destination.tm_sec = temp->tm_sec;
    destination.tm_min = temp->tm_min;
    destination.tm_hour = temp->tm_hour;
    destination.tm_mday = temp->tm_mday;
    destination.tm_mon = temp->tm_mon;
    destination.tm_gmtoff = temp->tm_gmtoff;
    destination.tm_isdst = temp->tm_isdst;
    destination.tm_wday = temp->tm_wday;
    destination.tm_yday = temp->tm_yday;
    destination.tm_zone = temp->tm_zone;
}


//accessors below this comment
struct tm* Countdown::getTargetTime(){
    return &targetTime;
}

struct tm* Countdown::getCreationTime(){
    return &creationTime;
}

std::string Countdown::getName(){
    return eventName;
}