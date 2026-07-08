#pragma once

#include "Action.h"

namespace Pokemon
{
    class Move;
    
    class AttackAction : public Action
    {
        private:
    
            Move* move;
    
        public:
    
            AttackAction(Move* move);
    
            void execute(Match& match) override;
    };
}