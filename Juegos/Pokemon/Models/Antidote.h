#pragma once

#include "Item.h"

class Antidote : public Item
{
public:

    Antidote();

    void use(Pokemon& target) override;
};