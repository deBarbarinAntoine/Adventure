//
// Created by athor on 11/03/2024.
//

#include "potion.h"

potion::potion(std::string name, float manaModifier, float hpModifier, bool selfUse) {
    m_name = std::move(name);
    m_manaModifier = manaModifier;
    m_hpModifier = hpModifier;
    m_selfUse = selfUse;
}
