//
// Created by athor on 11/03/2024.
//

#include <iostream>
#include "battle.h"

// battle loop
void battle::run() {
    do {
    m_player->turn();
    if (m_enemy->isDead()) {
        break;
    }
    m_enemy->turn();
 } while (!m_enemy->isDead() && !m_player->isDead());
    if (m_enemy->isDead()) {
        m_enemy->getDrop();
        m_player->gainXp(m_enemy->getXp());
    } else if (m_player->isDead()) {
        std::cout << "GAME OVER!\n";
    }
}

// creating a new battle
battle::battle(player* Player) {
    m_player = Player;
    m_enemy = new enemy(Player->getLevel(), Player->getEquipmentStats());
    m_enemy->setCharacterStats();
}
