//
// Created by athor on 11/03/2024.
//

#pragma once

#ifndef ADVENTURE_CHARACTER_H
#define ADVENTURE_CHARACTER_H


#include "weapon.h"
#include "armor.h"
#include "potion.h"
#include "skill.h"
#include <vector>
#include <array>

class character {

protected:

    // experience points (to level-up)
    int m_xp;

    // level
    int m_level;

    // attack power
    float m_attack;

    // defense (percentage of damage ignored)
    float m_defense;

    // health points
    float m_hp;

    // max health points
    float m_maxHp;

    // mana ...that's magic!
    float m_mana;

    // max mana points
    float m_maxMana;

    // armor (equipped): some more defense here
    armor* m_armor = nullptr;

    // weapon (equipped): some more attack here
    weapon* m_weapon = nullptr;

    // inventory
    std::vector<item*> m_inventory;

    // skills (only 4, I know it's not much... it remembers me of Pokémon, though)
    std::array<skill*, 4> m_skills = {nullptr, nullptr, nullptr, nullptr};

public:
    character() = default;
    virtual ~character();
    void takeDamage(float damage);
    bool isDead() const;
    virtual void levelUp() = 0;
    void hpRegen(float regen);
    void manaRegen(float regen);
    void manaUse(float amount);
    void deleteItem(const item *it);
    void usePotion(potion* pot);
    void usePotion(potion* pot, character* adv);
    void takePotionDamage(potion* pot);
    void equip(weapon* newWeapon);
    void equip(armor* newArmor);
    void learn(skillbook* newSkill, int index);
    virtual float useSkill(skill* attack); // returns 0 if not enough mana!
    int getLevel() const { return m_level; }
    std::vector<skillbook*> getSkillbooks() const;
    std::vector<potion*> getPotions() const;
    std::vector<equipment*> getStoredEquipment() const;
    void pocketItem(item* it);
    float getEquipmentStats() const { return m_weapon->getAttack() + m_armor->getDefense(); }
    void gainXp(int xp) { m_xp += xp; }
    std::vector<equipment*> getCurrentEquipment() const { return std::vector<equipment*>{m_weapon, m_armor}; }
    armor* getCurrentArmor() const { return m_armor; }
    weapon* getCurrentWeapon() const { return m_weapon; }
    float getHp() const { return m_hp; }
    bool isHealthPotion() const;
    potion* getHealthPot();
    std::array<skill*, 4> getSkills() const { return m_skills; }
    float getCurrentMana() const { return m_mana; }
    float getMaxHp() const { return m_maxHp; }
    float getMaxMana() const { return m_maxMana; }
    int getXp() const { return m_xp; }
    virtual std::string getClassName() const = 0;
    void printSkills();
    void printEquipment();
    std::vector<item *> printInventory();
    std::vector<skillbook*> getSortedSkillbooks();
    std::vector<potion*> getSortedPotions();
    std::vector<equipment*> getSortedEquipment();
    void useItem(item *it);
    void learnSkillMenu(skillbook* skb);
    void rest();
};

std::ostream& operator<<(std::ostream& flux, character* a);


#endif //ADVENTURE_CHARACTER_H
