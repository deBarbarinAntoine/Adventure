//
// Created by athor on 11/03/2024.
//

#pragma once

#ifndef ADVENTURE_ITEM_H
#define ADVENTURE_ITEM_H


#include <string>

// just to say that equipments, skillbooks and potions are items
class item {

protected:
    // name of the thing
    std::string m_name;

public:
    item() = default;
    virtual ~item() = default;

    // to get the thing's name from anywhere
    std::string getName() const { return m_name; }
};


#endif //ADVENTURE_ITEM_H
