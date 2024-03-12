//
// Created by athor on 11/03/2024.
//

#include "skill.h"
#include <iomanip>
#include <iostream>

// skill constructor using a skillbook (it's like when you learn it, right?)
skill::skill(skillbook *skillBook) {
    m_name = skillBook->getName();
    m_attack = skillBook->getAttack();
    m_manaCost = skillBook->getManaCost();
}

// displaying the skill's information
std::ostream& operator<<(std::ostream& flux, skill* a) {
    flux << std::fixed << std::setprecision(1);
    flux << a->getName() << "\t" << a->getManaCost() << "\t" << a->getAttack() << "\n";
    return flux;
}