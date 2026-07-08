#pragma once

#include "Command.h"

class Item;

class BagCommand : public Command
{
    private:

        Item* item;

    public:

        BagCommand(Item* item);

        void execute(Match& match) override;
};