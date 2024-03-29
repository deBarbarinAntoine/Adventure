//
// Created by athor on 11/03/2024.
//

#pragma once

#ifndef ADVENTURE_SKILLBOOK_H
#define ADVENTURE_SKILLBOOK_H


#include "item.h"

class skillbook: public item {
protected:
    // how much mana it costs to use (is it magic?)
    float m_manaCost;

    // its attack power
    float m_attack;

public:
    skillbook(float manaCost, float attack);
    std::string getName() const { return m_name; };
    float getManaCost() const { return m_manaCost; };
    float getAttack() const { return m_attack; };
};

// for displaying purposes
std::ostream& operator<<(std::ostream& flux, skillbook* a);


#endif //ADVENTURE_SKILLBOOK_H
