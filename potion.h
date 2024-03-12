//
// Created by athor on 11/03/2024.
//

#pragma once

#ifndef ADVENTURE_POTION_H
#define ADVENTURE_POTION_H


#include "item.h"

class potion: public item {
protected:

    // how much mana will you gain/loose?
    float m_manaModifier;

    // how much health points will you gain/loose?
    float m_hpModifier;

    // is it for you or for your enemies?
    bool m_selfUse;

public:
    potion(std::string name, float manaModifier, float hpModifier, bool selfUse);
    bool isSelfUse() const { return m_selfUse; }
    float manaModifier() const { return m_manaModifier; };
    float hpModifier() const { return m_hpModifier; };

    // just to make sure it's a health potion
    struct isHealthPot {
        const potion* pot1;
        const potion* pot2 = new potion("health potion", 0, 15, true);
        isHealthPot() : pot1(pot2) {}
        bool operator()(potion* pot2) const { return pot1->getName() == pot2->getName(); }
    };

};

// for displaying purposes
std::ostream& operator<<(std::ostream& flux, potion* a);

#endif //ADVENTURE_POTION_H
