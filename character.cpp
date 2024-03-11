//
// Created by athor on 11/03/2024.
//

#include "character.h"

void character::takeDamage(float damage) {
    float defense = m_defense + m_armor->getDefense();
    damage -= damage * (defense / 100);
    m_hp -= damage;
}

bool character::isDead() const {
    return m_hp > 0;
}

void character::usePotion(potion* pot) {
    if (pot->isSelfUse()) {
        character::hpRegen(pot->hpModifier());
        character::manaRegen(pot->manaModifier());
    }
}

void character::deleteItem(item *it) {
    int index = 0;
    for (item*& owned: m_inventory) {
        if (owned == it) {
            break;
        }
        index++;
    }
    m_inventory.erase(m_inventory.begin() + index);
    delete &it;
}

void character::hpRegen(float regen) {
    m_hp += regen;
    if (m_hp > m_maxHp) {
        m_hp = m_maxHp;
    }
}

void character::manaRegen(float regen) {
    m_mana += regen;
    if (m_mana > m_maxMana) {
        m_mana = m_maxMana;
    }
}

void character::usePotion(potion *pot, character *adv) {
    if (pot->isSelfUse()) {
        character::usePotion(pot);
    } else {
        adv->takePotionDamage(pot);
    }
}

void character::takePotionDamage(potion *pot) {
    if (!pot->isSelfUse()) {
        character::takeDamage(pot->hpModifier());
        character::manaUse(pot->manaModifier());
    }
}

void character::manaUse(float damage) {
    m_mana -= damage;
    if (m_mana < 0) {
        m_mana = 0;
    }
}

void character::equip(weapon *newWeapon) {
    if (m_weapon != nullptr) {
        m_inventory.push_back(m_weapon);
    }
    m_weapon = newWeapon;
    character::deleteItem(newWeapon);
}

void character::equip(armor *newArmor) {
    if (m_armor != nullptr) {
        m_inventory.push_back(m_armor);
    }
    m_armor = newArmor;
    character::deleteItem(newArmor);
}

void character::learn(skillbook *newSkill, int index) {
    m_skills[index] = new skill(newSkill);
    character::deleteItem(newSkill);
}

float character::useSkill(skill *attack) {
    if (m_mana >= attack->getManaCost()) {
        character::manaUse(attack->getManaCost());
        return attack->getAttack();
    } else {
        return 0;
    }
}
