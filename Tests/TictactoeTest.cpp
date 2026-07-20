// Quick test — TicTacToe header-only restructuring verification
// Compila TicTacToe sin tocar otros juegos
#include <iostream>
#include "../Juegos/Tictactoe/Tictactoe.h"

int main() {
    std::cout << "=== TicTacToe UI Test ===" << std::endl;
    std::cout << "Compilacion OK. Iniciando juego..." << std::endl << std::endl;

    Common::InitTerminalRawMode();
    Tictactoe::PlayTicTacToe();

    return 0;
}
