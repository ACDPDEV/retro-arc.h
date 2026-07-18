#include <iostream>
#include "../Common/Color.h"
#include "../Common/UnicodeGlyphs.h"
using namespace std;

int main() {
    //10 pasos, comenzando en verde y acabando en rojo
    vector<array<int, 3>> colors = Common::Gradient(100, {10, 67, 120}, {127, 0, 25});

    for (int i = 0; i < colors.size(); i++) {
    cout << Common::Color(colors[i], {-1,-1,-1}) << "\u2588"; //█
    }

cout << Common::ResetColor();
    return 0;
}