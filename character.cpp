//
// Created by athor on 11/03/2024.
//

#include "character.h"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>

// Ouch! It hurts...
void character::takeDamage(float damage) {
    float armorDefense = 0;
    if (m_armor != nullptr) {
        armorDefense = m_armor->getDefense();
    }
    float defense = m_defense + armorDefense;
    damage -= damage * (defense / 100);
    m_hp -= damage;
    std::cout << damage << " damage";
}

// Hey! You there?
bool character::isDead() const {
    return m_hp > 0;
}

// let's take a potion
void character::usePotion(potion* pot) {
    if (pot->isSelfUse()) {
        this->hpRegen(pot->hpModifier());
        this->manaRegen(pot->manaModifier());
        this->deleteItem(pot);
    }
}

// Watch it! This item will disappear...
void character::deleteItem(const item *it) {
    int index = 0;
    for (const item* owned: m_inventory) {
        if (owned == it) {

            // index retrieved successfully!
            break;
        }
        index++;
    }
    m_inventory.erase(m_inventory.begin() + index);
}

// retrieving some health: it's so good!
void character::hpRegen(float regen) {
    m_hp += regen;
    if (m_hp > m_maxHp) {
        m_hp = m_maxHp;
    }
}

// retrieving some mana: I'm beat and exhausted!
void character::manaRegen(float regen) {
    m_mana += regen;
    if (m_mana > m_maxMana) {
        m_mana = m_maxMana;
    }
}

// let's use any potion/poison during the battle!
void character::usePotion(potion *pot, character *adv) {
    if (pot->isSelfUse()) {
        this->usePotion(pot);
    } else {
        adv->takePotionDamage(pot);
        this->deleteItem(pot);
    }
}

// ahahah, take that poison, you dumb monster!
void character::takePotionDamage(potion *pot) {
    if (!pot->isSelfUse()) {
        this->takeDamage(pot->hpModifier());
        this->manaUse(pot->manaModifier());
    }
}

// hey! My mana is disappearing!
void character::manaUse(float amount) {
    m_mana -= amount;
    if (m_mana < 0) {
        m_mana = 0;
    }
}

// let's try that new weapon, okay?
void character::equip(weapon *newWeapon) {
    if (m_weapon != nullptr) {

        //put the current weapon in the inventory (no waste, okay?)
        m_inventory.push_back(m_weapon);
    }
    m_weapon = newWeapon;

    // remove the new weapon from the inventory (no cheat!)
    this->deleteItem(newWeapon);
}

// ohoh! That new armor seems outstanding!
void character::equip(armor *newArmor) {
    if (m_armor != nullptr) {

        //put the current armor in the inventory (no waste, okay?)
        m_inventory.push_back(m_armor);
    }
    m_armor = newArmor;

    // remove the new armor from the inventory (no cheat!)
    this->deleteItem(newArmor);
}

// let's learn some arcane art!
void character::learn(skillbook *newSkill, int index) {
    m_skills[index] = new skill(newSkill);
    this->deleteItem(newSkill);
}

// let's attack with that!
float character::useSkill(skill *attack) {
    if (m_mana >= attack->getManaCost()) {
        this->manaUse(attack->getManaCost());
        return attack->getAttack();
    } else {
        return 0;
    }
}

// skillbooks getter
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

// potions getter
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

//equipment getter
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

// nobody watches... let's take that!
void character::pocketItem(item *it) {
    m_inventory.push_back(it);
}

// hey! Where is he?... Who was it?... Was there someone else here?...
character::~character() {
    delete m_armor;
    delete m_weapon;
    delete &m_inventory;
    delete &m_skills;
}

// is it a poison or can I take it to heal myself?
bool character::isHealthPotion() const {
    std::vector<potion*> potions = this->getPotions();
    return std::any_of(potions.begin(), potions.end(), potion::isHealthPot());
}

// where is my health potion?... Ah, here it is!
potion *character::getHealthPot() {
    if (this->isHealthPotion()) {
        for (potion* pot:this->getPotions()) {
            if (pot->getName() == "health potion") {
                return pot;
            }
        }
    }

    // ooops, there's nothing here
    return nullptr;
}

// watch how talented I am!
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

// here's my weapon and armor: good, right?
void character::printEquipment() {
    std::cout << " - Equipment:\n";
    std::cout << "Type\tName\t\tAttack\tDefense\n";
    std::cout << this->getCurrentWeapon();
    std::cout << this->getCurrentArmor();
}

// let's see what I have looted till now...
std::vector<item *> character::printInventory() {
    std::vector<item*> items;
    int index = 1;

    std::cout << "Inventory:\n";
    std::cout << " - Skillbooks\n";
    std::cout << "Index\tName\t\tMana\tAttack\n";

    // retrieving the skillbooks in order
    std::vector<skillbook*> skillbooks = this->getSortedSkillbooks();
    for (skillbook* skb : skillbooks) {
        std::cout << index << ".\t" << skb;
        index++;
    }
    std::cout << "\n";

    std::cout << " - Equipment\n";
    std::cout << "Index\tType\tName\t\tAttack\tDefense\n";

    // retrieving the equipments in order
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

    // retrieving the potions in order
    std::vector<potion*> potions = this->getSortedPotions();
    for (potion* pot : potions) {
        std::cout << index << ".\t" << pot;
        index++;
    }
    std::cout << index << ".\tReturn\n\n";

    // let's put it all in the bag to return it all in order
    items.insert(std::end(items), std::begin(skillbooks), std::end(skillbooks));
    items.insert(std::end(items), std::begin(equipments), std::end(equipments));
    items.insert(std::end(items), std::begin(potions), std::end(potions));

    return items;
}

// which attack is more powerfull?
bool SkillAttackCompare(skillbook* i, skillbook* j) {
    return i->getAttack() > j->getAttack();
}

// retrieve the skillbooks in order
std::vector<skillbook *> character::getSortedSkillbooks() {
    std::vector<skillbook*> skillbooks = this->getSkillbooks();
    if (skillbooks.empty()) {
        return {};
    }

    // sorting
    std::sort(skillbooks.begin(), skillbooks.end(), SkillAttackCompare);
    std::vector<skillbook*> sortedSkillbooks;

    // mana based attacks
    for (skillbook* skb : skillbooks) {
        if (skb->getManaCost() != 0) {
            sortedSkillbooks.push_back(skb);
        }
    }

    // melee attacks
    for (skillbook* skb : skillbooks) {
        if (skb->getManaCost() == 0) {
            sortedSkillbooks.push_back(skb);
        }
    }

    // return it all in order
    return sortedSkillbooks;
}

// which potion is more effective?
bool PotionEffectCompare(potion* i, potion* j) {
    return i->hpModifier() > j->hpModifier();
}

// retrieve all potions in order
std::vector<potion *> character::getSortedPotions() {
    std::vector<potion*> potions = this->getPotions();
    if (potions.empty()) {
        return {};
    }

    // sorting
    std::sort(potions.begin(), potions.end(), PotionEffectCompare);
    std::vector<potion*> sortedPotions;

    // good potions
    for (potion* pot : potions) {
        if (pot->isSelfUse()) {
            sortedPotions.push_back(pot);
        }
    }

    // poisons: be careful here!
    for (potion* pot : potions) {
        if (!pot->isSelfUse()) {
            sortedPotions.push_back(pot);
        }
    }

    // return it all in order
    return sortedPotions;
}

// which weapon is stronger?
bool WeaponStatCompare(weapon* i, weapon* j) {
    return i->getAttack() > j->getAttack();
}

// which armor is sturdier?
bool ArmorStatCompare(armor* i, armor* j) {
    return i->getDefense() > j->getDefense();
}

// retrieve all equipment in order
std::vector<equipment *> character::getSortedEquipment() {
    std::vector<equipment*> equipments = this->getStoredEquipment();
    std::vector<weapon*> weapons;
    std::vector<armor*> armors;

    // dividing between weapons and armors
    for (equipment* equ : equipments) {
        if (dynamic_cast<weapon*>(equ)) {
            weapons.push_back(dynamic_cast<weapon*>(equ));
        } else {
            armors.push_back(dynamic_cast<armor*>(equ));
        }
    }

    // sorting
    std::sort(weapons.begin(), weapons.end(), WeaponStatCompare);
    std::sort(armors.begin(), armors.end(), ArmorStatCompare);

    std::vector<equipment*> sortedEquipment;

    // put it all together and return it in order: weapons first and then armors
    sortedEquipment.insert(std::end(sortedEquipment), std::begin(weapons), std::end(weapons));
    sortedEquipment.insert(std::end(sortedEquipment), std::begin(armors), std::end(armors));

    return sortedEquipment;
}

// let's use that stuff!
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
            // hey, that's dangerous, you know?
            std::cout << "Impossible to use a poison now!\n";
            return;
        }
    } else {
        return;
    }
}

// learning skill menu (yes, you can only have 4 skills at a time)
void character::learnSkillMenu(skillbook *skb) {
    int choice;
    do {
        this->printSkills();
        std::cout << "5. Quit\n";
        std::cout << "Select a slot: ";

        // checking input
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();

            // clear input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

    // until you choose a valid option
    } while (choice < 1 || choice > 5);
    if (choice == 5) {

        // I changed idea
        return;
    }
    // let's learn that! Hey, I forgot the other one...
    this->learn(skb, choice - 1);
}

// displaying the character's information
std::ostream& operator<<(std::ostream& flux, character* a) {
    flux << std::fixed << std::setprecision(1);
    flux << a->getHp() << "/" << a->getMaxHp() << " HP\n";
    flux << a->getCurrentMana() << "/" << a->getMaxMana() << " Mana\n";
    flux << "Level " << a->getLevel() << "\t" << a->getXp() << "/100\n\n";
    a->printEquipment();
    a->printSkills();
    return flux;
}
