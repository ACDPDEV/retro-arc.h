#pragma once

#include "Item.h"

class Potion : public Item
{
private:

    int healPoints;

public:

    Potion(int healPoints);

    void use(Pokemon& target) override;
};