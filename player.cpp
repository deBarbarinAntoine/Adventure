//
// Created by athor on 11/03/2024.
//

#include "mage.h"
#include "warrior.h"
#include "menu.h"
#include "battle.h"
#include "player.h"

#include <iostream>
#include <limits>

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
        default: // unknown -> create a mage anyway... (just in case)
            std::cout << std::endl << m_name << " will be a mage!\n";
            m_character = new mage();
            break;
    }

}

void player::turn(enemy* adv) {
// todo player battle menu
}

void player::menu() {
    int choice;
    do {
        choice = 0;
        int res = system("cls");
        if (res != 0) {
            system("clear");
        }
        std::cout << this;

        choice = menu::getMenuChoice("------------ Main Menu ------------", std::vector<std::string>{"New Battle", "Inventory", "Quit"});
        switch (choice) {
            case 1:
                this->startBattle();
                break;
            case 2:
                this->inventoryMenu();
                break;
            default:
                break;
        }
    } while (choice != 3);
}

void player::creationMenu() {
    int res = system("cls");
    if (res != 0) {
        res = system("clear");
    }
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

void player::inventoryMenu() {
    int choice;
    std::vector<item*> options;
    do {
        options = m_character->printInventory();
        std::cout << "Choose an option: ";
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            // clear input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice < 1 || choice > options.size() + 1);
    if (choice == options.size() + 1) {
        return;
    } else {
        this->itemMenu(options[choice-1]);
    }
}

void player::itemMenu(item* it) {
    int choice;
    do {
        std::string action;
        if (dynamic_cast<weapon*>(it)) {
            std::cout << "Type\tName\t\tAttack\tDefense\n";
            std::cout << dynamic_cast<weapon*>(it);
            action = "Equip";
        } else if (dynamic_cast<armor*>(it)) {
            std::cout << "Type\tName\t\tAttack\tDefense\n";
            std::cout << dynamic_cast<armor*>(it);
            action = "Equip";
        } else if (dynamic_cast<skillbook*>(it)) {
            std::cout << "Name\t\tMana\tAttack\n";
            std::cout << dynamic_cast<skillbook*>(it);
            action = "Learn";
        } else if (dynamic_cast<potion*>(it)){
            std::cout << "Name\t\tMana\tHP\tType\n";
            std::cout << dynamic_cast<potion*>(it);
            action = "Use";
        }
        std::cout << "\n";
        std::cout << "1. " << action << "\n";
        std::cout << "2. Drop\n";
        std::cout << "3. Cancel\n";
        std::cout << "Choose an option: ";
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            // clear input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice < 1 || choice > 3);
    switch (choice) {
        case 1:
            m_character->useItem(it);
            break;
        case 2:
            m_character->deleteItem(it);
            break;
        default:
            break;
    }

}

std::ostream& operator<<(std::ostream& flux, player* a) {
    flux << a->getName() << ": " << a->getCharacter()->getClassName() << std::endl;
    flux << a->getCharacter() << std::endl;
    return flux;
}
