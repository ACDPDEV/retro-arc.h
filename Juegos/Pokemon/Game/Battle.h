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
    
            void Start();

            void Play();
    
            void NextRound();
    
            void Finish();
    };
}