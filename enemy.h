//
// Created by athor on 11/03/2024.
//

#ifndef ADVENTURE_ENEMY_H
#define ADVENTURE_ENEMY_H


#include <string>
#include "character.h"

class enemy {
private:
    std::string m_name;
    // std::vector<item> m_drop;
    int m_xp;
    character* m_character;

public:
    enemy(int level, float equipmentStats);
    ~enemy();
    void turn();
    void setCharacterStats();
};


#endif //ADVENTURE_ENEMY_H
