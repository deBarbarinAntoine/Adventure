//
// Created by athor on 11/03/2024.
//

#pragma once

#ifndef ADVENTURE_ARMOR_H
#define ADVENTURE_ARMOR_H


#include "equipment.h"
#include <iomanip>
#include <iostream>

class armor: public equipment {
protected:
    // defense is a float number between 0 and 100
    // that increments the character's defense every
    // time it's taking damage.
    float m_defense;

public:
    // armor constructor (or better named armor generator)
    armor(float defense);

    // getters
    std::string getName() const { return m_name; };
    float getDefense() const { return m_defense; };
};

// displaying info
std::ostream& operator<<(std::ostream& flux, armor* a);

#endif //ADVENTURE_ARMOR_H
