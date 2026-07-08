#pragma once

namespace PokemonGame
{
    class Action;
    
    class Round
    {
        private:
    
            Action* playerOneAction;
            Action* playerTwoAction;
    
        public:
    
            void execute();
    };
}