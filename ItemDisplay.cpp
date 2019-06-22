/**********************************************************************************
 * Class to format and interpret the data of a countdown into a useful display
 **********************************************************************************/

#include "ItemDisplay.hpp"

bool watch = true;
const int TWENTY_EIGHT_DAYS = 2419200;

ItemDisplay::ItemDisplay(Countdown thisCountdown) {
    itemCountdown = Countdown(thisCountdown);
}

void ItemDisplay::displayCountdown(ItemDisplay countdownItem) {
    time_t now = time(NULL);
    struct tm* tempTime = localtime(&now);
    struct tm* countdownTarget = countdownItem.itemCountdown.getTargetTime();
    int time[2][6] = {{countdownTarget->tm_sec, countdownTarget->tm_min, countdownTarget->tm_hour,
                     countdownTarget->tm_mday, countdownTarget->tm_mon, countdownTarget->tm_year},
                    {tempTime->tm_sec, tempTime->tm_min, tempTime->tm_hour,
                     tempTime->tm_mday, tempTime->tm_mon, tempTime->tm_year}};

    std::string outString = "";
    int diff = mktime(countdownTarget)-mktime(tempTime);


    if(diff < TWENTY_EIGHT_DAYS){
        time[0][0] = diff%60;
        diff/=60;
        time[0][1] = diff%60;
        diff/=60;
        time[0][2] = diff%24;
        diff/=24;
        time[0][3] = diff;
        time[0][4] = time[0][5] = 0;
    } else if(diff >= 0) {
        calcRemainingTime(time[0], time[1]);
    } else {
        calcRemainingTime(time[1], time[0]);
        for (int i = 0; i < 6; ++i) {
            time[0][i] = time[1][i];
        }
    }

    bool firstData = true;
    for (int j = 5; j >= 0; --j) {

        if(time[0][j] != 0 || (firstData && j == 0)){
            if(firstData){
                firstData = false;
            } else {
                std::cout<<" : ";
            }
            std::cout<<time[0][j]<<" ";
            switch (j){
                case 0: std::cout<<"seconds.";
                    break;
                case 1: std::cout<<"minutes";
                    break;
                case 2: std::cout<<"hours";
                    break;
                case 3: std::cout<<"days";
                    break;
                case 4: std::cout<<"months";
                    break;
                case 5: std::cout<<"years";
                    break;

            }
        }
    }
    std::cout<<std::endl;
}

void ItemDisplay::calcRemainingTime(int *highVal, int *lowVal) {
    bool leapYear = ((lowVal[5]%4) == 0 &&
                     ((lowVal[5]%100 != 0) ||
                      lowVal[5]%400 == 0)); //determine if year is leap year

    if (highVal[0] >= lowVal[0]) {//calculate difference of seconds
        highVal[0] -= (lowVal[0]);
    } else {
        highVal[1] -= 1;
        highVal[0] += 60;
        highVal[0] -= (lowVal[0]);
    }
    if (highVal[1] >= lowVal[1]) {//calculate difference of seconds
        highVal[1] -= (lowVal[1]);
    } else {
        highVal[2] -= 1;
        highVal[1] += 60;
        highVal[1] -= (lowVal[1]);
    }

    if (highVal[2] >= lowVal[2]) {//calculate difference of hours
        highVal[2] -= (lowVal[2]);
    } else {
        highVal[3] -= 1;
        highVal[2] += 24;
        highVal[2] -= (lowVal[2]);
    }

    if (highVal[3] >= lowVal[3]) {//calculate difference of days
        highVal[3] -= (lowVal[3]);
    } else {
        highVal[4] -= 1;

        switch(lowVal[4]){
            case 3:
            case 5:
            case 8:
            case 10: highVal[3] += 30;
                break;
            case 1: (leapYear)? highVal[3] += 29 :highVal[3] += 28;
                break;
            case 12: std::cout<<"Something's wrong with the code";
                break;
            default: highVal[3] += 31;
        }

        highVal[3] -= (lowVal[3]);

    }

    if (highVal[4] >= lowVal[4]) {//calculate difference of months
        highVal[4] -= (lowVal[4]);
    } else {
        highVal[5] -= 1;
        highVal[4] += 12;
        highVal[4] -= (lowVal[4]);
    }

    highVal[5] -= (lowVal[5]); //calculate difference of years
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
    getCurrentTime(); //get current time and store in now

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