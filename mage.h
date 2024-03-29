//
// Created by athor on 11/03/2024.
//

#pragma once

#ifndef ADVENTURE_MAGE_H
#define ADVENTURE_MAGE_H


#include "character.h"

class mage: public character{
public:
    mage();
    mage(int level, armor* Armor, weapon* Weapon, std::vector<item*> inventory);
    void levelUp() override;
    float useSkill(skill* attack) override;
    std::string getClassName() const override  { return "mage"; }
};


#endif //ADVENTURE_MAGE_H
