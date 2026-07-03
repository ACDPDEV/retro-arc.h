#include "../Common/Graphics.h"
#include "../Common/Sprite.h"
#include "RayquazaShiny.h"

using namespace std;

int main() {
    EnableUTF8();
    Clear();
    DrawSprite(0, 0, RayquazaShiny());
    GoToXY(0, 50);
    return 0;
}
