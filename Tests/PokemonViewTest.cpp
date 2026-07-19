#include "../Juegos/Pokemon/Views/TitleView.h"
#include "../Juegos/Pokemon/Views/PlayersView.h"
#include "../Juegos/Pokemon/Views/MochilaView.h"
#include "../Juegos/Pokemon/Views/PokemonSelectionView.h"
#include "../Juegos/Pokemon/Views/VictoryView.h"
#include "../Juegos/Pokemon/Views/HuidaView.h"
#include "../Juegos/Pokemon/Components/TitleComponent.h"
#include "../Juegos/Pokemon/Database/State.h"



#include "../Common/Terminal.h"

int main() {
    Common::InitTerminalRawMode();

    // Pokemon::TitleComponent();
    // Pokemon::TitleView();
    // Common::Sleep(2000);
    Pokemon::PlayersView();
    // Common::Sleep(2000);
    // Pokemon::MochilaView();
    // Common::Sleep(2000);
    Pokemon::PokemonSelectionView();
    // Common::Sleep(2000);
    // Pokemon::VictoryView();
    // Common::Sleep(2000);
    // Pokemon::HuidaView();
    // Common::Sleep(2000);

    return 0;
}
