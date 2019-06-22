/***************************************************************************
 ** Name:  Patricia Booth, Josh Jones, Lindsey Olmstead, Jason Rash
 ** Date:  6-22-2019
 ** Description:  Message Class to display the status of an event depending
 **               on the eventType.
 ***************************************************************************/

#ifndef BEAVERHACKSSUMMER19_MESSAGES_HPP
#define BEAVERHACKSSUMMER19_MESSAGES_HPP

#include "Countdown.hpp"
#include "ItemDisplay.hpp"

class Messages
{
private:
    eventType type;
    double percentComplete;    // Update as needed once ItemDisplay is complete.
public:
    Messages();
    Messages(eventType, double);
    eventType getEventType();
    void displayMessage();
};
#endif
