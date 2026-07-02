#include <iostream>
#include <conio.h>
#include <array>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "BuscaminasFunctions.h"

using namespace std;

// ======================================================================
// DATABASE
// ======================================================================

/**
 * Crea e inicializa el tablero de fondo con un caracter por defecto.
 * @param rows Número de filas.
 * @param cols Número de columnas.
 * @return Un tablero (Board) inicializado.
 */
vector<vector<int>> CreateBackgroundBoard(int rows, int cols) 
{
    
    vector<vector<int>> board(rows, vector<int>(cols, 0));
    
    return board;
}

/**
 * Ubica una cantidad específica de minas (representadas por el número 9)
 * de manera aleatoria en el tablero de fondo.
 * @param board Referencia al tablero de enteros.
 * @param minesQuantity Cantidad de minas a colocar.
 */
void PlaceMines(vector<vector<int>>& board, int minesQuantity) 
{
    int rows = board.size();
    int cols = board[0].size();
    int placedMines = 0;

    while (placedMines < minesQuantity) {
        int randomRow = rand() % rows;
        int randomCol = rand() % cols;

        if (board[randomRow][randomCol] != 9) {
            board[randomRow][randomCol] = 9;
            placedMines++;
        }
    }
}

/**
 * Recorre el tablero y calcula para cada celda vacía la cantidad de minas (9)
 * que tiene a su alrededor en las 8 direcciones posibles.
 * @param board Referencia al tablero de fondo.
 */
void CountAdjacentMines(vector<vector<int>>& board) 
{
    int rows = board.size();
    int cols = board[0].size();

    // Recorremos cada celda del tablero
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            
            // Si la celda actual es una mina, no necesitamos calcular nada para ella
            if (board[r][c] == 9) {
                continue;
            }

            int mineCount = 0;

            // Escaneamos las 8 celdas de alrededor usando desplazamientos (-1, 0, 1)
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    
                    int neighborRow = r + i;
                    int neighborCol = c + j;

                    // Verificar que el vecino esté dentro de los límites del tablero
                    if (neighborRow >= 0 && neighborRow < rows && neighborCol >= 0 && neighborCol < cols) {

                        if (board[neighborRow][neighborCol] == 9) {
                            mineCount++;
                        }
                    }
                    
                }
            }

            // Guardamos el total de minas encontradas en la celda central
            board[r][c] = mineCount;
        }
    }
}

// ======================================================================
// LOGICA
// ======================================================================
/*
    VALORES DE CADA ESTADO:

        0: Celda oculta (Hidden).

        1: Celda descubierta (Revealed).

        2: Celda con bandera (Flagged).
*/


/**
 * @brief Obtiene la tecla válida presionada por el usuario (flecha, ENTER o ESPACIO)
 * @param feedbackMessage Mensaje de retroalimentación en caso de errores de input
 * @returns el int que representa la tecla presionada por el usuario
 */
int GetUserKey(string& feedbackMessage)
{
    vector<int> validUserKeys = 
    {
        72,   // arriba
        75,   // izquierda
        80,   // abajo
        77,   // derecha
        13,   // Enter
        32    // Espacio
    };
    int userKey;
    userKey = getch(); // ---------------------------- USA FUNCION PORTABLE PORQUE SOLO FUNCIONA EN WINDOWS
    if(userKey == 0 || userKey == 224)
    {
        userKey = getch();
    }
    while(!BuscaminasIsValidOption(userKey, validUserKeys))
    {
        feedbackMessage = "Presiona las flechas y selecciona con ENTER o ESPACIO";
        userKey = getch();
        if(userKey == 0 || userKey == 224)
        {
            userKey = getch();
        }
    }

    return userKey;
}

/**
 * @brief Devuelve la nueva opción seleccionada según la tecla direccional que se presionó
 * @param option El valor previo de la opción
 * @param minOption El mínimo valor que puede tener la opción
 * @param maxOption El máximo valor que puede tener la opción
 * @param userKey la tecla que presionó el usuario
 */
int SetOption(int& option, int minOption, int maxOption, int userKey)
{
    int newOption = option;
    vector<int> validUserKeys = 
    {
        72,   // arriba
        75,   // izquierda
        80,   // abajo
        77,   // derecha
        13,   // Enter
        32    // Espacio
    };

    if(userKey == validUserKeys[0] || userKey == validUserKeys[1])
    {
        if(newOption > minOption)
            --newOption;
        else
            newOption = maxOption;
    }
    if(userKey == validUserKeys[2] || userKey == validUserKeys[3])
    {
        if(newOption < maxOption)
            ++newOption;
        else
            newOption == minOption;
    }

    return newOption;
}

/**
 * @brief Determina si la opción seleccionada se va a ejecutar o no
 * @param userKey Tecla presionada por el usuario
 * @returns true cuando la tecla es ESPACIO o ENTER
 */
bool CanExcecuteOption(int userKey)
{
    bool canExcecuteOption = false;
    vector<int> validUserKeys = 
    {
        72,   // arriba
        75,   // izquierda
        80,   // abajo
        77,   // derecha
        13,   // Enter
        32    // Espacio
    };

    if(userKey == validUserKeys[4] || userKey == validUserKeys[5])
    {
        canExcecuteOption = true;
    }
    return canExcecuteOption;
}

/**
 * @brief valida que la entrada del usuario sea una opción válida
 * @param option la opción ingresada por el usuario
 * @param validOptions el conjunto de opciones válidas para el programa
 */
bool BuscaminasIsValidOption(int option, vector<int>& validOptions)
{
    bool isValid = false;
    for(int i = 0; i < validOptions.size(); i++)
    {
        if(validOptions[i] == option)
        {
            isValid = true;
            break;
        }
    }
    return isValid;
}

/**
 * Crea e inicializa el tablero de estados con puros ceros (todas las celdas ocultas).
 * @param rows cantidad de filas del tablero
 * @param cols cantidad de columnas del tablero
 * @return Un tablero (Board) inicializado.
 */
vector<vector<int>> CreatePageStateBoard(int rows, int cols) 
{
    vector<vector<int>> stateBoard(rows, vector<int>(cols, 0));
    return stateBoard;
}

/**
 * @brief Determina la posicion inicial del jugador.
 * @param rows cantidad de filas del tablero
 * @param cols cantidad de columnas del tablero
 * @return posición inicial {fila, columna}
 */
array<int, 2> GetInitialPosition(int rows, int cols)
{
    array<int, 2> position;
    position[0] = rows / 2;
    position[1] = cols / 2;

    return position;
}

/**
 * @brief Procesa la jugada del usuario modificando el tablero de estados.
 * @param stateBoard Referencia al tablero lógico de estados.
 * @param row Fila seleccionada.
 * @param col Columna seleccionada.
 * @param action Tipo de acción (1 = Revelar, 2 = Bandera).
 */
void ExecuteAction(vector<vector<int>>& stateBoard, int row, int col, int action, string& feedbackMessage) 
{
    // Validar que las coordenadas estén dentro del tablero
    if (row < 0 || row >= stateBoard.size() || col < 0 || col >= stateBoard[0].size()) {
        feedbackMessage = "¡Coordenadas fuera de rango! Intenta de nuevo.\n";
        return;
    }

    if (action == 1) { // REVELAR
        if (stateBoard[row][col] == 0) {
            stateBoard[row][col] = 1; // Cambia a estado Revelado
            feedbackMessage = "";
        } else {
            feedbackMessage = "Esa celda ya no se puede revelar.\n";
        }
    } 
    else if (action == 2) { // BANDERA
        if (stateBoard[row][col] == 0) {
            stateBoard[row][col] = 2; // Pone bandera
            feedbackMessage = "";
        } else if (stateBoard[row][col] == 2) {
            stateBoard[row][col] = 0; // Si ya tenía bandera, la quita (regresa a oculto)
            feedbackMessage = "";
        } else {
            feedbackMessage = "No puedes poner bandera en una celda revelada.\n";
        }
    }
}


// ======================================================================
// VISTA --- 200 x 60
// ======================================================================

/**
 * Imprime el tablero en la consola.
 * @param board Referencia constante al tablero para evitar copias innecesarias.
 */
void DisplayBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << "\n";
    }
}