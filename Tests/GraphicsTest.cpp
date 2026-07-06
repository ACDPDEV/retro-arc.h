#include "../Common/Sprite.h"
#include "../Common/Color.h"
#include "../Common/Graphics.h"
#include "../Common/Music.h"
#include "../Common/Terminal.h"
#include "rayquaza.h"
#include "arceus.h"


using namespace std;

int main() {
    EnableUTF8();
    Clear();
    // for (int i = 0; i < 10; i++) {
    //     Clear();
    //     DrawAnimatedSprite(0, 0, {
    //         RayquazaShiny(),
    //         Rayquaza()
    //     }, 1000);
    // }

    // DrawFillRectangle(0, 0, 60, 20, EMPTY_BLOCK, COLOR_TRANSPARENT, BACKGROUND);
    // DrawText(8, 7, "Ingresa algo :)", FOREGROUND, COLOR_TRANSPARENT);
    // DrawFillRectangle(8, 9, 40, 2, EMPTY_BLOCK, COLOR_TRANSPARENT, SELECTION_BACKGROUND);

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

    HideCursor();

    Clear();
    SetTerminalColor(COLOR_TRANSPARENT, {0,0,0});
    PlayAudio("Sound.mp3");
    for (int i = 0;i < 20; i++) {
        DrawFillRectangle(0, 0, 100, 100, EMPTY_BLOCK, COLOR_TRANSPARENT, {0,0,0});
        DrawSprite(0, 0, rayquaza[i % rayquaza.size()]);
        DrawSprite(57, 0, rayquaza[i % rayquaza.size()]);
        Sleep(200);
    }

    GoToXY(0, 50);
    ShowCursor();
    return 0;
}
