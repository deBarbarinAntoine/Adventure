//
// Created by athor on 11/03/2024.
//

#pragma once

#ifndef ADVENTURE_SKILL_H
#define ADVENTURE_SKILL_H


#include "skillbook.h"
#include <string>

class skill {
protected:
    // the skill's name
    std::string m_name;

    // its attack power
    float m_attack;

    // its mana cost (is it magic?)
    float m_manaCost;

public:
    skill(skillbook *skillBook);
    ~skill() = default;
    std::string getName() const { return m_name; };
    float getManaCost() const { return m_manaCost; };
    float getAttack() const { return m_attack; };
};

// for displaying purposes
std::ostream& operator<<(std::ostream& flux, skill* a);


#endif //ADVENTURE_SKILL_H
