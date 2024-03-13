//
// Created by athor on 11/03/2024.
//

#pragma once

#ifndef ADVENTURE_PLAYER_H
#define ADVENTURE_PLAYER_H


#include "enemy.h"
#include <string>

class player {
protected:
    // your name (yours, not the anime)
    std::string m_name;

    // your character
    character* m_character;

public:
    player(std::string name, int type);
    ~player() { delete m_character; }
    bool turn(std::unique_ptr<enemy> &adv);
    void menu();
    static void creationMenu();
    int getLevel() const { return m_character->getLevel(); };
    float getEquipmentStats() const { return m_character->getEquipmentStats(); }
    bool isDead() const { return m_character->isDead(); }
    void gainXp(int xp) { m_character-> gainXp(xp); }
    void startBattle();
    void runBattle(std::unique_ptr<enemy> &adv);
    character* getCharacter() { return m_character; }
    std::string getName() const { return m_name; }
    void inventoryMenu();
    void itemMenu(item* it);
    void pocketItem(item* it) { m_character->pocketItem(it); }
    void takeDamage(float damage) { m_character->takeDamage(damage); }
};

// for displaying purposes
std::ostream& operator<<(std::ostream& flux, player* a);


#endif //ADVENTURE_PLAYER_H
