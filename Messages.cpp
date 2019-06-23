/***************************************************************************
 ** Name:  Patricia Booth, Josh Jones, Lindsey Olmstead, Jason Rash
 ** Date:  6-22-2019
 ** Description:  Message Class to display the status of an event depending
 **               on the eventType.
 ***************************************************************************/

#include <iostream>
#include "Messages.hpp"
using std::cout;
using std::endl;

/***************************************************************************
 Description:  Default Constructor for Message Class.
 ***************************************************************************/

Messages::Messages()
{
    type = NEUTRAL;
    percentComplete = 0.0;
}


/***************************************************************************
 Description:  Constructor for Message Class.
 ***************************************************************************/

Messages::Messages(eventType t, double c)
{
    type = t;
    percentComplete = c;
}


/***************************************************************************
 Description:  Setter function for the percentComplete member variable.
 ***************************************************************************/

void Messages::setPercentComplete(double p)
{
    percentComplete = p;
}


/***************************************************************************
 Description:  Setter function for the type member variable.
 ***************************************************************************/

void Messages::setType(eventType t)
{
    type = t;
}


/***************************************************************************
 Description:  Void function that returns a message displaying the percent
 **            complete based on whether the eventType is GOOD, NEUTRAL, or
 **            BAD.
 ***************************************************************************/

void Messages::displayMessage()
{
    if (type == GOOD)
    {
        cout << "Only " << percentComplete << " time remaining until event!" << endl;
    }
    else if (type == BAD)
    {
        cout << "Your event is " << 1 - percentComplete << " complete!" << endl;
    }
    else
    {
        cout << "Countdown " << percentComplete << " complete!" << endl;
    }
}
