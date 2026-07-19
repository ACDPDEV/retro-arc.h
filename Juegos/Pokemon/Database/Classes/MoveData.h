#pragma once
#include <string>
#include <vector>
#include "../../Models/Enums/PokemonType.h"

namespace PokemonDb {

    struct MoveData {
        std::string name;
        PokemonGame::PokemonType type;
        double baseDamage;
        double accuracy;
    };
}