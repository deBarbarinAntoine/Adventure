//
// Created by athor on 11/03/2024.
//

#ifndef ADVENTURE_WEAPON_H
#define ADVENTURE_WEAPON_H


#include "equipment.h"

class weapon: public equipment{
protected:
    float m_attack;
    bool m_isMagic;

public:
    weapon(float attack, bool isMagic);
    std::string getName() const { return m_name; };
    float getAttack() const { return m_attack; };
    bool isMagic() const { return m_isMagic; };
};


#endif //ADVENTURE_WEAPON_H
