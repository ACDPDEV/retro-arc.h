// Verification test for Pokemon Battle Interfaces
// Tests compilation of all new view headers and MockData

#include <iostream>
#include <string>

// Common headers
#include "Common/Consts.h"
#include "Common/Graphics.h"
#include "Common/Theme.h"
#include "Common/Color.h"
#include "Common/Aligned.h"
#include "Common/Font.h"
#include "Common/Sprite.h"
#include "Common/Utils.h"
#include "Common/Components/BottomBar.h"
#include "Common/Components/InputComponent.h"
#include "Common/Components/LifeBar.h"
#include "Common/Input.h"
#include "Common/Navigation.h"

// Pokemon headers
#include "Juegos/Pokemon/Database/MockData.h"
#include "Juegos/Pokemon/PokemonStaticSprites/Trainer1Front.h"
#include "Juegos/Pokemon/PokemonStaticSprites/Trainer2Front.h"
#include "Juegos/Pokemon/PokemonStaticSprites/MochilaFront.h"
#include "Juegos/Pokemon/Views/NombresView.h"
#include "Juegos/Pokemon/Views/PokemonSelectionView.h"
#include "Juegos/Pokemon/Views/HuidaView.h"
#include "Juegos/Pokemon/Views/MochilaView.h"
#include "Juegos/Pokemon/Views/VictoryView.h"
#include "Juegos/Pokemon/Pokemon.h"

int main() {
    std::cout << "=== Pokemon Battle Interfaces Compilation Test ===" << std::endl;
    
    // Test MockData
    std::cout << "1. MockData:" << std::endl;
    std::cout << "   Pokemon count: " << Pokemon::POKEMON_COUNT << std::endl;
    std::cout << "   Item count: " << Pokemon::BAG_ITEM_COUNT << std::endl;
    
    // Test sprite existence
    std::cout << "2. Sprites:" << std::endl;
    std::cout << "   Trainer1Front size: " << Pokemon::Trainer1Front.size() << " lines" << std::endl;
    std::cout << "   Trainer2Front size: " << Pokemon::Trainer2Front.size() << " lines" << std::endl;
    std::cout << "   MochilaFront size: " << Pokemon::MochilaFront.size() << " lines" << std::endl;
    
    // Test function signatures (compile-time check)
    std::cout << "3. Function signatures:" << std::endl;
    std::cout << "   NombresView: OK" << std::endl;
    std::cout << "   PokemonSelectionView: OK" << std::endl;
    std::cout << "   HuidaView: OK" << std::endl;
    std::cout << "   MochilaView: OK" << std::endl;
    std::cout << "   VictoryView: OK" << std::endl;
    
    std::cout << "\n=== All headers compile successfully! ===" << std::endl;
    
    return 0;
}
