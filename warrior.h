//
// Created by athor on 11/03/2024.
//

#pragma once

#ifndef ADVENTURE_WARRIOR_H
#define ADVENTURE_WARRIOR_H


#include "character.h"

class warrior: public character {
public:
    warrior();
    warrior(int level, armor* Armor, weapon* Weapon, std::vector<item*> inventory);
    void levelUp() override;
    float useSkill(skill* attack) override;
    std::string getClassName() const override { return "warrior"; }
};


#endif //ADVENTURE_WARRIOR_H
