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
    int m_xp;
    int m_level;
    float m_attack;
    float m_defense;
    float m_hp;
    float m_maxHp;
    float m_mana;
    float m_maxMana;
    armor* m_armor = nullptr;
    weapon* m_weapon = nullptr;
    std::vector<item*> m_inventory;
    std::array<skill*, 4> m_skills = {nullptr, nullptr, nullptr, nullptr};

public:
    character() = default;
    ~character();
    void takeDamage(float damage);
    bool isDead() const;
    virtual void levelUp() = 0;
    void hpRegen(float regen);
    void manaRegen(float regen);
    void manaUse(float damage);
    void deleteItem(item* it);
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
    std::vector<equipment*> getEquipment() const;
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
    virtual std::string getClassName() const = 0;
};

std::ostream& operator<<(std::ostream& flux, character* a);


#endif //ADVENTURE_CHARACTER_H
