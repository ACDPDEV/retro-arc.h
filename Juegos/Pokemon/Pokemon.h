#pragma once

#include "Views/TitleView.h"
#include "Views/InstructionsView.h"
#include "Views/PlayersView.h"
#include "Views/PokemonSelectionView.h"
#include "Views/HuidaView.h"
#include "Views/MochilaView.h"
#include "Views/VictoryView.h"
#include "Database/State.h"
#include "Bridge/PokemonBridge.h"
#include "Controllers/Game.h"
#include "PokemonUI.h"
#include "../../Common/Terminal.h"

namespace Pokemon {
    /// @brief Entry point for the Pokemon game flow
    /// @details Runs the complete game loop: Title → Menu → (Jugar | Instrucciones | Configuraciones | Volver)
    inline void Pokemon() {
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

                    PokemonGame::Game game;
                    game.Start(players.first, players.second);

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

                    if (!winner.empty()) {
                        VictoryView();
                    } else {
                        HuidaView();
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
