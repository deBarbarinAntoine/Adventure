//
// Created by athor on 11/03/2024.
//

#ifndef ADVENTURE_BATTLE_H
#define ADVENTURE_BATTLE_H


#include "player.h"
#include "enemy.h"

class battle {
private:
    player* m_player;
    enemy* m_enemy;

public:
    explicit battle(player* Player);
    void run();
};


#endif //ADVENTURE_BATTLE_H
