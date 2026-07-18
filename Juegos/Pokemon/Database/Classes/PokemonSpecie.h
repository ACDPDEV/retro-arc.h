#pragma once

#include <string>
#include "../../Models/Enums/PokemonType.h"

namespace PokemonGame
{
    class PokemonSpecies
    {
    private:

        const int id;
        const std::string name;
        const PokemonGame::PokemonType type;
        const double maxHp;
        const double defense;

    public:

        PokemonSpecies(
            const int id,
            const std::string& name,
            const PokemonGame::PokemonType type,
            const double maxHp,
            const double defense)
            :
            id(id),
            name(name),
            type(type),
            maxHp(maxHp),
            defense(defense)
        {
        }

        ~PokemonSpecies() = default;

        int GetId() const
        {
            return id;
        }

        const std::string& GetName() const
        {
            return name;
        }

        PokemonGame::PokemonType GetType() const
        {
            return type;
        }

        double GetMaxHp() const
        {
            return maxHp;
        }

        double GetDefense() const
        {
            return defense;
        }
    };
}