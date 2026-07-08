#pragma once

#include "Command.h"

class RunAction : public Action
{
    public:

        void execute(Match& match) override;
};