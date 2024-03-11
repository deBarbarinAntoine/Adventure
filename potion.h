//
// Created by athor on 11/03/2024.
//

#ifndef ADVENTURE_POTION_H
#define ADVENTURE_POTION_H


#include "item.h"

class potion: public item {
protected:
    float m_manaModifier;
    float m_hpModifier;
    bool m_selfUse;

public:
    potion(std::string name, float manaModifier, float hpModifier, bool selfUse);
    bool isSelfUse() const { return m_selfUse; }
    float manaModifier() const { return m_manaModifier; };
    float hpModifier() const { return m_hpModifier; };
};


#endif //ADVENTURE_POTION_H
