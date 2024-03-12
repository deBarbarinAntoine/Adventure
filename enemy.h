//
// Created by athor on 11/03/2024.
//

#pragma once

#ifndef ADVENTURE_ENEMY_H
#define ADVENTURE_ENEMY_H


#include "character.h"
#include <string>

class enemy {
private:
    // enemy's name (let's forget it)
    std::string m_name;

    // the experience points I can gain if I kill it
    int m_xp;

    // the enemy's character
    character* m_character;

public:
    enemy(int level, float equipmentStats);
    ~enemy();
    void turn(character* charPlayer);
    void setCharacterStats();
    bool isDead() const { return m_character->isDead(); }
    int getXp() const { return m_xp; }
    std::vector<item*> getDrop();
    std::string getName() const { return m_name; }
    character* getCharacter() { return m_character; }
    void takeDamage(float damage) { m_character->takeDamage(damage); }
};

// displaying enemy's information
std::ostream& operator<<(std::ostream& flux, enemy* a);

#endif //ADVENTURE_ENEMY_H
