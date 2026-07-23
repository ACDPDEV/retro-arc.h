/// @file PokemonLogicTest.cpp
/// @brief Assertion-based unit tests for pure-logic fixes in the Pokemon stabilization
///        batch (Phase 2, tasks 2.1/2.5/2.6; Phase 4, tasks 4.4/4.5). Deliberately avoids
///        any Common/Terminal, Common/Graphics or other TUI dependency so it can run
///        headlessly in CI/CLI.
/// @details Uses Common/Test.h macros (TEST, ASSERT_TRUE, ASSERT_EQ, TEST_RUNNER).
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Common/Test.h"
#include "Juegos/Pokemon/Commands/AttackCommand.h"
#include "Juegos/Pokemon/Models/Move.h"
#include "Juegos/Pokemon/Models/Player.h"
#include "Juegos/Pokemon/Models/Pokemon.h"
#include "Juegos/Pokemon/Models/Enums/PokemonType.h"
#include "Juegos/Pokemon/Controllers/PlayerController.h"
#include "Juegos/Pokemon/Database/PokemonDatabase.h"
#include "Juegos/Pokemon/Database/MockData.h"

using namespace std;

/// @brief REQ-2.5: Move()'s default constructor must initialize all members deterministically
TEST(MoveDefaultsTest) {
    PokemonGame::Move move;

    ASSERT_EQ(move.GetId(), 0);
    ASSERT_EQ(move.GetType(), PokemonGame::PokemonType::NORMAL);
    ASSERT_EQ(move.GetBaseDamage(), 0.0);
    ASSERT_TRUE(move.HasName() == false);
}

/// @brief REQ-2.6: Player::CanPlay() must not dereference a null active Pokemon
TEST(PlayerCanPlayNullSafetyTest) {
    PokemonGame::Player emptyTrainer("SinEquipo");
    // No pokemon added -> activePokemon stays nullptr internally.
    bool didNotCrash = true;
    bool result = false;
    try {
        result = emptyTrainer.CanPlay();
    } catch (...) {
        didNotCrash = false;
    }

    ASSERT_TRUE(didNotCrash);
    ASSERT_TRUE(result == false);
}

/// @brief REQ-2.6: AttackCommand::Execute must not dereference a null defender active Pokemon
TEST(AttackCommandNullSafetyTest) {
    PokemonGame::Move move(1, "Impactrueno", PokemonGame::PokemonType::ELECTRICO, 20.0, 100.0);
    PokemonGame::AttackCommand attackCommand(&move);

    PokemonGame::Player emptyDefender("SinPokemon");
    bool didNotCrash = true;
    try {
        attackCommand.Execute(emptyDefender);
    } catch (...) {
        didNotCrash = false;
    }

    ASSERT_TRUE(didNotCrash);
}

/// @brief REQ-4.4: named healing-item id constants must keep the values Round.h's
///        BAG branch and PlayerController::FillBag already rely on (3=Potion, 4=Super Potion)
TEST(HealingItemIdConstantsTest) {
    ASSERT_EQ(PokemonGame::PlayerController::ITEM_ID_POTION, 3);
    ASSERT_EQ(PokemonGame::PlayerController::ITEM_ID_SUPER_POTION, 4);
}

/// @brief REQ-4.5: MOCK_POKEMON's hp/maxHp must be derived from and match
///        PokemonDb::POKEMON_SPECIES_DB's baseHp for all 8 mock entries, via the shared
///        Pokemon::MockToDbId mapping.
TEST(MockPokemonMatchesDatabaseTest) {
    bool allMatch = true;
    for (int i = 0; i < Pokemon::POKEMON_COUNT; ++i) {
        int dbId = Pokemon::MockToDbId(i);
        int expectedHp = static_cast<int>(PokemonDb::POKEMON_SPECIES_DB[dbId - 1].GetBaseHp());
        if (Pokemon::MOCK_POKEMON[i].hp != expectedHp || Pokemon::MOCK_POKEMON[i].maxHp != expectedHp) {
            allMatch = false;
        }
    }
    ASSERT_TRUE(allMatch);
}

TEST_RUNNER()
