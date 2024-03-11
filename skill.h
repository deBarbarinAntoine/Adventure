//
// Created by athor on 11/03/2024.
//

#ifndef ADVENTURE_SKILL_H
#define ADVENTURE_SKILL_H


#include <string>
#include "skillbook.h"

class skill {
protected:
    std::string m_name;
    float m_attack;
    float m_manaCost;

public:
    skill(skillbook *skillBook);
    ~skill() = default;
    std::string getName() const { return m_name; };
    float getManaCost() const { return m_manaCost; };
    float getAttack() const { return m_attack; };
};


#endif //ADVENTURE_SKILL_H
