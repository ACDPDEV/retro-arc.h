/// @file PokemonLogicTest.cpp
/// @brief Assertion-based unit tests for pure-logic fixes in the Pokemon stabilization
///        batch (Phase 2, tasks 2.1/2.5/2.6; Phase 4, tasks 4.4/4.5). Deliberately avoids
///        any Common/Terminal, Common/Graphics or other TUI dependency so it can run
///        headlessly in CI/CLI.
/// @details Follows the project's AddTest/result/pass framework convention
///          (see Tests/InputTest.cpp) — exit code 0 if all tests pass, 1 otherwise.
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../Juegos/Pokemon/Commands/RunCommand.h"
#include "../Juegos/Pokemon/Commands/AttackCommand.h"
#include "../Juegos/Pokemon/Models/Move.h"
#include "../Juegos/Pokemon/Models/Player.h"
#include "../Juegos/Pokemon/Models/Pokemon.h"
#include "../Juegos/Pokemon/Models/Enums/PokemonType.h"
#include "../Juegos/Pokemon/Controllers/PlayerController.h"
#include "../Juegos/Pokemon/Database/PokemonDatabase.h"
#include "../Juegos/Pokemon/Database/MockData.h"

using namespace std;

vector<string> testNames;
vector<bool> testResults;
bool passed = true;

void AddTest(string name, bool result) {
    testNames.push_back(name);
    testResults.push_back(result);
    if (!result) passed = false;
}

/// @brief REQ-2.1: RunCommand::CanExecute must return true when the active Pokemon
///        is NOT fainted, and false when it IS fainted (inverted-boolean regression test)
void RunCommandTest() {
    PokemonGame::Player aliveTrainer("Ash");
    auto alivePokemon = std::make_shared<PokemonGame::Pokemon>(
        1, "Pikachu", PokemonGame::PokemonType::ELECTRICO, 35.0, 5.0);
    aliveTrainer.AddPokemon(alivePokemon);

    PokemonGame::Player faintedTrainer("Misty");
    auto faintedPokemon = std::make_shared<PokemonGame::Pokemon>(
        2, "Psyduck", PokemonGame::PokemonType::AGUA, 30.0, 5.0);
    faintedTrainer.AddPokemon(faintedPokemon);
    faintedPokemon->ReceiveDamage(9999.0); // bring HP to 0 -> IsFainted() == true

    PokemonGame::RunCommand runCommand;

    AddTest("RunCommand::CanExecute true si el Pokemon activo NO esta debilitado",
        runCommand.CanExecute(aliveTrainer) == true);

    AddTest("RunCommand::CanExecute false si el Pokemon activo esta debilitado",
        runCommand.CanExecute(faintedTrainer) == false);
}

/// @brief REQ-2.5: Move()'s default constructor must initialize all members deterministically
void MoveDefaultsTest() {
    PokemonGame::Move move;

    AddTest("Move() por defecto: id == 0", move.GetId() == 0);
    AddTest("Move() por defecto: type == PokemonType::NORMAL",
        move.GetType() == PokemonGame::PokemonType::NORMAL);
    AddTest("Move() por defecto: baseDamage == 0.0", move.GetBaseDamage() == 0.0);
    AddTest("Move() por defecto: HasName() == false (name se auto-inicializa vacio)",
        move.HasName() == false);
}

/// @brief REQ-2.6: Player::CanPlay() must not dereference a null active Pokemon
void PlayerCanPlayNullSafetyTest() {
    PokemonGame::Player emptyTrainer("SinEquipo");
    // No pokemon added -> activePokemon stays nullptr internally.
    bool didNotCrash = true;
    bool result = false;
    try {
        result = emptyTrainer.CanPlay();
    } catch (...) {
        didNotCrash = false;
    }

    AddTest("Player::CanPlay() no crashea sin Pokemon activo", didNotCrash);
    AddTest("Player::CanPlay() retorna false sin Pokemon activo", result == false);
}

/// @brief REQ-2.6: AttackCommand::Execute must not dereference a null defender active Pokemon
void AttackCommandNullSafetyTest() {
    PokemonGame::Move move(1, "Impactrueno", PokemonGame::PokemonType::ELECTRICO, 20.0, 100.0);
    PokemonGame::AttackCommand attackCommand(&move);

    PokemonGame::Player emptyDefender("SinPokemon");
    bool didNotCrash = true;
    try {
        attackCommand.Execute(emptyDefender);
    } catch (...) {
        didNotCrash = false;
    }

    AddTest("AttackCommand::Execute no crashea sin Pokemon activo del defensor", didNotCrash);
}

/// @brief REQ-4.4: named healing-item id constants must keep the values Round.h's
///        BAG branch and PlayerController::FillBag already rely on (3=Potion, 4=Super Potion)
void HealingItemIdConstantsTest() {
    AddTest("PlayerController::ITEM_ID_POTION == 3",
        PokemonGame::PlayerController::ITEM_ID_POTION == 3);
    AddTest("PlayerController::ITEM_ID_SUPER_POTION == 4",
        PokemonGame::PlayerController::ITEM_ID_SUPER_POTION == 4);
}

/// @brief REQ-4.5: MOCK_POKEMON's hp/maxHp must be derived from and match
///        PokemonDb::POKEMON_SPECIES_DB's baseHp for all 8 mock entries, via the shared
///        Pokemon::MockToDbId mapping.
void MockPokemonMatchesDatabaseTest() {
    bool allMatch = true;
    for (int i = 0; i < Pokemon::POKEMON_COUNT; ++i) {
        int dbId = Pokemon::MockToDbId(i);
        int expectedHp = static_cast<int>(PokemonDb::POKEMON_SPECIES_DB[dbId - 1].GetBaseHp());
        if (Pokemon::MOCK_POKEMON[i].hp != expectedHp || Pokemon::MOCK_POKEMON[i].maxHp != expectedHp) {
            allMatch = false;
        }
    }
    AddTest("MOCK_POKEMON[i].hp/maxHp coinciden con PokemonDb::POKEMON_SPECIES_DB para los 8 Pokemon", allMatch);
}

int main() {
    RunCommandTest();
    MoveDefaultsTest();
    PlayerCanPlayNullSafetyTest();
    AttackCommandNullSafetyTest();
    HealingItemIdConstantsTest();
    MockPokemonMatchesDatabaseTest();

    cout << endl;
    if (passed) cout << "Todos los tests pasaron." << endl << endl;
    else cout << "Algunos tests fallaron." << endl << endl;

    for (size_t i = 0; i < testResults.size(); ++i) {
        cout << (testResults[i] ? "[PASS] " : "[FAIL] ") << testNames[i] << endl;
    }

    int passedCount = 0;
    for (size_t i = 0; i < testResults.size(); ++i) if (testResults[i]) passedCount++;
    cout << endl << "Tests que pasaron: " << passedCount << "/" << testResults.size() << endl;

    return passed ? 0 : 1;
}
