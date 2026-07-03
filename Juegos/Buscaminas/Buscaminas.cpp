#include <iostream>
#include <conio.h>
#include <array>
#include <vector>
#include <algorithm>
#include "Buscaminas.h"
#include "BuscaminasFunctions.h"

using namespace std;

string feedbackMessage = "";

int main()
{
    // ======================================================================
    // CONFIGURACIONES
    // ======================================================================

    int rows = 10;
    int cols = 10;
    int minesQuantity = 8;
    
    const int minGameOption = 0;
    const int maxGameOption = 3;
    int gameOption = minGameOption;

    bool inGame = true;
    string playerName = "Player 1";

    // TODO encontrar los códigos que obtiene getch al presionar las teclas arriba, izquierda, abajo, derecha
    const vector<int> validUserKeys = 
    {
        72,   // arriba
        75,   // izquierda
        80,   // abajo
        77,   // derecha
        13,   // Enter
        32    // Espacio
    };

    int userKey;

    while (inGame)
    {
        /*

        MOSTRAR PANTALLA CON LAS OPCIONES Y TÍTULO. DEBE INCLUIR LA VARIABLE feebbackMessage

        */
        cout<<"Seleccione un opción";
        userKey = GetUserKey(feedbackMessage);

        // Determina movimiento de las flechas direccionales
        gameOption = SetOption(gameOption, minGameOption, maxGameOption, userKey);

        // ejecuta la acción solo si se presiona la tecla enter o espacio
        if(CanExcecuteOption(userKey))
        {

            switch (gameOption)
            {
                // OPCIÓN: JUGAR
                case 0:
                {
                    // SELECCIONAR NIVEL
                    /* TODO

                    PANTALLA PARA SELECCIONAR NIVEL

                    */

                    const int minLevelOption = 0;
                    const int maxLevelOption = 2;
                    int levelOption = minLevelOption;

                    do{
                        userKey = GetUserKey(feedbackMessage);
                        levelOption = SetOption(levelOption, minLevelOption, maxLevelOption, userKey);
                    }
                    while(!CanExcecuteOption(userKey));

                    rows = SetRowsByLevel(levelOption);
                    cols = SetColsByLevel(levelOption);
                    minesQuantity = SetMinesQuantity(rows, cols, levelOption);

                    vector<vector<int>> backgroundBoard = CreateBackgroundBoard(rows, cols);
                    PlaceMines(backgroundBoard, minesQuantity);
                    CountAdjacentMines(backgroundBoard);
    
                    const array<int, 2> initialPosition = GetInitialPosition(rows, cols);
                    int playerRow = initialPosition[0];
                    int playerCol = initialPosition[1];
    
                    vector<vector<int>> playerStateBoard = CreatePageStateBoard(rows, cols);
                    char actionKey;
                    bool gameOver = false;
                    bool wonGame = false;
    
                    while (!gameOver)
                    {
                        feedbackMessage = "Moverse: (W/A/S/D) | Revelar: (R) | Bandera: (B) | Salir: (Q): ";
                        // 1. Mostrar el tablero con la posición actual del cursor
                        // DisplayGame(backgroundBoard, playerStateBoard, playerRow, playerCol);   <<<<<<<<<<<<<<<< EVALUAR ESTA FUNCÓN <<<<<<<<<<<<<<<<<<<
    
                        // 2. Pedir la acción
                        actionKey = getch();
    
                        // 3. Procesar la entrada con un switch básico
                        switch (actionKey)
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
                        case 'r':
                        case 'R':
                            // El jugador decide revelar la celda donde está parado
                            ExecuteAction(playerStateBoard, playerRow, playerCol, 1, feedbackMessage);
    
                            // TODO : si bgBoard[playerRow][playerCol] == 9 -> gameOver = true;
                            break;
                        case 'b':
                        case 'B':
                            // El jugador decide poner/quitar bandera donde está parado
                            ExecuteAction(playerStateBoard, playerRow, playerCol, 2, feedbackMessage);
                            break;
                        case 'q':
                        case 'Q':
                            gameOver = true;
                            break;
                        }

                        // TODO validar si cumple con la condición para ganar
                        wonGame = IsWonGameState();
                        if(wonGame)
                            gameOver = true;
                    }

                    if(actionKey != 'q' || actionKey != 'Q')
                    {
                        // TODO mostrar la pantalla de victoria o resultado

                    }
                    break;
                }
    
                // OPCIÓN: CONFIGURACIONES
                case 1:
                    // TODO: CONFIGURAR NOMBRE DEL JUGADOR
                    break;
    
                // OPCIÓN: CRÉDITOS
                case 2:
                    // TODO: CRÉDITOS DE BUSCAMINAS
                    break;
                
        
                // OPCIÓN: SALIR
                case 3:
                    inGame = false;
                    break;
                
                default:
                    break;
            }
        }
        
        

    }
    

    return 0;
}