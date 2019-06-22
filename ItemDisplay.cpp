/**********************************************************************************
 * Class to format and interpret the data of a countdown into a useful display
 **********************************************************************************/

#include "ItemDisplay.hpp"

bool watch = true;
const int TWENTY_EIGHT_DAYS = 2419200;

ItemDisplay::ItemDisplay(Countdown thisCountdown) {
    itemCountdown = Countdown(thisCountdown);
}

void ItemDisplay::displayCountdown(ItemDisplay countdownItem) { //TODO(account for past
    time_t now = time(NULL);
    struct tm* tempTime = localtime(&now);
    struct tm* countdownTarget = countdownItem.itemCountdown.getTargetTime();
    int time[] = {countdownTarget->tm_sec, countdownTarget->tm_min, countdownTarget->tm_hour,
                  countdownTarget->tm_mday, countdownTarget->tm_mon, countdownTarget->tm_year};

    std::string outString = "";
    int diff = mktime(countdownTarget)-mktime(tempTime);
    if(diff < TWENTY_EIGHT_DAYS){
        time[0] = diff%60;
        diff/=60;
        time[1] = diff%60;
        diff/=60;
        time[2] = diff%24;
        diff/=24;
        time[3] = diff;
        time[4] = time[5] = 0;
    } else {
        if (time[0] >= tempTime->tm_sec) {
            time[0] -= (tempTime->tm_sec);
        } else {
            time[1] -= 1;
            time[0] += 60;
            time[0] -= (tempTime->tm_sec);
        }
        if (time[1] >= tempTime->tm_min) {
            time[1] -= (tempTime->tm_min);
        } else {

        }

        if (time[2] >= tempTime->tm_hour) {
            time[2] -= (tempTime->tm_hour);
        }

        if (time[3] >= tempTime->tm_mday) {
            time[3] -= (tempTime->tm_mday);
        }

        if (time[4] >= tempTime->tm_mon) {
            time[4] -= (tempTime->tm_mon);
        }

        if (time[5] >= tempTime->tm_year) {
            time[5] -= (tempTime->tm_year);
        }
    }
}

void ItemDisplay::watchCountdown(ItemDisplay watchItem) {
    std::thread t([](ItemDisplay watchItem) {

        while(watch){
            std::cout<<"\033[2J";
            watchItem.displayCountdown(watchItem);
            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
        }
    }, watchItem);
    t.detach();

    std::cin.get();
    watch = false;
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(2));
    watch = true;
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

int ItemDisplay::minutesToMidnight() {
    time_t now, midnight;
    time(&now);

    struct tm* temp = localtime(&now);
    temp->tm_hour = 23;
    temp->tm_min = 59;
    midnight = mktime(temp);
    if(temp->tm_sec < 30){
        midnight+=60;
    }
    return (midnight-now)/60;
}

void ItemDisplay::saveData() {
    itemCountdown.saveData();
}