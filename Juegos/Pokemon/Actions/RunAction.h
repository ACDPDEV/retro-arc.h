#pragma once

#include "Action.h"

class RunAction : public Action
{
    public:

        void execute(Match& match) override;
};