//
// Created by athor on 11/03/2024.
//

#include "enemy.h"
#include "mage.h"
#include "warrior.h"
#include <random>
#include <chrono>
#include <iostream>
#include <thread>

// randomNb generates a random integer between `min` and `max`.
int randomNb(int min, int max)  {
    if (min >= max) {
        return 0;
    }

    std::random_device rd;
    std::mt19937::result_type seed = rd() ^ (
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::seconds>(
                            std::chrono::system_clock::now().time_since_epoch()
                    ).count() +
            (std::mt19937::result_type)
                    std::chrono::duration_cast<std::chrono::microseconds>(
                            std::chrono::high_resolution_clock::now().time_since_epoch()
                    ).count() );

    std::mt19937 gen(seed);
    std::uniform_int_distribution<unsigned> distrib(min, max);

    return (int)(distrib(gen));
}

// generates a random enemy with comparable power level and equipments.
enemy::enemy(int level, float equipmentStats) {

    // setting up temporary variables for the enemy's generation
    float weaponAttack, armorDefense;
    bool weaponIsMagic;
    int playerLevel = level;
    std::vector<item*> inventory;

    // random throw between 0 and 100.000
    int random = randomNb(0, 100000);

    // randomize the enemy's level and equipment statistics
    if (random > 33333) {
        // 20% equipments increase
        equipmentStats *= 1.2;
    } else if (random > 11111) {
        // 1 level increase
        level += 1;
        // 10% equipments decrease
        equipmentStats *= .9;
    } else if (random > 3666) {
        // 1 level decrease
        level -= 1;
        // 30% equipments increase
        equipmentStats *= 1.3;
    } else if (random > 1222) {
        // 2 levels increase
        level += 2;
        // 20% equipments decrease
        equipmentStats *= .8;
    } else if (random > 407) {
        // 2 levels decrease
        level -= 2;
        // 40% equipments increase
        equipmentStats *= 1.4;
    }

    // setting experience points value
    if (level > playerLevel) {
        m_xp = 10 + (level - playerLevel) * 8;
    } else {
        m_xp = 10 - (playerLevel - level);
    }

    // setting the equipment statistics with one decimal only
    armorDefense = ((float)((int)((equipmentStats / 5) * 10))) / 10;
    weaponAttack = ((float)((int)((equipmentStats - armorDefense) * 10))) /10;

    // putting a health potion in the inventory
    inventory.push_back(new potion("health potion", 0, 15, true));

    // putting a mana potion in the inventory
    inventory.push_back(new potion("mana potion", 15, 0, true));

    // putting a poison in the inventory
    inventory.push_back(new potion("lethal poison", 0, 15, false));

    // setting the enemy's character's class (50/50 chance) and its skillbooks according to its level.
    if (random < 50000) {

        // create mage character

        if (level < 5) {
            m_name = "goblin shaman";
            inventory.push_back(new skillbook(5, 10));
            inventory.push_back(new skillbook(0 ,10));
        } else if (level < 10) {
            m_name = "hobgoblin shaman";
            inventory.push_back(new skillbook(10, 20));
            inventory.push_back(new skillbook(0 ,10));
        } else if (level < 15) {
            m_name = "kobold shaman";
            inventory.push_back(new skillbook(15, 30));
            inventory.push_back(new skillbook(10, 20));
            inventory.push_back(new skillbook(0 ,20));
        } else if (level < 20) {
            m_name = "orc summoner";
            inventory.push_back(new skillbook(20, 40));
            inventory.push_back(new skillbook(15, 30));
            inventory.push_back(new skillbook(0 ,30));
        } else if (level < 25) {
            m_name = "great orc mage";
            inventory.push_back(new skillbook(25, 50));
            inventory.push_back(new skillbook(20, 40));
            inventory.push_back(new skillbook(0 ,40));
        } else if (level < 30) {
            m_name = "ogre elementalist";
            inventory.push_back(new skillbook(30, 60));
            inventory.push_back(new skillbook(25, 50));
            inventory.push_back(new skillbook(0 ,50));
        } else if (level < 35) {
            m_name = "dark elemental";
            inventory.push_back(new skillbook(35, 70));
            inventory.push_back(new skillbook(30, 60));
            inventory.push_back(new skillbook(0 ,60));
        } else if (level < 40) {
            m_name = "demon prince";
            inventory.push_back(new skillbook(40, 80));
            inventory.push_back(new skillbook(35, 70));
            inventory.push_back(new skillbook(0 ,70));
        } else {
            m_name = "demon lord";
            inventory.push_back(new skillbook(45, 90));
            inventory.push_back(new skillbook(40, 80));
            inventory.push_back(new skillbook(0 ,80));
        }

        // setting the mage's weapon to a magic one for consistency
        weaponIsMagic = true;

        // creating the enemy's character with all generated information
        m_character = new mage(level, new armor(armorDefense), new weapon(weaponAttack, weaponIsMagic), inventory);

        // delete temporary inventory
//        delete &inventory;

    } else {

        // create warrior character

        if (level < 5) {
            m_name = "goblin warrior";
            inventory.push_back(new skillbook(5, 10));
            inventory.push_back(new skillbook(0 ,10));
        } else if (level < 10) {
            m_name = "hobgoblin warrior";
            inventory.push_back(new skillbook(5, 10));
            inventory.push_back(new skillbook(0 ,20));
        } else if (level < 15) {
            m_name = "kobold warrior";
            inventory.push_back(new skillbook(10, 20));
            inventory.push_back(new skillbook(0 ,20));
            inventory.push_back(new skillbook(0 ,30));
        } else if (level < 20) {
            m_name = "orc warrior";
            inventory.push_back(new skillbook(15, 30));
            inventory.push_back(new skillbook(0 ,30));
            inventory.push_back(new skillbook(0 ,40));
        } else if (level < 25) {
            m_name = "great orc captain";
            inventory.push_back(new skillbook(20, 40));
            inventory.push_back(new skillbook(0 ,40));
            inventory.push_back(new skillbook(0 ,50));
        } else if (level < 30) {
            m_name = "ogre commander";
            inventory.push_back(new skillbook(25, 50));
            inventory.push_back(new skillbook(0 ,50));
            inventory.push_back(new skillbook(0 ,60));
        } else if (level < 35) {
            m_name = "troll";
            inventory.push_back(new skillbook(30, 60));
            inventory.push_back(new skillbook(0 ,60));
            inventory.push_back(new skillbook(0 ,70));
        } else if (level < 40) {
            m_name = "dark knight";
            inventory.push_back(new skillbook(35, 70));
            inventory.push_back(new skillbook(0 ,70));
            inventory.push_back(new skillbook(0 ,80));
        } else {
            m_name = "demon champion";
            inventory.push_back(new skillbook(40, 80));
            inventory.push_back(new skillbook(0 ,80));
            inventory.push_back(new skillbook(0 ,90));
        }

        // setting the warrior's weapon to a melee one for consistency
        weaponIsMagic = false;

        // creating the enemy's character with all generated information
        m_character = new warrior(level, new armor(armorDefense), new weapon(weaponAttack, weaponIsMagic), inventory);

        // delete temporary inventory
//        delete &inventory;
    }
}

float enemy::turn() {
    if ((m_character->getHp() < 20) && (m_character->isHealthPotion())) {
        m_character->usePotion(m_character->getHealthPot());
    } else {
        std::array<skill*, 4> skills = m_character->getSkills();
        for (skill* singleSkill:skills) {
            if (m_character->getCurrentMana() >= singleSkill->getManaCost()) {
                float damage = m_character->useSkill(singleSkill);
                std::cout << std::fixed << std::setprecision(1);
                std::cout << this->getName() << " inflicted you ";
                std::this_thread::sleep_for(std::chrono::milliseconds(1500));
                return damage;
            }
        }
    }
    return 0;
}

void enemy::setCharacterStats() {
    // set the corresponding level (according to the experience points amount)
    m_character->levelUp();

    // learn all skills corresponding to the skillbooks present in the inventory
    // and put it afresh in the inventory for drops.
    int index = 0;
    for (skillbook* newSkill : m_character->getSkillbooks()) {
        if (index < 5) {
            m_character->learn(newSkill, index);
            m_character->pocketItem(newSkill);
            index++;
        } else {
            break;
        }
    }
}

// setting the drops randomly
std::vector<item *> enemy::getDrop() {
    std::vector<item*> drops;
    int random = randomNb(0, 100000);

    if (random > 80000) { // get 3 drops

        // equipment:
        if (random > 90000) {
            drops.push_back(m_character->getCurrentWeapon());
        } else {
            drops.push_back(m_character->getCurrentArmor());
        }

        // skillbook:
        int index = random % (int)(m_character->getSkillbooks().size());
        drops.push_back(m_character->getSkillbooks()[index]);

        // potion:
        int rand2 = randomNb(0, 100000);
        index = rand2 % (int)(m_character->getPotions().size());
        drops.push_back(m_character->getPotions()[index]);

    } else if (random > 60000) { // get 2 drops

        if (random > 75000) { // equipment or skillbook

            // weapon:
            drops.push_back(m_character->getCurrentWeapon());
        } else if (random > 70000) {

            // armor:
            drops.push_back(m_character->getCurrentArmor());
        } else {

            // skillbook:
            int index = random % (int)(m_character->getSkillbooks().size());
            drops.push_back(m_character->getSkillbooks()[index]);
        }

        // potion:
        int rand2 = randomNb(0, 100000);
        int index = rand2 % (int)(m_character->getPotions().size());
        drops.push_back(m_character->getPotions()[index]);

    } else if (random > 40000) { // get 1 drop

        // equipment:
        if (random > 53333) {
            if (random > 56666) {
                // weapon:
                drops.push_back(m_character->getCurrentWeapon());
            } else {
                // armor:
                drops.push_back(m_character->getCurrentArmor());
            }

            // skillbook:
        } else if (random > 46667) {
            int index = random % (int)(m_character->getSkillbooks().size());
            drops.push_back(m_character->getSkillbooks()[index]);
        } else {

            // potion:
            int rand2 = randomNb(0, 100000);
            int index = rand2 % (int)(m_character->getPotions().size());
            drops.push_back(m_character->getPotions()[index]);
        }

    } else if (random > 20000){

        // get health potion
        drops.push_back(new potion("health potion", 0, 15, true));

    } // else: get nothing... bad luck!

    return drops;
}

void enemy::battleMeet() {
    std::cout << std::fixed << std::setprecision(1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    std::cout << "\n";
    std::cout << this->getName() << ": " << this->getCharacter()->getClassName() << "\t" << this->getCharacter()->getHp() << "/" << this->getCharacter()->getMaxHp() << " HP\t" << this->getCharacter()->getCurrentMana() << "/" << this->getCharacter()->getMaxMana() << " Mana\n";
}
