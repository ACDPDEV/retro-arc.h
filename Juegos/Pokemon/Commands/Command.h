#pragma once

class Match;

class Command
{
    public:

        virtual ~Command() = default;

        virtual void execute(Match& match) = 0;
};