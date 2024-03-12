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
    std::string m_name;
    int m_xp;
    character* m_character;

public:
    enemy(int level, float equipmentStats);
    ~enemy();
    void turn(character* charPlayer);
    void setCharacterStats();
    bool isDead() const { return m_character->isDead(); }
    int getXp() const { return m_xp; }
    std::vector<item*> getDrop();
};


#endif //ADVENTURE_ENEMY_H
