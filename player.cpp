//
// Created by athor on 11/03/2024.
//

#include "mage.h"
#include "warrior.h"
#include "menu.h"
#include "player.h"

#include <iostream>
#include <limits>
#include <chrono>
#include <thread>

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
bool player::turn(std::unique_ptr<enemy> &adv) {

    int choice;
    int index;
    std::array<skill*, 4> skills = m_character->getSkills();
    std::vector<potion*> potions = m_character->getPotions();
    std::vector<skill*> availableSkills;
    std::vector<potion*> availablePotions;

    do {
        // clear the terminal: try windows command and if error, then linux command
        int res = system("cls");
        if (res != 0) {
            res = system("clear");
        }
        std::cout << std::fixed << std::setprecision(1);

        // displaying the enemy's information
        adv->battleMeet();
        std::cout << "\n\t----------------------------------------\n\n";

        // displaying the player's information
        std::cout << this->getName() << ": " << this->getCharacter()->getClassName() << "\t" << this->getCharacter()->getHp() << "/" << this->getCharacter()->getMaxHp() << " HP\t" << this->getCharacter()->getCurrentMana() << "/" << this->getCharacter()->getMaxMana() << " Mana\n";


        // displaying the player's options (in a menu)
        choice = 0;
        index = 1;
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

    // until you choose a valid option
    } while (choice < 1 || choice > index);

    // setting a valid index integer (beginning from value 0)
    int option = choice - 1;

    if (option < availableSkills.size()) {

        // Avadakedavra!... take that!
        float damage = m_character->useSkill(availableSkills[option]);

        std::cout << "You inflicted ";
        adv->takeDamage(damage);
        std::cout << " on the enemy.\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    } else if (option - availableSkills.size() < availablePotions.size()) {

        // let's take a potion instead (or throw poison, maybe?)
        m_character->usePotion(availablePotions[option - availableSkills.size()], adv->getCharacter());
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
        choice = menu::getMenuChoice("------------ Main Menu ------------", std::vector<std::string>{"New Battle", "Inventory", "Rest", "Quit"});

        switch (choice) {
            case 1:
                // starting the battle Waaaaggghh! (Oooops, I'm not an Ork...)
                this->startBattle();

                // if the player is dead, exit the current game...
                // sorry if it's a little harsh on you!
                if (this->isDead()) {
                    choice = 4;
                }
                break;
            case 2:
                // display the inventory
                this->inventoryMenu();
                break;
            case 3:
                // taking a little rest on the way to greatness is necessary
                this->rest();
                break;
            default:
                // nothing to do here
                break;
        }
    // until you want to quit ...or you die!
    } while (choice != 4);
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

    // clear the terminal: try windows command and if error, then linux command
    res = system("cls");
    if (res != 0) {
        res = system("clear");
    }

    // displaying the class selection menu
    int choice = menu::getMenuChoice("Hello "+ name +" Choose your class:", std::vector<std::string>{"Mage (more mana, less hp, magic boost)", "Warrior (more hp, less mana, melee boost)"});

    // creating the player, whoohooo!
    player* Player = new player(name, choice);

    // let's begin with the main menu
    Player->menu();
}

// let's start the battle, I crave some action here!...
void player::startBattle() {

    // creating the enemy
    std::unique_ptr<enemy> adv = std::make_unique<enemy>(this->getLevel(), this->getEquipmentStats());
    adv->setCharacterStats();

    // clear the terminal: try windows command and if error, then linux command
    int res = system("cls");
    if (res != 0) {
        res = system("clear");
    }

    // little introduction message
    std::cout << "You met a " << adv->getName() << "...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    // let's go to the battle loop to kill some mob
    this->runBattle(adv);
}

// inventory menu: to select and interact
// with the stuff you looted form your opponents
void player::inventoryMenu() {

    // clear the terminal: try windows command and if error, then linux command
    int res = system("cls");
    if (res != 0) {
        res = system("clear");
    }
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

    // clear the terminal: try windows command and if error, then linux command
    int res = system("cls");
    if (res != 0) {
        res = system("clear");
    }
    int choice;
    do {
        std::string action;

        // is it a weapon?
        if (dynamic_cast<weapon*>(it)) {
            std::cout << "Type\tName\t\t\tAttack\tDefense\n";
            std::cout << dynamic_cast<weapon*>(it);
            action = "Equip";

        // or an armor, maybe?
        } else if (dynamic_cast<armor*>(it)) {
            std::cout << "Type\tName\t\t\tAttack\tDefense\n";
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

void player::runBattle(std::unique_ptr<enemy> &adv) {
    do {

        // checking the player's turn return (pun not intentional)
        if (!this->turn(adv)) {

            // Flee from the battle if the player's turn returns false
            return;
        }
        // exit the loop if the player killed the enemy
        if (adv->isDead()) {
            break;
        }
        // enemy turn
        this->takeDamage(adv->turn());
        std::cout << ".\n";

        // little timer to read the message about the enemy's damage done.
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));

        // exit the loop if the player died... GAME OVER my dear!
    } while (!this->isDead());

    // player's win
    if (adv->isDead()) {
        std::cout << "Congratulations, you won!\n";

        // getting the drops
        std::vector<item*> drops = adv->getDrop();
        for (item* it : drops) {

            // displaying the corresponding information
            if (dynamic_cast<armor*>(it)) {
                std::cout << "You retrieved:\n";
                std::cout << "Type\tName\t\t\tAttack\tDefense\n";
                std::cout << dynamic_cast<armor*>(it);
            } else if (dynamic_cast<weapon*>(it)) {
                std::cout << "You retrieved:\n";
                std::cout << "Type\tName\t\t\tAttack\tDefense\n";
                std::cout << dynamic_cast<weapon*>(it);
            } else if (dynamic_cast<skillbook*>(it)) {
                std::cout << "You retrieved:\n";
                std::cout << "Name\t\tMana\tAttack\n";
                std::cout << dynamic_cast<skillbook*>(it);
            } else if (dynamic_cast<potion*>(it)) {
                std::cout << "You retrieved:\n";
                std::cout << "Name\t\tMana\tHP\tType\n";
                std::cout << dynamic_cast<potion*>(it);
            }

            // putting each item in the player's inventory
            this->pocketItem(it);
        }
        std::cout << "You gained " << adv->getXp() << " XP\n";

        // retrieve the enemy's worth Xp
        this->gainXp(adv->getXp());

        // level-up if necessary
        m_character->levelUp();

        // wait 3 sec to read all information
        std::this_thread::sleep_for(std::chrono::milliseconds(3500));

        // player's loss... GAME OVER...
    } else if (this->isDead()) {
        std::cout << "GAME OVER!\n";
    }
}

// displaying the player's information
std::ostream& operator<<(std::ostream& flux, player* a) {
    flux << a->getName() << ": " << a->getCharacter()->getClassName() << std::endl;
    flux << a->getCharacter() << std::endl;
    return flux;
}
