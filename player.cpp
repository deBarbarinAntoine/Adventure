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

// the player's constructor: we'll destroy them all!
player::player(std::string name, int type) {
    m_name = std::move(name);
    switch (type) {

        // creating a mage
        case 1:
            std::cout << std::endl << m_name << " chose to be a mage!\n";
            m_character = new mage();
            break;

        // creating a warrior
        case 2:
            std::cout << std::endl << m_name << " chose to be a warrior!\n";
            m_character = new warrior();
            break;

        // what did you do? Aaahhhh, just create a mage anyway...
        default:
            std::cout << std::endl << m_name << " will be a mage!\n";
            m_character = new mage();
            break;
    }

}

// the player's turn: let's beat some trash villain here!
bool player::turn(enemy* adv) {
    std::cout << adv;
    std::cout << "\n\n";
    std::cout << this;
    int choice;
    int index;
    std::array<skill*, 4> skills = m_character->getSkills();
    std::vector<potion*> potions = m_character->getPotions();
    std::vector<skill*> availableSkills;
    std::vector<potion*> availablePotions;
    do {
        choice = 0;
        index = 1;
        std::cout << "\n";
        std::cout << " - Skills:\n";
        std::cout << "Index\tName\t\tMana\tAttack\n";

        // looking for available and currently usable skills
        for (skill* singleSkill : skills) {
            if (singleSkill != nullptr) {
                if (singleSkill->getManaCost() > m_character->getCurrentMana()) {
                    continue;
                }
                std::cout << index << ".\t" << singleSkill;
                availableSkills.push_back(singleSkill);
                index++;
            }
        }
        std::cout << "\n";
        std::cout << " - Potions:\n";

        // looking for health potion
        for (potion* pot : potions) {
            if (pot->isSelfUse()) {
                std::cout << index << ".\t" << pot;
                availablePotions.push_back(pot);
                index++;
                break;
            }
        }

        // looking for poison
        for (potion* pot : potions) {
            if (!pot->isSelfUse()) {
                std::cout << index << ".\t" << pot;
                availablePotions.push_back(pot);
                index++;
                break;
            }
        }
        std::cout << index << ".\tFlee\n";
        std::cout << "Choose an option: ";

        // input validation
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();

            // clear input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice < 1 || choice > index);
    if (choice <= availableSkills.size()) {

        // Avadakedavra!... take that!
        float damage = m_character->useSkill(availableSkills[choice]);
        adv->takeDamage(damage);
        std::cout << "You inflicted " << damage << " damage on the enemy.\n";

    } else if (choice - availableSkills.size() <= availablePotions.size()) {

        // let's take a potion instead (or throw poison, maybe?)
        m_character->usePotion(availablePotions[choice - availableSkills.size()], adv->getCharacter());
    } else {
        // Flee from the battle!
        return false;
    }
    // Continue the battle
    return true;
}

// the player's main menu
void player::menu() {
    int choice;
    do {
        choice = 0;

        // clear the terminal: try windows command and if error, then linux command
        int res = system("cls");
        if (res != 0) {
            res = system("clear");
        }

        // player's info recap
        std::cout << this;

        // displaying the player's main menu
        choice = menu::getMenuChoice("------------ Main Menu ------------", std::vector<std::string>{"New Battle", "Inventory", "Quit"});

        switch (choice) {
            case 1:
                // starting the battle Waaaaggghh! (Oooops, I'm not an Ork...)
                this->startBattle();

                // if the player is dead, exit the current game...
                // sorry if it's a little harsh on you!
                if (this->isDead()) {
                    choice = 3;
                }
                break;
            case 2:
                // display the inventory
                this->inventoryMenu();
                break;
            default:
                // nothing to do here
                break;
        }
    // until you want to quit ...or you die!
    } while (choice != 3);
}

// display the player's creation menu: let's begin the adventure!
void player::creationMenu() {

    // clear the terminal: try windows command and if error, then linux command
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

    // rest assured, you'll have a name
    } while (name.empty() || name == "");

    // let's breathe a little, okay?
    std::cout << "\n\n";

    // displaying the class selection menu
    int choice = menu::getMenuChoice("Hello "+ name +" Choose your class:", std::vector<std::string>{"Mage (more mana, less hp, magic boost)", "Warrior (more hp, less mana, melee boost)"});

    // creating the player, whoohooo!
    player* Player = new player(name, choice);

    // let's begin with the main menu
    Player->menu();
}

// let's start the battle, I crave some action here!...
void player::startBattle() {

    // new battle (with me of course, I'm not a spectator)
    battle* Battle = new battle(this);

    // let's go to the battle loop to kill some mob
    Battle->run();

    // clear the battle when it's finished
    if (Battle) {
        delete &Battle;
    }
}

// inventory menu: to select and interact
// with the stuff you looted form your opponents
void player::inventoryMenu() {
    int choice;
    std::vector<item*> options;
    do {
        // print the inventory and retrieve the options in order
        // (to fetch the corresponding item afterward)
        options = m_character->printInventory();
        std::cout << "Choose an option: ";
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();

            // clear input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

    // until you choose something you have:
    // stop dreaming here, item 524749132 doesn't exist (I hope so)
    } while (choice < 1 || choice > options.size() + 1);
    if (choice == options.size() + 1) {

        // exit the menu
        return;
    } else {

        // the selected item's menu: let's do something with that stuff!
        this->itemMenu(options[choice-1]);
    }
}

// the item's menu: what to do with it?
void player::itemMenu(item* it) {
    int choice;
    do {
        std::string action;

        // is it a weapon?
        if (dynamic_cast<weapon*>(it)) {
            std::cout << "Type\tName\t\tAttack\tDefense\n";
            std::cout << dynamic_cast<weapon*>(it);
            action = "Equip";

        // or an armor, maybe?
        } else if (dynamic_cast<armor*>(it)) {
            std::cout << "Type\tName\t\tAttack\tDefense\n";
            std::cout << dynamic_cast<armor*>(it);
            action = "Equip";

        // beehhh, what else could it be? A skillbook?
        } else if (dynamic_cast<skillbook*>(it)) {
            std::cout << "Name\t\tMana\tAttack\n";
            std::cout << dynamic_cast<skillbook*>(it);
            action = "Learn";

        // last try... a potion?
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

        // checking the input
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();

            // clear input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

    // until you make a valid choice
    } while (choice < 1 || choice > 3);

    switch (choice) {
        case 1:
            // yeeesss! Use it!
            m_character->useItem(it);
            break;
        case 2:
            // meeehhh, that's trash, really!
            m_character->deleteItem(it);
            break;
            // I changed idea
        default:
            break;
    }

}

// displaying the player's information
std::ostream& operator<<(std::ostream& flux, player* a) {
    flux << a->getName() << ": " << a->getCharacter()->getClassName() << std::endl;
    flux << a->getCharacter() << std::endl;
    return flux;
}
