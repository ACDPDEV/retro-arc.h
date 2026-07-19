#pragma once

#include "Views/TitleView.h"
#include "Views/MenuView.h"
#include "Views/PlayersView.h"
#include "Views/PokemonSelectionView.h"
#include "Views/HuidaView.h"
#include "Views/MochilaView.h"
#include "Views/VictoryView.h"

namespace Pokemon {
    inline void Pokemon() {
        TitleView();
        MenuView();
    }
}
