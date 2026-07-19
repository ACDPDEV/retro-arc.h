#pragma once

#include "Views/TitleView.h"
#include "Views/MenuView.h"
#include "Views/PlayersView.h"
#include "Views/PokemonSelectionView.h"
#include "Views/HuidaView.h"
#include "Views/MochilaView.h"
#include "Views/VictoryView.h"
#include "Database/State.h"
#include "../../Common/Terminal.h"

namespace Pokemon {
    inline void Pokemon() {
        // 1. Title and Menu
        TitleView();
        Sleep(1000);
        MenuView();

        // 2. Player name input
        PlayersView();

        // 3. Pokemon selection — Player 1
        currentSelectionPlayer = 0;
        PokemonSelectionView();

        // 4. Pokemon selection — Player 2
        currentSelectionPlayer = 1;
        PokemonSelectionView();

        // 5. Placeholder: Battle would go here
        // For now, show a placeholder with dummy values
        currentPokemonName = "Pikachu";
        currentRound = 1;
        winnerName = playerNames[0];

        // 6. Show Victory or Huida (placeholder)
        HuidaView();
    }
}
