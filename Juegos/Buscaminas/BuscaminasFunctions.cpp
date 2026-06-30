#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <BuscaminasFunctions.h>

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
 * Crea e inicializa el tablero de estados con puros ceros (todas las celdas ocultas).
 */
vector<vector<int>> CreatePageStateBoard(int rows, int cols) 
{
    vector<vector<int>> stateBoard(rows, vector<int>(cols, 0));
    return stateBoard;
}

/**
 * Procesa la jugada del usuario modificando el tablero de estados.
 * @param stateBoard Referencia al tablero lógico de estados.
 * @param r Fila seleccionada.
 * @param c Columna seleccionada.
 * @param action Tipo de acción (1 = Revelar, 2 = Bandera).
 */
void ExecuteAction(vector<vector<int>>& stateBoard, int r, int c, int action) 
{
    // Validar que las coordenadas estén dentro del tablero
    if (r < 0 || r >= stateBoard.size() || c < 0 || c >= stateBoard[0].size()) {
        cout << "¡Coordenadas fuera de rango! Intenta de nuevo.\n";
        return;
    }

    if (action == 1) { // REVELAR
        if (stateBoard[r][c] == 0) {
            stateBoard[r][c] = 1; // Cambia a estado Revelado
        } else {
            cout << "Esa celda ya no se puede revelar.\n";
        }
    } 
    else if (action == 2) { // BANDERA
        if (stateBoard[r][c] == 0) {
            stateBoard[r][c] = 2; // Pone bandera
        } else if (stateBoard[r][c] == 2) {
            stateBoard[r][c] = 0; // Si ya tenía bandera, la quita (regresa a oculto)
        } else {
            cout << "No puedes poner bandera en una celda revelada.\n";
        }
    }
}


// ======================================================================
// VISTA
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