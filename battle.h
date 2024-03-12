//
// Created by athor on 11/03/2024.
//

#pragma once

#ifndef ADVENTURE_BATTLE_H
#define ADVENTURE_BATTLE_H


#include "player.h"

class battle {
private:
    // the player... that's you, reader!
    player* m_player;

    // the enemy (existent only in the battle)
    enemy* m_enemy;

public:
    // battle constructor
    explicit battle(player* Player);

    // battle destructor: destroy the enemy
    ~battle() { delete &m_enemy; }

    // battle loop
    void run();
};


#endif //ADVENTURE_BATTLE_H
