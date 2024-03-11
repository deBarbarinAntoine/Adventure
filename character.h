//
// Created by athor on 11/03/2024.
//

#ifndef ADVENTURE_CHARACTER_H
#define ADVENTURE_CHARACTER_H


#include <vector>
#include <array>
#include "item.h"
#include "weapon.h"
#include "armor.h"
#include "potion.h"
#include "enemy.h"
#include "skill.h"
#include "skillbook.h"

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
    int getLevel() const { return m_level; };
    std::vector<skillbook*> getSkillbooks();
    std::vector<potion*> getPotions();
    std::vector<equipment*> getEquipment();
};


#endif //ADVENTURE_CHARACTER_H
