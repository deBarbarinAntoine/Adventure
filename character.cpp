//
// Created by athor on 11/03/2024.
//

#include "character.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>

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

std::vector<equipment *> character::getStoredEquipment() const {
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

void character::printSkills() {
    std::array<skill*, 4> skills = this->getSkills();
    int index = 1;
    std::cout << "\n";
    std::cout << " - Skills:\n";
    std::cout << "Slot\tName\t\tMana\tAttack\n";
    for (skill* singleSkill : skills) {
        if (singleSkill != nullptr) {
            std::cout << index << ".\t" << singleSkill;
        } else {
            std::cout << index << ".\tEmpty\n";
        }
        index++;
    }
}

void character::printEquipment() {
    std::cout << " - Equipment:\n";
    std::cout << "Type\tName\t\tAttack\tDefense\n";
    std::cout << this->getCurrentWeapon();
    std::cout << this->getCurrentArmor();
}

std::vector<item *> character::printInventory() {
    std::vector<item*> items;
    int index = 1;
    std::cout << "Inventory:\n";
    std::cout << " - Skillbooks\n";
    std::cout << "Index\tName\t\tMana\tAttack\n";
    std::vector<skillbook*> skillbooks = this->getSortedSkillbooks();
    for (skillbook* skb : skillbooks) {
        std::cout << index << ".\t" << skb;
        index++;
    }
    std::cout << "\n";
    std::cout << " - Equipment\n";
    std::cout << "Index\tType\tName\t\tAttack\tDefense\n";
    std::vector<equipment*> equipments = this->getSortedEquipment();
    for (equipment* equ : equipments) {
        if (dynamic_cast<weapon*>(equ)) {
            std::cout << index << ".\t" << dynamic_cast<weapon*>(equ);
        } else {
            std::cout << index << ".\t" << dynamic_cast<armor*>(equ);
        }
        index++;
    }
    std::cout << "\n";
    std::cout << " - Potions\n";
    std::cout << "Index\tName\t\tMana\tHP\tType\n";
    std::vector<potion*> potions = this->getSortedPotions();
    for (potion* pot : potions) {
        std::cout << index << ".\t" << pot;
        index++;
    }
    std::cout << index << ".\tReturn\n\n";

    items.insert(std::end(items), std::begin(skillbooks), std::end(skillbooks));
    items.insert(std::end(items), std::begin(equipments), std::end(equipments));
    items.insert(std::end(items), std::begin(potions), std::end(potions));

    return items;
}

bool SkillAttackCompare(skillbook* i, skillbook* j) {
    return i->getAttack() > j->getAttack();
}

std::vector<skillbook *> character::getSortedSkillbooks() {
    std::vector<skillbook*> skillbooks = this->getSkillbooks();
    if (skillbooks.size() == 0) {
        return {};
    }
    std::sort(skillbooks.begin(), skillbooks.end(), SkillAttackCompare);
    std::vector<skillbook*> sortedSkillbooks;
    for (skillbook* skb : skillbooks) {
        if (skb->getManaCost() != 0) {
            sortedSkillbooks.push_back(skb);
        }
    }
    for (skillbook* skb : skillbooks) {
        if (skb->getManaCost() == 0) {
            sortedSkillbooks.push_back(skb);
        }
    }
    return sortedSkillbooks;
}

bool PotionEffectCompare(potion* i, potion* j) {
    return i->hpModifier() > j->hpModifier();
}

std::vector<potion *> character::getSortedPotions() {
    std::vector<potion*> potions = this->getPotions();
    if (potions.size() == 0) {
        return {};
    }
    std::sort(potions.begin(), potions.end(), PotionEffectCompare);
    std::vector<potion*> sortedPotions;
    for (potion* pot : potions) {
        if (pot->isSelfUse()) {
            sortedPotions.push_back(pot);
        }
    }
    for (potion* pot : potions) {
        if (!pot->isSelfUse()) {
            sortedPotions.push_back(pot);
        }
    }
    return sortedPotions;
}

bool WeaponStatCompare(weapon* i, weapon* j) {
    return i->getAttack() > j->getAttack();
}

bool ArmorStatCompare(armor* i, armor* j) {
    return i->getDefense() > j->getDefense();
}

std::vector<equipment *> character::getSortedEquipment() {
    std::vector<equipment*> equipments = this->getStoredEquipment();
    std::vector<weapon*> weapons;
    std::vector<armor*> armors;
    for (equipment* equ : equipments) {
        if (dynamic_cast<weapon*>(equ)) {
            weapons.push_back(dynamic_cast<weapon*>(equ));
        } else {
            armors.push_back(dynamic_cast<armor*>(equ));
        }
    }
    std::sort(weapons.begin(), weapons.end(), WeaponStatCompare);
    std::sort(armors.begin(), armors.end(), ArmorStatCompare);
    std::vector<equipment*> sortedEquipment;
    sortedEquipment.insert(std::end(sortedEquipment), std::begin(weapons), std::end(weapons));
    sortedEquipment.insert(std::end(sortedEquipment), std::begin(armors), std::end(armors));
    return sortedEquipment;
}

void character::useItem(item *it) {
    if (dynamic_cast<skillbook*>(it)) {
        this->learnSkillMenu(dynamic_cast<skillbook*>(it));
    } else if (dynamic_cast<weapon*>(it)) {
        this->equip(dynamic_cast<weapon*>(it));
    } else if (dynamic_cast<armor*>(it)) {
        this->equip(dynamic_cast<armor*>(it));
    } else if (dynamic_cast<potion*>(it)) {
        if (dynamic_cast<potion*>(it)->isSelfUse()) {
            this->usePotion(dynamic_cast<potion*>(it));
        } else {
            std::cout << "Impossible to use a poison now!\n";
            return;
        }
    } else {
        return;
    }
}

void character::learnSkillMenu(skillbook *skb) {
    int choice;
    do {
        this->printSkills();
        std::cout << "5. Quit\n";
        std::cout << "Select a slot: ";
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            // clear input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice < 1 || choice > 5);
    if (choice == 5) {
        return;
    }
    this->learn(skb, choice - 1);
}

std::ostream& operator<<(std::ostream& flux, character* a) {
    flux << std::fixed << std::setprecision(1);
    flux << a->getHp() << "/" << a->getMaxHp() << " HP\n";
    flux << a->getCurrentMana() << "/" << a->getMaxMana() << " Mana\n\n";
    a->printEquipment();
    a->printSkills();
    return flux;
}
