#include "../Common/Sprite.h"
#include "../Common/Color.h"
#include "../Common/Graphics.h"
#include "../Common/Music.h"
#include "rayquaza.h"


using namespace std;

int main() {
    Common::EnableUTF8();
    Common::Clear();
    // for (int i = 0; i < 10; i++) {
    //     Clear();
    //     DrawAnimatedSprite(0, 0, {
    //         RayquazaShiny(),
    //         Rayquaza()
    //     }, 1000);
    // }

    // DrawFillRectangle(0, 0, 60, 20, EMPTY_BLOCK, COLOR_DEFAULT, BACKGROUND);
    // DrawText(8, 7, "Ingresa algo :)", FOREGROUND_DARK, COLOR_DEFAULT);
    // DrawFillRectangle(8, 9, 40, 2, EMPTY_BLOCK, COLOR_DEFAULT, SELECTION_BACKGROUND);

    vector<vector<string>> rayquaza = {
        rayquaza00,
        rayquaza01,
        rayquaza02,
        rayquaza03,
        rayquaza04,
        rayquaza05,
        rayquaza06,
        rayquaza07,
        rayquaza08,
        rayquaza09
    };

    Common::HideCursor();

    Common::Clear();
    Common::SetTerminalColor(Common::COLOR_DEFAULT, {0,0,0});
    Common::PlayAudio("Sound.mp3");
    for (int i = 0;i < 20; i++) {
        Common::DrawFillRectangle(0, 0, 100, 100, Common::EMPTY_BLOCK, Common::COLOR_DEFAULT, {0,0,0});
        Common::DrawSprite(0, 0, rayquaza[i % rayquaza.size()]);
        Common::DrawSprite(57, 0, rayquaza[i % rayquaza.size()]);
        Common::Sleep(200);
    }

    Common::GoToXY(0, 50);
    Common::ShowCursor();
    return 0;
}
