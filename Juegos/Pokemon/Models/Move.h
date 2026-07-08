#pragma once

#include <string>

class Pokemon;

class Move
{
protected:

    std::string name;

    int baseDamage;

    int accuracy;

public:

    Move(
        const std::string& name,
        int damage,
        int accuracy);

    virtual ~Move() = default;

    virtual void execute(
        Pokemon& attacker,
        Pokemon& defender) = 0;
};