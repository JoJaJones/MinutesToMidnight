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



class ItemDisplay {
private:
    struct tm tempNow;
    struct tm* now;
    Countdown itemCountdown;
    std::string eventName;
    int seconds, minutes, hours, days, years;
    void countdownLoop(ItemDisplay watchItem);
    void getCurrentTime();
    void calcRemainingTime(int *highVal, int *lowVal);
public:
    ItemDisplay(Countdown thisCountdown);
    void displayCountdown(ItemDisplay countdownItem); //function to create a list view display of remaining time
    void watchCountdown(ItemDisplay watchItem); //function that uses clearing the screen to create dynamic countdown
    void saveData();
    int minutesToMidnight();
    double calcPercentElapsed();
};


#endif //BEAVERHACKSSUMMER19_ITEMDISPLAY_HPP
