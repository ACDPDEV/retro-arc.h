#pragma once
#include <iostream>
#include <vector>
#include <Buscaminas.h>
#include <BuscaminasFunctions.h>

using namespace std;

int main()
{
    const int rows = 10;
    const int cols = 10;
    const int minesQuantity = 8;

    vector<vector<int>> backgroundBoard = CreateBackgroundBoard(rows, cols);
    PlaceMines(backgroundBoard, minesQuantity);
    CountAdjacentMines(backgroundBoard);
    
    int playerRow = 0;
    int playerCol = 0;

    vector<vector<int>> playerStateBoard = CreatePageStateBoard(rows, cols);
    char input;
    bool gameOver = false;

    while (!gameOver)
    {
        // 1. Mostrar el tablero con la posición actual del cursor
        // DisplayGame(backgroundBoard, playerStateBoard, playerRow, playerCol);   <<<<<<<<<<<<<<<< EVALUAR ESTA FUNCÓN <<<<<<<<<<<<<<<<<<<

        // 2. Pedir la acción
        cout << "Moverse: (W/A/S/D) | Revelar: (X) | Bandera: (F) | Salir: (Q): ";
        cin >> input;

        // 3. Procesar la entrada con un switch básico
        switch (input)
        {
        case 'w':
        case 'W':
            if (playerRow > 0)
                playerRow--; // Sube
            break;
        case 's':
        case 'S':
            if (playerRow < rows - 1)
                playerRow++; // Baja
            break;
        case 'a':
        case 'A':
            if (playerCol > 0)
                playerCol--; // Izquierda
            break;
        case 'd':
        case 'D':
            if (playerCol < cols - 1)
                playerCol++; // Derecha
            break;
        case 'x':
        case 'X':
            // El jugador decide revelar la celda donde está parado
            ExecuteAction(playerStateBoard, playerRow, playerCol, 1);

            // TODO : si bgBoard[playerRow][playerCol] == 9 -> gameOver = true;
            break;
        case 'f':
        case 'F':
            // El jugador decide poner/quitar bandera donde está parado
            ExecuteAction(playerStateBoard, playerRow, playerCol, 2);
            break;
        case 'q':
        case 'Q':
            gameOver = true;
            break;
        }
    }

    return 0;
}