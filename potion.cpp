//
// Created by athor on 11/03/2024.
//

#include "potion.h"
#include <iomanip>
#include <iostream>

potion::potion(std::string name, float manaModifier, float hpModifier, bool selfUse) {
    m_name = std::move(name);
    m_manaModifier = manaModifier;
    m_hpModifier = hpModifier;
    m_selfUse = selfUse;
}

std::ostream& operator<<(std::ostream& flux, potion* a) {
    flux << std::fixed << std::setprecision(1);
    std::string type;
    if (a->isSelfUse()) {
        type = "potion";
    } else {
        type = "poison";
    }
    flux << a->getName() << "\t" << a->manaModifier() << "\t" << a->hpModifier() << "\t" << type << "\n";
    return flux;
}
