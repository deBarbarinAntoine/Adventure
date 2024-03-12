//
// Created by athor on 11/03/2024.
//

#pragma once

#ifndef ADVENTURE_SKILLBOOK_H
#define ADVENTURE_SKILLBOOK_H


#include "item.h"

class skillbook: public item {
protected:
    float m_manaCost;
    float m_attack;

public:
    skillbook(float manaCost, float attack);
    std::string getName() const { return m_name; };
    float getManaCost() const { return m_manaCost; };
    float getAttack() const { return m_attack; };
};


#endif //ADVENTURE_SKILLBOOK_H
