#pragma once

#include "Command.h"

class RunCommand : public Command
{
    public:

        void execute(Match& match) override;
};