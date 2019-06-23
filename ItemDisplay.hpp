/**********************************************************************************
 * Class to format and interpret the data of a countdown into a useful display
 **********************************************************************************/

#ifndef BEAVERHACKSSUMMER19_ITEMDISPLAY_HPP
#define BEAVERHACKSSUMMER19_ITEMDISPLAY_HPP

#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <thread>
#include "Countdown.hpp"
#include "Messages.hpp"



class ItemDisplay {
private:
    struct tm tempNow;
    struct tm now;
    Countdown* itemCountdown;
    std::string eventName;
    int seconds, minutes, hours, days, years;
    Messages countdownMessage;
    void countdownLoop(ItemDisplay watchItem);
    void getCurrentTime();
    void calcRemainingTime(int *highVal, int *lowVal);
public:
    ItemDisplay(std::string eventName, struct tm targetTime, eventType eType);
    ItemDisplay(std::string eventName, long targetTime, long creationTime, eventType eType);
    ItemDisplay();
    void displayCountdown();//function to create a list view display of remaining time
    void displayCountdown(ItemDisplay countdownItem);//test version comment out or delete
    void watchCountdown(ItemDisplay watchItem); //function that uses clearing the screen to create dynamic countdown
    void saveData();
    int minutesToMidnight();
    double calcPercentElapsed();
    std::string getEventName();
};


#endif //BEAVERHACKSSUMMER19_ITEMDISPLAY_HPP
