#pragma once

#include <string>
#include <vector>

class Move;

enum class PokemonType
{
    Normal,
    Fire,
    Water,
    Grass,
    Electric,
    Rock,
    Ice,
    Psychic,
    Ghost
};

class Pokemon
{
    private:

        std::string name;

        PokemonType type;

        int maxHp;
        int currentHp;

        int attack;
        int defense;
        int speed;

        std::vector<Move*> moves;

    public:

        Pokemon(
            const std::string& name,
            PokemonType type,
            int hp,
            int attack,
            int defense,
            int speed);

        virtual ~Pokemon();

        void receiveDamage(int damage);

        bool isFainted() const;

        void addMove(Move* move);

        Move* getMove(int index);

        PokemonType getType() const;
};