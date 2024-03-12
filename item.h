//
// Created by athor on 11/03/2024.
//

#pragma once

#ifndef ADVENTURE_ITEM_H
#define ADVENTURE_ITEM_H


#include <string>

class item {

protected:
    std::string m_name;

public:
    item() = default;
    virtual ~item() = default;
    std::string getName() const { return m_name; }
};


#endif //ADVENTURE_ITEM_H
