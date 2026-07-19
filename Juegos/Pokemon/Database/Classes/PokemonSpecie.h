#pragma once
#include <string>
#include <vector>
#include "../../Models/Enums/PokemonType.h"
#include "MoveData.h"

namespace PokemonDb {

    class PokemonSpecie 
    {
    private:
        int id;
        std::string name;
        PokemonGame::PokemonType type;

        double baseHp;
        double defense;
        std::vector<PokemonDb::MoveData> poolMoves;

    public:

        PokemonSpecie() 
            : id(0), name(""), type(PokemonGame::PokemonType::NORMAL), 
              baseHp(50.0), defense(3.0) {}

        PokemonSpecie(int id, const std::string& name, PokemonGame::PokemonType type, 
                      double hp, double defense, const std::vector<PokemonDb::MoveData>& moves)
            : id(id), name(name), type(type), baseHp(hp), defense(defense), poolMoves(moves) {}

        int GetId() const { return id; }
        std::string GetName() const { return name; }
        PokemonGame::PokemonType GetType() const { return type; }
        double GetBaseHp() const { return baseHp; }
        double GetDefense() const { return defense; }
        const std::vector<PokemonDb::MoveData>& GetPoolMoves() const { return poolMoves; }
    };
}