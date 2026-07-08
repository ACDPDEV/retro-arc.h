#pragma once

#include "Move.h"

class SpecialMove : public Move
{
public:

    using Move::Move;

    void execute(
        Pokemon& attacker,
        Pokemon& defender) override;
};