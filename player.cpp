//
// Created by athor on 11/03/2024.
//

#include "player.h"
#include "mage.h"
#include "warrior.h"

player::player(std::string name, int type) {
    m_name = std::move(name);
    switch (type) {
        case 0: // mage
            m_character = new mage();
            break;
        case 1: // warrior
            m_character = new warrior();
            break;
        default: // unknown -> create a mage anyway...
            m_character = new mage();
            break;
    }

}

void player::turn() {

}

void player::menu() {

}
