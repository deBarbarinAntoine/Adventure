//
// Created by athor on 11/03/2024.
//

#include "warrior.h"

warrior::warrior() {
    m_hp = 100;
    m_maxHp = 100;
    m_mana = 80;
    m_maxMana = 80;
    m_attack = 100;
    m_defense = 15;
    m_level = 1;
    m_xp = 0;
}

void warrior::levelUp() {
    while (m_xp >= 100) {
        m_maxHp += 10;
        m_hp = m_maxHp;
        m_maxMana += 5;
        m_mana = m_maxMana;
        m_attack += 10;
        m_defense += 1;
        m_level += 1;
        m_xp -= 100;
    }
}

float warrior::useSkill(skill *attack) {
    float damage = character::useSkill(attack);
    if (attack->getManaCost() == 0) {
        damage *= .2;
        if (!m_weapon->isMagic()){
            damage += m_weapon->getAttack();
        }
    } else {
        if (m_weapon->isMagic()){
            damage += m_weapon->getAttack();
        }
    }
    return damage;
}
