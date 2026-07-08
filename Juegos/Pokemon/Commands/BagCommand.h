#pragma once

#include "Command.h"

class Item;

class BagAction : public Action
{
    private:

        Item* item;

    public:

        BagAction(Item* item);

        void execute(Match& match) override;
};