//
// Created by thorgan on 11/03/24.
//

#ifndef ADVENTURE_MENU_H
#define ADVENTURE_MENU_H


#include <vector>
#include <string>

class menu {
public:
    static int getMenuChoice(std::string title, std::vector<std::string> options);
};


#endif //ADVENTURE_MENU_H
