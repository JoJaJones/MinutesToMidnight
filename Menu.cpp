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

void Menu::startMenu() // Menu ID: 1
{
	cout << "1. Create New Countdown\n"
		<< "2. List Current Countdowns\n"
		<< "3. Remove Countdown\n"
		<< "4. Exit\n";

	lowerMenuLimit = 1;
	upperMenuLimit = 4;
}

void Menu::getMenuChoice()
{
	getline(cin, strMenuChoice);
	/* Convert string to integer
	** This is just a placeholder until integrated
	** with input validation
	*/
	intMenuChoice = stoi(strMenuChoice);
}

/*******************************
** Menu Movement
*******************************/

void Menu::viewMenu(int userNumID)
{
	switch (userNumID)
	{
	case 1: // Main Menu
		startMenu();
		getMenuChoice();
		menuSelect(userNumID, intMenuChoice);
		break;
	}
}

void Menu::menuSelect(int userNumID, int intMenuChoice)
{
	switch (userNumID)
	{
	case 1: // Main Menu
		switch (intMenuChoice)
		{
		case 1:
			cout << "Here is where you create a countdown.\n";
			break;
		case 2:
			cout << "Here is where you list current countdowns.\n";
			break;
		case 3:
			cout << "Here is where you remove a countdown.\n";
			break;
		case 4:
			keepMenu = false;
			break;
		}
		break;
	}
}

/*******************************
** Public Functions
*******************************/

Menu::Menu()
{
	keepMenu = true;
	intMenuChoice = 0;
	strMenuChoice = " ";
	lowerMenuLimit = 0;
	upperMenuLimit = 0;
}

void Menu::displayMenu(int userNumID)
{
	switch (userNumID)
	{
	case 1: // Main Menu
		while (keepMenu)
		{
			viewMenu(1);
		}
		break;
	}
}
