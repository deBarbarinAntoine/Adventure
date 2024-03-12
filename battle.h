//
// Created by athor on 11/03/2024.
//

#pragma once

#ifndef ADVENTURE_BATTLE_H
#define ADVENTURE_BATTLE_H


#include "player.h"

class battle {
private:
    player* m_player;
    enemy* m_enemy;

public:
    explicit battle(player* Player);
    ~battle() { delete &m_enemy; }

    void run();
};


#endif //ADVENTURE_BATTLE_H
