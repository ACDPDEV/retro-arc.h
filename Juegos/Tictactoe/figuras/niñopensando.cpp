#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

// gotoxy (si tu graficos.cpp ya la tiene, no la dupliques)
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// convierte cada letra del "mapa" a un color de consola (0-15)
int colorDe(char c) {
    switch (c) {
        case 'C': return 15; // nube blanca
        case 'c': return 8;  // burbujitas grises
        case 'H': return 6;  // pelo (cafe)
        case 'S': return 14; // piel
        case 'E': return 0;  // ojos
        case 'M': return 0;  // boca
        case 'B': return 9;  // camisa
        default:  return 0;  // '.' = transparente (negro)
    }
}

// Funcion que dibuja un nino pensando con una nube, usando el truco
// del caracter de medio bloque (223 = '¯') para lograr el doble
// de resolucion vertical: el color de letra pinta el pixel de
// arriba y el color de fondo pinta el pixel de abajo.
void ninoPensando() {
    int x = 25, y = 5;
    const int W = 20, H = 22;

    string arte[H] = {
        ".........CCC........",
        ".......CCCCCCC......",
        "......CCCCCCCCC.....",
        ".....CCCCCCCCCCC....",
        "......CCCCCCCCC.....",
        ".......CCCCCCCC.....",
        ".......CCCCCCC......",
        "........cC..........",
        ".......cHHH.........",
        ".......HHHHH........",
        "......HHSSSHH.......",
        "......HSSSSSH.......",
        "......SHSSSSS.......",
        "......SESSSES.......",
        "......SSSSSSS.......",
        ".....S.SMMSS........",
        ".....SS.SSS.........",
        "........SS..........",
        ".......BBBBB........",
        ".....BBBBBBBBB......",
        "...BBBBBBBBBBBBB....",
        ".BBBBBBBBBBBBBBBBB.."
    };

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < H; i += 2) {
        gotoxy(x, y + i / 2);
        for (int j = 0; j < W; j++) {
            char arriba = arte[i][j];
            char abajo  = arte[i + 1][j];
            int fg = colorDe(arriba);
            int bg = colorDe(abajo);
            SetConsoleTextAttribute(h, fg | (bg << 4));
            cout << (char)223; // caracter de medio bloque superior
        }
    }

    SetConsoleTextAttribute(h, 7); // vuelve al color normal de consola
}
