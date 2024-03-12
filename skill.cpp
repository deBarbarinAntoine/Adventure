//
// Created by athor on 11/03/2024.
//

#include "skill.h"
#include <iomanip>
#include <iostream>

skill::skill(skillbook *skillBook) {
    m_name = skillBook->getName();
    m_attack = skillBook->getAttack();
    m_manaCost = skillBook->getManaCost();
}

std::ostream& operator<<(std::ostream& flux, skill* a) {
    flux << std::fixed << std::setprecision(1);
    flux << a->getName() << "\t" << a->getManaCost() << "\t" << a->getAttack() << "\n";
    return flux;
}