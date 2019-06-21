/**********************************************************************************
 * Class to format and interpret the data of a countdown into a useful display
 **********************************************************************************/

#ifndef BEAVERHACKSSUMMER19_ITEMDISPLAY_HPP
#define BEAVERHACKSSUMMER19_ITEMDISPLAY_HPP

#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include "Countdown.hpp"

class ItemDisplay {
private:
    struct tm tempNow;
    struct tm* now;
    Countdown itemCountdown;
    std::string eventName;
    int seconds, minutes, hours, days, years;
    double calcPercentElapsed();
    void getCurrentTime();
public:
    ItemDisplay(Countdown thisCountdown);
    void displayCountdown(); //function to create a list view display of remaining time
    void watchCountdown(); //function that uses clearing the screen to create dynamic countdown
    ~ItemDisplay();
};


#endif //BEAVERHACKSSUMMER19_ITEMDISPLAY_HPP
