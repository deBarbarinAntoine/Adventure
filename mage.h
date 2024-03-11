//
// Created by athor on 11/03/2024.
//

#ifndef ADVENTURE_MAGE_H
#define ADVENTURE_MAGE_H


#include "character.h"

class mage: public character{
protected:

public:
    mage();
    mage(int level, armor* Armor, weapon* Weapon, std::vector<item*> inventory);
    void levelUp() override;
    float useSkill(skill* attack) override;
};


#endif //ADVENTURE_MAGE_H
