#pragma once

#include <string>

class Pokemon;

class Item
{
protected:

    std::string name;

public:

    Item(const std::string& name);

    virtual ~Item() = default;

    virtual void use(Pokemon& target) = 0;
};