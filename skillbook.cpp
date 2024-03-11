//
// Created by athor on 11/03/2024.
//

#include "skillbook.h"

skillbook::skillbook(std::string name, float manaCost, float attack) {
    m_name = std::move(name);
    m_manaCost = manaCost;
    m_attack = attack;
}
