#pragma once
#include "Command.h"
#include "../Controllers/Battle.h"
#include "../Models/Item.h"
#include "../Models/Player.h"

namespace PokemonGame
{
    class PokemonGame::Item;
    
    class BagCommand : public PokemonGame::Command
    {
        private:
    
            PokemonGame::Item* item;
    
        public:
    
            BagCommand(PokemonGame::Item* item)
                :
                item(item)
            {

            }
    
            void Execute(
                PokemonGame::Player& affectedPlayer) override
            {
                item->Use(affectedPlayer.GetActivePokemon());
                item->RegisterUse();
            }
            
            bool CanExecute(PokemonGame::Player& actor) override
            {
                bool canExecute = true;
                if(!actor.GetBag().HasItemWithId(item->GetId()))
                    canExecute = false;
                else if(!item->CanUse())
                    canExecute = false;

                return canExecute;
            }
    };
}