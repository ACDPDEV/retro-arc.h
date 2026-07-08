#pragma once

#include "Command.h"

class Pokemon;

class SwitchPokemonCommand : public Command
{
    private:

        Pokemon* pokemon;

    public:

        SwitchPokemonCommand(Pokemon* pokemon);

        void execute(Match& match) override;
};