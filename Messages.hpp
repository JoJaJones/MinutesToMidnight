/***************************************************************************
 ** Name:  Patricia Booth, Josh Jones, Lindsey Olmstead, Jason Rash
 ** Date:  6-22-2019
 ** Description:  Message Class to display the status of an event depending
 **               on the eventType.
 ***************************************************************************/

#ifndef BEAVERHACKSSUMMER19_MESSAGES_HPP
#define BEAVERHACKSSUMMER19_MESSAGES_HPP

#include "Countdown.hpp"

class Messages
{
private:
    double percentComplete;
    eventType type;
public:
    Messages();
    Messages(eventType, double);
    void setPercentComplete(double);
    void setType(eventType);
    void displayMessage();
};
#endif
