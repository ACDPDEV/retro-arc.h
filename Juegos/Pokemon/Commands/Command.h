#pragma once

class Match;

namespace PokemonGame
{
    class Command
    {
        public:
    
            virtual ~Command() = default;
    
            virtual void execute(Match& match) = 0;
    };
}