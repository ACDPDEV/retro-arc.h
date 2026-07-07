#include <iostream>
#include <vector>
#include "../Common/Font.h"

using namespace std;

int main() {
    for (int i = 0; i < 9; i++) {
        cout << ConcatFont({FONT_R, FONT_E, FONT_T, FONT_R, FONT_O, FONT_A, FONT_R, FONT_C, FONT_DOT, FONT_H}, 2)[i] << endl;
    }
    for (int i = 0; i < 200; i++) {
        cout << "a";
    }
    return 0;
}
