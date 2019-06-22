/******************************************************************************
 * Name: Patricia Booth, Josh Jones, Lindsey Olmstead, Jason Rash
 * Date: 6-21-19
 * Description: Menu class to display User Interface
******************************************************************************/

#ifndef MENU_HPP
#define MENU_HPP

class Menu
{
    private:
        char menuChoice;

    public:
        Menu();
        void displayMenu();
        void getMenuChoice();
        bool isValidMenuChoice();
};

#endif
