#pragma once

namespace PokemonGame
{
    class Player;
    
    class Battle
    {
        private:
    
            Player* playerOne;
            Player* playerTwo;
    
        public:
    
            Battle(
                Player* playerOne,
                Player* playerTwo);
    
            void start();
    
            void nextRound();
    
            void finish();
    };
}