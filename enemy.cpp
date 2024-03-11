//
// Created by athor on 11/03/2024.
//

#include <random>
#include <chrono>
#include "enemy.h"
#include "mage.h"
#include "warrior.h"

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

    return distrib(gen);
}

// generates a random enemy with comparable power level and equipments.
enemy::enemy(int level, float equipmentStats) {

    weapon* Weapon;
    armor* Armor;
    float weaponAttack, armorDefense;
    bool weaponIsMagic;
    int playerLevel = level;
    std::vector<item*> inventory;

    int random = randomNb(0, 100000);

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

    armorDefense = ((float)((int)((equipmentStats / 5) * 10))) / 10;
    weaponAttack = ((float)((int)((equipmentStats - armorDefense) * 10))) /10;

    inventory.push_back(new potion("basic health potion", 0, 10, true));

    if (random < 50000) {
        // create mage
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
        weaponIsMagic = true;
        m_character = new mage(level, new armor(armorDefense), new weapon(weaponAttack, weaponIsMagic), inventory);
    } else {
        // create warrior
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
        weaponIsMagic = false;
        m_character = new warrior(level, new armor(armorDefense), new weapon(weaponAttack, weaponIsMagic), inventory);
    }
}

void enemy::turn() {

}

enemy::~enemy() {
    delete &m_character;
}

void enemy::setCharacterStats() {
    m_character->levelUp();
    int index = 0;
    for (skillbook* newSkill:m_character->getSkillbooks()) {
        if (index < 5) {
            m_character->learn(newSkill, index);
            m_character->deleteItem(newSkill);
            index++;
        } else {
            break;
        }
    }
}
