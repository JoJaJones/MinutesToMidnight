/******************************************************************************
 * Name: Patricia Booth, Josh Jones, Lindsey Olmstead, Jason Rash
 * Date: 6-21-19
 * Description: Menu class to display User Interface
******************************************************************************/

#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

#include "Validation.hpp"
#include "Countdown.hpp"
#include "ItemDisplay.hpp"


class Menu
{
    private:
		int intMenuChoice;
		std::string strMenuChoices;
		bool keepMenu;
		int lowerMenuLimit;
		int upperMenuLimit;
		Countdown utilCountdown;
		ItemDisplay utilItemDisplay;
		std::vector<ItemDisplay*> countdowns;

		// Helper Functions
		void createCountdown();
		void loadCountdowns();

		// Text Menus
		void startMenu();
		void countdownsMenu();

		// Request input
//		void getMenuChoice();

		// Menu movement
		void viewMenu(int userNumID);
		void menuSelect(int userNumID, int intMenuChoice);
		void menuExit();
    public:
        Menu();
        void displayMenu();
//        ~Menu();
};

#endif
