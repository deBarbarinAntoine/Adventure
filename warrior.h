//
// Created by athor on 11/03/2024.
//

#ifndef ADVENTURE_WARRIOR_H
#define ADVENTURE_WARRIOR_H


#include "character.h"

class warrior: public character {
protected:

public:
    warrior();
    void levelUp() override;
    float useSkill(skill* attack) override;
};


#endif //ADVENTURE_WARRIOR_H
