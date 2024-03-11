//
// Created by thorgan on 11/03/24.
//

#include <iostream>
#include <limits>
#include "menu.h"

int menu::getMenuChoice(std::string title, std::vector<std::string> options) {
    int minChoice = 1;
    int maxChoice = (int)(options.size());

    int choice;

    do {
        std::cout << title << "\n";
        for (int i = 0; i < maxChoice; ++i) {
            std::cout << i << options[i] << "\n";
        }
        std::cout << "Enter your choice ("<< minChoice << "-" << maxChoice << "): ";

        // input validation
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            // clear input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice >= minChoice && choice <= maxChoice);

    return choice;
}
