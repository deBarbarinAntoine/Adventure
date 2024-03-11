//
// Created by athor on 11/03/2024.
//

#ifndef ADVENTURE_ENEMY_H
#define ADVENTURE_ENEMY_H


#include <string>
#include "character.h"
#include "player.h"

class enemy {
private:
    std::string m_name;
    int m_xp;
    character* m_character;

public:
    enemy(int level, float equipmentStats);
    ~enemy();
    void turn(player* Player);
    void setCharacterStats();
    bool isDead() const { return m_character->isDead(); }
    int getXp() const { return m_xp; }
    std::vector<item*> getDrop();
};


#endif //ADVENTURE_ENEMY_H
