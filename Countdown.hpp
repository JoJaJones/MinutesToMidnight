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

enum eventType {GOOD, BAD, NEUTRAL};

class Countdown {
private:
    struct tm creationTime;
    struct tm targetTime;
    struct tm temp[2];
    std::string eventName;
    eventType thisEvent;
public:
    Countdown(std::string eventName, struct tm targetTime, eventType eType);
    Countdown(std::string eventName, long targetTime, long creationTime, eventType eType);
    void saveData();
    struct tm* getTargetTime();
    struct tm* getCreationTime();
    std::string getName();
    void timeCopier(struct tm &destination, time_t source);
};


#endif //BEAVERHACKSSUMMER19_COUNTDOWN_HPP
