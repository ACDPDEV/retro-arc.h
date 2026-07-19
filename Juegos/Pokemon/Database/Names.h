#pragma once

#include <string>

namespace Pokemon {
    // Player names are set dynamically via Common::playerName
    // Default value: "Player 1" (defined in Common/Variables.h)
    // No hardcoded names needed here — the system reads Common::playerName directly.
    inline std::string player1Name = "Cuack";
    inline std::string player2Name = "Renzo";
}
