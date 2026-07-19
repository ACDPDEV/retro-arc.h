#include "../Juegos/Pokemon/Views/TitleView.h"
#include "../Juegos/Pokemon/Views/NombresView.h"
#include "../Juegos/Pokemon/Views/MochilaView.h"
#include "../Juegos/Pokemon/Views/PokemonSelectionView.h"
#include "../Juegos/Pokemon/Views/VictoryView.h"
#include "../Juegos/Pokemon/Views/HuidaView.h"
#include "../Juegos/Pokemon/Components/TitleComponent.h"



#include "../Common/Terminal.h"

int main() {
    Common::InitTerminalRawMode();

    // Pokemon::TitleComponent();
    // Pokemon::TitleView();
    // Common::Sleep(2000);
    std::string player1Name = "";
    std::string player2Name = "";
    // Pokemon::NombresView(player1Name, player2Name);
    // Common::Sleep(2000);
    // Pokemon::MochilaView();
    // Common::Sleep(2000);
    int selectedPokemon = 0;
    // Pokemon::PokemonSelectionView(selectedPokemon);
    Common::Sleep(2000);
    Pokemon::VictoryView(player1Name, selectedPokemon, 1);
    // Common::Sleep(2000);
    // Pokemon::HuidaView(player1Name, "Psyduck", 1);
    // Common::Sleep(2000);

    return 0;
}
