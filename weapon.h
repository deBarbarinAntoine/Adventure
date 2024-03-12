//
// Created by athor on 11/03/2024.
//

#pragma once

#ifndef ADVENTURE_WEAPON_H
#define ADVENTURE_WEAPON_H


#include "equipment.h"

class weapon: public equipment{
protected:
    // the weapon attack power
    float m_attack;

    // is that weapon magic?
    bool m_isMagic;

public:
    weapon(float attack, bool isMagic);
    std::string getName() const { return m_name; };
    float getAttack() const { return m_attack; };
    bool isMagic() const { return m_isMagic; };
};

// for displaying purposes
std::ostream& operator<<(std::ostream& flux, weapon* a);

#endif //ADVENTURE_WEAPON_H
