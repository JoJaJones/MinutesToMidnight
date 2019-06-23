/******************************************************************************
 * Name: Patricia Booth, Josh Jones, Lindsey Olmstead, Jason Rash
 * Date: 6-21-19
 * Description: Menu class to display User Interface
******************************************************************************/

#include "Menu.hpp"

using std::cout;
using std::cin;
using std::getline; // user input
using std::stoi; // string to integer

/*******************************
** Text for Menus
*******************************/

//void Menu::startMenu() // Menu ID: 1
//{
//
//    "1. Create New Countdown\n"
//    "2. List Current Countdowns\n"
//    "3. Remove Countdown\n"
//    "4. Exit\n";
//}

//void Menu::getMenuChoice()
//{
//	getline(cin, strMenuChoice);
//	/* Convert string to integer
//	** This is just a placeholder until integrated
//	** with input validation
//	*/
//	intMenuChoice = stoi(strMenuChoice);
//}

/*******************************
** Menu Movement
*******************************/

void Menu::viewMenu(int userNumID)
{
    switch (userNumID)
    {
        case 1: // Main Menu
            std::cout<<"\033[2J\033[0;0H";
            strMenuChoices = "################################################################################\n"
                             "#                                                                              #\n"
                             "#                                                                              #\n"
                             "#                                                                              #\n"
                             "#                                                                              #\n"
                             "#                                                                              #\n"
                             "#                                                                              #\n"
                             "#                    "+getLogo()+             "                                #\n"
                                                                            "#                                                                              #\n"
                                                                            "#            Please make a selection from the following options:               #\n"
                                                                            "#            1. Create New Countdown                                           #\n"
                                                                            "#            2. List Current Countdowns                                        #\n"
                                                                            "#            3. Exit                                                           #\n"
                                                                            "#                                                                              #\n"
                                                                            "#                                                                              #\n"
                                                                            "#                                                                              #\n"
                                                                            "#                                                                              #\n"
                                                                            "#                                                                              #\n"
                                                                            "#                                                                              #\n"
                                                                            "#                                                                              #\n"
                                                                            "#                                                                              #\n"
                                                                            "#                                                                              #\n"
                                                                            "#                                                                              #\n"
                                                                            "#                                                                              #\n"
                                                                            "#                                                                              #\n"
                                                                            "################################################################################\n";



            intMenuChoice = getInt(lowerMenuLimit, upperMenuLimit, strMenuChoices);
            menuSelect(userNumID, intMenuChoice);
    }
}

void Menu::displayLogo() {
    cout<<"Minutes to Midnight ("<<utilItemDisplay.minutesToMidnight()<<")";
}

std::string Menu::getLogo(){
    std::string temp = "";
    int tempInt = utilItemDisplay.minutesToMidnight();
    temp = "Minutes to Midnight ("+std::to_string(tempInt)+")";
    if(tempInt < 1000 && tempInt > 99) {
        temp+=" ";
    } else if( tempInt < 100 && tempInt > 9) {
        temp+="  ";
    } else if(tempInt < 10) {
        temp+="   ";
    }

    return temp;
}
//working

void Menu::menuSelect(int userNumID, int intMenuChoice)
{
    switch (userNumID)
    {
        case 1: // Main Menu
            switch (intMenuChoice)
            {
                case 1:
                    createCountdown();
                    break;
                case 2:
                    countdownsMenu();
                    break;
                case 3:
                    menuExit();
            }
    }
}

//working
void Menu::menuExit() {
    // clear save file
    std::ofstream outFile;
    outFile.open("data.txt");
    outFile<<"";
    outFile.close();

    for (int i = 0; i < countdowns.size(); ++i) {
        countdowns[i]->saveData();
    }

    for (int j = countdowns.size()-1; j >= 0; --j) {
        delete countdowns[j]; //free heap menu
    }

    keepMenu = false;
}

//working
void Menu::createCountdown() {
    time_t now = time(NULL);
    struct tm temp;
    Countdown tempCd;
    tempCd.timeCopier(temp, now);
    std::string message, eventName;
    eventType eType;

    std::cout<<"\033[2J\033[0;0H";

    message = "What is the name of the event for this countdown?";
    eventName = sanitizeString(message);

    message = "Please input the year of the desired event";
    temp.tm_year = getInt(INT32_MIN, INT32_MAX, message) - 1900;

    message = "Please input the number of the month for the desired event.";
    temp.tm_mon = getInt(1, 12, message) - 1;

    int monMin = 1, monMax;
    bool isLeapYear = ((temp.tm_year%4) == 0 &&
                       ((temp.tm_year%100 != 0) ||
                        temp.tm_year%400 == 0));

    switch (temp.tm_mon){
        case 1: monMax = (isLeapYear)? 29 : 28;
            break;
        case 3:
        case 5:
        case 8:
        case 10: monMax = 30;
            break;
        default: monMax = 31;
    }

    message = "Please enter the day of the month of the desired event.";
    temp.tm_mday = getInt(monMin, monMax, message);

    message = "Please enter the hour in 24hr time of the desired event.";
    temp.tm_hour = getInt(0, 23, message);

    message = "Please enter the minute of the desired event.";
    temp.tm_min = getInt(0, 59, message);

    message = "Please enter the second of the desired event.";
    temp.tm_sec = getInt(0,59, message);

//    message = "Please select the type of event:"
//              "\n1. Something you're looking forward to"
//              "\n2. Something you're dreading"
//              "\n3. Something you're looking forward to the end of";
    int tempInt = 1;

    switch(tempInt){
        case 1:eType = GOOD;
            break;
        case 2:eType = BAD;
            break;
        case 3:eType = NEUTRAL;
    }

    countdowns.push_back(new ItemDisplay(eventName, temp, eType));//TODO(Deallocate)
    std::cout<<"\033[2J\033[0;0H";
}

//working
void Menu::countdownsMenu() {
    CountdownString countdownStr;
    std::string topBotStr = "################################################################################\n";
    std::string spacer =    "#                                                                              #\n";
    std::cout<<"\033[2J\033[0;0H";
    int choice = 0;
    int lineCount = 0;
    while(choice >= 0){
        cout<<topBotStr<<spacer<<"#                    "<<getLogo()<<"                                #\n"<<spacer;
        for (int i = 0; i < countdowns.size(); ++i) {

            if(lineCount%15 == 0 && i != 0){ // change to i%20 if messages gets integrated
                cout<<"\nPlease press enter to continue.";
                cout<<spacer<<topBotStr;
                cin.get();
                std::cout<<"\033[2J\033[0;0H";
                cout<<topBotStr<<spacer;
            }

            countdowns[i]->displayCountdown(countdownStr);
            countdownStr.firstPart = std::to_string(i+1)+") \""+countdowns[i]->getEventName()+"\":: " + countdownStr.firstPart;

            if (!countdownStr.secondPart.empty()) {
                countdownStr.secondPart = "     "+countdownStr.secondPart;
            }
            std::string* cdPtr[] = {&countdownStr.firstPart, &countdownStr.secondPart};

            if(!countdownStr.secondPart.empty()){
                lineCount+=2;
            } else {
                lineCount++;
            }

            for (int j = 0; j < 2; ++j) {

                for (int k = 0; k < 81; ++k) {
                    if(!cdPtr[j]->empty()){
                        if(k<5 || (k >= (cdPtr[j]->length()+5))){
                            cout<<spacer[k];
                        } else {
                            cout<<(*cdPtr[j])[k-5];
                        }
                    }
                }
            }
        }

        if(lineCount%16 != 0){
            for (int i = 0; i < (16-(lineCount%16)); ++i) {
                cout<<spacer;
            }
        }

        choice = getInt(0, countdowns.size()-1,spacer+"#  Enter a number of a countdown for additional options or enter 0 to return   #\n"
                                               "#  to main menu.                                                               #\n"+spacer+topBotStr);
        if(choice>=0){
            countdownOptions(choice);
        }
    }
}

void Menu::countdownOptions(int index) {
    std::string message = "What do you want to do with the "+countdowns[index]->getEventName()+" event?"
                                                                                               "\n1) Delete"
                                                                                               "\n2) Watch";
    int choice = getInt(1,2, message);
    switch(choice){
        case 1: countdowns.erase(countdowns.begin()+index);
            break;
        case 2: countdowns[index]->watchCountdown(*countdowns[index]);
    }
}

//working (FINALLY)
void Menu::loadCountdowns() {
    std::ifstream inFile;
    StringCarrier temp;
    eventType e;
    int tempInt;

    inFile.open("data.txt");
    if(inFile){
        std::string countdownData = "";
        while(!inFile.eof()){
            getline(inFile, countdownData);

            if(!countdownData.empty()){
                temp = splitString(countdownData);
                if(getInt(temp.targetString)>getInt(temp.creationString)) {//only add items that are not expired
                    tempInt = getInt(temp.enumString);

                    switch(tempInt){
                        case 0: e = GOOD;
                            break;
                        case 1: e = BAD;
                            break;
                        case 2: e = NEUTRAL;
                    }
                    countdowns.push_back(new ItemDisplay(temp.nameString, getInt(temp.targetString), getInt(temp.creationString), e)); //TODO(Deallocate)

                }
            }
        }
    }
    inFile.close();
}

/*******************************
** Public Functions
*******************************/

Menu::Menu()
{
    keepMenu = true;
    intMenuChoice = 0;
    lowerMenuLimit = 1;
    upperMenuLimit = 3;


    utilCountdown = Countdown();
    utilItemDisplay = ItemDisplay();

    loadCountdowns();
}

void Menu::displayMenu()
{

    while (keepMenu)
    {
        viewMenu(1);
    }

}
