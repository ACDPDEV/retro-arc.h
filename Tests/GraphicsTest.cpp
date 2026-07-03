#include "../Common/Sprite.h"
#include "RayquazaShiny.h"
#include "Rayquaza.h"


using namespace std;

int main() {
    EnableUTF8();
    Clear();
    for (int i = 0; i < 10; i++) {
        Clear();
        DrawAnimatedSprite(0, 0, {
            RayquazaShiny(),
            Rayquaza()
        }, 1000);
    }
    GoToXY(0, 50);
    return 0;
}
