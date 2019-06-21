/**********************************************************************************
 * Class to format and interpret the data of a countdown into a useful display
 **********************************************************************************/

#include "ItemDisplay.hpp"
ItemDisplay::ItemDisplay(Countdown thisCountdown) {
    itemCountdown = Countdown(thisCountdown);
}

void ItemDisplay::displayCountdown() {

}

void ItemDisplay::getCurrentTime(){
    time_t temp = time(NULL);
    now = localtime_r(&temp, &tempNow);
}

double ItemDisplay::calcPercentElapsed() {
    getCurrentTime(); //get current time and stor in now

    double target = static_cast<double>(mktime(itemCountdown.getTargetTime())); //convert target time to seconds in double
    double creation = static_cast<double>(mktime(itemCountdown.getCreationTime())); //convert creationTime to seconds in double
    double current = static_cast<double>(mktime(now)); // convert now to seconds in double

    current-=creation; //adjust by creation seconds
    target-=creation; // adjust by creation seconds

    return ((current/target)*100); //return percentage of countdown that has elapsed
}

ItemDisplay::~ItemDisplay() { //TODO(Weird bug where data is saved to file in reverse order of creation)
    itemCountdown.saveData();
}