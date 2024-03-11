//
// Created by athor on 11/03/2024.
//

#include <iostream>
#include "player.h"
#include "mage.h"
#include "warrior.h"
#include "menu.h"

player::player(std::string name, int type) {
    m_name = std::move(name);
    switch (type) {
        case 1: // mage
            m_character = new mage();
            break;
        case 2: // warrior
            m_character = new warrior();
            break;
        default: // unknown -> create a mage anyway...
            m_character = new mage();
            break;
    }

}

void player::turn(enemy* adv) {
// todo battle menu

}

void player::menu() {
// todo main player menu

}

void player::creationMenu() {
    std::string name;
    do {
        std::cout << "Please enter your name: ";
        std::cin >> name;
    } while (!name.empty() || name != "");

    std::cout << "\n\n";

    int choice = menu::getMenuChoice("--- Choose your class ---", std::vector<std::string>{"Mage (more mana, less hp, magic boost)", "Warrior (more hp, less mana, melee boost)"});

    player* Player = new player(name, choice);

    Player->menu();
}
