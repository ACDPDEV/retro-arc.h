#pragma once
#include "Command.h"
#include "../Models/Item.h"
#include "../Models/Player.h"

namespace PokemonGame
{
    
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
                if (!affectedPlayer.GetActivePokemon()) return;

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