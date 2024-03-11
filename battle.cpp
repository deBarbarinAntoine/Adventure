//
// Created by athor on 11/03/2024.
//

#include <iostream>
#include "battle.h"

void battle::run() {

}

battle::battle(player* Player) {
    m_player = Player;
    m_enemy = new enemy(Player->getLevel(), Player->getEquipmentStats());
}
