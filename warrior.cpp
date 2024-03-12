//
// Created by athor on 11/03/2024.
//

#include "warrior.h"
#include <utility>

// the birth of a warrior!...
warrior::warrior() {
    m_hp = 100;
    m_maxHp = 100;
    m_mana = 80;
    m_maxMana = 80;
    m_attack = 100;
    m_defense = 15;
    m_level = 1;
    m_xp = 0;
    m_inventory.push_back(new skillbook(5, 10));
    m_inventory.push_back(new skillbook(0, 10));
    m_inventory.push_back(new potion("health potion", 0, 15, true));
    m_inventory.push_back(new weapon(5, false));
    m_inventory.push_back(new armor(1));
}

// let's level-up! Yaaayyy!
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
        m_inventory.push_back(new skillbook(0, 10));
        m_inventory.push_back(new skillbook(5, 10));
        m_inventory.push_back(new potion("health potion", 0, 15, true));
        m_inventory.push_back(new weapon(5, false));
        m_inventory.push_back(new armor(1));
    }
}

// let's use that skill: physical damage is the best!
float warrior::useSkill(skill *attack) {
    float damage = character::useSkill(attack);
    if (attack->getManaCost() == 0) {
        damage *= 1.1;
        if (!m_weapon->isMagic()){
            damage += m_weapon->getAttack();
        } else {
            damage += m_weapon->getAttack() / 10;
        }
    } else {
        if (m_weapon->isMagic()){
            damage += m_weapon->getAttack();
        }
    }
    return damage;
}

// a warrior constructor (for enemies only, right?)
warrior::warrior(int level, armor *Armor, weapon *Weapon, std::vector<item*> inventory) {
    m_xp = 100 * level;
    m_armor = Armor;
    m_weapon = Weapon;
    m_inventory = std::move(inventory);
}
