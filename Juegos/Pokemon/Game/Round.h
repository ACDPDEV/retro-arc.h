#pragma once

class Action;

class Round
{
    private:

        Action* playerOneAction;
        Action* playerTwoAction;

    public:

        void execute();
};