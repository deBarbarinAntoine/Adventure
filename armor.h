//
// Created by athor on 11/03/2024.
//

#ifndef ADVENTURE_ARMOR_H
#define ADVENTURE_ARMOR_H


#include "equipment.h"

class armor: public equipment {
protected:
    float m_defense;

public:
    armor(std::string name, float defense);
    std::string getName() const { return m_name; };
    float getDefense() const { return m_defense; };
};


#endif //ADVENTURE_ARMOR_H
