#include "game.h"
#include "Views/TictactoeUI.h"
#include "../../Common/Components/BottomBar.h"
#include <ctime>
#include <cstdlib>

namespace Tictactoe
{
    /// @brief Lógica principal del juego (menú + bucle)
    void Run()
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        Common::EnableUTF8();

        while (true)
        {
            int opcion = DrawMenuScreen();

            if (opcion == 0)
            {
                DrawTransition();
                do
                {
                    Common::Clear();
                    Common::DrawBackground();
                    jugarOriginal();
                } while (jugarNuevamente());
            }
            else if (opcion == 1)
            {
                DrawTransition();
                do
                {
                    Common::Clear();
                    Common::DrawBackground();
                    jugarFutbol();
                } while (jugarNuevamente());
            }
            else if (opcion == 2)
            {
                Common::Clear();
                Common::DrawBackground();
                DrawInstructions(false);
            }
            else
            {
                break;
            }
        }

        Common::ShowCursor();
    }
}

/// @brief Punto de entrada del programa
int main()
{
    Common::InitTerminalRawMode();
    Tictactoe::Run();
    return 0;
}
