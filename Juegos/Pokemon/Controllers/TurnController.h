#pragma once

#include <string>
#include <memory>
#include <vector>
#include "../Models/Player.h"
#include "../Models/Bag.h"
#include "../Models/Item.h"
#include "../Models/Pokemon.h"
#include "../Enums/ChooseCommandOption.h"
#include "../Commands/Command.h"
#include "../Commands/AttackCommand.h"
#include "../Commands/SwitchPokemonCommand.h"
#include "../Commands/BagCommand.h"

namespace PokemonGame
{
    
    class TurnController
    {
        private:
            PokemonGame::Player& player;
    
        public:
    
            TurnController(PokemonGame::Player& player)
                :player(player)
            {
            }

            std::unique_ptr<PokemonGame::Command> ChooseCommand(PokemonGame::ChooseCommandOption option, int entityId)
            {
                switch (option)
                {
                    case PokemonGame::ChooseCommandOption::FIGHT:
                    {
                        if (!player.GetActivePokemon())
                            return nullptr;

                        PokemonGame::Move* move = player.GetActivePokemon()->GetMoveById(entityId);
                        return std::make_unique<PokemonGame::AttackCommand>(move);

                        break;
                    }

                    case PokemonGame::ChooseCommandOption::BAG:
                    {
                        PokemonGame::Item* item = player.GetBag().GetItemById(entityId);
                        return std::make_unique<PokemonGame::BagCommand>(item);

                        break;
                    }

                    case PokemonGame::ChooseCommandOption::POKEMON:
                    {
                        PokemonGame::Pokemon* selectedPokemon = player.GetPokemonById(entityId);
                        return std::make_unique<PokemonGame::SwitchPokemonCommand>(selectedPokemon);

                        break;
                    }

                    default:
                    {
                        return nullptr;
                    }
                }
            }
    
            ~TurnController() = default;

            PokemonGame::Player& GetPlayer()
            {
                return player;
            }


            bool HasLost()
            {
                return !player.CanPlay() || player.IsTeamDefeated();
            }

    };
}