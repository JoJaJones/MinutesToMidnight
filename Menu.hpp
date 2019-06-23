/******************************************************************************
 * Name: Patricia Booth, Josh Jones, Lindsey Olmstead, Jason Rash
 * Date: 6-21-19
 * Description: Menu class to display User Interface
******************************************************************************/

#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <string>

class Menu
{
    private:
		int intMenuChoice;
		std::string strMenuChoice;
		bool keepMenu;
		int lowerMenuLimit;
		int upperMenuLimit;

		// Text Menus
		void startMenu();

		// Request input
		void getMenuChoice();

		// Menu movement
		void viewMenu(int userNumID);
		void menuSelect(int userNumID, int intMenuChoice);
    public:
        Menu();
        void displayMenu(int userNumID);
};

#endif
