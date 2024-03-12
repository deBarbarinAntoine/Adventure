//
// Created by athor on 11/03/2024.
//

#include "weapon.h"
#include <iomanip>
#include <iostream>

weapon::weapon(float attack, bool isMagic) {
    if (attack < 10) {
        if (isMagic) {
            m_name = "wooden wand";
        } else {
            m_name = "wooden club";
        }
    } else if (attack < 15) {
        if (isMagic) {
            m_name = "iron wand";
        } else {
            m_name = "iron dagger";
        }
    } else if (attack < 20) {
        if (isMagic) {
            m_name = "steel staff";
        } else {
            m_name = "steel spear";
        }
    } else if (attack < 25) {
        if (isMagic) {
            m_name = "ornate steel staff";
        } else {
            m_name = "ornate steel sword";
        }
    } else if (attack < 30) {
        if (isMagic) {
            m_name = "titanium staff";
        } else {
            m_name = "titanium halberd";
        }
    } else if (attack < 35) {
        if (isMagic) {
            m_name = "refined titanium staff";
        } else {
            m_name = "refined titanium rapier";
        }
    } else if (attack < 40) {
        if (isMagic) {
            m_name = "orichalcum orb";
        } else {
            m_name = "orichalcum sword";
        }
    } else {
        if (isMagic) {
            m_name = "mithril orb";
        } else {
            m_name = "mithril greatsword";
        }
    }
    m_attack = attack;
    m_isMagic = isMagic;
}

std::ostream& operator<<(std::ostream& flux, weapon* a) {
    flux << std::fixed << std::setprecision(1);
    flux << "Weapon\t";
    if (a == nullptr) {
        flux << "Empty\n";
    } else {
        std::string magic;

        if (a->isMagic()) {
            magic = "\tmagic";
        }
        flux << a->getName() << "\t" << a->getAttack() << "\t\t" << magic << "\n";
    }
    return flux;
}
