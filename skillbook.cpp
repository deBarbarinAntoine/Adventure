//
// Created by athor on 11/03/2024.
//

#include "skillbook.h"
#include <iomanip>
#include <iostream>

// skillbook constructor/generator
skillbook::skillbook(float manaCost, float attack) {

    // magic skills
    if (manaCost > 0) {
        if (attack < 20) {
            m_name = "magic bullet";
        } else if (attack < 30) {
            m_name = "earth fist";
        } else if (attack < 40) {
            m_name = "wind slash";
        } else if (attack < 50) {
            m_name = "fireball";
        } else if (attack < 60) {
            m_name = "thunder strike";
        } else if (attack < 70) {
            m_name = "magma pillar";
        } else if (attack < 80) {
            m_name = "dark spear";
        } else if (attack < 90) {
            m_name = "dark storm";
        } else {
            m_name = "pluri-elemental storm";
        }

    // melee skills
    } else {
        if (attack < 20) {
            m_name = "basic strike";
        } else if (attack < 30) {
            m_name = "charged strike";
        } else if (attack < 40) {
            m_name = "slash";
        } else if (attack < 50) {
            m_name = "heavy slash";
        } else if (attack < 60) {
            m_name = "thrust";
        } else if (attack < 70) {
            m_name = "charged thrust";
        } else if (attack < 80) {
            m_name = "light combo";
        } else if (attack < 90) {
            m_name = "aggressive combo";
        } else {
            m_name = "charged combo";
        }
    }
    m_manaCost = manaCost;
    m_attack = attack;
}

// displaying the skillbook's information
std::ostream& operator<<(std::ostream& flux, skillbook* a) {
    flux << std::fixed << std::setprecision(1);
    flux << a->getName() << "\t" << a->getManaCost() << "\t" << a->getAttack() << "\n";
    return flux;
}
