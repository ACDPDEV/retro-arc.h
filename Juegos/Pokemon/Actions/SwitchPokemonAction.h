#pragma once

#include "Action.h"

class Pokemon;

class SwitchPokemonAction : public Action
{
    private:

        Pokemon* pokemon;

    public:

        SwitchPokemonAction(Pokemon* pokemon);

        void execute(Match& match) override;
};