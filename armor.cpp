//
// Created by athor on 11/03/2024.
//

#include "armor.h"

// creates an armor according to the `defense` parameter
armor::armor(float defense) {
    if (defense < 2) {
        m_name = "leather shirt\t";
    } else if (defense < 3.5) {
        m_name = "hard leather armor";
    } else if (defense < 5) {
        m_name = "basic iron armor   ";
    } else if (defense < 7) {
        m_name = "iron chainmail\t";
    } else if (defense < 9) {
        m_name = "steel armor\t";
    } else if (defense < 12) {
        m_name = "steel chainmail    ";
    } else if (defense < 15) {
        m_name = "orichalcum chainmail";
    } else {
        m_name = "mithril chainmail  ";
    }
    m_defense = defense;
}

// to handle the armor's display easily
std::ostream& operator<<(std::ostream& flux, armor* a) {
    flux << std::fixed << std::setprecision(1);
    flux << "Armor\t";
    if (a == nullptr) {
        flux << "Empty\n";
    } else {
        flux << a->getName() << "\t\t" << a->getDefense() <<  "\n";
    }
    return flux;
}
