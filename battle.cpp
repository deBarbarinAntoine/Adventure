//
// Created by athor on 11/03/2024.
//

#include "battle.h"
#include <iostream>
#include <chrono>
#include <thread>

// battle loop
void battle::run() {
    do {

        // checking the player's turn return (pun not intentional)
        if (!m_player->turn(m_enemy)) {

            // Flee from the battle if the player's turn returns false
            return;
        }
        // exit the loop if the player killed the enemy
        if (m_enemy->isDead()) {
            break;
        }
        // enemy turn
        m_enemy->turn(m_player->getCharacter());

    // until either of the two is dead
    } while (!m_enemy->isDead() && !m_player->isDead());

    // player's win
    if (m_enemy->isDead()) {
        std::cout << "Congratulations, you won!\n";

        // getting the drops
        std::vector<item*> drops = m_enemy->getDrop();
        for (item* it : drops) {
            std::cout << "You retrieved " << it;

            // putting each item in the player's inventory
            m_player->pocketItem(it);
        }
        std::cout << "You gained " << m_enemy->getXp() << " XP\n";

        // retrieve the enemy's worth Xp
        m_player->gainXp(m_enemy->getXp());

        // wait 3 sec to read all information
        std::this_thread::sleep_for(std::chrono::seconds(3));

    // player's loss... GAME OVER...
    } else if (m_player->isDead()) {
        std::cout << "GAME OVER!\n";
    }
}

// creating and setting a new battle
battle::battle(player* Player) {
    m_player = Player;
    m_enemy = new enemy(Player->getLevel(), Player->getEquipmentStats());
    m_enemy->setCharacterStats();
}
