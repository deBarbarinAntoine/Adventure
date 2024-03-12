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
    float m_defense;

public:
    armor(float defense);
    std::string getName() const { return m_name; };
    float getDefense() const { return m_defense; };
};

std::ostream& operator<<(std::ostream& flux, armor* a);

#endif //ADVENTURE_ARMOR_H
