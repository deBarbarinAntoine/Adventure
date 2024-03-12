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
    std::string m_name;
    character* m_character;

public:
    player(std::string name, int type);
    void turn(enemy* adv);
    void menu();
    static void creationMenu();
    int getLevel() const { return m_character->getLevel(); };
    float getEquipmentStats() const { return m_character->getEquipmentStats(); }
    bool isDead() const { return m_character->isDead(); }
    void gainXp(int xp) { m_character-> gainXp(xp); }
    void takeDamage(float damage) { m_character->takeDamage(damage); }
    void startBattle();
    character* getCharacter() { return m_character; }
    std::string getName() const { return m_name; }
};


std::ostream& operator<<(std::ostream& flux, player* a);


#endif //ADVENTURE_PLAYER_H
