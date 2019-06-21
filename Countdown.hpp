/**********************************************************************************
 * Class to represent the countdown objects created by the user
 *
 * Will get the creation time when it is created and determine the target time
 * based on current date and user input date
 **********************************************************************************/

#ifndef BEAVERHACKSSUMMER19_COUNTDOWN_HPP
#define BEAVERHACKSSUMMER19_COUNTDOWN_HPP

#include <string>
#include <ctime>
#include <fstream>
#include <time.h>


class Countdown {
private:
    struct tm* creationTime;
    struct tm* targetTime;
    struct tm temp[2];
    std::string eventName;
public:
    Countdown(std::string eventName, struct tm* targetTime);
    Countdown(std::string eventName, long targetTime, long creationTime);
    Countdown(Countdown &aCountdown);
    Countdown();
    void saveData();
    struct tm* getTargetTime();
    struct tm* getCreationTime();
    std::string getName();
};


#endif //BEAVERHACKSSUMMER19_COUNTDOWN_HPP
