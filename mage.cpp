//
// Created by athor on 11/03/2024.
//

#include "mage.h"

#include <utility>

mage::mage() {
    m_hp = 80;
    m_maxHp = 80;
    m_mana = 120;
    m_maxMana = 120;
    m_attack = 70;
    m_defense = 10;
    m_level = 1;
    m_xp = 0;
    m_inventory.push_back(new skillbook(5, 10));
    m_inventory.push_back(new skillbook(0, 10));
    m_inventory.push_back(new potion("basic health potion", 0, 10, true));
    m_inventory.push_back(new weapon(5, true));
    m_inventory.push_back(new armor(1));
}

void mage::levelUp() {
    while (m_xp >= 100) {
        m_maxHp += 5;
        m_hp = m_maxHp;
        m_maxMana += 10;
        m_mana = m_maxMana;
        m_attack += 5;
        m_defense += .5;
        m_level += 1;
        m_xp -= 100;
    }
}

float mage::useSkill(skill *attack) {
    float damage = character::useSkill(attack);
    if (attack->getManaCost() > 0) {
        damage *= .2;
        if (m_weapon->isMagic()){
            damage += m_weapon->getAttack();
        }
    } else {
        if (!m_weapon->isMagic()) {
            damage += m_weapon->getAttack();
        }
    }
    return damage;
}

mage::mage(int level, armor *Armor, weapon *Weapon, std::vector<item*> inventory) {
    m_xp = 100 * level;
    m_armor = Armor;
    m_weapon = Weapon;
    m_inventory = std::move(inventory);
}
