cmake_minimum_required(VERSION 3.27)
project(Adventure)

set(CMAKE_CXX_STANDARD 20)

add_executable(Adventure main.cpp
        battle.cpp
        battle.h
        player.cpp
        player.h
        enemy.cpp
        enemy.h
        character.cpp
        character.h
        mage.cpp
        mage.h
        warrior.cpp
        warrior.h
        item.cpp
        item.h
        equipment.cpp
        equipment.h
        weapon.cpp
        weapon.h
        armor.cpp
        armor.h
        potion.cpp
        potion.h
        skillbook.cpp
        skillbook.h
        skill.cpp
        skill.h
        menu.cpp
        menu.h)
