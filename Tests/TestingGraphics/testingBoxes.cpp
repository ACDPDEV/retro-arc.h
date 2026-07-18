#include <iostream>
#include "../../Common/Color.h"
#include "../../Common/Graphics.h"
#include "../../Common/Music.h"
#include "../../Common/Terminal.h"
#include "../../Common/Aligned.h"
#include "../../Common/Components/BottomBar.h"
#include "../../Juegos/Pokemon/PokemonUI.h"
using namespace std;

void PrintPrimaryBox(int x, int y, int width, int height, string text, array<int, 3> textColor, array<int, 3> borderColor, array<int, 3> fillColor);

int main()
{
    // BLANCO {255,255,255}
    // CREMA {255, 236,153}
    /* PrintPrimaryBox(30, 10, 36, 3, "", {255, 236, 153}, {255, 255, 255}, {255, 236, 153});
    Common::DrawBottomBar(); */
    Pokemon::BattleBeginningTitleView();
    Common::Sleep(2000);
    Pokemon::BattleBeginningAnimationView();
    Common::Sleep(2000);
    /* Pokemon::BattleOptionsView(14, "PSYDUCK",  "ROCKRUFF", "PSYDUCK");
    Common::Sleep(2000);
    Pokemon::BattleOptionsFightView(14, "PSYDUCK",  "ROCKRUFF", "PSYDUCK");
    Common::Sleep(2000);
    Pokemon::BattleOptionsFightAttackedView(14, "PSYDUCK",  "ROCKRUFF", "PSYDUCK");
    Common::Sleep(2000);
    Pokemon::BattleOptionsFightEffectivenessView(14, "PSYDUCK",  "ROCKRUFF", "PSYDUCK");
    Common::Sleep(2000);
    Pokemon::BattleOptionsFightFaintedView(14, "PSYDUCK",  "ROCKRUFF", "PSYDUCK"); */
    Common::Sleep(2000);
    return 0;
}

void PrintPrimaryBox(int x, int y, int width, int height, string text, array<int, 3> textColor, array<int, 3> borderColor, array<int, 3> fillColor)
{
    const int textX = Common::AlignedX(x, width, text.length(), "center");
    const int textY = Common::AlignedY(y, height, 1, "center");

    Common::DrawFillRectangle(x, y - 1, width, 1, Common::LOWER_HALF_BLOCK, borderColor, {-1, -1, -1}); // borde superior
    Common::DrawFillRectangle(x, y + height, width, 1, Common::UPPER_HALF_BLOCK, borderColor, {-1, -1, -1}); // borde inferior
    Common::DrawFillRectangle(x, y, width, height, Common::FULL_BLOCK, borderColor, {-1, -1, -1}); // bordes de los costados
    Common::DrawFillRectangle(x + 1, y, width - 2, height, Common::FULL_BLOCK, fillColor, {-1, -1, -1}); // relleno del recuadro

    Common::DrawText(
        textX, textY,
        width, height,
        {text},
        textColor, fillColor);

    cout << "\033[H";
}