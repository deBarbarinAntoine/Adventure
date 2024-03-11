//
// Created by athor on 11/03/2024.
//

#include "armor.h"

armor::armor(std::string name, float defense) {
    m_defense = defense;
    m_name = std::move(name);
}
