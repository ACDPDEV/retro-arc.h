#pragma once

#include <cstdlib>
#include <ctime>

#include "Views/TitleView.h"
#include "Views/InstructionsView.h"
#include "Views/PlayersView.h"
#include "Views/PokemonSelectionView.h"
#include "Views/HuidaView.h"
#include "Views/VictoryView.h"
#include "Database/State.h"
#include "Bridge/PokemonBridge.h"
#include "Controllers/Game.h"
#include "PokemonUI.h"
#include "Sound/PokemonSound.h"
#include "../../Common/Terminal.h"
#include "../../Common/Input.h"

namespace Pokemon {
    /// @brief Entry point for the Pokemon game flow
    /// @details Runs the complete game loop: Title → Menu → (Jugar | Instrucciones | Configuraciones | Volver)
    inline void Pokemon() {
        // Seed the RNG once per process for the generic-attack sound pool (REQ-5.4)
        static bool seeded = false;
        if (!seeded) {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            seeded = true;
        }

        bool isRunning = true;

        while (isRunning) {
            // Title screen with menu selector — returns selected option index
            int selectedOption = TitleView();

            switch (selectedOption) {
                case 0: {
                    // Jugar — full game flow
                    PlayersView();

                    currentSelectionPlayer = 0;
                    PokemonSelectionView();

                    currentSelectionPlayer = 1;
                    PokemonSelectionView();

                    auto players = BuildPlayers();

                    BattleBeginningTitleView();
                    Common::Sleep(500);

                    // Battle intro transition: pokeball launch -> real active Pokemon sprites
                    // -> live battle screen (REQ-3.1/3.2). Split across PokemonUI.h (Piece A,
                    // no while(true), returns) and here (Piece B) to avoid a circular include
                    // between PokemonUI.h and Views/BattleViews.h.
                    int playerActiveId = players.first.GetActivePokemon() ? players.first.GetActivePokemon()->GetId() : 1;
                    int opponentActiveId = players.second.GetActivePokemon() ? players.second.GetActivePokemon()->GetId() : 1;

                    BattleIntroTransitionView(playerActiveId, opponentActiveId);

                    // DrawBattleBackground reads sprite IDs from the battleActivePokemonId1/2
                    // globals (set by Round::Play() each round), not from the Player objects
                    // directly — set them here so the first frame shown before game.Start()
                    // uses the real active Pokemon sprites instead of the 0-default fallback.
                    battleActivePokemonId1 = playerActiveId;
                    battleActivePokemonId2 = opponentActiveId;
                    DrawBattleBackground(players.first, players.second);

                    Common::DrainInput();

                    PokemonGame::Game game;
                    game.Start(players.first, players.second);

                    bool fled = (players.first.GetActivePokemon() && players.first.GetActivePokemon()->IsRunning())
                        || (players.second.GetActivePokemon() && players.second.GetActivePokemon()->IsRunning());

                    std::string winner;
                    if (players.first.GetActivePokemon() && players.first.GetActivePokemon()->IsRunning()) {
                        winner = players.second.GetName();
                    } else if (players.second.GetActivePokemon() && players.second.GetActivePokemon()->IsRunning()) {
                        winner = players.first.GetName();
                    } else if (players.second.GetActivePokemon() && players.second.GetActivePokemon()->IsFainted()) {
                        winner = players.first.GetName();
                    } else if (players.first.GetActivePokemon() && players.first.GetActivePokemon()->IsFainted()) {
                        winner = players.second.GetName();
                    } else {
                        winner = players.first.GetName();
                    }

                    WriteBackState(winner, game.GetLastRoundCount());

                    // Stop battle music before transitioning to result screen
                    StopBattleMusic();

                    if (fled) {
                        HuidaView();
                    } else {
                        VictoryView();
                    }
                    break;
                }
                case 1: {
                    // Instrucciones
                    InstructionsView();
                    break;
                }
                case 2: {
                    // Configuraciones — proximamente
                    Common::Sleep(1000);
                    break;
                }
                case 3: {
                    // Volver
                    isRunning = false;
                    break;
                }
            }
        }
    }
}
