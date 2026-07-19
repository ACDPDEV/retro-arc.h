#include <iostream>
#include <vector>
#include "../Common/Font.h"

using namespace std;

int main() {
    for (int i = 0; i < 9; i++) {
        cout << ConcatFont({FONT9_R, FONT9_E, FONT9_T, FONT9_R, FONT9_O, FONT9_A, FONT9_R, FONT9_C, FONT9_DOT, FONT9_H}, 2)[i] << endl;
    }
    for (int i = 0; i < 200; i++) {
        cout << "a";
    }
    return 0;
}
