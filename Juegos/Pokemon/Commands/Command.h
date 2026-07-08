#pragma once

class Match;

class Action
{
    public:

        virtual ~Action() = default;

        virtual void execute(Match& match) = 0;
};