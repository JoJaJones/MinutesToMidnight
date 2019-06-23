/**********************************************************************************
 * Class to format and interpret the data of a countdown into a useful display
 **********************************************************************************/

#include "ItemDisplay.hpp"

bool watch = true; //bool value for dynamic countdown
const int TWENTY_EIGHT_DAYS = 2419200; //amount of seconds in 28 days used to streamline remaining time calculations

/**********************************************************************************
 * Constructor for the ItemDisplay class
 *
 * Constructs ItemDisplay from the information in the save file
 **********************************************************************************/
ItemDisplay::ItemDisplay(std::string eventName, long targetTime, long creationTime, eventType eType) {
    itemCountdown = new Countdown(eventName, targetTime, creationTime, eType); //TODO(Deallocate)
    countdownMessage = Messages(itemCountdown->getEventType(), 0);
}

/**********************************************************************************
 * Constructor for the ItemDisplay class
 *
 * Constructs ItemDisplay from the user inputs
 **********************************************************************************/
ItemDisplay::ItemDisplay(std::string eventName, struct tm targetTime, eventType eType) {
    itemCountdown = new Countdown(eventName, targetTime, eType); //TODO(Deallocate)
    countdownMessage = Messages(itemCountdown->getEventType(), 0);
}

/**********************************************************************************
 * Default constructor to allow access to minutesToMidnight functionality
 **********************************************************************************/
ItemDisplay::ItemDisplay() {}

/**********************************************************************************
 * Function to format and display the time remaining in the countdown until the
 * target time
 **********************************************************************************/
void ItemDisplay::displayCountdown(CountdownString &countdownStr) {

    getCurrentTime();
    struct tm* countdownTarget = itemCountdown->getTargetTime();
    int time[2][6] = {{countdownTarget->tm_sec, countdownTarget->tm_min, countdownTarget->tm_hour,
                              countdownTarget->tm_mday, countdownTarget->tm_mon, countdownTarget->tm_year},
                      {now.tm_sec, now.tm_min, now.tm_hour,
                              now.tm_mday, now.tm_mon, now.tm_year}};

    std::string outString = "";
    int diff = mktime(countdownTarget)-mktime(&now);


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


    std::string* strPtr[2] = {&countdownStr.firstPart, &countdownStr.secondPart};
    int count = 0, index = 0;
    *strPtr[0] = *strPtr[1] = "";
    for (int j = 5; j >= 0; --j) {

        if(time[0][j] != 0 || (count == 0 && j == 0)){
            if(count!=0) {
                *strPtr[index]+=" : ";
            }

            if(count==3){
                index=1;
            }
            *strPtr[index]+= std::to_string(time[0][j])+" ";
            switch (j){
                case 0: *strPtr[index]+="seconds.";
                    break;
                case 1: *strPtr[index]+="minutes";
                    break;
                case 2: *strPtr[index]+="hours";
                    break;
                case 3: *strPtr[index]+="days";
                    break;
                case 4: *strPtr[index]+="months";
                    break;
                case 5: *strPtr[index]+="years";
                    break;

            }
            count++;
        }
    }
}

/**********************************************************************************
 * Function to format and display the time remaining in the countdown until the
 * target time [Test version]
 **********************************************************************************/
void ItemDisplay::displayCountdown(ItemDisplay countdownItem, CountdownString &countdownStr) {
    getCurrentTime();
    struct tm* countdownTarget = countdownItem.itemCountdown->getTargetTime();
    int time[2][6] = {{countdownTarget->tm_sec, countdownTarget->tm_min, countdownTarget->tm_hour,
                              countdownTarget->tm_mday, countdownTarget->tm_mon, countdownTarget->tm_year},
                      {now.tm_sec, now.tm_min, now.tm_hour,
                              now.tm_mday, now.tm_mon, now.tm_year}};

    std::string outString = "";
    int diff = mktime(countdownTarget)-mktime(&now);


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

    std::string* strPtr[2] = {&countdownStr.firstPart, &countdownStr.secondPart};
    int count = 0, index = 0;
    *strPtr[0] = *strPtr[1] = "";
    for (int j = 5; j >= 0; --j) {

        if(time[0][j] != 0 || (count == 0 && j == 0)){
            if(count!=0) {
                *strPtr[index]+=" : ";
            }

            if(count==3){
                index=1;
            }
            *strPtr[index]+= std::to_string(time[0][j])+" ";
            switch (j){
                case 0: *strPtr[index]+="seconds.";
                    break;
                case 1: *strPtr[index]+="minutes";
                    break;
                case 2: *strPtr[index]+="hours";
                    break;
                case 3: *strPtr[index]+="days";
                    break;
                case 4: *strPtr[index]+="months";
                    break;
                case 5: *strPtr[index]+="years";
                    break;

            }
            count++;
        }
    }
}

/**********************************************************************************
 * Function to calculate the remaining time in terms of years, months, days,
 * hours, minutes, and seconds for countdowns with 28 days or more remaining
 * until the target time
 **********************************************************************************/
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

/**********************************************************************************
 * Function to creat a dynamic countdown for a specified countdown
 **********************************************************************************/
void ItemDisplay::watchCountdown(ItemDisplay watchItem) {

    std::thread t([](ItemDisplay watchItem) {
        CountdownString countdownStr;
        std::string topBotStr = "################################################################################\n";
        std::string spacer =    "#                                                                              #\n";
        while(watch){
            std::cout<<"\033[2J\033[0;0H";

            std::string temp = "";
            int tempInt = watchItem.minutesToMidnight();
            temp = "Minutes to Midnight ("+std::to_string(tempInt)+")";
            if(tempInt < 1000 && tempInt > 99) {
                temp+=" ";
            } else if( tempInt < 100 && tempInt > 9) {
                temp+="  ";
            } else if(tempInt < 10) {
                temp+="   ";
            }
            std::string* cdPtr[] = {&countdownStr.firstPart, &countdownStr.secondPart};
            std::cout<<topBotStr<<spacer<<"#                    "<<temp<<"                                #\n"<<spacer;
            watchItem.displayCountdown(watchItem, countdownStr);

            countdownStr.firstPart ="\""+watchItem.getEventName()+"\":: " + countdownStr.firstPart;

            if (!countdownStr.secondPart.empty()) {
                countdownStr.secondPart = "     "+countdownStr.secondPart;
            }

            for (int i = 0; i < 5; ++i) {
                std::cout<<spacer;
            }
            for (int j = 0; j < 2; ++j) {

                for (int k = 0; k < 81; ++k) {
                    if(!cdPtr[j]->empty()){
                        if(k<5 || (k >= (cdPtr[j]->length()+5))){
                            std::cout<<spacer[k];
                        } else {
                            std::cout<<(*cdPtr[j])[k-5];
                        }
                    }
                }
            }
            if(cdPtr[1]->empty()){
                std::cout<<spacer;
            }
            for (int l = 0; l < 10; ++l) {
                std::cout<<spacer;
            }
//                     "#                                                                              #\n";
            std::cout<<spacer<<"#                       Press enter to return to menu.                         #\n"
                     <<spacer<<topBotStr;
            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
        }
    }, watchItem);
    t.detach();

    std::cin.clear();
    std::cin.get();
    watch = false;
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(1357));
    std::cout<<"\033[2J\033[0;0H";
    watch = true;
}

/**********************************************************************************
 * Function to get the current time and store it in the member variable now
 **********************************************************************************/
void ItemDisplay::getCurrentTime(){
    time_t temp = time(NULL);
    itemCountdown->timeCopier(now, temp);
}

/**********************************************************************************
 * Function to calculate the percentage of the countdown that has elapsed based on
 * it's creation time and target time
 **********************************************************************************/
double ItemDisplay::calcPercentElapsed() {
    getCurrentTime(); //get current time and store in now

    double target = static_cast<double>(mktime(itemCountdown->getTargetTime())); //convert target time to seconds in double
    double creation = static_cast<double>(mktime(itemCountdown->getCreationTime())); //convert creationTime to seconds in double
    double current = static_cast<double>(mktime(&now)); // convert now to seconds in double

    current-=creation; //adjust by creation seconds
    target-=creation; // adjust by creation seconds

    return ((current/target)*100); //return percentage of countdown that has elapsed
}

/**********************************************************************************
 * Function that calculates the number of minutes until the next midnight
 **********************************************************************************/
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

/**********************************************************************************
 * Function to write data contained in the Countdown object to the data file
 **********************************************************************************/
void ItemDisplay::saveData() {
    itemCountdown->saveData();
}

//accessors below this comment
std::string ItemDisplay::getEventName() {
    return this->itemCountdown->getName();
}