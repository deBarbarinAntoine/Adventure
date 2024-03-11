//
// Created by athor on 11/03/2024.
//

#ifndef ADVENTURE_PLAYER_H
#define ADVENTURE_PLAYER_H


#include <string>
#include "character.h"

class player {
protected:
    std::string m_name;
    character* m_character;

public:
    player(std::string name, int type);
    void turn();
    void menu();
    int getLevel() const { return m_character->getLevel(); };
    float getEquipmentStats() const { return m_character->getEquipmentStats(); }
    bool isDead() const { return m_character->isDead(); }
    void gainXp(int xp) { m_character-> gainXp(xp); }
};


#endif //ADVENTURE_PLAYER_H
