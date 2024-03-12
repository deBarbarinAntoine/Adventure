//
// Created by athor on 11/03/2024.
//

#include "character.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

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
        this->hpRegen(pot->hpModifier());
        this->manaRegen(pot->manaModifier());
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
        this->usePotion(pot);
    } else {
        adv->takePotionDamage(pot);
    }
}

void character::takePotionDamage(potion *pot) {
    if (!pot->isSelfUse()) {
        this->takeDamage(pot->hpModifier());
        this->manaUse(pot->manaModifier());
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
    this->deleteItem(newWeapon);
}

void character::equip(armor *newArmor) {
    if (m_armor != nullptr) {
        m_inventory.push_back(m_armor);
    }
    m_armor = newArmor;
    this->deleteItem(newArmor);
}

void character::learn(skillbook *newSkill, int index) {
    m_skills[index] = new skill(newSkill);
    this->deleteItem(newSkill);
}

float character::useSkill(skill *attack) {
    if (m_mana >= attack->getManaCost()) {
        this->manaUse(attack->getManaCost());
        return attack->getAttack();
    } else {
        return 0;
    }
}

std::vector<skillbook *> character::getSkillbooks() const {
    std::vector<skillbook*> skillbooks;

    // Iterate through the inventory and check for type using dynamic_cast
    for (item* it : m_inventory) {
        skillbook* book = dynamic_cast<skillbook*>(it);
        if (book) {
            skillbooks.push_back(book);
        }
    }

    return skillbooks;
}

std::vector<potion *> character::getPotions() const {
    std::vector<potion*> potions;

    // Iterate through the inventory and check for type using dynamic_cast
    for (item* it : m_inventory) {
        potion* pot = dynamic_cast<potion*>(it);
        if (pot) {
            potions.push_back(pot);
        }
    }

    return potions;
}

std::vector<equipment *> character::getEquipment() const {
    std::vector<equipment*> equipments;

    // Iterate through the inventory and check for type using dynamic_cast
    for (item* it : m_inventory) {
        equipment* eq = dynamic_cast<equipment*>(it);
        if (eq) {
            equipments.push_back(eq);
        }
    }

    return equipments;
}

void character::pocketItem(item *it) {
    m_inventory.push_back(it);
}

character::~character() {
    delete &m_armor;
    delete &m_weapon;
    delete &m_inventory;
    delete &m_skills;
}

bool character::isHealthPotion() const {
    std::vector<potion*> potions = this->getPotions();
    return std::any_of(potions.begin(), potions.end(), potion::isHealthPot());
}

potion *character::getHealthPot() {
    if (this->isHealthPotion()) {
        for (potion* pot:this->getPotions()) {
            if (pot->getName() == "health potion") {
                return pot;
            }
        }
    }
    return nullptr;
}

std::ostream& operator<<(std::ostream& flux, character* a) {
    flux << std::fixed << std::setprecision(1);
    flux << a->getHp() << "/" << a->getMaxHp() << " HP" << std::endl;
    flux << a->getCurrentMana() << "/" << a->getMaxMana() << " Mana\n\n";
    flux << " - Equipment:\n";
    flux << "Type\tName\tAttack/Defense\n";
    flux << a->getCurrentWeapon();
    flux << a->getCurrentArmor();
    std::array<skill*, 4> skills = a->getSkills();
    int index = 1;
    flux << "\n";
    flux << " - Skills:\n";
    flux << "Slot\tName\tMana\tAttack\n";
    for (skill* singleSkill : skills) {
        if (singleSkill != nullptr) {
            flux << index << ".\t" << singleSkill;
        } else {
            flux << index << ".\tEmpty\n";
        }
        index++;
    }
    return flux;
}
