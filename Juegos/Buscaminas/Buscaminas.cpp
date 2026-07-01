#include <iostream>
#include <conio.h>
#include <array>
#include <vector>
#include "Buscaminas.h"
#include "BuscaminasFunctions.h"

using namespace std;

int main()
{
    // ======================================================================
    // CONFIGURACIONES
    // ======================================================================
    int rows = 10;
    int cols = 10;
    int minesQuantity = 8;
    char gameOption = '1';
    bool inGame = true;
    string playerName = "Player 1";
    vector<int> validGameOptions = {12}; // códigos ANSI de las flechas direccionales

    while (inGame)
    {
        cout<<"Seleccione un opción";
        gameOption = getch(); // ---------------------------- USA FUNCION PORTABLE PORQUE SOLO FUNCIONA EN WINDOWS
        while(BuscaminasIsValidOption(gameOption, validGameOptions))
        {
            cout << "Selecciona una opción válida";
            gameOption = getch();
        }


        switch (gameOption)
        {
            // OPCIÓN: JUGAR
            case 1:
            {
                vector<vector<int>> backgroundBoard = CreateBackgroundBoard(rows, cols);
                PlaceMines(backgroundBoard, minesQuantity);
                CountAdjacentMines(backgroundBoard);

                const array<int, 2> initialPosition = GetInitialPosition(rows, cols);
                int playerRow = initialPosition[0];
                int playerCol = initialPosition[1];

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
                break;
            }

            // OPCIÓN: CONFIGURACIONES
            case 2:
                // TODO: CONFIGURAR NOMBRE DEL JUGADOR
                break;

            // OPCIÓN: CRÉDITOS
            case 3:
                // TODO: CRÉDITOS DE BUSCAMINAS
                break;
            
            case 4:
                inGame = false;
                break;
            
            default:
                break;
        }
    }
    
    // ======================================================================
    // CRÉDITOS
    // ======================================================================


    // ======================================================================
    // IN-GAME
    // ======================================================================

    

    return 0;
}