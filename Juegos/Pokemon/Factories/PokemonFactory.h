#pragma once

#include <memory>
#include "../Models/Pokemon.h"
#include "../Models/Move.h"
#include "../Database/Classes/MoveData.h"
#include "../Database/Classes/PokemonSpecie.h"
#include "../Database/PokemonDatabase.h"

namespace PokemonGame
{
    class PokemonFactory
    {
        public:
            static std::unique_ptr<PokemonGame::Pokemon> Create(int pokemonId)
            {
                // 1. Buscar la especie correspondiente en la base de datos estática global
                const PokemonDb::PokemonSpecie* targetSpecie = nullptr;
                
                for (const auto& specie : PokemonDb::POKEMON_SPECIES_DB)
                {
                    if (specie.GetId() == pokemonId)
                    {
                        targetSpecie = &specie;
                        break;
                    }
                }

                // Si no se encuentra el ID solicitado en la DB, evitamos romper el flujo devolviendo nullptr
                if (targetSpecie == nullptr)
                {
                    return nullptr;
                }

                // 2. Instanciar el objeto Pokémon usando el diseño metodológico de atributos mitigados
                auto newPokemon = std::make_unique<PokemonGame::Pokemon>(
                    targetSpecie->GetId(),
                    targetSpecie->GetName(),
                    targetSpecie->GetType(),
                    targetSpecie->GetBaseHp(),
                    targetSpecie->GetDefense()
                );

                // 3. Poblar dinámicamente el pool de movimientos convirtiendo MoveData en objetos Move*
                int moveIdCounter = 1; // ID local para el índice de selección de comandos en consola
                for (const auto& dbMove : targetSpecie->GetPoolMoves())
                {
                    // Se crean instancias individuales con 'new'. El destructor de Pokemon se encargará de hacer el delete.
                    PokemonGame::Move* moveInstance = new PokemonGame::Move(
                        moveIdCounter++,
                        dbMove.name,
                        dbMove.type,
                        dbMove.baseDamage,
                        dbMove.accuracy
                    );
                    
                    newPokemon->AddMove(moveInstance);
                }

                return newPokemon;
            }
    };
}