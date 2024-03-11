//
// Created by athor on 11/03/2024.
//

#include "weapon.h"

weapon::weapon(std::string name, float attack, bool isMagic) {
    m_attack = attack;
    m_name = std::move(name);
    m_isMagic = isMagic;
}
