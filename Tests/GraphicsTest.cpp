#include "../Common/Sprite.h"
#include "../Common/Color.h"
#include "../Common/Graphics.h"
<<<<<<< HEAD
#include "../Common/Terminal.h"
#include "rayquaza.h"
#include "arceus.h"
=======
#include "../Common/Music.h"
#include "rayquaza.h"
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08


using namespace std;

int main() {
<<<<<<< HEAD
    EnableUTF8();
    Clear();
=======
    Common::EnableUTF8();
    Common::Clear();
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
    // for (int i = 0; i < 10; i++) {
    //     Clear();
    //     DrawAnimatedSprite(0, 0, {
    //         RayquazaShiny(),
    //         Rayquaza()
    //     }, 1000);
    // }

<<<<<<< HEAD
    // DrawFillRectangle(0, 0, 60, 20, EMPTY_BLOCK, COLOR_TRANSPARENT, BACKGROUND);
    // DrawText(8, 7, "Ingresa algo :)", FOREGROUND, COLOR_TRANSPARENT);
    // DrawFillRectangle(8, 9, 40, 2, EMPTY_BLOCK, COLOR_TRANSPARENT, SELECTION_BACKGROUND);
=======
    // DrawFillRectangle(0, 0, 60, 20, EMPTY_BLOCK, COLOR_DEFAULT, BACKGROUND);
    // DrawText(8, 7, "Ingresa algo :)", FOREGROUND_DARK, COLOR_DEFAULT);
    // DrawFillRectangle(8, 9, 40, 2, EMPTY_BLOCK, COLOR_DEFAULT, SELECTION_BACKGROUND);
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

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

<<<<<<< HEAD
    HideCursor();

    Clear();
    SetTerminalColor(COLOR_TRANSPARENT, {0,0,0});
    for (int i = 0;i < 20; i++) {
        DrawFillRectangle(0, 0, 100, 100, EMPTY_BLOCK, COLOR_TRANSPARENT, {0,0,0});
        DrawSprite(0, 0, rayquaza[i % rayquaza.size()]);
        DrawSprite(57, 0, rayquaza[i % rayquaza.size()]);
        Sleep(200);
    }

    GoToXY(0, 50);
    ShowCursor();
=======
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
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
    return 0;
}
