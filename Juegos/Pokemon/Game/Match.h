#pragma once

class Player;

class Match
{
    private:

        Player* playerOne;
        Player* playerTwo;

    public:

        Match(
            Player* playerOne,
            Player* playerTwo);

        void start();

        void nextRound();

        void finish();
};