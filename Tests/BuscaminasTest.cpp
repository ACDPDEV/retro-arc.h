// Quick test — Buscaminas UI refactor verification
// Compila solo Buscaminas sin tocar Pokemon ni MainMenu
#include <iostream>
#include "../Juegos/Buscaminas/Buscaminas.h"

int main() {
    std::cout << "=== Buscaminas UI Test ===" << std::endl;
    std::cout << "Compilacion OK. Iniciando juego..." << std::endl << std::endl;

    Common::InitTerminalRawMode();
    Buscaminas::PlayMinesweeper();

    return 0;
}
