#pragma once

#include "Move.h"

class StatusMove : public Move
{
public:

    using Move::Move;

    void execute(
        Pokemon& attacker,
        Pokemon& defender) override;
};