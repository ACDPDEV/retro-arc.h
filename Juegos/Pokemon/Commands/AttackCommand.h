#pragma once

#include "Command.h"

namespace Pokemon
{
    class Move;
    
    class AttackCommand : public Command
    {
        private:
    
            Move* move;
    
        public:
    
            AttackCommand(Move* move);
    
            void execute(Match& match) override;
    };
}