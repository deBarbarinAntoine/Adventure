//
// Created by athor on 11/03/2024.
//

#include "mage.h"
#include "warrior.h"
#include "menu.h"
#include "battle.h"
#include <iostream>

player::player(std::string name, int type) {
    m_name = std::move(name);
    switch (type) {
        case 1: // mage
            std::cout << std::endl << m_name << " chose to be a mage!\n";
            m_character = new mage();
            break;
        case 2: // warrior
            std::cout << std::endl << m_name << " chose to be a warrior!\n";
            m_character = new warrior();
            break;
        default: // unknown -> create a mage anyway...
            std::cout << std::endl << m_name << " will be a mage!\n";
            m_character = new mage();
            break;
    }

}

void player::turn(enemy* adv) {
// todo player battle menu
}

void player::menu() {
// todo main player menu
    std::cout << this;

    int choice = menu::getMenuChoice("------------ Main Menu ------------", std::vector<std::string>{"New Battle", "Inventory", "Quit"});
    switch (choice) {
        case 1:
            this->startBattle();
            break;
        case 2:
            //todo inventory menu
            break;
        case 3:
            break;
        default:
            break;
    }
}

void player::creationMenu() {
    std::string name;
    do {
        std::cout << "\n";
        std::cout << "Please enter your name: ";
        std::cout << " ";
        std::cin >> name;
    } while (name.empty() || name == "");

    std::cout << "\n\n";

    int choice = menu::getMenuChoice("Hello "+ name +" Choose your class:", std::vector<std::string>{"Mage (more mana, less hp, magic boost)", "Warrior (more hp, less mana, melee boost)"});

    player* Player = new player(name, choice);

    Player->menu();
}

void player::startBattle() {
    battle* Battle = new battle(this);
    Battle->run();
    delete &Battle;
}

std::ostream& operator<<(std::ostream& flux, player* a) {
    flux << a->getName() << ": " << a->getCharacter()->getClassName() << std::endl;
    flux << a->getCharacter() << std::endl;
    return flux;
}
