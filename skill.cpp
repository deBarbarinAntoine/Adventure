//
// Created by athor on 11/03/2024.
//

#include "skill.h"

skill::skill(skillbook *skillBook) {
    m_name = skillBook->getName();
    m_attack = skillBook->getAttack();
    m_manaCost = skillBook->getManaCost();
}
